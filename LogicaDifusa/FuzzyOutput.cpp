#include "pch.h"
#include "FuzzyOutput.h"


FuzzyOutput::FuzzyOutput()
{
}

FuzzyOutput::FuzzyOutput(int index) : FuzzyIO(index)
{
	this->index = index;
}


FuzzyOutput::~FuzzyOutput()
{
}

bool FuzzyOutput::truncate()
{
	fuzzySetArray *aux = this->fuzzySets;
	while (aux != NULL)
	{
		if (aux->fuzzySet->getPertinence() > 0.0f)
		{
			//Si no es L iniciado con pertenencia 1
		}
	}
	return true;
}
