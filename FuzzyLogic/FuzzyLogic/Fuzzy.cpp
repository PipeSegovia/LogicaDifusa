#include "pch.h"
#include "Fuzzy.h"

Fuzzy::Fuzzy()
{
	this->fuzzyInputs = NULL;
}

Fuzzy::~Fuzzy()
{
}

bool Fuzzy::addFuzzyInput(FuzzyInput * fuzzyInput)
{
	fuzzyInputArray *aux;

	//Asigno espacio en memoria
	aux = (fuzzyInputArray*)malloc(sizeof(fuzzyInputArray));
	if (aux == NULL)
	{
		return false;
	}

	aux->fuzzyInput = fuzzyInput;
	aux->next = NULL;

	//Si el arreglo de entradas difusas esta vacio
	if (this->fuzzyInputs == NULL)
	{
		this->fuzzyInputs = aux;
	}
	else
	{
		this->fuzzyInputs->next = aux;
	}

	return true;
}

bool Fuzzy::fuzzify()
{
	fuzzyInputArray *fuzzyInputAux;

	fuzzyInputAux = this->fuzzyInputs;
	//Inicializo las pertenencias en 0
	while (fuzzyInputAux != NULL)
	{
		fuzzyInputAux->fuzzyInput->resetFuzzySet();
		fuzzyInputAux = fuzzyInputAux->next;
	}

	//Calculo las pertenencias
	fuzzySetArray* fuzzySetAux;

	fuzzyInputAux = this->fuzzyInputs;
	while (fuzzyInputAux != NULL)
	{
		fuzzySetAux = fuzzyInputAux->fuzzyInput->getFuzzySets();
		while (fuzzySetAux != NULL)
		{
			fuzzySetAux->fuzzySet->calculatePertinence();
		}
	}

	return true;
}
