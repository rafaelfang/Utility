/*
 * BLANRImpl.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: cf797
 */

#include "BLANRImpl.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
BLANRImpl::BLANRImpl(char* theRootName) :
		UtilityInterface(theRootName) {
	// TODO Auto-generated constructor stub

}
void BLANRImpl::makeDirectory() {
	char cmd1[500];
	string outputFileFoldername(outputFileLocation);
	outputFileFoldername += "/";
	outputFileFoldername += rootName;
	outputFileFoldername += "/";
	//cout << outputFileFoldername << endl;
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd1 << endl;
	system(cmd1);

}
void BLANRImpl::populateResultVector() {

	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.blaNR";

	FILE* fptr = fopen((char*) inFilename.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}
	BLANRResult result;

	while (fgets(line, 500, fptr) != NULL) {
		if ((strstr(line, ">") != NULL) && !result.isFirstStateReached()) {
			//set first block information
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);
			while (strstr(line, "Length =") == NULL) {
				fgets(line, 500, fptr); //skip long name
			}
			char temp[10];
			int seqLen;
			sscanf(line, "%s = %d", temp, &seqLen);
			result.setLength(seqLen);
			//set first state reached
			result.setFirstStateReached(true);
		}
		if ((strstr(line, "Score =") != NULL)
				&& !result.isSecondStateReached()) {
			//set second block information
			float score;
			char* pos1 = strstr(line, "=");
			sscanf(pos1 + 1, "%f", &score);
			result.setScore(score);
			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);
			fgets(line, 500, fptr);
			pos1 = strstr(line, "(");
			int identities;
			sscanf(pos1 + 1, "%d", &identities);
			result.setIdentities(identities);
			pos2 = strstr(pos1 + 1, "(");
			int positives;
			sscanf(pos2 + 1, "%d", &positives);
			result.setPositives(positives);
			char* pos3 = strstr(pos2 + 1, "(");
			if (pos3 == NULL) {
				//there is no gaps
				result.setGaps(0);
			} else {
				int gaps;
				sscanf(pos3 + 1, "%d", &gaps);
				result.setGaps(gaps);
			}

			//set second state reached
			result.setSecondStateReached(true);
		}

		if ((strstr(line, "Query:") != NULL) && !result.isThirdStateReached()) {
			//set third block information
			int nInt1, nInt2;
			char var1[20], var2[20];
			char tmpQuery[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpQuery, &nInt2);
			result.setQueryStart(nInt1);
			string tmpQueryStr(tmpQuery);
			result.setQuery(tmpQueryStr);
			result.setQueryEnd(nInt2);
			fgets(line, 500, fptr);
			string tmpLineStr(line);
			result.setAlignment(tmpLineStr);
			fgets(line, 500, fptr);
			char tmpSubject[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpSubject, &nInt2);
			result.setSubjectStart(nInt1);
			string tmpSubjectStr(tmpSubject);
			result.setSubject(tmpSubjectStr);
			result.setSubjectEnd(nInt2);
			//set third state reached
			result.setThirdStateReached(true);
		}

		if ((strstr(line, "Query:") != NULL) && result.isThirdStateReached()) {
			//update third block information, so in this case
			//query, alignment and subject should be long string
			//the queryEnd and subjectEnd should also be updated
			int nInt1, nInt2;
			char var1[20], var2[20];
			char tmpQuery[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpQuery, &nInt2);
			string newQuery = result.getQuery();
			newQuery += tmpQuery;
			result.setQuery(newQuery);
			result.setQueryEnd(nInt2);
			fgets(line, 500, fptr);
			string newAlignment = result.getAlignment();
			newAlignment += line;
			result.setAlignment(newAlignment);
			fgets(line, 500, fptr);
			char tmpSubject[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpSubject, &nInt2);
			string newSubject = result.getSubject();
			newSubject += tmpSubject;
			result.setSubject(newSubject);
			result.setSubjectEnd(nInt2);

		}

		if ((strstr(line, "Score =") != NULL)
				&& result.isSecondStateReached()) {

			//first write the protein information to json

			blaNRResultVector.push_back(result);
			counter++;
			//then update the information and set the second state flag
			float score;
			char* pos1 = strstr(line, "=");
			sscanf(pos1 + 1, "%f", &score);
			result.setScore(score);
			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);
			fgets(line, 500, fptr);
			pos1 = strstr(line, "(");
			int identities;
			sscanf(pos1 + 1, "%d", &identities);
			result.setIdentities(identities);
			pos2 = strstr(pos1 + 1, "(");
			int positives;
			sscanf(pos2 + 1, "%d", &positives);
			result.setPositives(positives);
			char* pos3 = strstr(pos2 + 1, "(");
			if (pos3 == NULL) {
				//there is no gaps
				result.setGaps(0);
			} else {
				int gaps;
				sscanf(pos3 + 1, "%d", &gaps);
				result.setGaps(gaps);
			}

			result.setSecondStateReached(true);
			//unset the third block flag
			result.setThirdStateReached(false);

		}
		if ((strstr(line, ">") != NULL) && result.isFirstStateReached()) {

			blaNRResultVector.push_back(result);
			counter++;
			//then update the information set the first state flag
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);
			while (strstr(line, "Length =") == NULL) {
				fgets(line, 500, fptr); //skip long name
			}
			char temp[10];
			int seqLen;
			sscanf(line, "%s = %d", temp, &seqLen);
			result.setLength(seqLen);
			//unset second block flag and third block flag
			result.setSecondStateReached(false);
			result.setThirdStateReached(false);
		}

	}

	blaNRResultVector.push_back(result);
	fclose(fptr);
}

void BLANRImpl::write2Json() {

	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/";
	outFilename += "blaNR.json";
	//cout<<outFilename<<endl;
	ofstream outputFile(outFilename.c_str());

	outputFile << "{" << "\n";

	for (int i = 0; i < blaNRResultVector.size(); i++) {

		outputFile << "\"protein" << i << "\":{\n";
		outputFile << "\t\"proteinName\":\""
				<< blaNRResultVector[i].getProteinName() << "\",\n";
		outputFile << "\t\"Length\":\"" << blaNRResultVector[i].getLength()
				<< "\",\n";
		outputFile << "\t\"Score\":\"" << blaNRResultVector[i].getScore()
				<< "\",\n";
		outputFile << "\t\"Expect\":\"" << blaNRResultVector[i].getExpect()
				<< "\",\n";
		outputFile << "\t\"Identities\":\""
				<< blaNRResultVector[i].getIdentities() << "\",\n";
		outputFile << "\t\"Positives\":\""
				<< blaNRResultVector[i].getPositives() << "\",\n";
		outputFile << "\t\"Gaps\":\"" << blaNRResultVector[i].getGaps()
				<< "\",\n";
		outputFile << "\t\"QueyStart\":\""
				<< blaNRResultVector[i].getQueryStart() << "\",\n";
		outputFile << "\t\"Query\":\"" << blaNRResultVector[i].getQuery()
				<< "\",\n";
		outputFile << "\t\"QueryEnd\":\"" << blaNRResultVector[i].getQueryEnd()
				<< "\",\n";
		outputFile << "\t\"Alignment\":\""
				<< blaNRResultVector[i].getAlignment() << "\",\n";
		outputFile << "\t\"SubjectStart\":\""
				<< blaNRResultVector[i].getSubjectStart() << "\",\n";
		outputFile << "\t\"Subject\":\"" << blaNRResultVector[i].getSubject()
				<< "\",\n";
		outputFile << "\t\"SubjectEnd\":\""
				<< blaNRResultVector[i].getSubjectEnd() << "\"\n";
		outputFile << "},\n";
	}
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";

	outputFile.close();

}

void BLANRImpl::setup3DCoords() {

}
void BLANRImpl::findLocalAlign() {

}
void BLANRImpl::findGlobalAlign() {

}

BLANRImpl::~BLANRImpl() {
	// TODO Auto-generated destructor stub
}

