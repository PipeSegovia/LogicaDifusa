#pragma once
#ifndef FUZZYCOMPOSITION_H
#define FUZZYCOMPOSITION_H

#include <stdlib.h>

#define EPS 1.0E-3

//Lista enlazada que almacena los puntos de la funcion de pertenencia de salida
struct pointsArray
{
	pointsArray* previous;
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
	bool build();
	float avaliate();
private:
	bool rebuild(pointsArray* aSegmentBegin, pointsArray* aSegmentEnd, pointsArray* bSegmentBegin, pointsArray* bSegmentEnd);
	bool rmvPoint(pointsArray *point);

private:
	pointsArray *points;
	pointsArray *pointsCursor;
};


#endif // !FUZZYCOMPOSITION_H