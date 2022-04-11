#include "Printable2DArray.h"

void Printable2DArray::print(std::ostream& ostr, bool addHeaders, char hSep, char vSep) {
	int xMax = getXLen();
	int yMax = getYLen();

	if (addHeaders) {
		ostr << hSep;
		for (int x = 0; x < xMax; x++) {
			ostr << getHeaderForCol(x) << hSep;
		}
		ostr << vSep;

	}

	for (int y = 0; y < yMax; y++) {
		if (addHeaders) {
			ostr << getHeaderForRow(y) << hSep;
		}

		for (int x = 0; x < xMax; x++) {
			ostr << getCellAsStr(x, y) << hSep;
		}
		ostr << vSep;
	}


}
