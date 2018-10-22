#include "pch.h"
#include "FuzzyInput.h"


FuzzyInput::FuzzyInput()
{
}

FuzzyInput::FuzzyInput(int index) 
{
	this->index = index;
}


FuzzyInput::~FuzzyInput()
{
}

int FuzzyInput::get_index()
{
	return this->index;
}

void FuzzyInput::set_crispInput(float crispInput)
{
	this->crispInput = crispInput;
}

float FuzzyInput::get_crispInput()
{
	return this->crispInput;
}

bool FuzzyInput::calculateFuzzySetPertinences()
{
	fuzzySetArray *aux = (fuzzySetArray*)malloc(sizeof(fuzzySetArray));

	aux = this->fuzzySets;

	while (aux != NULL)
	{
		if (aux->fuzzySet != NULL)
		{
			aux->fuzzySet->calculatePertinence(this->crispInput);
		}
			aux = aux->next;
	}

	return true;
}
