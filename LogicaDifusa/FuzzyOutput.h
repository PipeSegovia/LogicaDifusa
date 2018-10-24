#pragma once
#ifndef FUZZYOUTPUT_H
#define FUZZYOUTPUT_H

#include "FuzzyIO.h"

class FuzzyOutput : public FuzzyIO
{
public:
	FuzzyOutput();
	FuzzyOutput(int index);
	~FuzzyOutput();
	bool truncate(); //Une los dos conjuntos difusos
private:
	int index;
};

#endif // !FUZZYOUTPUT_H