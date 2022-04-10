#include "CSV.h"
#define NPOS -1
#define BLANK_LINE buffer.find_first_not_of(' ', ref) == NPOS
#define LAST_CELL 2

CSV::CSV(){
	fileName = "NO FILE NAME ASSIGNED";
}

CSV::CSV(std::string fileExt) {
	setFileName(fileExt);
}

CSV::~CSV() {
	for (int i = rowCount-1; i >= 0; i--) {
		delete[] arr[i];
	}
	delete[] arr;
}


std::string CSV::getFileName() { return fileName; }

std::string CSV::getArrVal(int x, int y) {
	return arr[x][y];
}

std::string* CSV::getRowData(int x) {
	return arr[x];
}
int CSV::getRowCount()const { return rowCount; }
int CSV::getColCount()const { return colCount; }

void CSV::setFileName(std::string newName) {fileName = newName;}
void CSV::setRowCount(int x) { rowCount = x; }
void CSV::setColCount(int y) { colCount = y; }
void CSV::setArrVal(int x, int y, std::string data) {
	arr[x][y] = data;
}




bool CSV::importCSV() {
	std::ifstream file;
	std::string buffer;
	std::string temp;
	int pos = 0;
	int ref = 0;
	int flag = 0;


	if (initArr(file) == false) return false;

	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "Error Opening File: " << fileName << std::endl;
		return false;
	}

	for (int x = 0; x < rowCount; x++) {
		ref = 0;
		flag = 0;
		std::getline(file, buffer);
		if (buffer.empty()) {
			x--;
			continue;
		}

		//Experimental Algorithm -- Needs Cleaned Up/Whitespace removal feature
		// 
		//for (int y = 0; y < colCount; y++) {
		//	if (flag == LAST_CELL) {
		//		arr[x][y] = "";
		//		continue;
		//	}
		//	if (buffer.find_first_of(',', ref) != NPOS) {
		//		pos = (buffer.find_first_of(',', ref));
		//		temp = buffer.substr(ref, (pos-ref));
		//		ref += temp.size() + 1;
		//		arr[x][y] = temp;
		//		std::cout << arr[x][y];
		//		temp.erase();
		//	}
		//	else
		//	{
		//		flag = LAST_CELL; 
		//		arr[x][y] = buffer.substr(ref);
		//		std::cout << arr[x][y];
		//		continue;
		//	}
		//}
		//std::cout << std::endl;
		//}


		//Import Info
		for (int y = 0; y < colCount; y++) {
			if ((pos = buffer.find_first_of(",")) != NPOS) {
				arr[x][y] = buffer.substr(0, pos);
				buffer.erase(0, pos + 1);
			}
			else if ((pos = buffer.size()) > 0) {
				arr[x][y] = buffer.substr(0, pos);
				buffer.erase(0, pos);
			}
			else {
				arr[x][y] = "";
			}
		}
	}
	file.close();
}
bool CSV::initArr(std::ifstream& file) {

	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "Error Opening File: " << fileName << std::endl;
		return false;
	}
	countArrDimensions(file);
	file.close();
	//Initializing 2D Array
	arr = new std::string * [rowCount];
	for (int i = 0; i < rowCount; i++) {
		arr[i] = new std::string[colCount];
	}
}
void CSV::countArrDimensions(std::ifstream& file) {
	int tempColCount = 1;
	std::string buffer;

	while (!file.eof()) {
		std::getline(file, buffer);
		if (!buffer.empty()) {
			for (int i = 0; i < buffer.size(); i++) {//Counts the # of columns
				if (buffer[i] == ',') {
					tempColCount++;
				}
			}
			if (colCount < tempColCount) colCount = tempColCount;
			rowCount++;
			buffer.erase();
			tempColCount = 0;
		}
	}
}





void CSV::printArr() {
	try {
		for (int i = 0; i < rowCount; i++) {
			for (int ii = 0; ii < colCount; ii++){
				std::cout << arr[i][ii] << " ";
			}
			std::cout << std::endl;
		}
	}
	catch (...) {
		std::cout << "Array uninitialized.";
	}
}

