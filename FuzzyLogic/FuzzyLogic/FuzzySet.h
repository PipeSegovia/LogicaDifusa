#pragma once
#ifndef FUZZYSET_H
#define FUZZYSET_H

class FuzzySet 
{
public:
	FuzzySet();
	FuzzySet(float a, float b, float c, float d, int typeFunction);
	~FuzzySet();
	bool calculatePertinence(float crispValue);
	void setPertinence(float pertinence);
	float getPertinence();
	void reset();
private:
	bool functionL(float crispValue);
	bool functionGamma(float crispValue);
	bool functionTrapezoidal(float crispValue);	
	
private:
	int typeFunction;
	float a;
	float b;
	float c;
	float d;
	float pertinence;
};

#endif // !FUZZYSET_H