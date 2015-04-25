/*
 * BLANRResult.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: cf797
 */

#include "BLANRResult.h"

BLANRResult::BLANRResult() {
	// TODO Auto-generated constructor stub

}

BLANRResult::~BLANRResult() {
	// TODO Auto-generated destructor stub
}

string& BLANRResult::getAlignment() {
	return alignment;
}

void BLANRResult::setAlignment(string& alignment) {
	this->alignment = alignment;
}

float BLANRResult::getExpect() {
	return expect;
}

void BLANRResult::setExpect(float expect) {
	this->expect = expect;
}

bool BLANRResult::isFirstStateReached() {
	return firstStateReached;
}

void BLANRResult::setFirstStateReached(bool firstStateReached = false) {
	this->firstStateReached = firstStateReached;
}

int BLANRResult::getGaps() {
	return gaps;
}

void BLANRResult::setGaps(int gaps) {
	this->gaps = gaps;
}

int BLANRResult::getIdentities() {
	return identities;
}

void BLANRResult::setIdentities(int identities) {
	this->identities = identities;
}

int BLANRResult::getLength() {
	return length;
}

void BLANRResult::setLength(int length) {
	this->length = length;
}

int BLANRResult::getPositives() {
	return positives;
}

void BLANRResult::setPositives(int positives) {
	this->positives = positives;
}

string& BLANRResult::getQuery() {
	return query;
}

void BLANRResult::setQuery(string& query) {
	this->query = query;
}

int BLANRResult::getQueryEnd() {
	return queryEnd;
}

void BLANRResult::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

int BLANRResult::getQueryStart() {
	return queryStart;
}

void BLANRResult::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

float BLANRResult::getScore() {
	return score;
}

void BLANRResult::setScore(float score) {
	this->score = score;
}

bool BLANRResult::isSecondStateReached() {
	return secondStateReached;
}

void BLANRResult::setSecondStateReached(bool secondStateReached = false) {
	this->secondStateReached = secondStateReached;
}

string& BLANRResult::getSubject() {
	return subject;
}

void BLANRResult::setSubject(string& subject) {
	this->subject = subject;
}

int BLANRResult::getSubjectEnd() {
	return subjectEnd;
}

void BLANRResult::setSubjectEnd(int subjectEnd) {
	this->subjectEnd = subjectEnd;
}

int BLANRResult::getSubjectStart() {
	return subjectStart;
}

void BLANRResult::setSubjectStart(int subjectStart) {
	this->subjectStart = subjectStart;
}

bool BLANRResult::isThirdStateReached() {
	return thirdStateReached;
}

void BLANRResult::setThirdStateReached(bool thirdStateReached = false) {
	this->thirdStateReached = thirdStateReached;
}

string& BLANRResult::getProteinName() {
	return proteinName;
}

void BLANRResult::setProteinName(string& proteinName) {
	this->proteinName = proteinName;
}
