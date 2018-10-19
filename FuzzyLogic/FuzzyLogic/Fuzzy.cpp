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
		fuzzyInputArray *auxFuzzyInput = (fuzzyInputArray*)malloc(sizeof(fuzzyInputArray));
		auxFuzzyInput = this->fuzzyInputs;
		auxFuzzyInput->next = NULL;

		this->fuzzyInputs = aux;	
		aux->next = auxFuzzyInput;

	}
	
	return true;
}

int Fuzzy::sizeFuzzyInputArray()
{
	int cont = 1;
	if (this->fuzzyInputs == NULL)
	{
		return 0;
	}
	else
	{
		while (this->fuzzyInputs != NULL)
		{
			cont++;
			this->fuzzyInputs = this->fuzzyInputs->next;
		}
		return cont;
	}
	return 0;
}

bool Fuzzy::fuzzify()
{
	fuzzyInputArray *fuzzyInputAux = (fuzzyInputArray*)malloc(sizeof(fuzzyInputArray));

	fuzzyInputAux = this->fuzzyInputs;
	fuzzyInputAux->next = NULL;
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
		//	fuzzySetAux->fuzzySet->calculatePertinence();
		}
	}
	
	return true;
}
