#include "ShapeRenderer.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../Utilities/Macros.hpp"

/**
 * @brief アンチエイリアス付きの塗りつぶした円を描画
 * @param renderer SDLレンダラー
 * @param x 中心のx座標
 * @param y 中心のy座標
 * @param rad 半径
 * @param r 赤成分
 * @param g 緑成分
 * @param b 青成分
 * @param a アルファ成分
 */
void ShapeRenderer::aafilledCircleRGBA(SDL_Renderer *renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (rad <= 1) {
        ERR("radius must be greater than 1");
    }
    aacircleRGBA(renderer, x, y, rad, r, g, b, a);
    // 弦を描画して円を塗りつぶす
    for (Sint16 i = 1; i < rad; i++) {
        Sint16 len = static_cast<Sint16>(std::sqrt(rad * rad - i * i));  // 弦の長さ
        // 上と下に弦を描画
        aalineRGBA(renderer, x - len, y + i, x + len, y + i, r, g, b, a);
        aalineRGBA(renderer, x - len, y - i, x + len, y - i, r, g, b, a);
    }
    // 最後に中心の線を描画
    aalineRGBA(renderer, x - rad, y, x + rad, y, r, g, b, a);
}

/**
 * @brief アンチエイリアス付きの塗りつぶした角丸四角形を描画
 * @param renderer SDLレンダラー
 * @param x1 右上のx座標 (top-right)
 * @param y1 右上のy座標 (top-right)
 * @param x2 左下のx座標 (bottom-left)
 * @param y2 左下のy座標 (bottom-left)
 * @param rad 角の半径
 * @param r 赤成分
 * @param g 緑成分
 * @param b 青成分
 * @param a アルファ成分
 */
void ShapeRenderer::aafilledRoundRectRGBA(SDL_Renderer *renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    x1--, y2--;
    // 四隅に円を描画
    aafilledCircleRGBA(renderer, x1 - rad, y1 + rad, rad, r, g, b, a);
    aafilledCircleRGBA(renderer, x2 + rad, y1 + rad, rad, r, g, b, a);
    aafilledCircleRGBA(renderer, x1 - rad, y2 - rad, rad, r, g, b, a);
    aafilledCircleRGBA(renderer, x2 + rad, y2 - rad, rad, r, g, b, a);
    // 十字架を描画
    boxRGBA(renderer, x1 - rad, y1, x2 + rad, y2, r, g, b, a);
    boxRGBA(renderer, x1, y1 + rad, x2, y2 - rad, r, g, b, a);
}