/*
 * HHRImpl.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: cf797
 */

#include "HHRImpl.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

HHRImpl::HHRImpl(char* theRootName) :
		UtilityInterface(theRootName) {
	// TODO Auto-generated constructor stub

}
void HHRImpl::makeDirectory() {
	char cmd1[500];
	string outputFileFoldername(outputFileLocation);
	outputFileFoldername += "/";
	outputFileFoldername += rootName;
	outputFileFoldername += "/";
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd << endl;
	system(cmd1);

	char cmd2[500];
	string outputFileLocal3DFoldername(outputFileLocation);
	outputFileLocal3DFoldername += "/";
	outputFileLocal3DFoldername += rootName;
	outputFileLocal3DFoldername += "/local/";
	sprintf(cmd2, "mkdir -p %s", (char*) outputFileLocal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd2);

	char cmd3[500];
	string outputFileGlobal3DFoldername(outputFileLocation);
	outputFileGlobal3DFoldername += "/";
	outputFileGlobal3DFoldername += rootName;
	outputFileGlobal3DFoldername += "/Global/";
	sprintf(cmd3, "mkdir -p %s", (char*) outputFileGlobal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd3);
}
void HHRImpl::populateResultVector() {
	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.hhr";

	FILE* inputFile = fopen((char*) inFilename.c_str(), "r");
	if (inputFile == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}

	HHRResult result;

	while (fgets(line, 200, inputFile) != NULL) {

		if (strstr(line, ">") != NULL) {
			counter++;
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

			char* pos6 = strstr(pos5 + 1, "=");
			float similarity;
			sscanf(pos6 + 1, "%f", &similarity);
			result.setSimilarities(similarity);

			char* pos7 = strstr(pos6 + 1, "=");
			float sumProbs;
			sscanf(pos7 + 1, "%f", &sumProbs);
			result.setSumProbs(sumProbs);

			fgets(line, 200, inputFile); //blank

			//get the query
			fgets(line, 200, inputFile);
			char query_ss_pred[100];
			sscanf(line + 17, "%s", query_ss_pred);
			string strQuery_ss_pred(query_ss_pred);
			result.setQuerySsPred(strQuery_ss_pred);

			fgets(line, 200, inputFile);
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

			//get the TPred
			fgets(line, 200, inputFile);
			char tPred[100];
			sscanf(line + 17, "%s", tPred);
			string strTPred(tPred);
			result.setTargetSsPred(strTPred);

			counter++;
			string searchDBFilename(DBInfoLocation);
			searchDBFilename += proteinName;
			searchDBFilename += ".db";
			//cout<<searchDBFilename<<endl;

			hhrResultVector.push_back(result);
		}
	}

	fclose(inputFile);
}

void HHRImpl::write2Json() {

	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/";
	outFilename += "hhr.json";
	cout<<outFilename<<endl;
	ofstream outputFile(outFilename.c_str());

	outputFile << "{" << "\n";
	for (int i = 0; i < hhrResultVector.size(); i++) {
		outputFile << "\"protein" << i << "\":{\n";
		outputFile << "\t\"proteinName\":\""
				<< hhrResultVector[i].getProteinName() << "\",\n";
		outputFile << "\t\"probab\":\"" << hhrResultVector[i].getProbab()
				<< "\",\n";
		outputFile << "\t\"eValue\":\"" << hhrResultVector[i].getExpect()
				<< "\",\n";
		outputFile << "\t\"score\":\"" << hhrResultVector[i].getScore()
				<< "\",\n";
		outputFile << "\t\"alignedCols\":\""
				<< hhrResultVector[i].getAlignedCols() << "\",\n";
		outputFile << "\t\"identities\":\""
				<< hhrResultVector[i].getIdentities() << "\",\n";
		outputFile << "\t\"similarity\":\""
				<< hhrResultVector[i].getSimilarities() << "\",\n";
		outputFile << "\t\"sumProbs\":\"" << hhrResultVector[i].getSumProbs()
				<< "\",\n";
		outputFile << "\t\"QuerySSPred\":\""
				<< hhrResultVector[i].getQuerySsPred() << "\",\n";
		outputFile << "\t\"QueryStart\":\""
				<< hhrResultVector[i].getQueryStart() << "\",\n";
		outputFile << "\t\"Query\":\"" << hhrResultVector[i].getQuery()
				<< "\",\n";
		outputFile << "\t\"QueryEnd\":\"" << hhrResultVector[i].getQueryEnd()
				<< "\",\n";
		outputFile << "\t\"QueryConsensus\":\""
				<< hhrResultVector[i].getQueryConsensus() << "\",\n";
		outputFile << "\t\"alignment\":\"" << hhrResultVector[i].getAlignment()
				<< "\",\n";
		outputFile << "\t\"TargetStart\":\""
				<< hhrResultVector[i].getTargetStart() << "\",\n";
		outputFile << "\t\"TargetConsensus\":\""
				<< hhrResultVector[i].getTargetConsensus() << "\",\n";
		outputFile << "\t\"TargetEnd\":\"" << hhrResultVector[i].getTargetEnd()
				<< "\",\n";
		outputFile << "\t\"target\":\"" << hhrResultVector[i].getTarget()
				<< "\",\n";
		outputFile << "\t\"tPred\":\"" << hhrResultVector[i].getTargetSsPred()
				<< "\"\n";
		outputFile << "},\n";
	}
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";

	outputFile.close();

}

void HHRImpl::setup3DCoords() {
	for (int i = 0; i < hhrResultVector.size(); i++) {
		string proteinDBFilename(DBInfoLocation);
		proteinDBFilename += "/";
		proteinDBFilename += hhrResultVector[i].getProteinName();
		proteinDBFilename += ".db";
		FILE* fptr = fopen((char*) proteinDBFilename.c_str(), "r");
		if (fptr == NULL) {
			cout << proteinDBFilename << " can't open!" << endl;
		}
		char line[500];
		char proteinSeq[500];
		int seqLength;
		vector<float> Xs;
		vector<float> Ys;
		vector<float> Zs;
		while (fgets(line, 500, fptr) != NULL) {
			if (strstr(line, ">Reference Sequence Info:") != NULL) {
				fgets(line, 500, fptr);
				sscanf(line, "%s", proteinSeq);
				string s(proteinSeq);
				seqLength = s.size();
				//cout<<seqLength<<endl;
				continue;
			}
			if (strstr(line, ">Ca XYZ:") != NULL) {
				Xs.resize(seqLength + 1);
				Ys.resize(seqLength + 1);
				Zs.resize(seqLength + 1);

				float temp;
				for (int j = 1; j <= seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Xs[j] = temp;
				}
				for (int j = 1; j <= seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Ys[j] = temp;
				}
				for (int j = 1; j <= seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Zs[j] = temp;
				}
				break;
			}
		}
		fclose(fptr);
		hhrResultVector[i].setXCoords(Xs);
		hhrResultVector[i].setYCoords(Ys);
		hhrResultVector[i].setZCoords(Zs);

	}
}

void HHRImpl::findLocalAlign() {
	string proteinName;
	int subjectStart;
	string subject;
	int subjectEnd;
	for (int i = 0; i < hhrResultVector.size(); i++) {
		proteinName = hhrResultVector[i].getProteinName();
		subjectStart = hhrResultVector[i].getQueryStart();
		subject = hhrResultVector[i].getQuery();
		subjectEnd = hhrResultVector[i].getQueryEnd();
		vector<float> Xs = hhrResultVector[i].getXCoords();
		vector<float> Ys = hhrResultVector[i].getYCoords();
		vector<float> Zs = hhrResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/local/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += subject;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		for (int j = 1; j <= subject.size(); j++) {
			if (subject[j] == '-') {
				outJsonFile << "\"" << subject[j] << "\":\""
						<< "10000,10000,10000\"\n";
			} else {

				outJsonFile << "\"" << subject[j - 1] << "\":\""
						<< Xs[subjectStart + j - 1] << ","
						<< Ys[subjectStart + j - 1] << ","
						<< Zs[subjectStart + j - 1] << "\"\n";
			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();

	}
}
void HHRImpl::findGlobalAlign() {
	string proteinName;
	int subjectStart;
	string subject;
	int subjectEnd;
	int queryStart;
	string query;
	int queryEnd;
	for (int i = 0; i < hhrResultVector.size(); i++) {
		proteinName = hhrResultVector[i].getProteinName();
		queryStart = hhrResultVector[i].getQueryStart();
		query = hhrResultVector[i].getQuery();
		queryEnd = hhrResultVector[i].getQueryEnd();
		subjectStart = hhrResultVector[i].getTargetStart();
		subject = hhrResultVector[i].getTarget();
		subjectEnd = hhrResultVector[i].getTargetEnd();
		int headMore = queryStart - 1;
		int tailMore = proteinSeqLength - queryEnd;
		vector<float> Xs = hhrResultVector[i].getXCoords();
		vector<float> Ys = hhrResultVector[i].getYCoords();
		vector<float> Zs = hhrResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/Global/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += subject;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		while (headMore > 0) {
			outJsonFile << "\"" << "h" << "\":\"" << Xs[subjectStart - headMore]
					<< "," << Ys[subjectStart - headMore] << ","
					<< Zs[subjectStart - headMore] << "\"\n";
			headMore--;
		}
		for (int j = 1; j <= subject.size(); j++) {
			if (subject[j] == '-') {
				outJsonFile << "\"" << subject[j] << "\":\""
						<< "10000,10000,10000\"\n";
			} else {

				outJsonFile << "\"" << subject[j - 1] << "\":\""
						<< Xs[subjectStart + j - 1] << ","
						<< Ys[subjectStart + j - 1] << ","
						<< Zs[subjectStart + j - 1] << "\"\n";
			}

		}
		if (tailMore > 0) {
			for (int k = 1; k < tailMore; k++) {
				outJsonFile << "\"" << "t" << "\":\"" << Xs[subjectEnd + k]
						<< "," << Ys[subjectEnd + k] << ","
						<< Zs[subjectEnd + k] << "\"\n";
			}
		}
		outJsonFile << "}\n";
		outJsonFile.close();
	}

}

HHRImpl::~HHRImpl() {
	// TODO Auto-generated destructor stub
}

