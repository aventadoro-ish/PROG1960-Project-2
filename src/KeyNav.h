#pragma once
#include "utils.h"
#include <conio.h>	


//Joshua Rice

enum KEYCODES{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	BACKSPACE = 8,
	DELETE = 83
};

typedef struct{
	unsigned x;
	unsigned y;
}coord;

class KeyNav {
private:
	std::string forbidKeys;
	std::string textBuffer;
	coord buffPos;
	coord cursPos;

public:

	KeyNav();
	KeyNav(int, int);
	KeyNav(int, int, std::string, int = 0, int = 0);//BUFF xy, ForbidKeys, CURSOR xy
	~KeyNav();

	int bufferKeyParser(int);
	int menuKeyParser(int);
	

	//MODIFY FORBIDDEN KEYS
	bool isForbidden(int);
	std::string getForbidKeys();
	void setForbidKeys(std::string, bool append);
	void resetForbids();

	void letterForbid(bool);
	void numForbid(bool);
	
	//Check for Duplicates?
	
	//TEXT BUFFER
	void redrawBuffer();
	std::string getTextBuffer();
	void clearTextBuffer();
	void setBuffPos(int, int);

	//CURSOR POSITION
	int getCursX();
	int getCursY();

	void setCursY(int);
	void setCursX(int);
	void stdOffset();
};