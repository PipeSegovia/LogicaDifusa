#pragma once
#ifndef FUZZYRULECONSECUENT_H
#define FUZZYRULECONSECUENT_H

#include "FuzzySet.h"
#include <math.h>
#include <stdlib.h>


class FuzzyRuleConsequent
{
public:
	FuzzyRuleConsequent();
	~FuzzyRuleConsequent();
	bool addOutput(FuzzySet *fuzzySet);
	bool evaluate(float power);
private:
	FuzzySet* fuzzyOutput;
};

#endif // !FUZZYRULECONSECUENT_H


