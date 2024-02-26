#include "Parameter.hpp"

#include "../../Define/Define.hpp"

/**
 * @brief パラメータを設定する
 */
void Parameter::set(std::string key, int value) {
    params[key] = value;
}

/**
 * @brief パラメータを取得する
 */
int Parameter::get(std::string key) const {
    return params.contains(key) ? params.at(key) : Define::ERROR;
}