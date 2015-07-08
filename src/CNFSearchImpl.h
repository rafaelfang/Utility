/*
 * CNFSearchImpl.h
 *
 *  Created on: Jul 2, 2015
 *      Author: cf797
 */

#ifndef CNFSEARCHIMPL_H_
#define CNFSEARCHIMPL_H_

#include <vector>

#include "CNFSearchResult.h"
#include "UtilityInterface.h"

class CNFSearchImpl: public UtilityInterface {
public:
	CNFSearchImpl(char*);
	void makeDirectory();
	void populateResultVector();
	void write2Json();
	void setup3DCoords();
	void findLocalAlign();
	void write2PDB();
	void findGlobalAlign();
	virtual ~CNFSearchImpl();
private:
	vector<CNFSearchResult> cnfSearchResultVector;
};

#endif /* CNFSEARCHIMPL_H_ */
