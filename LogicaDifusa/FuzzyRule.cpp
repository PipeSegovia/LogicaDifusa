#include "pch.h"
#include "FuzzyRule.h"


FuzzyRule::FuzzyRule()
{
}

FuzzyRule::FuzzyRule(int index, FuzzyAntecedent * fuzzyRuleAntecedent, FuzzyRuleConsequent * fuzzyRuleConsecuent)
{
	this->index = index;
	this->fuzzyRuleAntecedent = fuzzyRuleAntecedent;
	this->fuzzyRuleConsecuent = fuzzyRuleConsecuent;
	this->fired = false;
}


FuzzyRule::~FuzzyRule()
{
}

int FuzzyRule::getIndex()
{
	return this->index;
}

bool FuzzyRule::evaluateExpression()
{
	if (this->fuzzyRuleAntecedent != NULL)
	{
		float powerOfAntecedent = this->fuzzyRuleAntecedent->evaluate();

		(powerOfAntecedent > 0.0) ? (this->fired = true) : (this->fired = false);

		this->fuzzyRuleConsecuent->evaluate(powerOfAntecedent);
		this->power = powerOfAntecedent;
	}
	return this->fired;
}

bool FuzzyRule::isFired()
{
	return this->fired;
}

float FuzzyRule::getPowerOfRule()
{
	return this->power;
}
