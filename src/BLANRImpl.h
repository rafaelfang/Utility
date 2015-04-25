/*
 * BLANRImpl.h
 *
 *  Created on: Apr 24, 2015
 *      Author: cf797
 */

#ifndef BLANRIMPL_H_
#define BLANRIMPL_H_
#include <vector>

#include "BLANRResult.h"
#include "UtilityInterface.h"

class BLANRImpl: public UtilityInterface {
public:
	BLANRImpl(char*);
	void makeDirectory();
	void populateResultVector();
	void write2Json();
	void setup3DCoords();
	void findLocalAlign();
	void findGlobalAlign();
	virtual ~BLANRImpl();
private:
	vector<BLANRResult> blaNRResultVector;
};

#endif /* BLANRIMPL_H_ */
