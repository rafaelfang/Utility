/*
 * CNFSearchResult.h
 *
 *  Created on: Jul 2, 2015
 *      Author: cf797
 */

#ifndef CNFSEARCHRESULT_H_
#define CNFSEARCHRESULT_H_

#include <string>

#include "AlignmentResult.h"

using namespace std;

class CNFSearchResult: public AlignmentResult {
public:
	CNFSearchResult();
	virtual ~CNFSearchResult();
	string& getAlignmentPart();
	void setAlignmentPart(string& alignmentPart);
	bool isFirstStateReached();
	void setFirstStateReached(bool firstStateReached);
	string& getProteinName();
	void setProteinName(string& proteinName);

	string& getSequenceAccConf();
	void setSequenceAccConf(string& sequenceAccConf);
	string& getSequenceAccPred();
	void setSequenceAccPred(string& sequenceAccPred);
	string& getSequenceAlignment();
	void setSequenceAlignment(string& sequenceAlignment);
	int getSequenceEnd();
	void setSequenceEnd(int sequenceEnd);
	string& getSequenceSseConf();
	void setSequenceSseConf(string& sequenceSseConf);
	string& getSequenceSsePred();
	void setSequenceSsePred(string& sequenceSsePred);
	int getSequenceStart();
	void setSequenceStart(int sequenceStart);
	string& getTargetAccReal();
	void setTargetAccReal(string& targetAccReal);
	string& getTargetAlignment();
	void setTargetAlignment(string& targetAlignment);
	int getTargetEnd();
	void setTargetEnd(int targetEnd);
	string& getTargetSseReal();
	void setTargetSseReal(string& targetSseReal);
	int getTargetStart();
	void setTargetStart(int targetStart);
	bool isSecondStateReached() ;
	void setSecondStateReached(bool secondStateReached);

private:
	bool firstStateReached;
	bool secondStateReached;

	string proteinName;
	string targetSseReal;
	string targetAccReal;
	string targetAlignment;
	int targetStart;
	int targetEnd;
	string alignmentPart;
	string sequenceAlignment;
	int sequenceStart;
	int sequenceEnd;
	string sequenceAccPred;
	string sequenceAccConf;
	string sequenceSsePred;
	string sequenceSseConf;

};

#endif
