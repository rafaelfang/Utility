/*
 * HHRNRImpl.h
 *
 *  Created on: Apr 25, 2015
 *      Author: cf797
 */

#ifndef HHRNRIMPL_H_
#define HHRNRIMPL_H_

#include <vector>

#include "HHRNRResult.h"
#include "UtilityInterface.h"

using namespace std;
class HHRNRImpl: public UtilityInterface {
public:
	HHRNRImpl(char*);
	void makeDirectory();
	void populateResultVector();
	void write2Json();
	void setup3DCoords();
	void findLocalAlign();
	void write2PDB();
	void findGlobalAlign();
	virtual ~HHRNRImpl();
private:
	vector<HHRNRResult> hhrNRResultVector;
};

#endif /* HHRNRIMPL_H_ */
