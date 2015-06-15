/*
 * HHRResult.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cf797
 */

#include "HHRResult.h"

HHRResult::HHRResult() {
	// TODO Auto-generated constructor stub

}

bool HHRResult::isFirstStateReached() {
	return firstStateReached;
}

void HHRResult::setFirstStateReached(bool firstStateReached = false) {
	this->firstStateReached = firstStateReached;
}

bool HHRResult::isSecondStateReached() {
	return secondStateReached;
}

void HHRResult::setSecondStateReached(bool secondStateReached = false) {
	this->secondStateReached = secondStateReached;
}

int HHRResult::getAlignedCols() {
	return aligned_cols;
}

void HHRResult::setAlignedCols(int alignedCols) {
	aligned_cols = alignedCols;
}

string& HHRResult::getAlignment() {
	return alignment;
}

void HHRResult::setAlignment(string& alignment) {
	this->alignment = alignment;
}

string& HHRResult::getConfidence() {
	return confidence;
}

void HHRResult::setConfidence(string& confidence) {
	this->confidence = confidence;
}

float HHRResult::getExpect() {
	return expect;
}

void HHRResult::setExpect(float expect) {
	this->expect = expect;
}

int HHRResult::getIdentities() {
	return identities;
}

void HHRResult::setIdentities(int identities) {
	this->identities = identities;
}

float HHRResult::getProbab() {
	return probab;
}

void HHRResult::setProbab(float probab) {
	this->probab = probab;
}

string& HHRResult::getProteinName() {
	return proteinName;
}

void HHRResult::setProteinName(string& proteinName) {
	this->proteinName = proteinName;
}

string& HHRResult::getQuery() {
	return query;
}

void HHRResult::setQuery(string& query) {
	this->query = query;
}

string& HHRResult::getQueryConsensus() {
	return queryConsensus;
}

void HHRResult::setQueryConsensus(string& queryConsensus) {
	this->queryConsensus = queryConsensus;
}

int HHRResult::getQueryEnd() {
	return queryEnd;
}

void HHRResult::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

int HHRResult::getQueryStart() {
	return queryStart;
}

void HHRResult::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

float HHRResult::getScore() {
	return score;
}

void HHRResult::setScore(float score) {
	this->score = score;
}

int HHRResult::getSimilarities() {
	return similarities;
}

void HHRResult::setSimilarities(int similarities) {
	this->similarities = similarities;
}

float HHRResult::getSumProbs() {
	return sum_probs;
}

void HHRResult::setSumProbs(float sumProbs) {
	sum_probs = sumProbs;
}

string& HHRResult::getTarget() {
	return target;
}

void HHRResult::setTarget(string& target) {
	this->target = target;
}

string& HHRResult::getTargetSsPred() {
	return target_ss_pred;
}

void HHRResult::setTargetSsPred(string& targetSsPred) {
	target_ss_pred = targetSsPred;
}

string& HHRResult::getTargetConsensus() {
	return targetConsensus;
}

void HHRResult::setTargetConsensus(string& targetConsensus) {
	this->targetConsensus = targetConsensus;
}

int HHRResult::getTargetEnd() {
	return targetEnd;
}

void HHRResult::setTargetEnd(int targetEnd) {
	this->targetEnd = targetEnd;
}

int HHRResult::getTargetStart() {
	return targetStart;
}

void HHRResult::setTargetStart(int targetStart) {
	this->targetStart = targetStart;
}

string& HHRResult::getQuerySsPred() {
	return query_ss_pred;
}

void HHRResult::setQuerySsPred(string& querySsPred) {
	query_ss_pred = querySsPred;
}
HHRResult::~HHRResult() {
	// TODO Auto-generated destructor stub
}

