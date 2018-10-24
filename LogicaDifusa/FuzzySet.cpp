#include "pch.h"
#include "FuzzySet.h"


FuzzySet::FuzzySet()
{
	this->a = 0.0f;
	this->b = 0.0f;
	this->c = 0.0f;
	this->d = 0.0f;
	this->pertinence = 0.0f;
	this->typeFunction = 0;
}

FuzzySet::FuzzySet(float a, float b, float c, float d, int typeFunction)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->typeFunction = typeFunction;
}


FuzzySet::~FuzzySet()
{
}

float FuzzySet::getPointA()
{
	return this->a;
}

float FuzzySet::getPointB()
{
	return this->b;
}

float FuzzySet::getPointC()
{
	return this->c;
}

float FuzzySet::getPointD()
{
	return this->d;
}

void FuzzySet::calculatePertinence(float crispValue)
{
	switch (this->typeFunction)
	{
	case 1:
		functionL(crispValue);
		break;
	case 2:
		functionGamma(crispValue);
		break;
	case 3:
		functionTrapezoide(crispValue);
		break;
	default:
		break;
	}
}

void FuzzySet::functionL(float crispValue)
{
	if (crispValue <= this->a)
	{
		this->pertinence = 1.0f;
	}
	else if (crispValue > this->a && crispValue < this->b)
	{
		this->pertinence = 1 - ((crispValue - this->a)/(this->b - this->a));
	}
	else if (crispValue >= this->b)
	{
		this->pertinence = 0.0f;
	}
}

void FuzzySet::functionGamma(float crispValue)
{
	if (crispValue <= this->c)
	{
		this->pertinence = 0.0f;
	}
	else if (crispValue > this->c && crispValue < this->d)
	{
		this->pertinence = (crispValue - this->c) / (this->d - this->c);
	}
	else if (crispValue >= this->d)
	{
		this->pertinence = 1.0f;
	}
}

void FuzzySet::functionTrapezoide(float crispValue)
{
	if (crispValue <= this->a)
	{
		this->pertinence = 0.0f;
	}
	else if (crispValue > this->a && crispValue <= this->b)
	{
		this->pertinence = (crispValue - this->a) / (this->b - this->a);
	}
	else if (crispValue > this->b && crispValue <= this->c)
	{
		this->pertinence = 1.0f;
	}
	else if (crispValue > this->c && crispValue <= this->d)
	{
		this->pertinence = (this->d - crispValue) / (this->d - this->c);
	}
	else if (crispValue > this->d)
	{
		this->pertinence = 0.0f;
	}
}

void FuzzySet::setPertinence(float pertinence)
{
	if (this->pertinence < pertinence)
	{
		this->pertinence = pertinence;

	}
}

float FuzzySet::getPertinence()
{
	return this->pertinence;
}

void FuzzySet::reset()
{
	this->pertinence = 0.0f;
}
