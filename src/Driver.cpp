//============================================================================
// Name        : Utility.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstring>
#include <iostream>

#include "BLANRImpl.h"
#include "BLAPDBImpl.h"
#include "CNFSearchImpl.h"
#include "HHRImpl.h"
#include "HHRNRImpl.h"

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
		blaPDBImpl.write2PDB();
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

	// -hhr T0837
	if (strcmp(argv[1], "-hhr") == 0) {
		HHRImpl hhrImpl(argv[2]);
		hhrImpl.populateResultVector();
		hhrImpl.makeDirectory();
		hhrImpl.write2Json();
		hhrImpl.setup3DCoords();
		hhrImpl.findLocalAlign();
		hhrImpl.findGlobalAlign();
		hhrImpl.write2PDB();
	}

	// -hhrNR T0837
	if (strcmp(argv[1], "-hhrNR") == 0) {
		HHRNRImpl hhrNRImpl(argv[2]);
		hhrNRImpl.populateResultVector();
		hhrNRImpl.makeDirectory();
		hhrNRImpl.write2Json();
		//hhrNRImpl.setup3DCoords();
		//hhrNRImpl.findLocalAlign();
		//hhrNRImpl.findGlobalAlign();
	}

	if (strcmp(argv[1], "-cnfSearch") == 0) {
		CNFSearchImpl cnfSearchImpl(argv[2]);
		cnfSearchImpl.populateResultVector();
		cnfSearchImpl.makeDirectory();
		cnfSearchImpl.write2Json();
		cnfSearchImpl.setup3DCoords();
		cnfSearchImpl.findLocalAlign();
		cnfSearchImpl.findGlobalAlign();
		cnfSearchImpl.write2PDB();
	}

	return 0;
}
