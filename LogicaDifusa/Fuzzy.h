#pragma once
#ifndef FUZZY_H
#define FUZZY_H

#include "FuzzyInput.h"


struct fuzzyInputArray
{
	FuzzyInput *fuzzyInput;
	fuzzyInputArray *next;
};

class Fuzzy
{
public:
	Fuzzy();
	~Fuzzy();
	bool addFuzzyInput(FuzzyInput* fuzzyInput);
	bool fuzzify();
	bool setInput(int fuzzyInputIndex,float crispValue);
private:
	fuzzyInputArray* fuzzyInputs;
};

#endif // !FUZZY_H