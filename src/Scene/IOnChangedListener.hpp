#pragma once

#include "AbstractScene/AbstractScene.hpp"
#include "Parameter/Parameter.hpp"
#include "SceneType.hpp"

/**
 * @brief コールバックするためのリスナーインターフェイス
 */
class IOnChangedListener {
  public:
    IOnChangedListener() = default;
    virtual ~IOnChangedListener() = default;
    virtual void on_changed(const SceneType scene_type, const Parameter &param, const bool should_clear_stuck) = 0;
};