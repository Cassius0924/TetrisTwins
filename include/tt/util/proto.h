#ifndef UTIL_PROTO_H
#define UTIL_PROTO_H

#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>

namespace util::proto {

using namespace google::protobuf;

template <typename T>
std::vector<T> to_vector(const RepeatedField<T> &repeated_field) {
    return std::vector<T>(repeated_field.begin(), repeated_field.end());
}

template <typename T>
RepeatedField<T> to_repeated_field(const std::vector<T> &vec) {
    RepeatedField<T> repeated_field;
    for (const auto &elem : vec) {
        repeated_field.Add(elem);
    }
    return repeated_field;
}

template <typename T, typename U>
std::vector<std::vector<T>> to_vector2(const RepeatedPtrField<U> &repeated_field) {
    std::vector<std::vector<T>> vec;
    const FieldDescriptor *field = U::GetDescriptor()->field(0);
    const Reflection *reflection = U::GetReflection();
    for (const auto &elem : repeated_field) {
        vec.push_back(to_vector<T>(reflection->GetRepeatedField<T>(elem, field)));
    }
    return vec;
}

template <typename T, typename U>
RepeatedPtrField<U> to_repeated_field(const std::vector<std::vector<T>> &vec) {
    RepeatedPtrField<U> repeated_field;
    for (const auto &elem : vec) {
        repeated_field.Add()->mutable_value()->CopyFrom(to_repeated_field<T>(elem));
    }
    return repeated_field;
}

// template <typename T, typename U>
// void to_repeated_field(const std::vector<std::vector<T>> &vec, RepeatedPtrField<U> &repeated_field) {
//     for (const auto &elem : vec) {
//         repeated_field.Add()->CopyFrom(to_repeated_field<T>(elem));
//     }
//     return repeated_field;
// }
//

} // namespace util::proto

#endif // UTIL_PROTO_H
