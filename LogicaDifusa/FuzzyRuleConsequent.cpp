#include "pch.h"
#include "FuzzyRuleConsequent.h"


FuzzyRuleConsequent::FuzzyRuleConsequent()
{
}


FuzzyRuleConsequent::~FuzzyRuleConsequent()
{
	free(this->fuzzyOutput);
}

bool FuzzyRuleConsequent::addOutput(FuzzySet * fuzzySet)
{
	if (fuzzySet == NULL)
	{
		return false;
	}
	this->fuzzyOutput = fuzzySet;

	return true;
}

bool FuzzyRuleConsequent::evaluate(float power)
{
	this->fuzzyOutput->setPertinence(power);
	return true;
}
