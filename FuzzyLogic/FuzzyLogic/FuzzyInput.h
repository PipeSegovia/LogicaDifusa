#pragma once
#ifndef FUZZYINPUT_H
#define FUZZYINPUT_H

#include <math.h>
#include <malloc.h>
#include "FuzzySet.h"
//Lista de conjuntos difusos
struct fuzzySetArray
{
	FuzzySet *fuzzySet;
	fuzzySetArray *next;
};

class FuzzyInput 
{
public:
	FuzzyInput(int index);
	~FuzzyInput();
	void setCrispInput(float crispInput);
	float getCrispInput();
	bool addFuzzySet(FuzzySet* fuzzySet);
	void resetFuzzySet(); //Resetea las pertenencias del arreglo de fuzzySet
	void cleanFuzzySet(fuzzySetArray *aux); //Libera la memoria del arreglo de fuzzySet
	fuzzySetArray* getFuzzySets();
private:
	int index;
	float crispInput;
	fuzzySetArray *fuzzySet;
};

#endif // !FUZZYINPUT_H

