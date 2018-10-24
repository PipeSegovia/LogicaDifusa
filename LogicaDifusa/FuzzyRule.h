#pragma once
#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include "FuzzyAntecedent.h"
#include "FuzzyRuleConsequent.h"


class FuzzyRule
{
public:
	FuzzyRule();
	FuzzyRule(int index, FuzzyAntecedent *fuzzyRuleAntecedent, FuzzyRuleConsequent *fuzzyRuleConsecuent);
	~FuzzyRule();
	int getIndex();
	bool evaluateExpression();
	bool isFired();
	float getPowerOfRule();
	
private:
	int index;
	bool fired; 
	FuzzyAntecedent *fuzzyRuleAntecedent;
	FuzzyRuleConsequent *fuzzyRuleConsecuent;
	float power;
};

#endif // !FUZZYRULE_H



