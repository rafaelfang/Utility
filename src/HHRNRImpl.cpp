/*
 * HHRNRImpl.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cf797
 */

#include "HHRNRImpl.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

HHRNRImpl::HHRNRImpl(char* theRootName) :
		UtilityInterface(theRootName) {
	// TODO Auto-generated constructor stub

}

void HHRNRImpl::makeDirectory() {
	char cmd1[500];
	string outputFileFoldername(outputFileLocation);
	outputFileFoldername += "/";
	outputFileFoldername += rootName;
	outputFileFoldername += "/HHRNR/";
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd << endl;
	system(cmd1);

}
void HHRNRImpl::populateResultVector() {
	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.hhrNR";
	FILE* inputFile = fopen((char*) inFilename.c_str(), "r");
	if (inputFile == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}

	HHRNRResult result;

	while (fgets(line, 500, inputFile) != NULL) {

		if (strstr(line, ">") != NULL && !result.isFirstStateReached()) {
			//set first block information
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);

			while (strstr(line, "Probab=") == NULL) {
				fgets(line, 500, inputFile); //skip long name
			}

			//get probab, E-value, Score, Aligned_cols, Identities, Similarity, Sum_probs

			pos1 = strstr(line, "=");
			float probab;
			sscanf(pos1 + 1, "%f", &probab);
			result.setProbab(probab);

			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);

			char* pos3 = strstr(pos2 + 1, "=");
			float score;
			sscanf(pos3 + 1, "%f", &score);
			result.setScore(score);

			char* pos4 = strstr(pos3 + 1, "=");
			int alignedCols;
			sscanf(pos4 + 1, "%d", &alignedCols);
			result.setAlignedCols(alignedCols);

			char* pos5 = strstr(pos4 + 1, "=");
			float identities;
			sscanf(pos5 + 1, "%f", &identities);
			result.setIdentities(identities);

			result.setFirstStateReached(true);
		}

		if ((strstr(line, "Q ref|") != NULL)
				&& !result.isSecondStateReached()) {

			//set second block information

			//get the query

			int queryStart;
			char query[100];
			int queryEnd;
			sscanf(line + 17, "%d %s %d", &queryStart, query, &queryEnd);
			result.setQueryStart(queryStart);
			string strQuery(query);
			result.setQuery(strQuery);
			result.setQueryEnd(queryEnd);

			//get the Q Consensus
			fgets(line, 200, inputFile);
			int QConsensusStart;
			char QConsensus[100];
			int QConsensusEnd;
			sscanf(line + 17, "%d %s %d", &QConsensusStart, QConsensus,
					&QConsensusEnd);
			string strQConsensus(QConsensus);
			result.setQueryConsensus(strQConsensus);

			//get alignment
			fgets(line, 200, inputFile);
			char alignment[100];
			sscanf(line + 17, "%s", alignment);
			string strAlignment(alignment);
			result.setAlignment(strAlignment);

			//get the T Consensus
			fgets(line, 200, inputFile);
			int targetStart;
			char targetConsensus[100];
			int targetEnd;
			sscanf(line + 17, "%d %s %d", &targetStart, targetConsensus,
					&targetEnd);
			result.setTargetStart(targetStart);
			string strTargetConsensus(targetConsensus);
			result.setTargetConsensus(strTargetConsensus);
			result.setTargetEnd(targetEnd);

			//get the Target
			fgets(line, 200, inputFile);

			char target[100];

			sscanf(line + 17, "%d %s %d", &targetStart, target, &targetEnd);
			string strTarget(target);
			result.setTarget(strTarget);

			//get the TDssp
			fgets(line, 200, inputFile);
			char tDssp[100];
			sscanf(line + 17, "%s", tDssp);
			string strTDssp(tDssp);
			result.setTargetSsDssp(strTDssp);

			//get the TPred
			fgets(line, 200, inputFile);
			char tPred[100];
			sscanf(line + 17, "%s", tPred);
			string strTPred(tPred);
			result.setTargetSsPred(strTPred);

			//get the TConf
			fgets(line, 200, inputFile);
			char tConf[100];
			sscanf(line + 17, "%s", tConf);
			string strTConf(tConf);
			result.setConfidence(strTConf);

			result.setSecondStateReached(true);

		}

		if ((strstr(line, "Q ref|") != NULL) && result.isSecondStateReached()) {
			//update second block information, so in this case
			//quert, alignment and target should be long string
			//the queryEnd and targetEnd should also be updated
			//get the query

			int queryStart;
			char query[100];
			int queryEnd;
			sscanf(line + 17, "%d %s %d", &queryStart, query, &queryEnd);

			string additionalQuery(query);
			string newQuery = result.getQuery();
			newQuery += additionalQuery;
			result.setQuery(newQuery);
			result.setQueryEnd(queryEnd);

			//get the Q Consensus
			fgets(line, 200, inputFile);
			int QConsensusStart;
			char QConsensus[100];
			int QConsensusEnd;
			sscanf(line + 17, "%d %s %d", &QConsensusStart, QConsensus,
					&QConsensusEnd);
			string additionalQConsensus(QConsensus);
			string newQConsesus = result.getQueryConsensus();
			newQConsesus += additionalQConsensus;
			result.setQueryConsensus(newQConsesus);

			//get alignment
			fgets(line, 200, inputFile);
			char alignment[100];
			sscanf(line + 17, "%s", alignment);
			string additionalAlignment(alignment);
			string newAlignment = result.getAlignment();
			newAlignment += additionalAlignment;
			result.setAlignment(newAlignment);

			//get the T Consensus
			fgets(line, 200, inputFile);
			int targetStart;
			char targetConsensus[100];
			int targetEnd;
			sscanf(line + 17, "%d %s %d", &targetStart, targetConsensus,
					&targetEnd);

			string additionalTargetConsensus(targetConsensus);
			string newTargetConsensus = result.getTargetConsensus();
			newTargetConsensus += additionalTargetConsensus;
			result.setTargetConsensus(newTargetConsensus);
			result.setTargetEnd(targetEnd);

			//get the Target
			fgets(line, 200, inputFile);

			char target[100];

			sscanf(line + 17, "%d %s %d", &targetStart, target, &targetEnd);
			string additionalTarget(target);
			string newTarget = result.getTarget();
			newTarget += additionalTarget;
			result.setTarget(newTarget);

			//get the TPred
			fgets(line, 200, inputFile);
			char tPred[100];
			sscanf(line + 17, "%s", tPred);
			string additionalTPred(tPred);
			string newTPred = result.getTargetSsPred();
			newTPred += additionalTPred;
			result.setTargetSsPred(newTPred);

			//get the TConf
			fgets(line, 200, inputFile);
			char tConf[100];
			sscanf(line + 17, "%s", tConf);
			string additionalTConf(tConf);
			string newTConf = result.getConfidence();
			newTConf += additionalTConf;
			result.setConfidence(newTConf);

		}

		if ((strstr(line, ">") != NULL) && result.isFirstStateReached()) {
			//first push the result to the vector
			hhrNRResultVector.push_back(result);
			//then update the information set the first state flag
			//set first block information
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);

			while (strstr(line, "Probab=") == NULL) {
				fgets(line, 500, inputFile); //skip long name
			}

			//get probab, E-value, Score, Aligned_cols, Identities, Similarity, Sum_probs

			pos1 = strstr(line, "=");
			float probab;
			sscanf(pos1 + 1, "%f", &probab);
			result.setProbab(probab);

			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);

			char* pos3 = strstr(pos2 + 1, "=");
			float score;
			sscanf(pos3 + 1, "%f", &score);
			result.setScore(score);

			char* pos4 = strstr(pos3 + 1, "=");
			int alignedCols;
			sscanf(pos4 + 1, "%d", &alignedCols);
			result.setAlignedCols(alignedCols);

			char* pos5 = strstr(pos4 + 1, "=");
			float identities;
			sscanf(pos5 + 1, "%f", &identities);
			result.setIdentities(identities);

			result.setFirstStateReached(true);
			result.setSecondStateReached(false);
		}
	}
	hhrNRResultVector.push_back(result);
	fclose(inputFile);
}

void HHRNRImpl::write2Json() {

	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/HHRNR/";
	outFilename += "hhrNR.json";

	ofstream outputFile(outFilename.c_str());
	outputFile << "{" << "\n";
	for (int i = 0; i < hhrNRResultVector.size(); i++) {
		outputFile << "\"protein" << i << "\":{\n";
		outputFile << "\t\"proteinName\":\""
				<< hhrNRResultVector[i].getProteinName() << "\",\n";
		outputFile << "\t\"probab\":\"" << hhrNRResultVector[i].getProbab()
				<< "\",\n";
		outputFile << "\t\"eValue\":\"" << hhrNRResultVector[i].getExpect()
				<< "\",\n";
		outputFile << "\t\"score\":\"" << hhrNRResultVector[i].getScore()
				<< "\",\n";
		outputFile << "\t\"alignedCols\":\""
				<< hhrNRResultVector[i].getAlignedCols() << "\",\n";
		outputFile << "\t\"identities\":\""
				<< hhrNRResultVector[i].getIdentities() << "\",\n";
		outputFile << "\t\"similarity\":\""
				<< hhrNRResultVector[i].getSimilarities() << "\",\n";
		outputFile << "\t\"sumProbs\":\"" << hhrNRResultVector[i].getSumProbs()
				<< "\",\n";
		outputFile << "\t\"QuerySSPred\":\""
				<< hhrNRResultVector[i].getQuerySsPred() << "\",\n";
		outputFile << "\t\"QueryStart\":\""
				<< hhrNRResultVector[i].getQueryStart() << "\",\n";
		outputFile << "\t\"Query\":\"" << hhrNRResultVector[i].getQuery()
				<< "\",\n";
		outputFile << "\t\"QueryEnd\":\"" << hhrNRResultVector[i].getQueryEnd()
				<< "\",\n";
		outputFile << "\t\"QueryConsensus\":\""
				<< hhrNRResultVector[i].getQueryConsensus() << "\",\n";
		outputFile << "\t\"alignment\":\""
				<< hhrNRResultVector[i].getAlignment() << "\",\n";
		outputFile << "\t\"TargetStart\":\""
				<< hhrNRResultVector[i].getTargetStart() << "\",\n";
		outputFile << "\t\"TargetConsensus\":\""
				<< hhrNRResultVector[i].getTargetConsensus() << "\",\n";
		outputFile << "\t\"TargetEnd\":\""
				<< hhrNRResultVector[i].getTargetEnd() << "\",\n";
		outputFile << "\t\"target\":\"" << hhrNRResultVector[i].getTarget()
				<< "\",\n";
		outputFile << "\t\"tPred\":\"" << hhrNRResultVector[i].getTargetSsPred()
				<< "\"\n";
		outputFile << "},\n";
	}
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";

	outputFile.close();

}

void HHRNRImpl::setup3DCoords() {

}
void HHRNRImpl::findLocalAlign() {

}

void HHRNRImpl::write2PDB() {

}
void HHRNRImpl::findGlobalAlign() {

}
HHRNRImpl::~HHRNRImpl() {
	// TODO Auto-generated destructor stub
}

