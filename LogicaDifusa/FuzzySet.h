#pragma once
#ifndef FUZZYSET_H
#define FUZZYSET_H

class FuzzySet
{
public:
	FuzzySet();
	FuzzySet(float a, float b, float c, float d,int typeFunction);
	void calculatePertinence(float crispValue);
	void setPertinence(float pertinence);
	float getPertinence();
	void reset();
	~FuzzySet();
	//Metodos no modificados
	float getPointA();
	float getPointB();
	float getPointC();
	float getPointD();

private:
	void functionL(float crispValue);
	void functionGamma(float crispValue);
	void functionTrapezoide(float crispValue);
private:
	float a;
	float b;
	float c;
	float d;
	int typeFunction;
	float pertinence;
};

#endif