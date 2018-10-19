#pragma once
#ifndef FUZZY_H
#define FUZZY_H

#include "FuzzyInput.h"
#include "FuzzySet.h"
#include <math.h>
#include <malloc.h>


//lista de entradas difusas
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
	bool addFuzzyInput(FuzzyInput *fuzzyInput);
	int sizeFuzzyInputArray();
	bool fuzzify();
private:
	fuzzyInputArray* fuzzyInputs;
	fuzzySetArray* fuzzySets;
};

#endif // !FUZZY_H

