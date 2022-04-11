#pragma once
#include "utils.h"
#include <ostream>

class Printable2DArray {
private:

public:
	Printable2DArray() {}
	~Printable2DArray() {}

	virtual int getXLen() = 0;
	virtual int getYLen() = 0;

	virtual std::string getHeaderForRow(int y) = 0;
	virtual std::string getHeaderForCol(int x) = 0;

	virtual std::string getCellAsStr(int x, int y) = 0;

	void print(std::ostream& ostr, bool addHeaders = true, char hSep = ',', char vSep = '\n');

};
