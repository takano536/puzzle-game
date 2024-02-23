#pragma once

/**
 * @brief The Looper class
 * メインループを管理するクラス
 */
class Looper final {
  public:
    Looper() = default;
    ~Looper() = default;

    void loop() const;
};