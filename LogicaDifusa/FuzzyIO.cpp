#include "pch.h"
#include "FuzzyIO.h"


FuzzyIO::FuzzyIO()
{
}

FuzzyIO::FuzzyIO(int index)
{
	this->index = index;
	this->fuzzySets = NULL;
}


FuzzyIO::~FuzzyIO()
{
}

bool FuzzyIO::addFuzzySet(FuzzySet * fuzzySet)
{
	fuzzySetArray* aux = (fuzzySetArray*)malloc(sizeof(fuzzySetArray));
	if (aux == NULL)
	{
		return false;
	}
	aux->fuzzySet = fuzzySet;
	aux->next = NULL;

	//Si la lista esta vacia
	if (this->fuzzySets == NULL)
	{
		this->fuzzySets = aux;
	}
	else
	{
		//Inserto en la primera posicion de la lista
		fuzzySetArray* auxFuzzySets = (fuzzySetArray*)malloc(sizeof(fuzzySetArray));
		auxFuzzySets = this->fuzzySets;
		this->fuzzySets = aux;
		aux->next = auxFuzzySets;
	}
	return true;
}

void FuzzyIO::resetFuzzySets()
{
	fuzzySetArray* fuzzySetArrayAux = (fuzzySetArray*)malloc(sizeof(fuzzySetArray));
	fuzzySetArrayAux = this->fuzzySets;

	while (fuzzySetArrayAux != NULL)
	{
		fuzzySetArrayAux->fuzzySet->reset();
		fuzzySetArrayAux = fuzzySetArrayAux->next;
	}
}

void FuzzyIO::cleanFuzzySets(fuzzySetArray * aux)
{
	if (aux != NULL)
	{
		this->cleanFuzzySets(aux->next);
		free(aux);
	}
}
