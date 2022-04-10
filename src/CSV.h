#pragma once
#include "utils.h"
#include <fstream>


class CSV : private std::ofstream {
private:
	std::string fileName;
	std::string** arr;
	int rowCount = 0;
	int colCount = 1;

public:
	CSV(std::string fileExt);
	~CSV();

	std::string getFileName();
	std::ofstream getCurrFile();
	std::string getArrVal(int, int);//Do I need this?
	std::string* getRow(int);

	void setFileName()const;

	bool initArr(std::ifstream&);
	bool importCsv();
	void printArr();

};