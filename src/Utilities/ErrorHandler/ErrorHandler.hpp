#pragma once

#include <string>

/**
 * @brief エラーハンドラ
 * @details エラー終了処理を行う
 */
class ErrorHandler {
  public:
    static void finish(const std::string &error_message, const char *func, const int line);
};