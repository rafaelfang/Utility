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
#include <iomanip>
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
	outputFileFoldername += "/HHR/";
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd1 << endl;
	system(cmd1);

	char cmd2[500];
	string outputFileLocal3DFoldername(outputFileLocation);
	outputFileLocal3DFoldername += "/";
	outputFileLocal3DFoldername += rootName;
	outputFileLocal3DFoldername += "/HHR/local/";
	sprintf(cmd2, "mkdir -p %s", (char*) outputFileLocal3DFoldername.c_str());
	//cout << cmd2 << endl;
	system(cmd2);

	char cmd3[500];
	string outputFileGlobal3DFoldername(outputFileLocation);
	outputFileGlobal3DFoldername += "/";
	outputFileGlobal3DFoldername += rootName;
	outputFileGlobal3DFoldername += "/HHR/FullyExtended/";
	sprintf(cmd3, "mkdir -p %s", (char*) outputFileGlobal3DFoldername.c_str());
	//cout << cmd3 << endl;
	system(cmd3);

	char cmd4[500];
	string outputFilePdbFoldername(outputFileLocation);
	outputFilePdbFoldername += "/";
	outputFilePdbFoldername += rootName;
	outputFilePdbFoldername += "/HHR/pdbFiles/";
	sprintf(cmd4, "mkdir -p %s", (char*) outputFilePdbFoldername.c_str());
	//cout << cmd3 << endl;
	system(cmd4);
}
void HHRImpl::populateResultVector() {
	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.hhr";
	//cout << inFilename << endl;
	FILE* inputFile = fopen((char*) inFilename.c_str(), "r");
	if (inputFile == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}

	HHRResult result;

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
			hhrResultVector.push_back(result);
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
	hhrResultVector.push_back(result);
	fclose(inputFile);
}

void HHRImpl::write2Json() {

	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/HHR/";
	outFilename += "hhr.json";
	//cout << outFilename << endl;
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
		outputFile << "\t\"targetConf\":\""
				<< hhrResultVector[i].getConfidence() << "\",\n";
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
		char line[3000];
		char proteinSeq[3000];
		int seqLength;
		vector<float> Xs;
		vector<float> Ys;
		vector<float> Zs;
		vector<char> templateSeq;
		while (fgets(line, 3000, fptr) != NULL) {
			if (strstr(line, ">Reference Sequence Info:") != NULL) {
				fgets(line, 3000, fptr);
				sscanf(line, "%s", proteinSeq);
				string s(proteinSeq);
				seqLength = s.size();
				templateSeq.resize(seqLength);
				for (int j = 0; j < seqLength; j++) {
					templateSeq[j] = s[j];
				}
				//cout<<seqLength<<endl;
				continue;
			}
			if (strstr(line, ">Ca XYZ:") != NULL) {
				Xs.resize(seqLength);
				Ys.resize(seqLength);
				Zs.resize(seqLength);

				float temp;
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Xs[j] = temp;
				}
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Ys[j] = temp;
				}
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Zs[j] = temp;
				}
				break;
			}
		}
		fclose(fptr);
		hhrResultVector[i].setTemplateSeq(templateSeq);
		hhrResultVector[i].setXCoords(Xs);
		hhrResultVector[i].setYCoords(Ys);
		hhrResultVector[i].setZCoords(Zs);

	}
}

void HHRImpl::findLocalAlign() {
	string proteinName;
	int targetStart;
	string target;
	string query;
	int targetEnd;
	for (int i = 0; i < hhrResultVector.size(); i++) {
		proteinName = hhrResultVector[i].getProteinName();
		targetStart = hhrResultVector[i].getTargetStart();
		target = hhrResultVector[i].getTarget();
		query = hhrResultVector[i].getQuery();
		targetEnd = hhrResultVector[i].getTargetEnd();
		vector<float> Xs = hhrResultVector[i].getXCoords();
		vector<float> Ys = hhrResultVector[i].getYCoords();
		vector<float> Zs = hhrResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/HHR/local/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += query;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		for (int j = 0; j < query.size(); j++) {
			if (target[j] == '-' || query[j] == '-') {
				continue;
				//outJsonFile << "\"" << target[j-1] << "\":\""
				//		<< "10000,10000,10000\"\n";
			} else {

				outJsonFile << "\"" << query[j] << "\":\""
						<< Xs[targetStart + j] << "," << Ys[targetStart + j]
						<< "," << Zs[targetStart + j] << "\"\n";
			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();

	}
}

void HHRImpl::write2PDB() {
	string proteinName;
	int queryStart;
	string query;
	int queryEnd;
	int targetStart;
	string target;
	int targetEnd;
	for (int i = 0; i < hhrResultVector.size(); i++) {
		proteinName = hhrResultVector[i].getProteinName();
		queryStart = hhrResultVector[i].getQueryStart();
		query = hhrResultVector[i].getQuery();
		queryEnd = hhrResultVector[i].getQueryEnd();
		targetStart = hhrResultVector[i].getTargetStart();
		target = hhrResultVector[i].getTarget();
		targetEnd = hhrResultVector[i].getTargetEnd();
		int queryHeadMore = queryStart - 1;
		int queryTailMore = proteinSeqLength - queryEnd;
		vector<float> Xs = hhrResultVector[i].getXCoords();
		vector<float> Ys = hhrResultVector[i].getYCoords();
		vector<float> Zs = hhrResultVector[i].getZCoords();
		vector<char> templateSeq = hhrResultVector[i].getTemplateSeq();
		int targetHeadMore = targetStart - 1;
		int targetTailMore = Xs.size() - targetEnd;
		int headMore = 0;
		if (queryHeadMore > targetHeadMore) {
			headMore = targetHeadMore;
		} else {
			headMore = queryHeadMore;
		}

		int tailMore = 0;
		if (queryTailMore > targetTailMore) {
			tailMore = targetTailMore;
		} else {
			tailMore = queryTailMore;
		}
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/HHR/pdbFiles/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += query;
		protein3DCorrdsFilename += ".pdb";
		ofstream pdbFile((char*) protein3DCorrdsFilename.c_str(), ios::out);

		while (headMore > 0) {
			if (Xs[targetStart - headMore] != 10000
					&& Ys[targetStart - headMore] != 10000
					&& Zs[targetStart - headMore] != 10000) {
				pdbFile << "ATOM  ";				//record name
				pdbFile << right << setw(5) << targetStart - headMore; // atom serial number
				pdbFile << "  CA  "; //atom name
				pdbFile << setw(3)
						<< convertResidueName(
								originalProteinSeq[queryStart - headMore]);
				//pdbFile<<templateSeq[subjectStart - headMore];//for debug
				pdbFile << right << setw(6) << targetStart - headMore; // atom serial number
				pdbFile << "    ";
				pdbFile << right << setw(8.3) << Xs[targetStart - headMore];
				pdbFile << right << setw(8.3) << Ys[targetStart - headMore];
				pdbFile << right << setw(8.3) << Zs[targetStart - headMore];
				pdbFile << "  1.00  0.00\n";
			}

			headMore--;
		}
		for (int j = 0; j < target.size(); j++) {
			if (target[j] == '-' || query[j] == '-') {
				continue;
				//outJsonFile << "\"" << target[j - 1] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else {
				if (Xs[targetStart + j] != 10000 && Ys[targetStart + j] != 10000
						&& Zs[targetStart + j] != 10000) {
					pdbFile << "ATOM  ";				//record name
					pdbFile << right << setw(5) << targetStart + j; // atom serial number
					pdbFile << "  CA  "; //atom name
					pdbFile << setw(3) << convertResidueName(query[j]);
					//pdbFile<<query[ j - 1]; //for dubug
					pdbFile << right << setw(6) << targetStart + j; // atom serial number
					pdbFile << "    ";
					pdbFile << right << setw(8.3) << Xs[targetStart + j];
					pdbFile << right << setw(8.3) << Ys[targetStart + j];
					pdbFile << right << setw(8.3) << Zs[targetStart + j];
					pdbFile << "  1.00  0.00\n";
				}

			}

		}
		if (tailMore > 0) {
			for (int k = 1; k <= tailMore; k++) {
				if (Xs[targetEnd + k] != 10000 && Ys[targetEnd + k] != 10000
						&& Zs[targetEnd + k] != 10000) {
					pdbFile << "ATOM  ";				//record name
					pdbFile << right << setw(5) << targetEnd + k; // atom serial number
					pdbFile << "  CA  "; //atom name
					pdbFile << setw(3)
							<< convertResidueName(originalProteinSeq[queryEnd + k]);
					pdbFile << right << setw(6) << targetEnd + k; // atom serial number
					pdbFile << "    ";
					pdbFile << right << setw(8.3) << Xs[targetEnd + k];
					pdbFile << right << setw(8.3) << Ys[targetEnd + k];
					pdbFile << right << setw(8.3) << Zs[targetEnd + k];
					pdbFile << "  1.00  0.00\n";
				}

			}
		}
		pdbFile << "TER\n";
		pdbFile.close();
	}
}
void HHRImpl::findGlobalAlign() {
	string proteinName;
	int queryStart;
	string query;
	int queryEnd;
	int targetStart;
	string target;
	int targetEnd;
	for (int i = 0; i < hhrResultVector.size(); i++) {
		proteinName = hhrResultVector[i].getProteinName();
		queryStart = hhrResultVector[i].getQueryStart();
		query = hhrResultVector[i].getQuery();
		queryEnd = hhrResultVector[i].getQueryEnd();
		targetStart = hhrResultVector[i].getTargetStart();
		target = hhrResultVector[i].getTarget();
		targetEnd = hhrResultVector[i].getTargetEnd();
		int queryHeadMore = queryStart - 1;
		int queryTailMore = proteinSeqLength - queryEnd;
		vector<float> Xs = hhrResultVector[i].getXCoords();
		vector<float> Ys = hhrResultVector[i].getYCoords();
		vector<float> Zs = hhrResultVector[i].getZCoords();
		vector<char> templateSeq = hhrResultVector[i].getTemplateSeq();
		int targetHeadMore = targetStart - 1;
		int targetTailMore = Xs.size() - targetEnd;
		int headMore = 0;
		if (queryHeadMore > targetHeadMore) {
			headMore = targetHeadMore;
		} else {
			headMore = queryHeadMore;
		}

		int tailMore = 0;
		if (queryTailMore > targetTailMore) {
			tailMore = targetTailMore;
		} else {
			tailMore = queryTailMore;
		}
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/HHR/FullyExtended/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += query;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		while (headMore > 0) {
			outJsonFile << "\"" << originalProteinSeq[queryStart - headMore]
					<< "\":\"" << Xs[targetStart - headMore] << ","
					<< Ys[targetStart - headMore] << ","
					<< Zs[targetStart - headMore] << "\"\n";
			headMore--;
		}
		for (int j = 0; j < target.size(); j++) {
			if (target[j] == '-' || query[j] == '-') {
				continue;
				//outJsonFile << "\"" << target[j - 1] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else {

				outJsonFile << "\"" << target[j] << "\":\""
						<< Xs[targetStart + j] << "," << Ys[targetStart + j]
						<< "," << Zs[targetStart + j] << "\"\n";
			}

		}
		if (tailMore > 0) {
			for (int k = 1; k <= tailMore; k++) {
				outJsonFile << "\"" << originalProteinSeq[queryEnd + k] << "\":\""
						<< Xs[targetEnd + k] << "," << Ys[targetEnd + k] << ","
						<< Zs[targetEnd + k] << "\"\n";
			}
		}
		outJsonFile << "}\n";
		outJsonFile.close();
	}

}

HHRImpl::~HHRImpl() {
	// TODO Auto-generated destructor stub
}

