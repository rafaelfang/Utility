/*
 * CNFSearchResult.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: cf797
 */

#include "CNFSearchResult.h"

CNFSearchResult::CNFSearchResult() {
	// TODO Auto-generated ructor stub

}

CNFSearchResult::~CNFSearchResult() {
	// TODO Auto-generated destructor stub
}

string& CNFSearchResult::getAlignmentPart() {
	return alignmentPart;
}

void CNFSearchResult::setAlignmentPart(string& alignmentPart) {
	this->alignmentPart = alignmentPart;
}

bool CNFSearchResult::isFirstStateReached() {
	return firstStateReached;
}

void CNFSearchResult::setFirstStateReached(bool firstStateReached) {
	this->firstStateReached = firstStateReached;
}

string& CNFSearchResult::getProteinName() {
	return proteinName;
}

void CNFSearchResult::setProteinName(string& proteinName) {
	this->proteinName = proteinName;
}

string& CNFSearchResult::getSequenceAccConf() {
	return sequenceAccConf;
}

void CNFSearchResult::setSequenceAccConf(string& sequenceAccConf) {
	this->sequenceAccConf = sequenceAccConf;
}

string& CNFSearchResult::getSequenceAccPred() {
	return sequenceAccPred;
}

void CNFSearchResult::setSequenceAccPred(string& sequenceAccPred) {
	this->sequenceAccPred = sequenceAccPred;
}

string& CNFSearchResult::getSequenceAlignment() {
	return sequenceAlignment;
}

void CNFSearchResult::setSequenceAlignment(string& sequenceAlignment) {
	this->sequenceAlignment = sequenceAlignment;
}

int CNFSearchResult::getSequenceEnd() {
	return sequenceEnd;
}

void CNFSearchResult::setSequenceEnd(int sequenceEnd) {
	this->sequenceEnd = sequenceEnd;
}

string& CNFSearchResult::getSequenceSseConf() {
	return sequenceSseConf;
}

void CNFSearchResult::setSequenceSseConf(string& sequenceSseConf) {
	this->sequenceSseConf = sequenceSseConf;
}

string& CNFSearchResult::getSequenceSsePred() {
	return sequenceSsePred;
}

void CNFSearchResult::setSequenceSsePred(string& sequenceSsePred) {
	this->sequenceSsePred = sequenceSsePred;
}

int CNFSearchResult::getSequenceStart() {
	return sequenceStart;
}

void CNFSearchResult::setSequenceStart(int sequenceStart) {
	this->sequenceStart = sequenceStart;
}

string& CNFSearchResult::getTargetAccReal() {
	return targetAccReal;
}

void CNFSearchResult::setTargetAccReal(string& targetAccReal) {
	this->targetAccReal = targetAccReal;
}

string& CNFSearchResult::getTargetAlignment() {
	return targetAlignment;
}

void CNFSearchResult::setTargetAlignment(string& targetAlignment) {
	this->targetAlignment = targetAlignment;
}

int CNFSearchResult::getTargetEnd() {
	return targetEnd;
}

void CNFSearchResult::setTargetEnd(int targetEnd) {
	this->targetEnd = targetEnd;
}

string& CNFSearchResult::getTargetSseReal() {
	return targetSseReal;
}

void CNFSearchResult::setTargetSseReal(string& targetSseReal) {
	this->targetSseReal = targetSseReal;
}

int CNFSearchResult::getTargetStart() {
	return targetStart;
}

void CNFSearchResult::setTargetStart(int targetStart) {
	this->targetStart = targetStart;
}

bool CNFSearchResult::isSecondStateReached() {
	return secondStateReached;
}

void CNFSearchResult::setSecondStateReached(bool secondStateReached) {
	this->secondStateReached = secondStateReached;
}
