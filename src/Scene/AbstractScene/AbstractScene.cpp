#include "AbstractScene.hpp"

/**
 * @brief コンストラクタ
 * @param listener リスナー
 * @param params パラメータ
 */
AbstractScene::AbstractScene(IOnChangedListener *listener, const Parameter &params)
    : listener(listener) {
}