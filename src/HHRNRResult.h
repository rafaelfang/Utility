/*
 * HHRNRResult.h
 *
 *  Created on: Apr 25, 2015
 *      Author: cf797
 */

#ifndef HHRNRRESULT_H_
#define HHRNRRESULT_H_

#include <string>

#include "AlignmentResult.h"

class HHRNRResult: public AlignmentResult {
public:
	HHRNRResult();
	virtual ~HHRNRResult();
	int getAlignedCols();
	void setAlignedCols(int alignedCols);
	string& getAlignment();
	void setAlignment(string& alignment);
	string& getConfidence();
	void setConfidence(string& confidence);

	int getIdentities();
	void setIdentities(int identities);
	float getProbab();
	void setProbab(float probab);
	string& getProteinName();
	void setProteinName(string& proteinName);
	string& getQuery();
	void setQuery(string& query);
	string& getQueryConsensus();
	void setQueryConsensus(string& queryConsensus);
	float getScore();
	void setScore(float score);
	int getSimilarities();
	void setSimilarities(int similarities);
	float getSumProbs();
	void setSumProbs(float sumProbs);
	string& getTarget();
	void setTarget(string& target);
	string& getTargetSsDssp();
	void setTargetSsDssp(string& targetSsDssp);
	string& getTargetSsPred();
	void setTargetSsPred(string& targetSsPred);
	string& getTargetConsensus();
	void setTargetConsensus(string& targetConsensus);
	float getExpect();
	void setExpect(float expect);
	int getQueryEnd();
	void setQueryEnd(int queryEnd);
	int getQueryStart();
	void setQueryStart(int queryStart);
	int getTargetEnd();
	void setTargetEnd(int targetEnd);
	int getTargetStart();
	void setTargetStart(int targetStart);
	string& getQuerySsPred();
	void setQuerySsPred(string& querySsPred);
	bool isFirstStateReached();
	void setFirstStateReached(bool);
	bool isSecondStateReached();
	void setSecondStateReached(bool);

private:
	bool firstStateReached;
	bool secondStateReached;

	string proteinName;
	float probab;
	float expect;
	float score;
	int aligned_cols;
	int identities;
	int similarities;
	float sum_probs;
	string query_ss_pred;
	int queryStart;
	string query;
	int queryEnd;
	string queryConsensus;
	string alignment;
	int targetStart;
	int targetEnd;
	string targetConsensus;
	string target;
	string target_ss_dssp;
	string target_ss_pred;
	string confidence;
};

#endif /* HHRNRRESULT_H_ */
