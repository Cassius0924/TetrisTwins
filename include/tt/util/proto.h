#ifndef UTIL_PROTO_H
#define UTIL_PROTO_H

#include <google/protobuf/repeated_field.h>

namespace util::proto {

template <typename T>
std::vector<T> to_vector(const google::protobuf::RepeatedField<T> &repeated_field) {
    return std::vector<T>(repeated_field.begin(), repeated_field.end());
}

template <typename T>
google::protobuf::RepeatedField<T> to_repeated_field(const std::vector<T> &vec) {
    google::protobuf::RepeatedField<T> repeated_field;
    for (const auto &elem : vec) {
        repeated_field.Add(elem);
    }
    return repeated_field;
}

} // namespace util::proto

#endif // UTIL_PROTO_H
