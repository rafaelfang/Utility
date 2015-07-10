/*
 * CNFSearchImpl.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: cf797
 */

#include "CNFSearchImpl.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

CNFSearchImpl::CNFSearchImpl(char* theRootName) :
		UtilityInterface(theRootName) {
	// TODO Auto-generated constructor stub

}

void CNFSearchImpl::makeDirectory() {
	char cmd1[500];
	string outputFileFoldername(outputFileLocation);
	outputFileFoldername += "/";
	outputFileFoldername += rootName;
	outputFileFoldername += "/CNFSearch/";
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd << endl;
	system(cmd1);

	char cmd2[500];
	string outputFileLocal3DFoldername(outputFileLocation);
	outputFileLocal3DFoldername += "/";
	outputFileLocal3DFoldername += rootName;
	outputFileLocal3DFoldername += "/CNFSearch/local/";
	sprintf(cmd2, "mkdir -p %s", (char*) outputFileLocal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd2);

	char cmd3[500];
	string outputFileGlobal3DFoldername(outputFileLocation);
	outputFileGlobal3DFoldername += "/";
	outputFileGlobal3DFoldername += rootName;
	outputFileGlobal3DFoldername += "/CNFSearch/FullyExtended/";
	sprintf(cmd3, "mkdir -p %s", (char*) outputFileGlobal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd3);

	char cmd4[500];
	string outputFilePdb3DFoldername(outputFileLocation);
	outputFilePdb3DFoldername += "/";
	outputFilePdb3DFoldername += rootName;
	outputFilePdb3DFoldername += "/CNFSearch/pdbFiles/";
	sprintf(cmd4, "mkdir -p %s", (char*) outputFilePdb3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd4);
}
void CNFSearchImpl::populateResultVector() {

	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.rank";

	FILE* fptr = fopen((char*) inFilename.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}
	CNFSearchResult result;

	while (fgets(line, 500, fptr) != NULL) {
		if ((strstr(line, ">") != NULL) && !result.isFirstStateReached()) {
			//set first block information
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			for (int i = 0; i < strlen(proteinName); i++) {
				proteinName[i] = toupper(proteinName[i]);
			}
			string proteinNameStr(proteinName);
			proteinNameStr.insert(4, "_");
			result.setProteinName(proteinNameStr);

			//set first state reached
			result.setFirstStateReached(true);
			//cout<<result.getProteinName()<<endl;
		}
		if ((strstr(line, "T sse_real") != NULL)
				&& !result.isSecondStateReached()) {
			//set second block information
			char targetSseReal[500];
			char* pos1 = strstr(line, "T sse_real");
			sscanf(pos1 + 10, "%s", targetSseReal);
			string _targetSseReal(targetSseReal);
			//cout<<_targetSseReal<<endl;
			result.setTargetSseReal(_targetSseReal);
			//cout<<result.getTargetSseReal()<<endl;

			fgets(line, 500, fptr);
			char targetAccReal[500];
			char* pos2 = strstr(line, "T acc_real");
			sscanf(pos2 + 10, "%s", targetAccReal);
			string _targetAccReal(targetAccReal);
			//cout<<_targetAccReal<<endl;
			result.setTargetAccReal(_targetAccReal);
			//cout<<result.getTargetAccReal()<<endl;

			fgets(line, 500, fptr);
			char targetAlignment[500];
			char* pos3 = strstr(line, "T");
			int targetStart;
			int targetEnd;
			sscanf(pos3 + 10, " %d %s %d", &targetStart, targetAlignment,
					&targetEnd);
			string _targetAlignment(targetAlignment);
			result.setTargetStart(targetStart);
			result.setTargetEnd(targetEnd);
			result.setTargetAlignment(_targetAlignment);
			//cout<<targetStart<<_targetAlignment<<targetEnd<<endl;
			//cout<<result.getTargetAlignment()<<"arfasdfasdf"<<endl;
			char alignmentPart[500];
			fgets(alignmentPart, 500, fptr);
			string _alignmentPart(alignmentPart);
			result.setAlignmentPart(_alignmentPart);
			//cout<<_alignmentPart<<endl;

			char sequenceAlignment[500];
			fgets(line, 500, fptr);
			char* pos4 = strstr(line, "S");
			int sequenceStart;
			int sequenceEnd;
			sscanf(pos4 + 10, "%d %s %d", &sequenceStart, sequenceAlignment,
					&sequenceEnd);
			string _sequenceAlignment(sequenceAlignment);
			result.setSequenceStart(sequenceStart);
			result.setSequenceEnd(sequenceEnd);
			result.setSequenceAlignment(_sequenceAlignment);
			//cout<<sequenceStart<<_sequenceAlignment<<sequenceEnd<<endl;

			char sequenceAccPred[500];
			fgets(line, 500, fptr);
			char* pos5 = strstr(line, "S acc_pred");
			sscanf(pos5 + 10, "%s", sequenceAccPred);
			string _sequenceAccPred(sequenceAccPred);
			//cout<<_sequenceAccPred<<endl;
			result.setSequenceAccPred(_sequenceAccPred);

			char sequenceAccConf[500];
			fgets(line, 500, fptr);
			char* pos6 = strstr(line, "S acc_conf");
			sscanf(pos6 + 10, "%s", sequenceAccConf);
			string _sequenceAccConf(sequenceAccConf);
			//cout<<_sequenceAccConf<<endl;
			result.setSequenceAccConf(_sequenceAccConf);

			char sequenceSsePred[500];
			fgets(line, 500, fptr);
			char* pos7 = strstr(line, "S sse_pred");
			sscanf(pos7 + 10, "%s", sequenceSsePred);
			string _sequenceSsePred(sequenceSsePred);
			//cout<<_sequenceSsePred<<endl;
			result.setSequenceSsePred(_sequenceSsePred);

			char sequenceSseConf[500];
			fgets(line, 500, fptr);
			char* pos8 = strstr(line, "S sse_conf");
			sscanf(pos8 + 10, "%s", sequenceSseConf);
			string _sequenceSseConf(sequenceSseConf);
			//cout<<_sequenceSseConf<<endl;
			result.setSequenceSseConf(_sequenceSseConf);

			//set second state reached
			result.setSecondStateReached(true);
		}

		if ((strstr(line, "T sse_real") != NULL)
				&& result.isSecondStateReached()) {
			//update second block information, so in this case
			//query, alignment and subject should be long string
			//the queryEnd and subjectEnd should also be updated

			char targetSseRealAppend[500];
			char* pos1 = strstr(line, "T sse_real");
			sscanf(pos1 + 10, "%s", targetSseRealAppend);
			string _targetSseRealAppend(targetSseRealAppend);

			string _targetSseRealNew = result.getTargetSseReal()
					+ _targetSseRealAppend;
			//cout<<_targetSseRealNew<<endl;
			result.setTargetSseReal(_targetSseRealNew);

			fgets(line, 500, fptr);
			char targetAccRealAppend[500];
			char* pos2 = strstr(line, "T acc_real");
			sscanf(pos2 + 10, "%s", targetAccRealAppend);
			string _targetAccRealAppend(targetAccRealAppend);
			string _targetAccRealNew = result.getTargetAccReal()
					+ _targetAccRealAppend;
			//cout<<_targetAccRealNew<<endl;
			result.setTargetAccReal(_targetAccRealNew);

			fgets(line, 500, fptr);
			int nInt1, nInt2;
			char targetAlignmentAppend[500];

			char* pos3 = strstr(line, "T");
			sscanf(pos3 + 10, "%d %s %d", &nInt1, targetAlignmentAppend,
					&nInt2);
			string _targetAlignmentNew = result.getTargetAlignment();
			_targetAlignmentNew += targetAlignmentAppend;
			result.setTargetAlignment(_targetAlignmentNew);
			result.setTargetEnd(nInt2);
			//cout << result.getTargetStart() << result.getTargetAlignment()
			//		<< result.getTargetEnd() << endl;

			fgets(line, 500, fptr);
			string newAlignmentPart = result.getAlignmentPart();
			newAlignmentPart += line;
			result.setAlignmentPart(newAlignmentPart);
			//cout<<result.getAlignmentPart()<<endl;

			fgets(line, 500, fptr);
			char sequenceAlignmentAppend[200];
			char* pos4 = strstr(line, "S");
			sscanf(pos4 + 10, "%d %s %d", &nInt1, sequenceAlignmentAppend,
					&nInt2);
			string sequencePartNew = result.getSequenceAlignment();
			sequencePartNew += sequenceAlignmentAppend;
			result.setSequenceAlignment(sequencePartNew);
			result.setSequenceEnd(nInt2);
			//cout<<result.getSequenceAlignment()<<result.getSequenceEnd()<<endl;

			fgets(line, 500, fptr);
			char sequenceAccPredAppend[500];
			char* pos5 = strstr(line, "S acc_pred");
			sscanf(pos5 + 10, "%s", sequenceAccPredAppend);
			string _sequenceAccPredAppend(sequenceAccPredAppend);

			string _sequenceAccPredNew = result.getSequenceAccPred()
					+ _sequenceAccPredAppend;
			result.setSequenceAccPred(_sequenceAccPredNew);
			//cout<< result.getSequenceAccPred()<<endl;

			fgets(line, 500, fptr);
			char sequenceAccConfAppend[500];
			char* pos6 = strstr(line, "S acc_conf");
			sscanf(pos6 + 10, "%s", sequenceAccConfAppend);
			string _sequenceAccConfAppend(sequenceAccConfAppend);
			string _sequenceAccConfNew = result.getSequenceAccConf()
					+ _sequenceAccConfAppend;
			result.setSequenceAccConf(_sequenceAccConfNew);
			//cout<<result.getSequenceAccConf()<<endl;

			fgets(line, 500, fptr);
			char sequenceSsePredAppend[500];
			char* pos7 = strstr(line, "S sse_pred");
			sscanf(pos7 + 10, "%s", sequenceSsePredAppend);
			string _sequenceSsePredAppend(sequenceSsePredAppend);
			string _sequenceSsePredNew = result.getSequenceSsePred()
					+ _sequenceSsePredAppend;
			result.setSequenceSsePred(_sequenceSsePredNew);
			//cout<<result.getSequenceSsePred()<<endl;

			fgets(line, 500, fptr);
			char sequenceSseConfAppend[500];
			char* pos8 = strstr(line, "S sse_conf");
			sscanf(pos8 + 10, "%s", sequenceSseConfAppend);
			string _sequenceSseConfAppend(sequenceSseConfAppend);
			string _sequenceSseConfNew = result.getSequenceSseConf()
					+ _sequenceSseConfAppend;
			result.setSequenceSseConf(_sequenceSseConfNew);
			//cout<<result.getSequenceSseConf()<<endl;

		}

		if ((strstr(line, ">") != NULL) && result.isFirstStateReached()) {

			//first save the protein information to vector

			cnfSearchResultVector.push_back(result);

			//then update the information set the first state flag
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			//cout<<proteinName<<endl;
			for (int i = 0; i < strlen(proteinName); i++) {
				proteinName[i] = toupper(proteinName[i]);
			}
			string proteinNameStr(proteinName);
			proteinNameStr.insert(4, "_");
			result.setProteinName(proteinNameStr);
			//cout<<result.getProteinName()<<endl;
			//unset second block flag
			result.setFirstStateReached(true);
			result.setSecondStateReached(false);

		}

	}

	cnfSearchResultVector.push_back(result);

	fclose(fptr);

}

void CNFSearchImpl::write2Json() {
	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/CNFSearch/";
	outFilename += "cnfSearch.json";
	//cout << outFilename << endl;
	ofstream outputFile(outFilename.c_str());

	outputFile << "{" << "\n";
	for (int i = 1; i < cnfSearchResultVector.size(); i++) {
		outputFile << "\"protein" << i << "\":{\n";
		outputFile << "\t\"proteinName\":\""
				<< cnfSearchResultVector[i].getProteinName() << "\",\n";
		outputFile << "\t\"Target sse_real\":\""
				<< cnfSearchResultVector[i].getTargetSseReal() << "\",\n";

		outputFile << "\t\"Target acc_real\":\""
				<< cnfSearchResultVector[i].getTargetAccReal() << "\",\n";

		outputFile << "\t\"TargetStart\":\""
				<< cnfSearchResultVector[i].getTargetStart() << "\",\n";
		outputFile << "\t\"Target Alignment\":\""
				<< cnfSearchResultVector[i].getTargetAlignment() << "\",\n";
		outputFile << "\t\"TargetEnd\":\""
				<< cnfSearchResultVector[i].getTargetEnd() << "\",\n";
		outputFile << "\t\"alignment part\":\""
				<< cnfSearchResultVector[i].getAlignmentPart() << "\",\n";
		outputFile << "\t\"SequenceStart\":\""
				<< cnfSearchResultVector[i].getSequenceStart() << "\",\n";
		outputFile << "\t\"Sequence Alignment\":\""
				<< cnfSearchResultVector[i].getSequenceAlignment() << "\",\n";
		outputFile << "\t\"SequenceEnd\":\""
				<< cnfSearchResultVector[i].getSequenceEnd() << "\",\n";

		outputFile << "\t\"sequence acc_pred\":\""
				<< cnfSearchResultVector[i].getSequenceAccPred() << "\",\n";
		outputFile << "\t\"sequence acc_conf\":\""
				<< cnfSearchResultVector[i].getSequenceAccConf() << "\",\n";

		outputFile << "\t\"sequence sse_pred\":\""
				<< cnfSearchResultVector[i].getSequenceSsePred() << "\",\n";
		outputFile << "\t\"sequence sse_conf\":\""
				<< cnfSearchResultVector[i].getSequenceSseConf() << "\",\n";

		outputFile << "},\n";
	}
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";

	outputFile.close();
}

void CNFSearchImpl::setup3DCoords() {
	for (int i = 1; i < cnfSearchResultVector.size(); i++) {
		string proteinDBFilename(DBInfoLocation);
		proteinDBFilename += "/";
		proteinDBFilename += cnfSearchResultVector[i].getProteinName();
		proteinDBFilename += ".db";
		//cout<<cnfSearchResultVector[i].getProteinName()<<endl;
		FILE* fptr = fopen((char*) proteinDBFilename.c_str(), "r");
		if (fptr == NULL) {
			cout << proteinDBFilename << " can't open!" << endl;
			continue;
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
				//cout<<proteinSeq<<"::::"<<seqLength<<endl;
				continue;
			}
			if (strstr(line, ">Ca XYZ:") != NULL) {
				Xs.resize(seqLength);
				Ys.resize(seqLength);
				Zs.resize(seqLength);

				float temp;
				//cout << proteinDBFilename << endl;
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Xs[j] = temp;
					//cout<< Xs[j] << " ";
				}
				//cout<<"==============X========"<<endl;
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Ys[j] = temp;
					//cout<< Ys[j] << " ";
				}
				//cout<<"==============Y========"<<endl;
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Zs[j] = temp;
					//cout<< Zs[j] << " ";
				}
				//cout<<"==============Z========"<<endl;
				break;
			}
		}
		fclose(fptr);
		//cout << "---------" << seqLength << endl;
		cnfSearchResultVector[i].setTemplateSeq(templateSeq);
		cnfSearchResultVector[i].setXCoords(Xs);
		cnfSearchResultVector[i].setYCoords(Ys);
		cnfSearchResultVector[i].setZCoords(Zs);

	}
}
void CNFSearchImpl::findLocalAlign() {
	string proteinName;
	int targetStart;
	string targetAlignment;
	string sequenceAlignment;
	int targetEnd;
	for (int i = 1; i < cnfSearchResultVector.size(); i++) {
		vector<float> XCoords = cnfSearchResultVector[i].getXCoords();
		if (XCoords.empty()) {
			cout << cnfSearchResultVector[i].getProteinName()
					<< " this db file not exist" << endl;
			continue;
		}
		proteinName = cnfSearchResultVector[i].getProteinName();
		targetStart = cnfSearchResultVector[i].getTargetStart();
		targetAlignment = cnfSearchResultVector[i].getTargetAlignment();
		sequenceAlignment = cnfSearchResultVector[i].getSequenceAlignment();
		targetEnd = cnfSearchResultVector[i].getTargetEnd();
		vector<float> Xs = cnfSearchResultVector[i].getXCoords();
		vector<float> Ys = cnfSearchResultVector[i].getYCoords();
		vector<float> Zs = cnfSearchResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/CNFSearch/local/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += sequenceAlignment;
		protein3DCorrdsFilename += ".json";
		//cout<<protein3DCorrdsFilename<<endl;
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";

		int offset = 0;
		for (int j = 0; j < sequenceAlignment.size(); j++) {
			if (targetAlignment[j] == '-' && sequenceAlignment[j] != '-') {
				continue;
				//outJsonFile << "\"" << target[j-1] << "\":\""
				//		<< "10000,10000,10000\"\n";
			} else if (targetAlignment[j] != '-'
					&& sequenceAlignment[j] == '-') {
				offset++;
				continue;
			} else if (targetAlignment[j] == '-'
					&& sequenceAlignment[j] == '-') {
				continue;
			} else {
				outJsonFile << "\"" << sequenceAlignment[j] << "\":\""
						<< Xs[targetStart + offset - 1] << ","
						<< Ys[targetStart + offset - 1] << ","
						<< Zs[targetStart + offset - 1] << "\"\n";
				offset++;
			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();

	}
}
void CNFSearchImpl::write2PDB() {

	string proteinName;
	int targetStart;
	string targetAlignment;
	int targetEnd;
	int sequenceStart;
	string sequenceAlignment;
	int sequenceEnd;
	for (int i = 1; i < cnfSearchResultVector.size(); i++) {
		vector<float> XCoords = cnfSearchResultVector[i].getXCoords();
		if (XCoords.empty()) {
			cout << cnfSearchResultVector[i].getProteinName()
					<< " this db file not exist" << endl;
			continue;
		}
		proteinName = cnfSearchResultVector[i].getProteinName();
		targetStart = cnfSearchResultVector[i].getTargetStart();
		targetAlignment = cnfSearchResultVector[i].getTargetAlignment();
		targetEnd = cnfSearchResultVector[i].getTargetEnd();
		sequenceStart = cnfSearchResultVector[i].getSequenceStart();
		sequenceAlignment = cnfSearchResultVector[i].getSequenceAlignment();
		sequenceEnd = cnfSearchResultVector[i].getSequenceEnd();
		//cout << proteinName << endl;
		//targetStart<<targetAlignment<<targetEnd<<sequenceStart<<sequenceAlignment<<sequenceEnd<<endl;
		int targetHeadMore = targetStart - 1;
		int targetTailMore = proteinSeqLength - targetEnd;
		vector<float> Xs = cnfSearchResultVector[i].getXCoords();
		vector<float> Ys = cnfSearchResultVector[i].getYCoords();
		vector<float> Zs = cnfSearchResultVector[i].getZCoords();
		vector<char> templateSeq = cnfSearchResultVector[i].getTemplateSeq();
		int sequenceHeadMore = sequenceStart - 1;
		int sequenceTailMore = Xs.size() - sequenceEnd;
		int headMore = 0;
		if (targetHeadMore > sequenceHeadMore) {
			headMore = sequenceHeadMore;
		} else {
			headMore = targetHeadMore;
		}

		int tailMore = 0;
		if (targetTailMore > sequenceTailMore) {
			tailMore = sequenceTailMore;
		} else {
			tailMore = targetTailMore;
		}
		//cout<<tailMore<<"tailmore"<<endl;
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/CNFSearch/pdbFiles/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += sequenceAlignment;
		protein3DCorrdsFilename += ".pdb";
		ofstream pdbFile((char*) protein3DCorrdsFilename.c_str(), ios::out);

		while (headMore > 0) {
			if (Xs[targetStart - headMore - 1] != 10000
					&& Ys[targetStart - headMore - 1] != 10000
					&& Zs[targetStart - headMore - 1] != 10000) {
				pdbFile << "ATOM  ";				//record name
				pdbFile << right << setw(5) << sequenceStart - headMore; // atom serial number
				pdbFile << "  CA  "; //atom name
				pdbFile << setw(3)
						<< convertResidueName(
								originalProteinSeq[sequenceStart - headMore - 1]);
				//pdbFile<<templateSeq[subjectStart - headMore];//for debug
				pdbFile << right << setw(6) << sequenceStart - headMore; // atom serial number
				pdbFile << "    ";
				pdbFile << right << setw(8.3) << Xs[targetStart - headMore - 1];
				pdbFile << right << setw(8.3) << Ys[targetStart - headMore - 1];
				pdbFile << right << setw(8.3) << Zs[targetStart - headMore - 1];
				pdbFile << "  1.00  0.00\n";
			}

			headMore--;
		}
		int targetPos = 1;
		int sequencePos = 1;

		for (int j = 0; j < targetAlignment.size(); j++) {

			if (targetAlignment[j] == '-' && sequenceAlignment[j] != '-') {
				sequencePos++;
				continue;
				//outJsonFile << "\"" << target[j-1] << "\":\""
				//		<< "10000,10000,10000\"\n";
			} else if (targetAlignment[j] != '-'
					&& sequenceAlignment[j] == '-') {
				targetPos++;
				continue;
			} else if (targetAlignment[j] == '-'
					&& sequenceAlignment[j] == '-') {
				continue;
			} else {
				if (Xs[targetStart + targetPos - 2] != 10000
						&& Ys[targetStart + targetPos - 2] != 10000
						&& Zs[targetStart + targetPos - 2] != 10000) {
					pdbFile << "ATOM  ";				//record name
					pdbFile << right << setw(5)
							<< sequenceStart + sequencePos - 1;	// atom serial number
					pdbFile << "  CA  ";				//atom name
					pdbFile << setw(3)
							<< convertResidueName(sequenceAlignment[j]);
					//pdbFile<<query[ j - 1]; //for dubug
					pdbFile << right << setw(6)
							<< sequenceStart + sequencePos - 1;	// atom serial number
					pdbFile << "    ";
					pdbFile << right << setw(8.3)
							<< Xs[targetStart + targetPos - 2];
					pdbFile << right << setw(8.3)
							<< Ys[targetStart + targetPos - 2];
					pdbFile << right << setw(8.3)
							<< Zs[targetStart + targetPos - 2];
					pdbFile << "  1.00  0.00\n";
				}
				targetPos++;
				sequencePos++;

			}

		}
		if (tailMore > 0) {
			for (int k = 0; k < tailMore; k++) {
				if (Xs[targetEnd + k] != 10000 && Ys[targetEnd + k] != 10000
						&& Zs[targetEnd + k] != 10000) {
					pdbFile << "ATOM  ";				//record name
					pdbFile << right << setw(5) << sequenceEnd + k; // atom serial number
					pdbFile << "  CA  "; //atom name
					pdbFile << setw(3)
							<< convertResidueName(
									originalProteinSeq[sequenceEnd + k]);
					pdbFile << right << setw(6) << sequenceEnd + k; // atom serial number
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
void CNFSearchImpl::findGlobalAlign() {

	string proteinName;
	int sequenceStart;
	string sequence;
	int sequenceEnd;
	int targetStart;
	string target;
	int targetEnd;
	for (int i = 0; i < cnfSearchResultVector.size(); i++) {
		vector<float> XCoords = cnfSearchResultVector[i].getXCoords();
		if (XCoords.empty()) {
			cout << cnfSearchResultVector[i].getProteinName()
					<< " this db file not exist" << endl;
			continue;
		}
		proteinName = cnfSearchResultVector[i].getProteinName();
		sequenceStart = cnfSearchResultVector[i].getSequenceStart();
		sequence = cnfSearchResultVector[i].getSequenceAlignment();
		targetStart = cnfSearchResultVector[i].getTargetStart();
		target = cnfSearchResultVector[i].getTargetAlignment();
		targetEnd = cnfSearchResultVector[i].getTargetEnd();
		int sequenceHeadMore = sequenceStart - 1;
		int sequenceTailMore = proteinSeqLength - sequenceEnd;
		vector<float> Xs = cnfSearchResultVector[i].getXCoords();
		vector<float> Ys = cnfSearchResultVector[i].getYCoords();
		vector<float> Zs = cnfSearchResultVector[i].getZCoords();
		vector<char> templateSeq = cnfSearchResultVector[i].getTemplateSeq();
		int targetHeadMore = targetStart - 1;
		int targetTailMore = Xs.size() - targetEnd;
		int headMore = 0;
		if (sequenceHeadMore > targetHeadMore) {
			headMore = targetHeadMore;
		} else {
			headMore = sequenceHeadMore;
		}

		int tailMore = 0;
		if (sequenceTailMore > targetTailMore) {
			tailMore = targetTailMore;
		} else {
			tailMore = sequenceTailMore;
		}
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/CNFSearch/FullyExtended/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += sequence;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		while (headMore > 0) {
			outJsonFile << "\"" << originalProteinSeq[sequenceStart - headMore - 1]
					<< "\":\"" << Xs[targetStart - headMore - 1] << ","
					<< Ys[targetStart - headMore - 1] << ","
					<< Zs[targetStart - headMore - 1] << "\"\n";
			headMore--;
		}
		int offset = 0;
		for (int j = 0; j < target.size(); j++) {
			if (target[j] == '-' && sequence[j] != '-') {
				continue;
				//outJsonFile << "\"" << target[j-1] << "\":\""
				//		<< "10000,10000,10000\"\n";
			} else if (target[j] != '-' && sequence[j] == '-') {
				offset++;
				continue;
			} else if (target[j] == '-' && sequence[j] == '-') {
				continue;
			} else {
				outJsonFile << "\"" << sequence[j] << "\":\""
						<< Xs[targetStart + offset - 1] << ","
						<< Ys[targetStart + offset - 1] << ","
						<< Zs[targetStart + offset - 1] << "\"\n";
				offset++;
			}

		}
		if (tailMore > 0) {
			for (int k = 0; k < tailMore; k++) {
				outJsonFile << "\"" << originalProteinSeq[sequenceEnd + k]
						<< "\":\"" << Xs[targetEnd + k] << ","
						<< Ys[targetEnd + k] << "," << Zs[targetEnd + k]
						<< "\"\n";
			}
		}
		outJsonFile << "}\n";
		outJsonFile.close();
	}
}
CNFSearchImpl::~CNFSearchImpl() {
	// TODO Auto-generated destructor stub
}

