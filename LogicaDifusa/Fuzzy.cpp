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
	fuzzyInputArray* aux = (fuzzyInputArray*)malloc(sizeof(fuzzyInputArray));

	if (aux == NULL)
	{
		return false;
	}

	aux->fuzzyInput = fuzzyInput;
	aux->next = NULL;
	//Esta vacio
	if (this->fuzzyInputs == NULL)
	{
		this->fuzzyInputs = aux;
	}
	else
	{
		fuzzyInputArray *nodoAux = this->fuzzyInputs;
		this->fuzzyInputs = aux;
		this->fuzzyInputs->next = nodoAux;
	}

	return true;
}

bool Fuzzy::fuzzify()
{

	fuzzyInputArray* fuzzyInputAux;

	fuzzyInputAux = this->fuzzyInputs;
	//Reseteo los valores de pertenencia de los conjuntos difusos
	while (fuzzyInputAux != NULL)
	{
		fuzzyInputAux->fuzzyInput->resetFuzzySets();
		fuzzyInputAux = fuzzyInputAux->next;
	}

	//Calculo los grados de pertenencia de cada fuzzySet
	fuzzyInputAux = this->fuzzyInputs;
	while (fuzzyInputAux != NULL)
	{
		fuzzyInputAux->fuzzyInput->calculateFuzzySetPertinences();
		fuzzyInputAux = fuzzyInputAux->next;
	}

	return true;
}

bool Fuzzy::setInput(int fuzzyInputIndex, float crispValue)
{
	fuzzyInputArray *aux;
	aux = this->fuzzyInputs;

	while (aux != NULL)
	{
		if (aux->fuzzyInput->get_index() == fuzzyInputIndex)
		{
			aux->fuzzyInput->set_crispInput(crispValue);
			return true;
		}
		aux = aux->next;
	}
	return false;
}
