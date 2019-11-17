#pragma once

//STD Includes
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <filesystem>

using string = std::string;
template <typename T> using shared_ptr = std::shared_ptr<T>;
template <typename T> using vector = std::vector<T>;
template <typename T_KEY, typename T_VAL> using map = std::map<T_KEY, T_VAL>;

#include "User.h"