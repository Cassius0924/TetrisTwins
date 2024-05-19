#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <any>
#include <functional>
#include <unordered_map>

#include <google/protobuf/message.h>

namespace net {

// FIXME: 是否需要改成shared_ptr?
class Dispatcher {
private:
    template <typename T>
    using Callback = std::function<void(std::unique_ptr<T>)>;

    std::unordered_map<const google::protobuf::Descriptor *, Callback<google::protobuf::Message>> _callback_map{};

public:
    explicit Dispatcher() = default;

    ~Dispatcher() = default;

    template <typename T>
    void register_message_callback(Callback<T> callback) {
        _callback_map[T::descriptor()] = [callback, this](std::unique_ptr<google::protobuf::Message> message){
            // 向下转型，需要使用dynamic_cast；由于是unique_ptr，所以需要使用release转移message消息对象的所有权
            callback(std::unique_ptr<T>(dynamic_cast<T*>(message.release())));
        };
    }
    template <typename T>
    void on_message(std::unique_ptr<T> message) {
        auto it = _callback_map.find(message->GetDescriptor());
        if (it != _callback_map.end()) {
            it->second(std::move(message));
        } else {
            // TODO：处理无回调函数消息类型
            abort();
        }
    }

};

} // namespace net

#endif // DISPATCHER_H
