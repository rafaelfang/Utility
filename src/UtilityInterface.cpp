/*
 * Utility.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#include "UtilityInterface.h"

#include <fstream>

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
