#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constant
{
constexpr int kFramesPerSecond{60};
constexpr int kMsPerFrame{1000 / kFramesPerSecond};
constexpr int kScreenWidth{1280};
constexpr int kScreenHeight{720};
constexpr int kDefaultPlayerXPos{100};
constexpr int kDefaultPlayerYPos{100};
constexpr int kPlayerSpeed{4};
constexpr int kPlayerBulletSpeed{16};
constexpr int kEnemyBulletSpeed{4};
constexpr int kFPS{60};
} // namespace Constant

#endif //CONSTANTS_H