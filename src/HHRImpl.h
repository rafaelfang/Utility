/*
 * HHRImpl.h
 *
 *  Created on: Apr 24, 2015
 *      Author: cf797
 */

#ifndef HHRIMPL_H_
#define HHRIMPL_H_

#include <vector>

#include "HHRResult.h"
#include "UtilityInterface.h"

using namespace std;
class HHRImpl: public UtilityInterface {
public:
	HHRImpl(char*);
	void makeDirectory();
	void populateResultVector();
	void write2Json();
	void setup3DCoords();
	void findLocalAlign();
	void findGlobalAlign();
	virtual ~HHRImpl();
private:
	vector<HHRResult> hhrResultVector;
};

#endif /* HHRIMPL_H_ */
