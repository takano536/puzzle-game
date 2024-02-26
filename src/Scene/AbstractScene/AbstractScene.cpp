#include "AbstractScene.hpp"

/**
 * @brief コンストラクタ
 * @param listener リスナー
 * @param param パラメータ
 */
AbstractScene::AbstractScene(IOnChangedListener *listener, const Parameter &param)
    : listener(listener) {
}