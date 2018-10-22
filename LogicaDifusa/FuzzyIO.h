#pragma once
#ifndef FUZZYIO_H
#define FUZZYIO_H

#include "FuzzySet.h"
#include <math.h>
#include <malloc.h>

//Arreglo de conjuntos difusos
//Se utiliza para los Fuzzy Input y Fuzzy Output
struct fuzzySetArray
{
	FuzzySet* fuzzySet;
	fuzzySetArray *next;
};

class FuzzyIO
{
public:
	FuzzyIO();
	FuzzyIO(int index);
	~FuzzyIO();
	bool addFuzzySet(FuzzySet* fuzzySet);
	void resetFuzzySets();
	void cleanFuzzySets(fuzzySetArray* aux);
protected:
	int index;
	fuzzySetArray* fuzzySets;
};

#endif // !FUZZYIO_H