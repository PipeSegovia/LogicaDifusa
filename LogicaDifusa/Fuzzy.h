#pragma once
#ifndef FUZZY_H
#define FUZZY_H

#include "FuzzyInput.h"
#include "FuzzyRule.h"

//Lista de entradas difusa
struct fuzzyInputArray
{
	FuzzyInput *fuzzyInput;
	fuzzyInputArray *next;
};

//Lista de reglas
struct fuzzyRuleArray
{
	FuzzyRule *fuzzyRule;
	fuzzyRuleArray *next;
};

class Fuzzy
{
public:
	Fuzzy();
	~Fuzzy();
	bool addFuzzyInput(FuzzyInput* fuzzyInput);
	bool addFuzzyRule(FuzzyRule *fuzzyRule);
	bool fuzzify();
	bool setInput(int fuzzyInputIndex,float crispValue);
	bool isFiredRule(int fuzzyRuleIndex);
private:
	fuzzyInputArray* fuzzyInputs;
	fuzzyRuleArray *fuzzyRules;
};

#endif // !FUZZY_H