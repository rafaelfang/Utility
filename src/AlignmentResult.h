/*
 * AlignmentResult.h
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#ifndef ALIGNMENTRESULT_H_
#define ALIGNMENTRESULT_H_

#include <string>
#include <vector>

using namespace std;
class AlignmentResult {
public:
	AlignmentResult();

	virtual ~AlignmentResult();
	vector<float>& getXCoords();
	void setXCoords(vector<float>& coords);
	vector<float>& getYCoords();
	void setYCoords(vector<float>& coords);
	vector<float>& getZCoords();
	void setZCoords(vector<float>& coords);
	 vector<char>& getTemplateSeq() ;
	void setTemplateSeq( vector<char>& templateSeq);

protected:

	vector<float> XCoords;
	vector<float> YCoords;
	vector<float> ZCoords;
	vector<char> templateSeq;
};

#endif /* ALIGNMENTRESULT_H_ */
