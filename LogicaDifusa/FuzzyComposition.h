#pragma once
#ifndef FUZZYCOMPOSITION_H
#define FUZZYCOMPOSITION_H

#include <stdlib.h>

//Lista que almacena los puntos de la funcion de pertenencia de salida
struct pointsArray
{
	float point;
	float pertinence;
	pointsArray *next;
};

class FuzzyComposition
{
public:
	FuzzyComposition();
	~FuzzyComposition();
	bool addPoint(float point, float pertinence);
	bool checkPoint(float point,float pertinence); //ve si existe este punto
private:
	pointsArray *points;
};


#endif // !FUZZYCOMPOSITION_H