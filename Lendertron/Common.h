//STD Includes
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <filesystem>

#include <windows.h>
#define WIN32_LEAN_AND_MEAN

//Types from standard lib that will be used a lot, so will be wanting to use without std::
using std::string;

//Useful modern cpp smart reference counting pointer. On copy of the pointer object,
//ref count increases, and on destruction of shared_ptr ref count decreases.
//When ref count == 0, frees pointed to memory.
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::map;