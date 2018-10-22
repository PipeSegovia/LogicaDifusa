#include "pch.h"
#include "FuzzyAntecedent.h"


FuzzyAntecedent::FuzzyAntecedent()
{
	this->op = 0;
	this->mode = 0;
	this->fuzzySet1 = NULL;
	this->fuzzySet2 = NULL;
	this->fuzzyRuleAntecedent1 = NULL;
	this->fuzzyRuleAntecedent2 = NULL;
}


FuzzyAntecedent::~FuzzyAntecedent()
{
}

bool FuzzyAntecedent::joinSingle(FuzzySet * fuzzySet)
{
	if (fuzzySet) {
		this->mode = MODE_FS;
		this->fuzzySet1 = fuzzySet;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinAND(FuzzySet * fuzzySet1, FuzzySet * fuzzySet2)
{
	if (fuzzySet1 != NULL && fuzzySet2 != NULL) {
		this->op = OP_AND;
		this->mode = MODE_FS_FS;
		this->fuzzySet1 = fuzzySet1;
		this->fuzzySet2 = fuzzySet2;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinAND(FuzzyAntecedent * fuzzyRuleAntecedent, FuzzySet * fuzzySet1)
{
	if (fuzzySet1 != NULL && fuzzyRuleAntecedent != NULL) {
		this->op = OP_AND;
		this->mode = MODE_FS_FRA;
		this->fuzzySet1 = fuzzySet1;
		this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinAND(FuzzySet * fuzzySet1, FuzzyAntecedent * fuzzyRuleAnteceden)
{
	if (fuzzySet1 != NULL && fuzzyRuleAnteceden != NULL) {
		this->op = OP_AND;
		this->mode = MODE_FS_FRA;
		this->fuzzySet1 = fuzzySet1;
		this->fuzzyRuleAntecedent1 = fuzzyRuleAnteceden;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinAND(FuzzyAntecedent * fuzzyRuleAntecedent1, FuzzyAntecedent * fuzzyRuleAntecedent2)
{
	if (fuzzyRuleAntecedent1 != NULL && fuzzyRuleAntecedent2 != NULL) {
		this->op = OP_AND;
		this->mode = MODE_FRA_FRA;
		this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
		this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinOR(FuzzySet * fuzzySet1, FuzzySet * fuzzySet2)
{
	if (fuzzySet1 != NULL && fuzzySet2 != NULL) {
		this->op = OP_OR;
		this->mode = MODE_FS_FS;
		this->fuzzySet1 = fuzzySet1;
		this->fuzzySet2 = fuzzySet2;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinOR(FuzzyAntecedent * fuzzyRuleAntecedent, FuzzySet * fuzzySet1)
{
	if (fuzzySet1 != NULL && fuzzyRuleAntecedent != NULL) {
		this->op = OP_OR;
		this->mode = MODE_FS_FRA;
		this->fuzzySet1 = fuzzySet1;
		this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinOR(FuzzySet * fuzzySet1, FuzzyAntecedent * fuzzyRuleAntecede)
{
	if (fuzzySet1 != NULL && fuzzyRuleAntecede != NULL) {
		this->op = OP_OR;
		this->mode = MODE_FS_FRA;
		this->fuzzySet1 = fuzzySet1;
		this->fuzzyRuleAntecedent1 = fuzzyRuleAntecede;
		return true;
	}
	return false;
}

bool FuzzyAntecedent::joinOR(FuzzyAntecedent * fuzzyRuleAntecedent1, FuzzyAntecedent * fuzzyRuleAntecedent2)
{
	if (fuzzyRuleAntecedent1 != NULL && fuzzyRuleAntecedent2 != NULL) {
		this->op = OP_OR;
		this->mode = MODE_FRA_FRA;
		this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
		this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
		return true;
	}
	return false;
}

float FuzzyAntecedent::evaluate()
{
	switch (this->mode) {
	case MODE_FS:
		return this->fuzzySet1->getPertinence();
		break;
	case MODE_FS_FS:
		switch (this->op) {
		case OP_AND:
			if (this->fuzzySet1->getPertinence() > 0.0 && this->fuzzySet2->getPertinence() > 0.0) {
				if (this->fuzzySet1->getPertinence() < this->fuzzySet2->getPertinence()) {
					return this->fuzzySet1->getPertinence();
				}
				else {
					return this->fuzzySet2->getPertinence();
				}
			}
			else {
				return 0.0;
			}
			break;
		case OP_OR:
			if (this->fuzzySet1->getPertinence() > 0.0 || this->fuzzySet2->getPertinence() > 0.0) {
				if (this->fuzzySet1->getPertinence() > this->fuzzySet2->getPertinence()) {
					return this->fuzzySet1->getPertinence();
				}
				else {
					return this->fuzzySet2->getPertinence();
				}
			}
			else {
				return 0.0;
			}
			break;
		default:
			return 0.0;
		}
		break;
	case MODE_FS_FRA:
		switch (this->op) {
		case OP_AND:
			if (this->fuzzySet1->getPertinence() > 0.0 && fuzzyRuleAntecedent1->evaluate() > 0.0) {
				if (this->fuzzySet1->getPertinence() < fuzzyRuleAntecedent1->evaluate()) {
					return this->fuzzySet1->getPertinence();
				}
				else {
					return fuzzyRuleAntecedent1->evaluate();
				}
			}
			else {
				return 0.0;
			}
			break;
		case OP_OR:
			if (this->fuzzySet1->getPertinence() > 0.0 || fuzzyRuleAntecedent1->evaluate() > 0.0) {
				if (this->fuzzySet1->getPertinence() > fuzzyRuleAntecedent1->evaluate()) {
					return this->fuzzySet1->getPertinence();
				}
				else {
					return fuzzyRuleAntecedent1->evaluate();
				}
			}
			else {
				return 0.0;
			}
			break;
		default:
			return 0.0;
		}
		break;
	case MODE_FRA_FRA:
		switch (this->op) {
		case OP_AND:
			if (fuzzyRuleAntecedent1->evaluate() > 0.0 && fuzzyRuleAntecedent2->evaluate() > 0.0) {
				if (fuzzyRuleAntecedent1->evaluate() < fuzzyRuleAntecedent2->evaluate()) {
					return fuzzyRuleAntecedent1->evaluate();
				}
				else {
					return fuzzyRuleAntecedent2->evaluate();
				}
			}
			else {
				return 0.0;
			}
			break;
		case OP_OR:
			if (fuzzyRuleAntecedent1->evaluate() > 0.0 || fuzzyRuleAntecedent2->evaluate() > 0.0) {
				if (fuzzyRuleAntecedent1->evaluate() > fuzzyRuleAntecedent2->evaluate()) {
					return fuzzyRuleAntecedent1->evaluate();
				}
				else {
					return fuzzyRuleAntecedent2->evaluate();
				}
			}
			else {
				return 0.0;
			}
			break;
		default:
			return 0.0;
		}
		break;
	default:
		return 0.0;
	}
	return 0.0;
}
