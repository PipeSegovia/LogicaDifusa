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
			//Si es L
			if (aux->fuzzySet->getPointC() == aux->fuzzySet->getPointD()) //Se espera que ambos sean 0
			{
				//Si este punto no esta en la nueva figura entonces lo inserto
				if (this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointA(),0.0f) == false)
				{
					this->fuzzyComposition.addPoint(aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence());
					this->fuzzyComposition.addPoint(aux->fuzzySet->getPointB(), 0.0f);
				}
			}
			//Si es Trapezio
			if (aux->fuzzySet->getPointA() != aux->fuzzySet->getPointB() && aux->fuzzySet->getPointB() != aux->fuzzySet->getPointC() && aux->fuzzySet->getPointC() != aux->fuzzySet->getPointD())
			{
				if (aux->fuzzySet->getPertinence() == 1.0) {
					if (this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence()) == false) {
						this->fuzzyComposition.addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
					}

					if (this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence()) == false) {
						this->fuzzyComposition.addPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence());
					}
				}
				else {
					float newPointB = aux->fuzzySet->getPointB();
					float newPertinenceB = aux->fuzzySet->getPertinence();

					rebuild(aux->fuzzySet->getPointA(), 0.0, aux->fuzzySet->getPointB(), 1.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointB, &newPertinenceB);

					if (this->fuzzyComposition.checkPoint(newPointB, newPertinenceB) == false) {
						this->fuzzyComposition.addPoint(newPointB, newPertinenceB);
					}

					float newPointC = aux->fuzzySet->getPointB();
					float newPertinenceC = aux->fuzzySet->getPertinence();

					rebuild(aux->fuzzySet->getPointC(), 1.0, aux->fuzzySet->getPointD(), 0.0, aux->fuzzySet->getPointA(), aux->fuzzySet->getPertinence(), aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence(), &newPointC, &newPertinenceC);

					if (this->fuzzyComposition.checkPoint(newPointC, newPertinenceC) == false) {
						this->fuzzyComposition.addPoint(newPointC, newPertinenceC);
					}
				}
			}
			//Si es Gamma
			if (aux->fuzzySet->getPointA() == aux->fuzzySet->getPointB()) //Se espera que ambos sean 0
			{
				if (this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointD(), 0.0) == false || aux->fuzzySet->getPointD() == aux->fuzzySet->getPointA()) {
					this->fuzzyComposition.addPoint(aux->fuzzySet->getPointD(), aux->fuzzySet->getPertinence());
					this->fuzzyComposition.addPoint(aux->fuzzySet->getPointC(), 0.0);
				}
			}
		}
		aux = aux->next;
	}
	this->fuzzyComposition.build();
	return true;
}

int FuzzyOutput::getIndex()
{
	return this->index;
}

float FuzzyOutput::getCrispOutput()
{
	return this->fuzzyComposition.avaliate();
}

bool FuzzyOutput::rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float * point, float * pertinence)
{
	return false;
}
