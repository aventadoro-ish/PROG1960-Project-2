#pragma once
#include "KeyNav.h"

typedef struct menuItem{
	std::string name;
	coord position;
};

class Menu : private KeyNav {
private:
	std::string titleBlock;
	menuItem* itemList;

public:
	Menu();
	~Menu();



};
