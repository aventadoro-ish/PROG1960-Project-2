#pragma once
#include "utils.h"
#include <fstream>

/// Joshua Rice

class CSV{
private:
	std::string fileName;
	std::string** arr;
	int rowCount = 0;
	int colCount = 1;

public:
	CSV();
	CSV(std::string);
	~CSV();

	std::string getFileName();
	std::ofstream getCurrFile();
	std::string getArrVal(int, int);//Do I need this?
	std::string* getRowData(int);
	int getRowCount() const;
	int getColCount() const;

	void setFileName(std::string);
	void setRowCount(int);
	void setColCount(int);
	void setArrVal(int, int, std::string);

	bool importCSV();
	void countArrDimensions(std::ifstream&);
	bool initArr(std::ifstream&);




	//void printArr();

};

