#include "pch.h"
#include "FuzzyComposition.h"


FuzzyComposition::FuzzyComposition()
{
	this->points = NULL;
}


FuzzyComposition::~FuzzyComposition()
{
}

bool FuzzyComposition::addPoint(float point, float pertinence)
{
	pointsArray *aux = (pointsArray*)malloc(sizeof(pointsArray));

	if (aux == NULL)
	{
		return true;
	}

	aux->point = point;
	aux->pertinence = pertinence;
	aux->next = NULL;

	if (this->points == NULL)
	{
		this->points = aux;
	}
	else
	{
		pointsArray* auxPoints = (pointsArray*)malloc(sizeof(pointsArray));
		auxPoints = this->points;
		this->points = aux;
		aux->next = auxPoints;
	}

	return true;
}

bool FuzzyComposition::checkPoint(float point, float pertinence)
{
	pointsArray *aux = this->points;

	while (aux != NULL)
	{
		if (aux->point == point && aux->pertinence == pertinence)
		{
			return true;
		}
		aux = aux->next;
	}

	return false;
}
