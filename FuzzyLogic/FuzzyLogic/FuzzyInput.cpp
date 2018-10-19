#include "pch.h"
#include "FuzzyInput.h"

FuzzyInput::FuzzyInput(int index)
{
	this->index = index;
	this->fuzzySet = NULL;
}

FuzzyInput::~FuzzyInput(){}

void FuzzyInput::setCrispInput(float crispInput)
{
	this->crispInput = crispInput;
}

float FuzzyInput::getCrispInput()
{
	return this->crispInput;
}

bool FuzzyInput::addFuzzySet(FuzzySet * fuzzySet)
{
	fuzzySetArray *aux;
	//Asigno un espacio de memoria
	aux = (fuzzySetArray*)malloc(sizeof(fuzzySetArray));
	if (aux == NULL)
	{
		return false;
	}
	aux->fuzzySet = fuzzySet;
	aux->next = NULL;

	if (this->fuzzySet == NULL)
	{
		this->fuzzySet = aux;
	}

	return true;
}

void FuzzyInput::resetFuzzySet()
{
	fuzzySetArray *fuzzySetsAux;
	fuzzySetsAux = this->fuzzySet;
	while (fuzzySetsAux != NULL)
	{
		fuzzySetsAux->fuzzySet->reset();
		fuzzySetsAux = fuzzySetsAux->next;
	}
}

void FuzzyInput::cleanFuzzySet(fuzzySetArray *aux)
{
	if (aux != NULL)
	{
		this->cleanFuzzySet(aux->next);
		free(aux);
	}
}
