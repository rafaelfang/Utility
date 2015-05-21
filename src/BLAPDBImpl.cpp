/*
 * BLAPDBImpl.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#include "BLAPDBImpl.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

BLAPDBImpl::BLAPDBImpl(char* theRootName) :
		UtilityInterface(theRootName) {
	// TODO Auto-generated constructor stub

}
void BLAPDBImpl::makeDirectory() {
	char cmd1[500];
	string outputFileFoldername(outputFileLocation);
	outputFileFoldername += "/";
	outputFileFoldername += rootName;
	outputFileFoldername += "/BLAPDB/";
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd << endl;
	system(cmd1);

	char cmd2[500];
	string outputFileLocal3DFoldername(outputFileLocation);
	outputFileLocal3DFoldername += "/";
	outputFileLocal3DFoldername += rootName;
	outputFileLocal3DFoldername += "/BLAPDB/local/";
	sprintf(cmd2, "mkdir -p %s", (char*) outputFileLocal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd2);

	char cmd3[500];
	string outputFileGlobal3DFoldername(outputFileLocation);
	outputFileGlobal3DFoldername += "/";
	outputFileGlobal3DFoldername += rootName;
	outputFileGlobal3DFoldername += "/BLAPDB/FullyExtended/";
	sprintf(cmd3, "mkdir -p %s", (char*) outputFileGlobal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd3);

	char cmd4[500];
	string outputFilePdb3DFoldername(outputFileLocation);
	outputFilePdb3DFoldername += "/";
	outputFilePdb3DFoldername += rootName;
	outputFilePdb3DFoldername += "/BLAPDB/pdbFiles/";
	sprintf(cmd4, "mkdir -p %s", (char*) outputFilePdb3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd4);
}
void BLAPDBImpl::populateResultVector() {

	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.blaPDB";

	FILE* fptr = fopen((char*) inFilename.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}
	BLAPDBResult result;

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
			string searchDBFilename(DBInfoLocation);
			searchDBFilename += result.getProteinName();
			searchDBFilename += ".db";
			//find the local alignment
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			blaPDBResultVector.push_back(result);
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

			//first write the protein information to json
			string searchDBFilename(DBInfoLocation);
			searchDBFilename += result.getProteinName();
			searchDBFilename += ".db";
			//find the local alignment
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			blaPDBResultVector.push_back(result);
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
	string searchDBFilename(DBInfoLocation);
	searchDBFilename += result.getProteinName();
	searchDBFilename += ".db";
	//find the local alignment
	//aaaaaaaaaaaaaa
	//aaaaaaaaaaaaaa
	//aaaaaaaaaaaaaa

	blaPDBResultVector.push_back(result);

	fclose(fptr);

}
void BLAPDBImpl::write2Json() {

	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/BLAPDB/";
	outFilename += "blaPDB.json";
	//cout<<outFilename<<endl;
	ofstream outputFile(outFilename.c_str());

	outputFile << "{" << "\n";

	for (int i = 0; i < blaPDBResultVector.size(); i++) {

		outputFile << "\"protein" << i << "\":{\n";
		outputFile << "\t\"proteinName\":\""
				<< blaPDBResultVector[i].getProteinName() << "\",\n";
		outputFile << "\t\"Length\":\"" << blaPDBResultVector[i].getLength()
				<< "\",\n";
		outputFile << "\t\"Score\":\"" << blaPDBResultVector[i].getScore()
				<< "\",\n";
		outputFile << "\t\"Expect\":\"" << blaPDBResultVector[i].getExpect()
				<< "\",\n";
		outputFile << "\t\"Identities\":\""
				<< blaPDBResultVector[i].getIdentities() << "\",\n";
		outputFile << "\t\"Positives\":\""
				<< blaPDBResultVector[i].getPositives() << "\",\n";
		outputFile << "\t\"Gaps\":\"" << blaPDBResultVector[i].getGaps()
				<< "\",\n";
		outputFile << "\t\"QueyStart\":\""
				<< blaPDBResultVector[i].getQueryStart() << "\",\n";
		outputFile << "\t\"Query\":\"" << blaPDBResultVector[i].getQuery()
				<< "\",\n";
		outputFile << "\t\"QueryEnd\":\"" << blaPDBResultVector[i].getQueryEnd()
				<< "\",\n";
		outputFile << "\t\"Alignment\":\""
				<< blaPDBResultVector[i].getAlignment() << "\",\n";
		outputFile << "\t\"SubjectStart\":\""
				<< blaPDBResultVector[i].getSubjectStart() << "\",\n";
		outputFile << "\t\"Subject\":\"" << blaPDBResultVector[i].getSubject()
				<< "\",\n";
		outputFile << "\t\"SubjectEnd\":\""
				<< blaPDBResultVector[i].getSubjectEnd() << "\"\n";
		outputFile << "},\n";
	}
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";

	outputFile.close();

}

void BLAPDBImpl::setup3DCoords() {
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		string proteinDBFilename(DBInfoLocation);
		proteinDBFilename += "/";
		proteinDBFilename += blaPDBResultVector[i].getProteinName();
		proteinDBFilename += ".db";
		FILE* fptr = fopen((char*) proteinDBFilename.c_str(), "r");
		if (fptr == NULL) {
			cout << proteinDBFilename << " can't open!" << endl;
		}
		char line[3000];
		char proteinSeq[3000];
		int seqLength;
		vector<float> Xs;
		vector<float> Ys;
		vector<float> Zs;
		while (fgets(line, 3000, fptr) != NULL) {
			if (strstr(line, ">Reference Sequence Info:") != NULL) {
				fgets(line, 3000, fptr);
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
		blaPDBResultVector[i].setXCoords(Xs);
		blaPDBResultVector[i].setYCoords(Ys);
		blaPDBResultVector[i].setZCoords(Zs);

	}
}
void BLAPDBImpl::findLocalAlign() {
	string proteinName;
	int subjectStart;
	string subject;
	string query;
	int subjectEnd;
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		proteinName = blaPDBResultVector[i].getProteinName();
		subjectStart = blaPDBResultVector[i].getSubjectStart();
		subject = blaPDBResultVector[i].getSubject();
		query = blaPDBResultVector[i].getQuery();
		subjectEnd = blaPDBResultVector[i].getSubjectEnd();
		vector<float> Xs = blaPDBResultVector[i].getXCoords();
		vector<float> Ys = blaPDBResultVector[i].getYCoords();
		vector<float> Zs = blaPDBResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/BLAPDB/local/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += query;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		for (int j = 1; j <= subject.size(); j++) {
			if (subject[j - 1] == '-' || query[j - 1] == '-') {
				continue;
				//outJsonFile << "\"" << subject[j - 1] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else {

				outJsonFile << "\"" << query[j - 1] << "\":\""
						<< Xs[subjectStart + j - 1] << ","
						<< Ys[subjectStart + j - 1] << ","
						<< Zs[subjectStart + j - 1] << "\"\n";
			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();

	}
}

void BLAPDBImpl::write2PDB() {
	string proteinName;
	int subjectStart;
	string subject;
	string query;
	int subjectEnd;
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		proteinName = blaPDBResultVector[i].getProteinName();
		subjectStart = blaPDBResultVector[i].getSubjectStart();
		subject = blaPDBResultVector[i].getSubject();
		query = blaPDBResultVector[i].getQuery();
		subjectEnd = blaPDBResultVector[i].getSubjectEnd();
		vector<float> Xs = blaPDBResultVector[i].getXCoords();
		vector<float> Ys = blaPDBResultVector[i].getYCoords();
		vector<float> Zs = blaPDBResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/BLAPDB/pdbFiles/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += query;
		protein3DCorrdsFilename += ".pdb";
		ofstream pdbFile((char*) protein3DCorrdsFilename.c_str(), ios::out);

		for (int j = 1; j <= subject.size(); j++) {
			if (subject[j - 1] == '-' || query[j - 1] == '-') {
				continue;
				//outJsonFile << "\"" << subject[j - 1] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else {

				pdbFile << "ATOM" << setw(6) //record name
						<< subjectStart + j - 1<< setw(5) // atom serial number
						<< "CA"<< setw(4) //atom name
						<< setw(1) //alternate location indicator
						<< convertResidueName(query.at(j - 1))
						<< setw(3) //residue name
						<< subjectStart + j - 1
						<< setw(5) // atom serial number
						<< Xs[subjectStart + j - 1] << setw(8)
						<< Ys[subjectStart + j - 1] << setw(8)
						<< Zs[subjectStart + j - 1] << setw(8) << "1.00 0.00\n";

			}

		}
		pdbFile << "TER\n";
		pdbFile.close();

	}

}
void BLAPDBImpl::findGlobalAlign() {
	string proteinName;
	int subjectStart;
	string subject;
	int subjectEnd;
	int queryStart;
	string query;
	int queryEnd;
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		proteinName = blaPDBResultVector[i].getProteinName();
		queryStart = blaPDBResultVector[i].getQueryStart();
		query = blaPDBResultVector[i].getQuery();
		queryEnd = blaPDBResultVector[i].getQueryEnd();
		subjectStart = blaPDBResultVector[i].getSubjectStart();
		subject = blaPDBResultVector[i].getSubject();
		subjectEnd = blaPDBResultVector[i].getSubjectEnd();
		int queryHeadMore = queryStart - 1;
		int queryTailMore = proteinSeqLength - queryEnd;
		vector<float> Xs = blaPDBResultVector[i].getXCoords();
		vector<float> Ys = blaPDBResultVector[i].getYCoords();
		vector<float> Zs = blaPDBResultVector[i].getZCoords();
		int subjectHeadMore = subjectStart - 1;
		int subjectTailMore = Xs.size() - subjectEnd;
		int headMore = 0;

		if (queryHeadMore > subjectHeadMore) {
			headMore = subjectHeadMore;
		} else {
			headMore = queryHeadMore;
		}

		int tailMore = 0;
		if (queryTailMore > subjectTailMore) {
			tailMore = subjectTailMore;
		} else {
			tailMore = queryTailMore;
		}
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/BLAPDB/FullyExtended/";
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
			if (subject[j - 1] == '-' || query[j - 1] == '-') {
				continue;
				//outJsonFile << "\"" << subject[j] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else {

				outJsonFile << "\"" << query[j - 1] << "\":\""
						<< Xs[subjectStart + j - 1] << ","
						<< Ys[subjectStart + j - 1] << ","
						<< Zs[subjectStart + j - 1] << "\"\n";
			}

		}
		//cout<<"Tailmore"<<tailMore<<endl;;
		if (tailMore > 0) {
			for (int k = 1; k <= tailMore; k++) {
				outJsonFile << "\"" << "t" << "\":\"" << Xs[subjectEnd + k]
						<< "," << Ys[subjectEnd + k] << ","
						<< Zs[subjectEnd + k] << "\"\n";
			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();
	}

}

BLAPDBImpl::~BLAPDBImpl() {
// TODO Auto-generated destructor stub
}

