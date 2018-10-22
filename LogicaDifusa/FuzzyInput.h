#pragma once
#ifndef FUZZYINPUT_H
#define FUZZYINPUT_H

#include "FuzzyIO.h"


class FuzzyInput : public FuzzyIO
{
public:
	FuzzyInput();
	FuzzyInput(int index);
	~FuzzyInput();
	int get_index();
	void set_crispInput(float crispInput);
	float get_crispInput();
	bool calculateFuzzySetPertinences();

private: 
	int index;
	float crispInput;
};

#endif // !FUZZYINPUT_H