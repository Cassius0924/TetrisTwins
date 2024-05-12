#ifndef BASE_NONCOPYABLE_H
#define BASE_NONCOPYABLE_H

class NonCopyable {
public:
    // 删除拷贝构造函数和赋值运算符
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;

protected:
    // 默认构造函数和析构函数
    NonCopyable() = default;
    virtual  ~NonCopyable() = default;
};

#endif //BASE_NONCOPYABLE_H
