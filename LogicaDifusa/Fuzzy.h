#pragma once
#ifndef FUZZY_H
#define FUZZY_H

#include "FuzzyInput.h"
#include "FuzzyRule.h"
#include "FuzzyOutput.h"

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

//Lista de salidas difusas
struct fuzzyOutputArray
{
	FuzzyOutput *fuzzyOutput;
	fuzzyOutputArray *next;
};

class Fuzzy
{
public:
	Fuzzy();
	~Fuzzy();
	bool addFuzzyInput(FuzzyInput* fuzzyInput);
	bool addFuzzyRule(FuzzyRule *fuzzyRule);
	bool addFuzzyOutput(FuzzyOutput *fuzzyOutput);
	bool fuzzify();
	bool setInput(int fuzzyInputIndex,float crispValue);
	bool isFiredRule(int fuzzyRuleIndex);
	float defuzzify(int fuzzyOutputIndex);
private:
	fuzzyInputArray* fuzzyInputsCursor;
	fuzzyInputArray* fuzzyInputs;
	fuzzyRuleArray *fuzzyRules;
	fuzzyRuleArray* fuzzyRulesCursor;
	fuzzyOutputArray* fuzzyOutputsCursor;
	fuzzyOutputArray *fuzzyOutputs;
};

#endif // !FUZZY_H