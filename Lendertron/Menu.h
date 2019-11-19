#pragma once
#include "CommonIncludes.h"

typedef void (*MenuItemCallback)();

struct MenuItem
{
	string ItemText;
	MenuItemCallback ItemCallback;
};

class Menu
{
public:

private:
};