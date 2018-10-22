#pragma once
#ifndef FUZZYANTECEDENT_H
#define FUZZYANTECEDENT_H

#include "FuzzySet.h"
#include <math.h>

#define OP_AND 1
#define OP_OR 2
#define MODE_FS 1
#define MODE_FS_FS 2
#define MODE_FS_FRA 3
#define MODE_FRA_FRA 4

class FuzzyAntecedent
{
public:
	FuzzyAntecedent();
	~FuzzyAntecedent();
	bool joinSingle(FuzzySet* fuzzySet);
	bool joinAND(FuzzySet *fuzzySet1, FuzzySet *fuzzySet2);
	bool joinAND(FuzzyAntecedent *fuzzyRuleAntecedent, FuzzySet *fuzzySet1);
	bool joinAND(FuzzySet *fuzzySet1, FuzzyAntecedent *fuzzyRuleAnteceden);
	bool joinAND(FuzzyAntecedent *fuzzyRuleAntecedent1, FuzzyAntecedent *fuzzyRuleAntecedent2);
	bool joinOR(FuzzySet *fuzzySet1, FuzzySet *fuzzySet2);
	bool joinOR(FuzzyAntecedent *fuzzyRuleAntecedent, FuzzySet *fuzzySet1);
	bool joinOR(FuzzySet *fuzzySet1, FuzzyAntecedent *fuzzyRuleAntecede);
	bool joinOR(FuzzyAntecedent *fuzzyRuleAntecedent1, FuzzyAntecedent *fuzzyRuleAntecedent2);
	float evaluate();
	

private:

	int op; //operador AND o OR
	int mode;
	FuzzySet* fuzzySet1; //FS
	FuzzySet* fuzzySet2; //FS
	FuzzyAntecedent* fuzzyRuleAntecedent1; //FRA
	FuzzyAntecedent* fuzzyRuleAntecedent2; //FRA

};

#endif // !FUZZYANTECEDENT_H
