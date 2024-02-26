#pragma once

#include <map>
#include <string>

/**
 * @brief シーン間で共有するパラメータを管理するクラス
 */
class Parameter {
  public:
    Parameter() = default;
    virtual ~Parameter() = default;

    void set(std::string key, int value);
    int get(std::string key) const;

  private:
    std::map<std::string, int> params;
};