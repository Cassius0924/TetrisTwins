#include <tt/util/math.h>

#include <random>

namespace util::math {

int random_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

} // namespace util::math