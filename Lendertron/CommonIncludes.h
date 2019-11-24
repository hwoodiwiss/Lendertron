//STD Includes
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <filesystem>

#include <windows.h>
#define WIN32_LEAN_AND_MEAN

//Types from standard lib that will be used a lot, so will be wanting to use without std::
using string = std::string;

//Useful modern cpp smart reference counting pointer. On copy of the pointer object,
//ref count increases, and on destruction of shared_ptr ref count decreases.
//When ref count == 0, frees pointed to memory.
template <typename T> using shared_ptr = std::shared_ptr<T>;

template <typename T> using vector = std::vector<T>;
template <typename T_KEY, typename T_VAL> using map = std::map<T_KEY, T_VAL>;