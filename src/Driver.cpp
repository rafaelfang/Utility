//============================================================================
// Name        : Utility.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>

#include "BLAPDBImpl.h"
#include "BLANRImpl.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "not enough arguments" << endl;
		cout << "<executable> <type> <proteinName>" << endl;

	}

	// -blaPDB T0837
	if (strcmp(argv[1], "-blaPDB") == 0) {
		BLAPDBImpl blaPDBImpl(argv[2]);
		blaPDBImpl.populateResultVector();
		blaPDBImpl.makeDirectory();
		blaPDBImpl.write2Json();
		blaPDBImpl.setup3DCoords();
		blaPDBImpl.findLocalAlign();
		blaPDBImpl.findGlobalAlign();
	}

	// -blaNR T0837
	if (strcmp(argv[1], "-blaNR") == 0) {
		BLANRImpl blaNRImpl(argv[2]);
		blaNRImpl.populateResultVector();
		blaNRImpl.makeDirectory();
		blaNRImpl.write2Json();
		//blaPDBImpl.setup3DCoords();
		//blaPDBImpl.findLocalAlign();
		//blaPDBImpl.findGlobalAlign();
	}

	return 0;
}
