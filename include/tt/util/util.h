#ifndef UTIL_H
#define UTIL_H

#include <string>

#include "tt/util/device.h"
#include "tt/util/math.h"
#include "tt/util/noncopyable.h"
#include "tt/util/proto.h"
#include "tt/util/safe_deque.h"

namespace util {

/**
 * 获取游戏帧率
 */
int fps();

/**
 * 无缓存获取键盘输入
 * @return 输入字符
 */
char getch();

}


#endif //UTIL_H
