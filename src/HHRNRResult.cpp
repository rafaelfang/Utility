/*
 * HHRNRResult.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cf797
 */

#include "HHRNRResult.h"

HHRNRResult::HHRNRResult() {
	// TODO Auto-generated constructor stub

}

HHRNRResult::~HHRNRResult() {
	// TODO Auto-generated destructor stub
}
int HHRNRResult::getAlignedCols() {
	return aligned_cols;
}

void HHRNRResult::setAlignedCols(int alignedCols) {
	aligned_cols = alignedCols;
}

string& HHRNRResult::getAlignment() {
	return alignment;
}

void HHRNRResult::setAlignment(string& alignment) {
	this->alignment = alignment;
}

string& HHRNRResult::getConfidence() {
	return confidence;
}

void HHRNRResult::setConfidence(string& confidence) {
	this->confidence = confidence;
}

int HHRNRResult::getIdentities() {
	return identities;
}

void HHRNRResult::setIdentities(int identities) {
	this->identities = identities;
}

float HHRNRResult::getProbab() {
	return probab;
}

void HHRNRResult::setProbab(float probab) {
	this->probab = probab;
}

string& HHRNRResult::getProteinName() {
	return proteinName;
}

void HHRNRResult::setProteinName(string& proteinName) {
	this->proteinName = proteinName;
}

string& HHRNRResult::getQuery() {
	return query;
}

void HHRNRResult::setQuery(string& query) {
	this->query = query;
}

string& HHRNRResult::getQueryConsensus() {
	return queryConsensus;
}

void HHRNRResult::setQueryConsensus(string& queryConsensus) {
	this->queryConsensus = queryConsensus;
}

float HHRNRResult::getScore() {
	return score;
}

void HHRNRResult::setScore(float score) {
	this->score = score;
}

int HHRNRResult::getSimilarities() {
	return similarities;
}

void HHRNRResult::setSimilarities(int similarities) {
	this->similarities = similarities;
}

float HHRNRResult::getSumProbs() {
	return sum_probs;
}

void HHRNRResult::setSumProbs(float sumProbs) {
	sum_probs = sumProbs;
}

string& HHRNRResult::getTarget() {
	return target;
}

void HHRNRResult::setTarget(string& target) {
	this->target = target;
}

string& HHRNRResult::getTargetSsDssp() {
	return target_ss_dssp;
}

void HHRNRResult::setTargetSsDssp(string& targetSsDssp) {
	target_ss_dssp = targetSsDssp;
}

string& HHRNRResult::getTargetSsPred() {
	return target_ss_pred;
}

void HHRNRResult::setTargetSsPred(string& targetSsPred) {
	target_ss_pred = targetSsPred;
}

string& HHRNRResult::getTargetConsensus() {
	return targetConsensus;
}

void HHRNRResult::setTargetConsensus(string& targetConsensus) {
	this->targetConsensus = targetConsensus;
}

float HHRNRResult::getExpect() {
	return expect;
}

void HHRNRResult::setExpect(float expect) {
	this->expect = expect;
}

int HHRNRResult::getQueryEnd() {
	return queryEnd;
}

void HHRNRResult::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

int HHRNRResult::getQueryStart() {
	return queryStart;
}

void HHRNRResult::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

int HHRNRResult::getTargetEnd() {
	return targetEnd;
}

void HHRNRResult::setTargetEnd(int targetEnd) {
	this->targetEnd = targetEnd;
}

int HHRNRResult::getTargetStart() {
	return targetStart;
}

void HHRNRResult::setTargetStart(int targetStart) {
	this->targetStart = targetStart;
}

string& HHRNRResult::getQuerySsPred() {
	return query_ss_pred;
}

void HHRNRResult::setQuerySsPred(string& querySsPred) {
	query_ss_pred = querySsPred;
}
