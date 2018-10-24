#pragma once
#ifndef FUZZYOUTPUT_H
#define FUZZYOUTPUT_H

#include "FuzzyIO.h"
#include "FuzzyComposition.h"


class FuzzyOutput : public FuzzyIO
{
public:
	FuzzyOutput();
	FuzzyOutput(int index);
	~FuzzyOutput();
	bool truncate(); //Une los dos conjuntos difusos
	int getIndex();
	float getCrispOutput();
private:
	bool rebuild(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *point, float *pertinence);
private:
	int index;
	FuzzyComposition fuzzyComposition;
};

#endif // !FUZZYOUTPUT_H