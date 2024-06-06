#include "tt/net/packer.h"

#include <google/protobuf/message.h>

namespace net {

std::string serialize(const MessageData &message_data) {
    std::string result;
    uint32_t tmp = htonl(message_data.length);
    result.reserve(message_data.length);
    result.append(reinterpret_cast<char *>(&tmp), k_UINT32_SIZE);
    tmp = htonl(message_data.type_name_length);
    result.append(reinterpret_cast<char *>(&tmp), k_UINT32_SIZE);
    result.append(message_data.type_name.c_str(), message_data.type_name_length);
    result.append(message_data.message.c_str(), message_data.message.size());
    return result;
}

std::string pack_message(const google::protobuf::Message &message) {
    MessageData message_data{};
    const std::string &type_name = message.GetTypeName();
    message_data.type_name_length = static_cast<uint32_t>(type_name.size());
    message_data.type_name = type_name;
    message.SerializeToString(&message_data.message);
    message_data.length =
        static_cast<uint32_t>(2 * sizeof(uint32_t) + message_data.type_name_length + message_data.message.size());
    return serialize(message_data);
}

bool deserialize(const std::string &input, MessageData &message_data) noexcept {
    if (input.size() < 2 * k_UINT32_SIZE) {
        return false; // 输入的字符串太短，无法包含 length 和 type_name_length
    }
    const char *data = input.data();
    size_t offset = 0;

    message_data.length = extract_uint32(data, offset);
    if (message_data.length > input.size()) {
        return false; // length 大于输入的字符串的长度，这是不可能的
    }

    message_data.type_name_length = extract_uint32(data, offset);
    if (offset + message_data.type_name_length > message_data.length) {
        return false; // type_name_length 太长，超出了 length 的范围
    }

    message_data.type_name = extract_string(data, offset, message_data.type_name_length);
    message_data.message = extract_string(data, offset, message_data.length - offset);
    return true;
}

std::unique_ptr<google::protobuf::Message> unpack_message(const std::string &input) noexcept {
    MessageData message_data;
    if (!deserialize(input, message_data)) {
        return nullptr;
    }

    auto message = create_message(message_data.type_name);
    if (message == nullptr) {
        return nullptr;
    }

    if (!message->ParseFromString(message_data.message)) {
        return nullptr;
    }
    return message;
}

std::unique_ptr<google::protobuf::Message> create_message(const std::string &type_name) {
    const google::protobuf::Descriptor *descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
    if (descriptor == nullptr) {
        return nullptr;
    }

    const google::protobuf::Message *prototype =
        google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    if (prototype == nullptr) {
        return nullptr;
    }

    return std::unique_ptr<google::protobuf::Message>(prototype->New());
}

std::string try_extract_one_pack_data(std::string &total_buffer) {
    if (total_buffer.size() < k_UINT32_SIZE) { // 如果小于消息长度字段的长度
        return {};
    }
    uint32_t length = unpack_message_length(total_buffer);
    if (total_buffer.size() < length) {
        return {};
    }
    std::string pack_data = total_buffer.substr(0, length);
    total_buffer = total_buffer.substr(length); // 剩余的数据
    return pack_data;
}

} // namespace net