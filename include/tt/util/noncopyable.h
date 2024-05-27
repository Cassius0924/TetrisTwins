#ifndef UTIL_NONCOPYABLE_H
#define UTIL_NONCOPYABLE_H

namespace util {

class noncopyable {
public:
    // 删除拷贝构造函数和赋值运算符
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;

protected:
    // 默认构造函数和析构函数
    noncopyable() = default;
    virtual ~noncopyable() = default;
};

}

#endif // UTIL_NONCOPYABLE_H
