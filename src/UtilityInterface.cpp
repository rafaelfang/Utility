/*
 * Utility.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#include "UtilityInterface.h"

#include <cstdio>
#include <fstream>
#include <iostream>

#include "json/json.h"

UtilityInterface::UtilityInterface(char* rootName) {
	setRootName(rootName);
	loadConfigurationFile();

}
void UtilityInterface::loadConfigurationFile() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open("configuration.json", ios::binary);

	if (reader.parse(is, root)) {
		DBInfoLocation = root["DBInfoLocation"].asString();
		inputFileLocation = root["inputFileLocation"].asString();
		outputFileLocation = root["outputFileLocation"].asString();
		proteinLocation = root["proteinLocation"].asString();
	}

	is.close();
}

UtilityInterface::~UtilityInterface() {
	// TODO Auto-generated destructor stub
}

char* UtilityInterface::getRootName() {
	return rootName;
}

void UtilityInterface::setRootName(char* rootName) {
	this->rootName = rootName;
}

void UtilityInterface::findProteinSeqLength() {
	string inFilename(proteinLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += ".fasta";
	cout<<inFilename<<endl;

	FILE* fptr = fopen((char*) inFilename.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}
	char line[500];
	fgets(line, 500, fptr);
	fgets(line, 500, fptr);
	string proteinSeq(line);
	proteinSeqLength= proteinSeq.size();
}


