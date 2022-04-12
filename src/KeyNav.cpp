#include "KeyNav.h"
#define CURSOR_RELATIVE ((buffPos.x + textBuffer.size()) - cursPos.x)

KeyNav::KeyNav() {
	forbidKeys = "";
	textBuffer = "";
	buffPos.x = 0;
	buffPos.y = 0;
	cursPos.x = 0;
	cursPos.y = 0;
}

KeyNav::KeyNav(int buffX, int buffY, std::string forbidlist, int cursX, int cursY) {
	buffPos.x = buffX;
	buffPos.y = buffY;
	forbidKeys = forbidlist;
	cursPos.x = cursX;
	cursPos.y = cursY;
}

KeyNav::~KeyNav() {}


bool KeyNav::isForbidden(int x) {
	char c = x;
	if (forbidKeys.find_first_of(c) != std::string::npos) { return false; }
	else return true;
}

std::string KeyNav::getForbidKeys() { return forbidKeys; }

void KeyNav::setForbidKeys(std::string keys, bool append) {
	if (append) {
		forbidKeys.append(keys);
	}
	else forbidKeys = keys;
}

void KeyNav::letterForbid(bool append) {
	if (append) {
		forbidKeys.append("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz");
	}
	else forbidKeys = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
}

void KeyNav::numForbid(bool append) {
	if (append) {
		forbidKeys.append("0123456789");
	}
	else forbidKeys = "0123456789";
}

void KeyNav::resetForbids() {
	forbidKeys = "";
}


void KeyNav::redrawBuffer() {
	moveCursor(buffPos.x, buffPos.y);
	printf("\033[0K");
	std::cout << textBuffer;
	moveCursor(cursPos.x, cursPos.y);
}

std::string KeyNav::getTextBuffer() { return textBuffer; }

void KeyNav::clearTextBuffer() {
	moveCursor(buffPos.x, buffPos.y);
	printf("\033[0K");
}

void KeyNav::setBuffPos(int x, int y) {
	buffPos.x = x;
	buffPos.y = y;
	setCursX(x);
	setCursY(y);
}


int KeyNav::getCursX() { return cursPos.x; }
void KeyNav::setCursX(int x) { 
	cursPos.x = x;
	moveCursor(cursPos.x, cursPos.y);
}

int KeyNav::getCursY() { return cursPos.y; }
void KeyNav::setCursY(int y) {
	cursPos.y = y;
	moveCursor(cursPos.x, cursPos.y);
}


int KeyNav::keyParser(int key, bool insideBuffer) {
	int cmd;
	if (insideBuffer) {
		switch (key) {
		case ENTER:
			getTextBuffer();
			return 1;
		case BACKSPACE:
			if (textBuffer.size() == 0)return 1;
			textBuffer.erase(textBuffer.size() - 1 );
			--cursPos.x;
			redrawBuffer();
			break;
		case 224:
			cmd = _getch();
			switch (cmd) {
			case LEFT:
				if (cursPos.x == buffPos.x) break;
				--cursPos.x;
				return 0;
			case RIGHT:
				if (CURSOR_RELATIVE == 1) break;
				++cursPos.x;
				return 0;
			case UP:
				return 0;
			case DOWN:
				return 0;
			default:
				return 0;
				}
		default:
				textBuffer.push_back(key);
				++cursPos.x;
				redrawBuffer();
				return 0;
		}
	}
	else {
		switch (key) {
		case ENTER:
			return 1;
		case BACKSPACE:
			return 2;
		case 224:
			cmd = _getch();
			switch (cmd) {
			case UP:
				--cursPos.y;
				setCursY(cursPos.y);
				return 0;
			case DOWN:
				++cursPos.y;
				setCursY(cursPos.y);
				return 0;
			case LEFT:
				--cursPos.x;
				setCursX(cursPos.x);
				return 0;
			case RIGHT:
				++cursPos.x;
				setCursX(cursPos.x);
				return 0;
			}
		}
	}
}