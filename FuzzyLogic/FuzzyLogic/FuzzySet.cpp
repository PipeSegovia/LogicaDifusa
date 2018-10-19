#include "pch.h"
#include "FuzzySet.h"

FuzzySet::FuzzySet()
{
}

FuzzySet::FuzzySet(float a, float b, float c, float d, int typeFunction)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->pertinence = 0.0;
	this->typeFunction = typeFunction;
}

FuzzySet::~FuzzySet()
{
}

bool FuzzySet::calculatePertinence(float crispValue)
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
		functionTrapezoidal(crispValue);
		break;
	default:
		break;
	}

	return true;
}

void FuzzySet::setPertinence(float pertinence)
{
	if(this->pertinence < pertinence)
	{ 
		this->pertinence = pertinence;
	}
}

float FuzzySet::getPertinence()
{
	return this->pertinence;
}

bool FuzzySet::functionL(float crispValue)
{
	if (crispValue <= this->a)
	{
		this->pertinence = 1.0;
	}
	else if (crispValue > this->a && crispValue < this->b)
	{
		this->pertinence = 1 - ((crispValue - this->a)/(this->b - this->a));
	}
	else if (crispValue >= this->b) 
	{
		this->pertinence = 0.0;
	}

	return true;
}

bool FuzzySet::functionGamma(float crispValue)
{
	if (crispValue <= this->a) 
	{
		this->pertinence = 0.0;
	}
	else if (crispValue > this->a && crispValue < this->b)
	{
		this->pertinence = (crispValue - this->a) / (this->b - this->a);
	}
	else if (crispValue >= this->b)
	{
		this->pertinence = 1.0;
	}

	return true;
}

bool FuzzySet::functionTrapezoidal(float crispValue)
{

	if (crispValue <= this->a)
	{
		this->pertinence = 0.0;
	}
	else if (crispValue > this->a && crispValue <= this->b)
	{
		this->pertinence = (crispValue - this->a) / (this->b - this->a);
	}
	else if (crispValue > this->b && crispValue <= this->c)
	{
		this->pertinence = 1.0;
	}
	else if (crispValue > this->c && crispValue <= this->d) 
	{
		this->pertinence = (this->d - crispValue) / (this->d - this->c);
	}
	else if (crispValue > this->d)
	{
		this->pertinence = 0.0;
	}
	return true;
}

void FuzzySet::reset()
{
	this->pertinence =  0.0;
}

