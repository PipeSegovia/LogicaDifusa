#include "pch.h"
#include "Fuzzy.h"


Fuzzy::Fuzzy()
{
	this->fuzzyInputs = NULL;
	this->fuzzyRules = NULL;
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

bool Fuzzy::addFuzzyRule(FuzzyRule * fuzzyRule)
{
	fuzzyRuleArray *aux = (fuzzyRuleArray*)malloc(sizeof(fuzzyRuleArray));
	if (aux == NULL)
	{
		return false;
	}

	aux->fuzzyRule = fuzzyRule;
	aux->next = NULL;

	if (this->fuzzyRules == NULL)
	{
		this->fuzzyRules = aux;
	}
	else
	{
		fuzzyRuleArray *nodoAux = this->fuzzyRules;
		this->fuzzyRules = aux;
		this->fuzzyRules->next = nodoAux;
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

	//Evaluando las reglas que se van a disparar
	fuzzyRuleArray *fuzzyRuleAux;
	fuzzyRuleAux = this->fuzzyRules;
	//Calculando las pertenencias de todos los FuzzyInput
	while (fuzzyRuleAux != NULL)
	{
		fuzzyRuleAux->fuzzyRule->evaluateExpression();
		fuzzyRuleAux = fuzzyRuleAux->next;
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

bool Fuzzy::isFiredRule(int fuzzyRuleIndex)
{
	fuzzyRuleArray *aux;
	aux = this->fuzzyRules;
	while (aux != NULL) {
		if (aux->fuzzyRule->getIndex() == fuzzyRuleIndex) {
			return aux->fuzzyRule->isFired();
		}
		aux = aux->next;
	}
	return false;
}
