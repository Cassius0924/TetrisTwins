#ifndef NET_PACKER_H
#define NET_PACKER_H

#include <google/protobuf/message.h>

#include "tt/net/net_define.h"

namespace net {

constexpr uint32_t k_UINT32_SIZE = sizeof(uint32_t);

// struct MessageDataPro {
//     uint32_t length;                 // 整个消息的长度（包括sizeof(length)的长度）
//     ushort protocol;                 // 协议类型：json、protobuf、xml、string
//     uint32_t proto_type_name_length; // 类型名长度
//     std::string proto_type_name;     // 类型名
//     std::string message;             // 消息
// };

/**
 * 消息数据结构体
 */
struct MessageData {
    uint32_t length = 0;           // 整个消息的长度（包括sizeof(length)的长度）
    uint32_t type_name_length = 0; // 类型名长度
    std::string type_name;       // 类型名
    std::string message;         // 消息
};

/**
 * 序列化 MessageData 对象
 * @param message_data MessageData 对象
 * @return 序列化后的字符串
 */
std::string serialize(const MessageData &message_data);

/**
 * 将 google::protobuf::Message 对象打包成 MessageData 对象并序列化
 * @param message google::protobuf::Message 对象
 * @return MessageData 对象序列化后的字符串
 */
std::string pack_message(const google::protobuf::Message &message);

/**
 * 提取字符串中特定位置的 uint32_t 数据
 * @param data 字符串
 * @param offset 偏移量
 * @return uint32_t 数据
 */
inline uint32_t extract_uint32(const char *data, size_t &offset) {
    uint32_t result = ntohl(*reinterpret_cast<const uint32_t *>(data + offset));
    offset += k_UINT32_SIZE;
    return result;
}

/**
 * 将字符串前四个字节转换为 uint32_t 数据
 * @param data 字符串
 * @return uint32_t 数据
 */
inline uint32_t extract_uint32(const char *data) {
    uint32_t result = ntohl(*reinterpret_cast<const uint32_t *>(data));
    return result;
}

/**
 * 提取字符串中特定位置的字符串数据
 * @param data 字符串
 * @param offset 偏移量
 * @param length 长度
 * @return string 数据
 */
inline std::string extract_string(const char *data, size_t &offset, uint32_t length) {
    std::string result(data + offset, length);
    offset += length;
    return result;
}

/**
 * 反序列化 MessageData 对象
 * @param input 输入的字符串
 * @param message_data MessageData 对象
 * @return 是否反序列化成功
 */
bool deserialize(const std::string &input, MessageData &message_data) noexcept;

/**
 * 将字符串反序列化为 MessageData 对象并拆包成 google::protobuf::Message 智能指针
 * @param input 字符串
 * @return google::protobuf::Message 智能指针
 */
std::unique_ptr<google::protobuf::Message> unpack_message(const std::string &input) noexcept;

/**
 * 提取字符串中的消息长度
 * @param input 字符串
 * @return 消息长度
 */
inline uint32_t unpack_message_length(const std::string &input) {
    return extract_uint32(input.data());
}

/**
 * 使用反射机制基于类型名创建 google::protobuf::Message 智能指针
 * @param type_name 类型名
 * @return google::protobuf::Message 智能指针
 */
std::unique_ptr<google::protobuf::Message> create_message(const std::string &type_name);

/**
 * 尝试从缓冲区中提取一个完整的数据包
 * @param total_buffer 缓冲区
 * @return 数据包，若提取失败则返回空字符串
 */
std::string try_extract_one_pack_data(std::string &total_buffer);

}

#endif
