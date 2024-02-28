#include "ColorGradator.hpp"

#include <algorithm>

/**
 * @brief カラーグラデーション配列を生成する
 * @param left 左端の色
 * @param right 右端の色
 * @param step 分割数
 * @return グラデーションされた色
 */
std::vector<SDL_Color> ColorGradator::gradate(const SDL_Color &left, const SDL_Color &right, int step) {
    std::vector<SDL_Color> colors(step);

    for (int i = 0; i < step; i++) {
        colors[i].r = left.r + (right.r - left.r) * i / step;
        colors[i].g = left.g + (right.g - left.g) * i / step;
        colors[i].b = left.b + (right.b - left.b) * i / step;
        colors[i].a = 255;
    }

    return colors;
}