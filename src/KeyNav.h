#pragma once
#include "utils.h"
#include "Printable2DArray.h"
#include <conio.h>	

typedef struct coord {
	int x;
	int y;
};

class KeyNav {
private:
	std::string forbidKeys;
	std::string textBuffer;
	coord buffPos;
	coord cursPos;

public:

	KeyNav();
	KeyNav(int, int, std::string, int = 0, int = 0);//BUFF xy, ForbidKeys, CURSOR xy
	~KeyNav();

	int keyParser();
	int virtual selectResult(int) = 0;

	//MODIFY FORBIDDEN KEYS
	void getForbidKeys();
	void setForbidKeys(bool append);
	void letterForbid(bool append);
	void numForbid(bool append);
	void resetForbid();

	//TEXT BUFFER
	int getBuffX();
	void setBuffX(int);

	int getBuffY();
	void setBuffY(int);

	void printBuffer();
	std::string bufferResults();

	//CURSOR POSITION
	int getCursX();
	void setCursX(int);

	void getCursY();
	void setCursY(int);


};