#include "pch.h"
#include "FuzzyInput.h"
#include "FuzzyOutput.h"
#include "FuzzySet.h"
#include "Fuzzy.h"
#include "FuzzyAntecedent.h"
#include "FuzzyRuleConsequent.h"
#include "FuzzyRule.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Logica difusa con las percepciones: autonomia, desempeño, motivacion, eficacia." << endl;
	cout << "Vamos a suponer que la complejidad y dificultad de este ejemplo es Basica y la actividad es la primera" << endl;

	int const L = 1;
	int const GAMMA = 2;
	int const TRAPEZOIDAL = 3;

	Fuzzy* fuzzy = new Fuzzy();


	//FuzzyInput
	//AUTONOMIA
	FuzzyInput* autonomia = new FuzzyInput(1);

	FuzzySet* alta = new FuzzySet(2.0f, 3.0f, 0.0f, 0.0f, L);
	autonomia->addFuzzySet(alta);
	FuzzySet* media = new FuzzySet(1.0f, 3.0f, 5.0f, 8.0f, TRAPEZOIDAL);
	autonomia->addFuzzySet(media);
	FuzzySet* baja = new FuzzySet(0.0f, 0.0f, 5.0f, 8.0f, GAMMA);
	autonomia->addFuzzySet(baja);

	fuzzy->addFuzzyInput(autonomia);

	//EFICACIA
	FuzzyInput* eficacia = new FuzzyInput(2);

	FuzzySet* buena = new FuzzySet(1.0f, 2.0f, 0.0f, 0.0f, L);
	eficacia->addFuzzySet(buena);
	FuzzySet* regular = new FuzzySet(1.0f, 2.0f, 3.0f, 4.0f, TRAPEZOIDAL);
	eficacia->addFuzzySet(regular);
	FuzzySet* mala = new FuzzySet(0.0f, 0.0f, 3.0f, 4.0f, GAMMA);
	eficacia->addFuzzySet(mala);

	fuzzy->addFuzzyInput(eficacia);

	//MOTIVACION
	FuzzyInput* motivacion = new FuzzyInput(3);

	FuzzySet* aceptable = new FuzzySet(147.0f, 153.0f, 0.0f, 0.0f, L);
	motivacion->addFuzzySet(aceptable);
	FuzzySet* moderada = new FuzzySet(150.0f, 154.0f, 250.0f, 270.0f, TRAPEZOIDAL);
	motivacion->addFuzzySet(moderada);
	FuzzySet* inaceptable = new FuzzySet(0.0f, 0.0f, 260.0f, 270.0f, GAMMA);
	motivacion->addFuzzySet(inaceptable);

	fuzzy->addFuzzyInput(motivacion);

	//DESEMPEÑO
	FuzzyInput* desempeño = new FuzzyInput(4);

	FuzzySet* logrado = new FuzzySet(0.0f, 0.0f, 3.0f, 4.0f, GAMMA);
	desempeño->addFuzzySet(logrado);
	FuzzySet* medianamente_logrado = new FuzzySet(1.0f, 2.0f, 3.0f, 4.0f, TRAPEZOIDAL);
	desempeño->addFuzzySet(medianamente_logrado);
	FuzzySet* no_logrado = new FuzzySet(1.0f, 2.0f, 0.0f, 0.0f, L);
	desempeño->addFuzzySet(no_logrado);

	fuzzy->addFuzzyInput(desempeño);

	//FuzzyOutput

	//porcentaje de actuacion
	FuzzyOutput* actuacion = new FuzzyOutput(1);

	FuzzySet* buenaActuacion = new FuzzySet(0.0f, 0.0f, 71.0f, 90.0f, L);
	actuacion->addFuzzySet(buenaActuacion);
	FuzzySet* mediaActuacion = new FuzzySet(50.0f, 55.0f, 60.0f, 70.0f, TRAPEZOIDAL);
	actuacion->addFuzzySet(mediaActuacion);
	FuzzySet* malaActuacion = new FuzzySet(45.0f, 49.0f, 0.0f, 0.0f, GAMMA);
	actuacion->addFuzzySet(malaActuacion);

	fuzzy->addFuzzyOutput(actuacion);


	//Rules

	//Regla1 => IF (Alta y Buena y Aceptable y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Alta

	FuzzyAntecedent *altaANDbuena0 = new FuzzyAntecedent();
	altaANDbuena0->joinAND(alta,buena);
	FuzzyAntecedent *altaANDbuenaANDaceptable0 = new FuzzyAntecedent();
	altaANDbuenaANDaceptable0->joinAND(altaANDbuena0,aceptable);

	FuzzyAntecedent* logradoORMedianamente_logrado = new FuzzyAntecedent();
	logradoORMedianamente_logrado->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORMedianamente_logradoORno_logrado = new FuzzyAntecedent();
	logradoORMedianamente_logradoORno_logrado->joinOR(logradoORMedianamente_logrado, no_logrado);

	FuzzyAntecedent* altaANDbuenaANDaceptableANDlogradoORMedianamente_logradoORno_logrado = new FuzzyAntecedent();
	altaANDbuenaANDaceptableANDlogradoORMedianamente_logradoORno_logrado->joinAND(altaANDbuenaANDaceptable0, logradoORMedianamente_logradoORno_logrado);

	FuzzyRuleConsequent* thenBuena = new FuzzyRuleConsequent();
	thenBuena->addOutput(buenaActuacion);

	FuzzyRule* regla1 = new FuzzyRule(1, altaANDbuenaANDaceptableANDlogradoORMedianamente_logradoORno_logrado, thenBuena);
	fuzzy->addFuzzyRule(regla1);

	//Regla2 => IF (Alta y Buena y Moderada y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Alta

	FuzzyAntecedent* altaANDbuena2 = new FuzzyAntecedent();
	altaANDbuena2->joinAND(alta, buena);
	FuzzyAntecedent* altaANDbuenaANDmoderada = new FuzzyAntecedent();
	altaANDbuenaANDmoderada->joinAND(altaANDbuena2, moderada);

	FuzzyAntecedent* logradoORMedianamente_logrado2 = new FuzzyAntecedent();
	logradoORMedianamente_logrado2->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORMedianamente_logradoORno_logrado2 = new FuzzyAntecedent();
	logradoORMedianamente_logradoORno_logrado2->joinOR(logradoORMedianamente_logrado2, no_logrado);

	FuzzyAntecedent* altaANDbuenaANDamoderadaANDlogradoORMedianamente_logradoORno_logrado = new FuzzyAntecedent();
	altaANDbuenaANDamoderadaANDlogradoORMedianamente_logradoORno_logrado->joinAND(altaANDbuenaANDmoderada, logradoORMedianamente_logradoORno_logrado2);

	FuzzyRuleConsequent* thenBuena2 = new FuzzyRuleConsequent();
	thenBuena2->addOutput(buenaActuacion);

	FuzzyRule* regla2 = new FuzzyRule(2, altaANDbuenaANDamoderadaANDlogradoORMedianamente_logradoORno_logrado, thenBuena2);
	fuzzy->addFuzzyRule(regla2);

	//Regla3 => IF (Alta y Buena y Inaceptable y (Logrado OR Medianamente Logrado)) THEN Alta

	FuzzyAntecedent* altaANDbuena3 = new FuzzyAntecedent();
	altaANDbuena3->joinAND(alta, buena);
	FuzzyAntecedent* altaANDbuenaANDinaceptable = new FuzzyAntecedent();
	altaANDbuenaANDinaceptable->joinAND(altaANDbuena2, inaceptable);

	FuzzyAntecedent* logradoORMedianamente_logrado3 = new FuzzyAntecedent();
	logradoORMedianamente_logrado3->joinOR(logrado, medianamente_logrado);

	FuzzyAntecedent* altaANDbuenaANDinaceptableANDlogradoORMedianamente_logrado = new FuzzyAntecedent();
	altaANDbuenaANDinaceptableANDlogradoORMedianamente_logrado->joinAND(altaANDbuenaANDinaceptable, logradoORMedianamente_logrado3);

	FuzzyRuleConsequent* thenBuena3 = new FuzzyRuleConsequent();
	thenBuena3->addOutput(buenaActuacion);

	FuzzyRule* regla3 = new FuzzyRule(3, altaANDbuenaANDinaceptableANDlogradoORMedianamente_logrado, thenBuena3);
	fuzzy->addFuzzyRule(regla3);

	//Regla4 => IF (Alta y Regular y Aceptable y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Alta

	FuzzyAntecedent* altaANDregular = new FuzzyAntecedent();
	altaANDregular->joinAND(alta, regular);
	FuzzyAntecedent* altaANDregularANDaceptable = new FuzzyAntecedent();
	altaANDregularANDaceptable->joinAND(altaANDregular, aceptable);

	FuzzyAntecedent* logradoORMedianamente_logrado4 = new FuzzyAntecedent();
	logradoORMedianamente_logrado4->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORMedianamente_logradoORno_logrado3 = new FuzzyAntecedent();
	logradoORMedianamente_logradoORno_logrado3->joinOR(logradoORMedianamente_logrado4, no_logrado);

	FuzzyAntecedent* altaANDregularANDaceptableANDlogradoORMedianamente_logradoORno_logrado = new FuzzyAntecedent();
	altaANDregularANDaceptableANDlogradoORMedianamente_logradoORno_logrado->joinAND(altaANDregularANDaceptable, logradoORMedianamente_logradoORno_logrado3);

	FuzzyRuleConsequent* thenBuena4 = new FuzzyRuleConsequent();
	thenBuena4->addOutput(buenaActuacion);

	FuzzyRule* regla4 = new FuzzyRule(4, altaANDregularANDaceptableANDlogradoORMedianamente_logradoORno_logrado, thenBuena4);
	fuzzy->addFuzzyRule(regla4);

	//Regla 5 => IF (Alta y Regular y Moderada y Logrado) THEN Alta

	FuzzyAntecedent* altaANDregular2 = new FuzzyAntecedent();
	altaANDregular2->joinAND(alta, regular);
	FuzzyAntecedent* moderadaANDlogrado2 = new FuzzyAntecedent();
	moderadaANDlogrado2->joinAND(moderada, logrado);

	FuzzyAntecedent* altaANDregularANDmoderadaANDlogrado = new FuzzyAntecedent();
	altaANDregularANDmoderadaANDlogrado->joinAND(altaANDregular2, moderadaANDlogrado2);

	FuzzyRuleConsequent* thenBuena5 = new FuzzyRuleConsequent();
	thenBuena5->addOutput(buenaActuacion);

	FuzzyRule* regla5 = new FuzzyRule(5, altaANDregularANDmoderadaANDlogrado, thenBuena5);
	fuzzy->addFuzzyRule(regla5);

	//Regla 6 => IF (Alta y Regular y Inaceptable y Logrado) THEN Alta

	FuzzyAntecedent* altaANDregular3 = new FuzzyAntecedent();
	altaANDregular3->joinAND(alta, regular);
	FuzzyAntecedent* inaceptableANDlogrado = new FuzzyAntecedent();
	inaceptableANDlogrado->joinAND(inaceptable, logrado);

	FuzzyAntecedent* altaANDregularANDinaceptableANDlogrado = new FuzzyAntecedent();
	altaANDregularANDinaceptableANDlogrado->joinAND(altaANDregular3, inaceptableANDlogrado);

	FuzzyRuleConsequent* thenBuena6 = new FuzzyRuleConsequent();
	thenBuena6->addOutput(buenaActuacion);

	FuzzyRule* regla6 = new FuzzyRule(6, altaANDregularANDinaceptableANDlogrado, thenBuena6);
	fuzzy->addFuzzyRule(regla6);

	//Regla 7 => IF (Alta y Mala y Aceptable y (Logrador OR Medianamente Logrado)) THEN Alta

	FuzzyAntecedent* altaANDmala = new FuzzyAntecedent();
	altaANDmala->joinAND(alta, mala);
	FuzzyAntecedent* altaANDmalaANDaceptable = new FuzzyAntecedent();
	altaANDmalaANDaceptable->joinAND(altaANDmala, aceptable);

	FuzzyAntecedent* logradoORMedianamente_logrado5 = new FuzzyAntecedent();
	logradoORMedianamente_logrado5->joinOR(logrado, medianamente_logrado);

	FuzzyAntecedent* altaANDmalaANDaceptableANDlogradoORMedianamente_logradoORno_logrado = new FuzzyAntecedent();
	altaANDmalaANDaceptableANDlogradoORMedianamente_logradoORno_logrado->joinAND(altaANDmalaANDaceptable, logradoORMedianamente_logrado5);

	FuzzyRuleConsequent* thenBuena7 = new FuzzyRuleConsequent();
	thenBuena7->addOutput(buenaActuacion);

	FuzzyRule* regla7 = new FuzzyRule(7, altaANDmalaANDaceptableANDlogradoORMedianamente_logradoORno_logrado, thenBuena7);
	fuzzy->addFuzzyRule(regla7);

	//Regla 8 => IF (Media y Buena y Aceptable y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Alta

	FuzzyAntecedent* mediaANDbuena = new FuzzyAntecedent();
	mediaANDbuena->joinAND(media, buena);
	FuzzyAntecedent* mediaANDbuenaANDaceptable = new FuzzyAntecedent();
	mediaANDbuenaANDaceptable->joinAND(mediaANDbuena, aceptable);

	FuzzyAntecedent* logradoORMedianamente_logrado6 = new FuzzyAntecedent();
	logradoORMedianamente_logrado6->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORMedianamente_logradoORno_logrado4 = new FuzzyAntecedent();
	logradoORMedianamente_logradoORno_logrado4->joinOR(logradoORMedianamente_logrado6, no_logrado);

	FuzzyAntecedent* mediaANDbuenaANDaceptableANDlogradoORMedianamente_logradoORno_logrado = new FuzzyAntecedent();
	mediaANDbuenaANDaceptableANDlogradoORMedianamente_logradoORno_logrado->joinAND(mediaANDbuenaANDaceptable, logradoORMedianamente_logradoORno_logrado4);

	FuzzyRuleConsequent* thenBuena8 = new FuzzyRuleConsequent();
	thenBuena8->addOutput(buenaActuacion);

	FuzzyRule* regla8 = new FuzzyRule(8, mediaANDbuenaANDaceptableANDlogradoORMedianamente_logradoORno_logrado, thenBuena8);
	fuzzy->addFuzzyRule(regla8);

	//Regla 9 => IF (Media y Buena y Moderada y Logrado) THEN Alta

	FuzzyAntecedent* mediaANDbuena2 = new FuzzyAntecedent();
	mediaANDbuena2->joinAND(media, buena);
	FuzzyAntecedent* moderadaANDlogrado3 = new FuzzyAntecedent();
	moderadaANDlogrado3->joinAND(moderada, logrado);

	FuzzyAntecedent* mediaANDbuenaANDmoderadaANDlogrado = new FuzzyAntecedent();
	mediaANDbuenaANDmoderadaANDlogrado->joinAND(mediaANDbuena2, moderadaANDlogrado3);

	FuzzyRuleConsequent* thenBuena9 = new FuzzyRuleConsequent();
	thenBuena9->addOutput(buenaActuacion);

	FuzzyRule* regla9 = new FuzzyRule(9, mediaANDbuenaANDmoderadaANDlogrado, thenBuena9);
	fuzzy->addFuzzyRule(regla9);

	//Regla 10 => IF (Media y Buena y Inaceptable y Logrado) THEN Alta

	FuzzyAntecedent* mediaANDbuena3 = new FuzzyAntecedent();
	mediaANDbuena3->joinAND(media, buena);
	FuzzyAntecedent* inaceptableANDlogrado2 = new FuzzyAntecedent();
	inaceptableANDlogrado2->joinAND(inaceptable, logrado);

	FuzzyAntecedent* mediaANDbuenaANDinaceptableANDlogrado = new FuzzyAntecedent();
	mediaANDbuenaANDinaceptableANDlogrado->joinAND(mediaANDbuena3, inaceptableANDlogrado2);

	FuzzyRuleConsequent* thenBuena10 = new FuzzyRuleConsequent();
	thenBuena10->addOutput(buenaActuacion);

	FuzzyRule* regla10 = new FuzzyRule(10, mediaANDbuenaANDinaceptableANDlogrado, thenBuena10);
	fuzzy->addFuzzyRule(regla10);

	//Regla 11 => IF (Media y Regular y Aceptable y Logrado) THEN Alta

	FuzzyAntecedent* mediaANDregular = new FuzzyAntecedent();
	mediaANDregular->joinAND(media, regular);
	FuzzyAntecedent* aceptableANDlogrado3 = new FuzzyAntecedent();
	aceptableANDlogrado3->joinAND(aceptable, logrado);

	FuzzyAntecedent* mediaANDregularANDceptableANDlogrado = new FuzzyAntecedent();
	mediaANDregularANDceptableANDlogrado->joinAND(mediaANDregular, aceptableANDlogrado3);

	FuzzyRuleConsequent* thenBuena11 = new FuzzyRuleConsequent();
	thenBuena11->addOutput(buenaActuacion);

	FuzzyRule* regla11 = new FuzzyRule(11, mediaANDregularANDceptableANDlogrado, thenBuena11);
	fuzzy->addFuzzyRule(regla11);

	//Regla 12 => IF (Baja y Buena y Aceptable y (Logrado OR Medianamente Logrado)) THEN Alta

	FuzzyAntecedent* bajaANDbuena = new FuzzyAntecedent();
	bajaANDbuena->joinAND(baja, buena);
	FuzzyAntecedent* bajaANDbuenaANDaceptable = new FuzzyAntecedent();
	bajaANDbuenaANDaceptable->joinAND(bajaANDbuena, aceptable);
	FuzzyAntecedent* logradoORmedianamenteLogrado = new FuzzyAntecedent();
	logradoORmedianamenteLogrado->joinOR(logrado, medianamente_logrado);

	FuzzyAntecedent* bajaANDbuenaANDlogradoORmedianamenteLogrado = new FuzzyAntecedent();
	bajaANDbuenaANDlogradoORmedianamenteLogrado->joinAND(bajaANDbuenaANDaceptable, logradoORmedianamenteLogrado);

	FuzzyRuleConsequent* thenBuena12 = new FuzzyRuleConsequent();
	thenBuena12->addOutput(buenaActuacion);

	FuzzyRule* regla12 = new FuzzyRule(12, bajaANDbuenaANDlogradoORmedianamenteLogrado, thenBuena12);
	fuzzy->addFuzzyRule(regla12);

	//Regla 13 => IF (Baja y Buena y Moderada y Logrado) THEN Alta

	FuzzyAntecedent* bajaANDbuena2 = new FuzzyAntecedent();
	bajaANDbuena2->joinAND(baja, buena);
	FuzzyAntecedent* moderadaANDlogrado4 = new FuzzyAntecedent();
	moderadaANDlogrado4->joinAND(moderada, logrado);

	FuzzyAntecedent* bajaANDbuenaANDmoderadaANDlogrado = new FuzzyAntecedent();
	bajaANDbuenaANDmoderadaANDlogrado->joinAND(bajaANDbuena2, moderadaANDlogrado4);

	FuzzyRuleConsequent* thenBuena13 = new FuzzyRuleConsequent();
	thenBuena13->addOutput(buenaActuacion);

	FuzzyRule* regla13 = new FuzzyRule(13, bajaANDbuenaANDmoderadaANDlogrado, thenBuena13);
	fuzzy->addFuzzyRule(regla13);

	//Regla 14 => IF (Baja y Regular y Aceptable y Logrado) THEN Alta

	FuzzyAntecedent* bajaANDregular = new FuzzyAntecedent();
	bajaANDregular->joinAND(baja, regular);
	FuzzyAntecedent* aceptableANDlogrado4 = new FuzzyAntecedent();
	aceptableANDlogrado4->joinAND(aceptable, logrado);

	FuzzyAntecedent* bajaANDregularANDaceptableANDlogrado = new FuzzyAntecedent();
	bajaANDregularANDaceptableANDlogrado->joinAND(bajaANDregular, aceptableANDlogrado4);

	FuzzyRuleConsequent* thenBuena14 = new FuzzyRuleConsequent();
	thenBuena14->addOutput(buenaActuacion);

	FuzzyRule* regla14 = new FuzzyRule(14, bajaANDregularANDaceptableANDlogrado, thenBuena14);
	fuzzy->addFuzzyRule(regla14);

	//Regla 15 => IF (Alta y Buena y Inaceptable y No Logrado) THEN Media

	FuzzyAntecedent* altaANDbuena4 = new FuzzyAntecedent();
	altaANDbuena4->joinAND(alta, buena);
	FuzzyAntecedent* inaceptableANDnoLogrado = new FuzzyAntecedent();
	inaceptableANDnoLogrado->joinAND(inaceptable, no_logrado);

	FuzzyAntecedent* altaANDbuenaANDinaceptableANDnoLogrado = new FuzzyAntecedent();
	altaANDbuenaANDinaceptableANDnoLogrado->joinAND(altaANDbuena4, inaceptableANDnoLogrado);

	FuzzyRuleConsequent* thenMedia = new FuzzyRuleConsequent();
	thenMedia->addOutput(mediaActuacion);

	FuzzyRule* regla15 = new FuzzyRule(15, altaANDbuenaANDinaceptableANDnoLogrado, thenMedia);
	fuzzy->addFuzzyRule(regla15);

	//Regla 16 => IF (Alta  Regular y Moderada y (Medianamente Logrado OR No Logrado)) THEN Media

	FuzzyAntecedent* altaANDregula4 = new FuzzyAntecedent();
	altaANDregula4->joinAND(alta, regular);
	FuzzyAntecedent* altaANDregularANDmoderada = new FuzzyAntecedent();
	altaANDregularANDmoderada->joinAND(altaANDregula4, moderada);

	FuzzyAntecedent* medianamentelogradoORnologrado = new FuzzyAntecedent();
	medianamentelogradoORnologrado->joinOR(medianamente_logrado, no_logrado);

	FuzzyAntecedent* altaANDregularANDmoderadaANDmedianamentelogradoORnologrado = new FuzzyAntecedent();
	altaANDregularANDmoderadaANDmedianamentelogradoORnologrado->joinAND(altaANDregularANDmoderada, medianamentelogradoORnologrado);

	FuzzyRuleConsequent* thenMedia2 = new FuzzyRuleConsequent();
	thenMedia2->addOutput(mediaActuacion);

	FuzzyRule* regla16 = new FuzzyRule(16, altaANDregularANDmoderadaANDmedianamentelogradoORnologrado, thenMedia2);
	fuzzy->addFuzzyRule(regla16);

	//Regla 17 => IF (Alta y Regular y Inaceptable y Medianamente Logrado) THEN Media

	FuzzyAntecedent* altaANDregular4 = new FuzzyAntecedent();
	altaANDregular4->joinAND(alta, regular);
	FuzzyAntecedent* inaceptableANDmedianamentelogrado = new FuzzyAntecedent();
	inaceptableANDmedianamentelogrado->joinAND(inaceptable, medianamente_logrado);

	FuzzyAntecedent* altaANDregularANDinaceptableANDmedianamentelogrado = new FuzzyAntecedent();
	altaANDregularANDinaceptableANDmedianamentelogrado->joinAND(altaANDregular4, inaceptableANDmedianamentelogrado);

	FuzzyRuleConsequent* thenMedia3 = new FuzzyRuleConsequent();
	thenMedia3->addOutput(mediaActuacion);

	FuzzyRule* regla17 = new FuzzyRule(17, altaANDregularANDinaceptableANDmedianamentelogrado, thenMedia3);
	fuzzy->addFuzzyRule(regla17);

	//Regla 18 => IF (Alta y Mala y Aceptable y No Logrado) THEN Media

	FuzzyAntecedent* altaANDmala2 = new FuzzyAntecedent();
	altaANDmala2->joinAND(alta, mala);
	FuzzyAntecedent* aceptableANDnologrado2 = new FuzzyAntecedent();
	inaceptableANDmedianamentelogrado->joinAND(aceptable, no_logrado);

	FuzzyAntecedent* altaANDmalaANDaceptableANDnologrado = new FuzzyAntecedent();
	altaANDmalaANDaceptableANDnologrado->joinAND(altaANDmala2, aceptableANDnologrado2);

	FuzzyRuleConsequent* thenMedia4 = new FuzzyRuleConsequent();
	thenMedia4->addOutput(mediaActuacion);

	FuzzyRule* regla18 = new FuzzyRule(18, altaANDmalaANDaceptableANDnologrado, thenMedia4);
	fuzzy->addFuzzyRule(regla18);

	//Regla 19 => IF (Alta y Mala y Moderada y Medianamente Logrado) THEN Media

	FuzzyAntecedent* altaANDmala3 = new FuzzyAntecedent();
	altaANDmala3->joinAND(alta, mala);
	FuzzyAntecedent* moderadaANDmedianamentelogrado2 = new FuzzyAntecedent();
	moderadaANDmedianamentelogrado2->joinAND(moderada, medianamente_logrado);

	FuzzyAntecedent* altaANDmalaANDmoderadaANDmedianamentelogrado = new FuzzyAntecedent();
	altaANDmalaANDmoderadaANDmedianamentelogrado->joinAND(altaANDmala3, moderadaANDmedianamentelogrado2);

	FuzzyRuleConsequent* thenMedia5 = new FuzzyRuleConsequent();
	thenMedia5->addOutput(buenaActuacion);

	FuzzyRule* regla19 = new FuzzyRule(19, altaANDmalaANDmoderadaANDmedianamentelogrado, thenMedia5);
	fuzzy->addFuzzyRule(regla19);

	//Regla 20 => IF (Alta y Mala y Inaceptable y Logrado) THEN Media

	FuzzyAntecedent* altaANDmala4 = new FuzzyAntecedent();
	altaANDmala4->joinAND(alta, mala);
	FuzzyAntecedent* inaceptableANDlogrado3 = new FuzzyAntecedent();
	inaceptableANDlogrado3->joinAND(inaceptable, logrado);

	FuzzyAntecedent* altaANDmalaANDinaceptableANDlogrado = new FuzzyAntecedent();
	altaANDmalaANDinaceptableANDlogrado->joinAND(altaANDmala4, inaceptableANDlogrado3);

	FuzzyRuleConsequent* thenMedia6 = new FuzzyRuleConsequent();
	thenMedia6->addOutput(mediaActuacion);

	FuzzyRule* regla20 = new FuzzyRule(20, altaANDmalaANDinaceptableANDlogrado, thenMedia6);
	fuzzy->addFuzzyRule(regla20);

	//Regla 21 => IF (Media y Buena y Moderada y (Medianamente Logrado OR No Logrado)) THEN Media

	FuzzyAntecedent* mediaANDbuena4 = new FuzzyAntecedent();
	mediaANDbuena4->joinAND(media, buena);
	FuzzyAntecedent* mediaANDbuenaANDmoderada2 = new FuzzyAntecedent();
	mediaANDbuenaANDmoderada2->joinAND(mediaANDbuena4, moderada);

	FuzzyAntecedent* medianamenteloradoORnologrado = new FuzzyAntecedent();
	medianamenteloradoORnologrado->joinOR(medianamente_logrado, no_logrado);

	FuzzyAntecedent* mediaANDbuenaANDmoderadaANDmedianamentelogradoORnologrado = new FuzzyAntecedent();
	mediaANDbuenaANDmoderadaANDmedianamentelogradoORnologrado->joinOR(mediaANDbuenaANDmoderada2, medianamenteloradoORnologrado);

	FuzzyRuleConsequent* thenMedia7 = new FuzzyRuleConsequent();
	thenMedia7->addOutput(mediaActuacion);

	FuzzyRule* regla21 = new FuzzyRule(21, mediaANDbuenaANDmoderadaANDmedianamentelogradoORnologrado, thenMedia7);
	fuzzy->addFuzzyRule(regla21);

	//Regla 22 => IF (Media y Buena y Inaceptable y Medianamente Logrado) THEN Media

	FuzzyAntecedent* mediaANDbuena5 = new FuzzyAntecedent();
	mediaANDbuena5->joinAND(media, buena);
	FuzzyAntecedent* inaceptableANDmedianamentelogrado2 = new FuzzyAntecedent();
	inaceptableANDmedianamentelogrado2->joinAND(inaceptable, medianamente_logrado);

	FuzzyAntecedent* mediaANDbuenaANDinaceptableANDmedianamentelogrado = new FuzzyAntecedent();
	mediaANDbuenaANDinaceptableANDmedianamentelogrado->joinAND(mediaANDbuena5, inaceptableANDmedianamentelogrado2);

	FuzzyRuleConsequent* thenMedia8 = new FuzzyRuleConsequent();
	thenMedia8->addOutput(mediaActuacion);

	FuzzyRule* regla22 = new FuzzyRule(22, mediaANDbuenaANDinaceptableANDmedianamentelogrado, thenMedia8);
	fuzzy->addFuzzyRule(regla22);

	//Regla 23 => IF (Media y Regular y Aceptable y (Medianamente Logrado OR No Logrado)) THEN Media

	FuzzyAntecedent* mediaANDregular2 = new FuzzyAntecedent();
	mediaANDregular2->joinAND(media, regular);
	FuzzyAntecedent* mediaANDregularANDaceptable = new FuzzyAntecedent();
	mediaANDregularANDaceptable->joinAND(mediaANDregular2, aceptable);

	FuzzyAntecedent* medianamenteloradoORnologrado2 = new FuzzyAntecedent();
	medianamenteloradoORnologrado2->joinOR(medianamente_logrado, no_logrado);

	FuzzyAntecedent* mediaANDregularANDaceptableANDmedianamentelogradoORnologrado = new FuzzyAntecedent();
	mediaANDregularANDaceptableANDmedianamentelogradoORnologrado->joinAND(mediaANDregularANDaceptable, medianamenteloradoORnologrado2);

	FuzzyRuleConsequent* thenMedia9 = new FuzzyRuleConsequent();
	thenMedia9->addOutput(mediaActuacion);

	FuzzyRule* regla23 = new FuzzyRule(23, mediaANDregularANDaceptableANDmedianamentelogradoORnologrado, thenMedia9);
	fuzzy->addFuzzyRule(regla23);

	//Regla 24 => IF (Media y Regular y Moderada y (Logrado OR Medianamente Logrado OR  No Logrado)) THEN Media

	FuzzyAntecedent* mediaANDregular3 = new FuzzyAntecedent();
	mediaANDregular3->joinAND(media, regular);
	FuzzyAntecedent* mediaANDregularANDmoderada = new FuzzyAntecedent();
	mediaANDregularANDmoderada->joinAND(mediaANDregular3, moderada);

	FuzzyAntecedent* logradoORmedianamentelogrado2 = new FuzzyAntecedent();
	logradoORmedianamentelogrado2->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORmedianamentelogradoORnologrado = new FuzzyAntecedent();
	logradoORmedianamentelogradoORnologrado->joinOR(logradoORmedianamentelogrado2, no_logrado);

	FuzzyAntecedent* mediaANDregularANDmoderadaANDlogradoORmedianamentelogradoORnologrado = new FuzzyAntecedent();
	mediaANDregularANDmoderadaANDlogradoORmedianamentelogradoORnologrado->joinAND(mediaANDregularANDmoderada, logradoORmedianamentelogradoORnologrado);

	FuzzyRuleConsequent* thenMedia10 = new FuzzyRuleConsequent();
	thenMedia10->addOutput(mediaActuacion);

	FuzzyRule* regla24 = new FuzzyRule(24, mediaANDregularANDmoderadaANDlogradoORmedianamentelogradoORnologrado, thenMedia10);
	fuzzy->addFuzzyRule(regla24);

	//Regla 25 => IF (Media y Mala y Aceptable y (Logrado OR Medianamente Logrado)) THEN Media

	FuzzyAntecedent* mediaANDmala = new FuzzyAntecedent();
	mediaANDmala->joinAND(media, mala);
	FuzzyAntecedent* mediaANDmalaANDaceptable = new FuzzyAntecedent();
	mediaANDmalaANDaceptable->joinAND(mediaANDmala, aceptable);

	FuzzyAntecedent* logradoORmedianamentelogrado3 = new FuzzyAntecedent();
	logradoORmedianamentelogrado3->joinOR(logrado, medianamente_logrado);

	FuzzyAntecedent* mediaANDmalaANDaceptableANDlogradoORmedianamentelogrado = new FuzzyAntecedent();
	mediaANDmalaANDaceptableANDlogradoORmedianamentelogrado->joinAND(mediaANDmalaANDaceptable, logradoORmedianamentelogrado3);

	FuzzyRuleConsequent* thenMedia11 = new FuzzyRuleConsequent();
	thenMedia11->addOutput(mediaActuacion);

	FuzzyRule* regla25 = new FuzzyRule(25, mediaANDmalaANDaceptableANDlogradoORmedianamentelogrado, thenMedia11);
	fuzzy->addFuzzyRule(regla25);

	//Regla 26 => IF (Media y Mala y Moderada y Medianamente Logrado) THEN Media

	FuzzyAntecedent* mediaANDmala2 = new FuzzyAntecedent();
	mediaANDmala2->joinAND(media, mala);
	FuzzyAntecedent* mediaANDmalaANDmoderada = new FuzzyAntecedent();
	mediaANDmalaANDmoderada->joinAND(mediaANDmala2, moderada);

	FuzzyAntecedent* mediaANDmalaANDmoderadaANDmedianamentelogrado = new FuzzyAntecedent();
	mediaANDmalaANDmoderadaANDmedianamentelogrado->joinAND(mediaANDmalaANDmoderada, medianamente_logrado);

	FuzzyRuleConsequent* thenMedia12 = new FuzzyRuleConsequent();
	thenMedia12->addOutput(mediaActuacion);

	FuzzyRule* regla26 = new FuzzyRule(26, mediaANDmalaANDmoderadaANDmedianamentelogrado, thenMedia12);
	fuzzy->addFuzzyRule(regla26);

	//Regla 27 => IF (Baja y Buena y Aceptable y (No Logrado OR Medianamente Logrado)) THEN Media

	FuzzyAntecedent* bajaANDbuena3 = new FuzzyAntecedent();
	bajaANDbuena3->joinAND(baja, buena);
	FuzzyAntecedent* bajaANDbuenaANDaceptable2 = new FuzzyAntecedent();
	bajaANDbuenaANDaceptable2->joinAND(bajaANDbuena3, aceptable);

	FuzzyAntecedent* nologradoORmedianamentelogrado = new FuzzyAntecedent();
	nologradoORmedianamentelogrado->joinOR(no_logrado, medianamente_logrado);

	FuzzyAntecedent *bajaANDbuenaANDaceptableANDnologradoORmedianamenteLogrado = new FuzzyAntecedent();
	bajaANDbuenaANDaceptableANDnologradoORmedianamenteLogrado->joinAND(bajaANDbuenaANDaceptable2, nologradoORmedianamentelogrado);

	FuzzyRuleConsequent* thenMedia13 = new FuzzyRuleConsequent();
	thenMedia13->addOutput(mediaActuacion);

	FuzzyRule* regla27 = new FuzzyRule(27, bajaANDbuenaANDaceptableANDnologradoORmedianamenteLogrado, thenMedia13);
	fuzzy->addFuzzyRule(regla27);

	//Regla 28 => IF (Baja y Buena y Inaceptable y Logrado) THEN Media

	FuzzyAntecedent* bajaANDbuena4 = new FuzzyAntecedent();
	bajaANDbuena4->joinAND(baja, buena);
	FuzzyAntecedent* inaceptableANDlogrado4 = new FuzzyAntecedent();
	inaceptableANDlogrado4->joinAND(inaceptable, logrado);

	FuzzyAntecedent* bajaANDbuenaANDinaceptableANDlogrado = new FuzzyAntecedent();
	bajaANDbuenaANDinaceptableANDlogrado->joinAND(bajaANDbuena4, inaceptableANDlogrado4);

	FuzzyRuleConsequent* thenMedia14 = new FuzzyRuleConsequent();
	thenMedia14->addOutput(mediaActuacion);

	FuzzyRule* regla28 = new FuzzyRule(28, bajaANDbuenaANDinaceptableANDlogrado, thenMedia14);
	fuzzy->addFuzzyRule(regla28);

	//Regla 29 => IF (Baja y Regular y Aceptable y Medianamente Logrado) THEN Media

	FuzzyAntecedent* bajaANDregular2 = new FuzzyAntecedent();
	bajaANDregular2->joinAND(baja, regular);
	FuzzyAntecedent* aceptableANDmedianamentelogrado3 = new FuzzyAntecedent();
	aceptableANDmedianamentelogrado3->joinAND(aceptable, medianamente_logrado);

	FuzzyAntecedent* bajaANDregularANDaceptableANDmedianamentelogrado = new FuzzyAntecedent();
	bajaANDregularANDaceptableANDmedianamentelogrado->joinAND(bajaANDregular2, aceptableANDmedianamentelogrado3);

	FuzzyRuleConsequent* thenMedia15 = new FuzzyRuleConsequent();
	thenMedia15->addOutput(mediaActuacion);

	FuzzyRule* regla29 = new FuzzyRule(29, bajaANDregularANDaceptableANDmedianamentelogrado, thenMedia15);
	fuzzy->addFuzzyRule(regla29);

	//Regla 30 => IF (Baja y Regular y Moderada y (Logrado OR Medianamente Logrado)) THEN Media

	FuzzyAntecedent* bajaANDregular3 = new FuzzyAntecedent();
	bajaANDregular3->joinAND(baja, regular);
	FuzzyAntecedent* bajaANDregularANDmoderada = new FuzzyAntecedent();
	bajaANDregularANDmoderada->joinAND(bajaANDregular3, moderada);

	FuzzyAntecedent* logradoORmedianamentelogrado4 = new FuzzyAntecedent();
	logradoORmedianamentelogrado4->joinOR(logrado, medianamente_logrado);

	FuzzyAntecedent *bajaANDregularANDmoderadaANDlogradoORmedianamentelogrado = new FuzzyAntecedent();
	bajaANDregularANDmoderadaANDlogradoORmedianamentelogrado->joinAND(bajaANDregularANDmoderada, logradoORmedianamentelogrado4);

	FuzzyRuleConsequent* thenMedia16 = new FuzzyRuleConsequent();
	thenMedia16->addOutput(mediaActuacion);

	FuzzyRule* regla30 = new FuzzyRule(30, bajaANDregularANDmoderadaANDlogradoORmedianamentelogrado, thenMedia16);
	fuzzy->addFuzzyRule(regla30);

	//Regla 31 => IF (Baja y Mala y Aceptable y Medianamente Logrado) THEN Media

	FuzzyAntecedent* bajaANDmala = new FuzzyAntecedent();
	bajaANDmala->joinAND(baja, mala);
	FuzzyAntecedent* aceptableANDmedianamentelogrado4 = new FuzzyAntecedent();
	aceptableANDmedianamentelogrado4->joinAND(aceptable, medianamente_logrado);

	FuzzyAntecedent* bajaANDmalaANDaceptableANDmedianamentelogrado = new FuzzyAntecedent();
	bajaANDmalaANDaceptableANDmedianamentelogrado->joinAND(bajaANDmala, aceptableANDmedianamentelogrado4);

	FuzzyRuleConsequent* thenMedia17 = new FuzzyRuleConsequent();
	thenMedia17->addOutput(mediaActuacion);

	FuzzyRule* regla31 = new FuzzyRule(31, bajaANDmalaANDaceptableANDmedianamentelogrado, thenMedia17);
	fuzzy->addFuzzyRule(regla31);

	//Regla 32 => IF (Alta y Regular y Inaceptable y No Logrado) THEN Baja

	FuzzyAntecedent* altaANDregular5 = new FuzzyAntecedent();
	altaANDregular5->joinAND(alta, regular);
	FuzzyAntecedent* inaceptableANDnologrado2 = new FuzzyAntecedent();
	inaceptableANDnologrado2->joinAND(inaceptable, no_logrado);

	FuzzyAntecedent* altaANDregularANDinaceptableANDnologrado = new FuzzyAntecedent();
	altaANDregularANDinaceptableANDnologrado->joinAND(altaANDregular5, inaceptableANDnologrado2);

	FuzzyRuleConsequent* thenBaja = new FuzzyRuleConsequent();
	thenBaja->addOutput(malaActuacion);

	FuzzyRule* regla32 = new FuzzyRule(32, altaANDregularANDinaceptableANDnologrado, thenBaja);
	fuzzy->addFuzzyRule(regla32);

	//Regla 33 => IF (Alta y Mala y Moderada y No Logrado) THEN Baja

	FuzzyAntecedent* altaANDmala5 = new FuzzyAntecedent();
	altaANDmala5->joinAND(alta, mala);
	FuzzyAntecedent* moderadaANDnologrado = new FuzzyAntecedent();
	moderadaANDnologrado->joinAND(moderada, no_logrado);

	FuzzyAntecedent* altaANDmalaANDmoderadaANDnologrado = new FuzzyAntecedent();
	altaANDmalaANDmoderadaANDnologrado->joinAND(altaANDmala5, moderadaANDnologrado);

	FuzzyRuleConsequent* thenBaja2 = new FuzzyRuleConsequent();
	thenBaja2->addOutput(malaActuacion);

	FuzzyRule* regla33 = new FuzzyRule(33, altaANDmalaANDmoderadaANDnologrado, thenBaja2);
	fuzzy->addFuzzyRule(regla33);

	//Regla 34 => IF (Alta y Mala y Inaceptable y (Medianamente Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* altaANDmala6 = new FuzzyAntecedent();
	altaANDmala6->joinAND(alta, mala);
	FuzzyAntecedent* altaANDmalaANDinaceptable2 = new FuzzyAntecedent();
	altaANDmalaANDinaceptable2->joinAND(altaANDmala6, inaceptable);

	FuzzyAntecedent* medianamentelogradoORnologrado1 = new FuzzyAntecedent();
	medianamentelogradoORnologrado1->joinOR(medianamente_logrado, no_logrado);

	FuzzyAntecedent* altaANDmalaANDinaceptableANDmedianamentelogradoORnologrado = new FuzzyAntecedent();
	altaANDmalaANDinaceptableANDmedianamentelogradoORnologrado->joinAND(altaANDmalaANDinaceptable2, medianamentelogradoORnologrado1);
	FuzzyRuleConsequent* thenBaja3 = new FuzzyRuleConsequent();
	thenBaja3->addOutput(malaActuacion);

	FuzzyRule* regla34 = new FuzzyRule(34, altaANDmalaANDinaceptableANDmedianamentelogradoORnologrado, thenBaja3);
	fuzzy->addFuzzyRule(regla34);

	//Regla 35 => IF (Media y Buena y Inaceptable y No Logrado) THEN Baja

	FuzzyAntecedent* mediaANDbuena6 = new FuzzyAntecedent();
	mediaANDbuena6->joinAND(media, buena);
	FuzzyAntecedent* inaceptableANDnologrado3 = new FuzzyAntecedent();
	inaceptableANDnologrado3->joinAND(inaceptable, no_logrado);

	FuzzyAntecedent* mediaANDbuenaANDinaceptableANDnologrado = new FuzzyAntecedent();
	mediaANDbuenaANDinaceptableANDnologrado->joinAND(mediaANDbuena6, inaceptableANDnologrado3);

	FuzzyRuleConsequent* thenBaja4 = new FuzzyRuleConsequent();
	thenBaja4->addOutput(malaActuacion);

	FuzzyRule* regla35 = new FuzzyRule(35, mediaANDbuenaANDinaceptableANDnologrado, thenBaja4);
	fuzzy->addFuzzyRule(regla35);

	//Regla 36 => IF (Media y Regular y Inaceptable y No Logrado) THEN Baja 

	FuzzyAntecedent* mediaANDregular4 = new FuzzyAntecedent();
	mediaANDregular4->joinAND(media, regular);
	FuzzyAntecedent* inaceptableANDnologrado4 = new FuzzyAntecedent();
	inaceptableANDnologrado4->joinAND(inaceptable, no_logrado);

	FuzzyAntecedent* mediaANDregularANDinaceptableANDnologrado = new FuzzyAntecedent();
	mediaANDregularANDinaceptableANDnologrado->joinAND(mediaANDregular4, inaceptableANDnologrado4);

	FuzzyRuleConsequent* thenBaja5 = new FuzzyRuleConsequent();
	thenBaja5->addOutput(malaActuacion);

	FuzzyRule* regla36 = new FuzzyRule(36, mediaANDregularANDinaceptableANDnologrado, thenBaja5);
	fuzzy->addFuzzyRule(regla36);

	//Regla 37 => IF (Media y Mala y Aceptable y No Logrado) THEN Baja

	FuzzyAntecedent* mediaANDmala3 = new FuzzyAntecedent();
	mediaANDmala3->joinAND(media, mala);
	FuzzyAntecedent* aceptableANDnologrado5 = new FuzzyAntecedent();
	aceptableANDnologrado5->joinAND(aceptable, no_logrado);

	FuzzyAntecedent* mediaANDmalaANDaceptableANDnologrado = new FuzzyAntecedent();
	mediaANDmalaANDaceptableANDnologrado->joinAND(mediaANDmala3, aceptableANDnologrado5);

	FuzzyRuleConsequent* thenBaja6 = new FuzzyRuleConsequent();
	thenBaja6->addOutput(malaActuacion);

	FuzzyRule* regla37 = new FuzzyRule(37, mediaANDmalaANDaceptableANDnologrado, thenBaja6);
	fuzzy->addFuzzyRule(regla37);

	//Regla 38 => IF (Media y Mala y Moderada y (Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* mediaANDmala4 = new FuzzyAntecedent();
	mediaANDmala4->joinAND(media, mala);
	FuzzyAntecedent* mediaANDmalaANDmoderada2 = new FuzzyAntecedent();
	mediaANDmalaANDmoderada2->joinAND(mediaANDmala4, moderada);

	FuzzyAntecedent* logradoORnologrado = new FuzzyAntecedent();
	logradoORnologrado->joinOR(logrado, no_logrado);

	FuzzyAntecedent* mediaANDmalaANDmoderadaANDlogradoORnologrado = new FuzzyAntecedent();
	mediaANDmalaANDmoderadaANDlogradoORnologrado->joinAND(mediaANDmalaANDmoderada2, logradoORnologrado);

	FuzzyRuleConsequent* thenBaja7 = new FuzzyRuleConsequent();
	thenBaja7->addOutput(malaActuacion);

	FuzzyRule* regla38 = new FuzzyRule(38, mediaANDmalaANDmoderadaANDlogradoORnologrado, thenBaja7);
	fuzzy->addFuzzyRule(regla38);

	//Regla 39 => IF (Media y Mala y Inaceptable y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* mediaANDmala5 = new FuzzyAntecedent();
	mediaANDmala5->joinAND(media, mala);
	FuzzyAntecedent* mediaANDmalaANDinaceptable = new FuzzyAntecedent();
	mediaANDmalaANDinaceptable->joinAND(mediaANDmala5, inaceptable);

	FuzzyAntecedent* logradoORmedianamentelogrado5 = new FuzzyAntecedent();
	logradoORmedianamentelogrado5->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORmedianamentelogradoORnologrado2 = new FuzzyAntecedent();
	logradoORmedianamentelogradoORnologrado2->joinOR(logradoORmedianamentelogrado5, no_logrado);


	FuzzyAntecedent* mediaANDmalaANDinaceptableANDlogradoORmedianamentelogradoORlogrado = new FuzzyAntecedent();
	mediaANDmalaANDinaceptableANDlogradoORmedianamentelogradoORlogrado->joinAND(mediaANDmalaANDinaceptable, logradoORmedianamentelogradoORnologrado2);

	FuzzyRuleConsequent* thenBaja8 = new FuzzyRuleConsequent();
	thenBaja8->addOutput(malaActuacion);

	FuzzyRule* regla39 = new FuzzyRule(39, mediaANDmalaANDinaceptableANDlogradoORmedianamentelogradoORlogrado, thenBaja8);
	fuzzy->addFuzzyRule(regla39);

	//Regla 40 => IF (Baja y Buena y Moderada y No logrado) THEN Baja

	FuzzyAntecedent* bajaANDbuena5 = new FuzzyAntecedent();
	bajaANDbuena5->joinAND(baja, buena);
	FuzzyAntecedent* moderadaANDnologrado2 = new FuzzyAntecedent();
	moderadaANDnologrado2->joinAND(moderada, no_logrado);

	FuzzyAntecedent* bajaANDbuenaANDmoderadaANDnologrado = new FuzzyAntecedent();
	bajaANDbuenaANDmoderadaANDnologrado->joinAND(bajaANDbuena5, moderadaANDnologrado2);

	FuzzyRuleConsequent* thenBaja9 = new FuzzyRuleConsequent();
	thenBaja9->addOutput(malaActuacion);

	FuzzyRule* regla40 = new FuzzyRule(40, bajaANDbuenaANDmoderadaANDnologrado, thenBaja9);
	fuzzy->addFuzzyRule(regla40);

	//Regla 41 => IF (Baja y Buena y Inaceptable y (Medianamente Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* bajaANDbuena6 = new FuzzyAntecedent();
	bajaANDbuena6->joinAND(baja, buena);
	FuzzyAntecedent* bajaANDbuenaANDinaceptable2 = new FuzzyAntecedent();
	bajaANDbuenaANDinaceptable2->joinAND(bajaANDbuena6, inaceptable);

	FuzzyAntecedent* medianamentelogradoORnologrado2 = new FuzzyAntecedent();
	medianamentelogradoORnologrado2->joinOR(medianamente_logrado, no_logrado);

	FuzzyAntecedent* bajaANDbuenaANDinaceptableANDmedianamentelogradoORnologrado = new FuzzyAntecedent();
	bajaANDbuenaANDinaceptableANDmedianamentelogradoORnologrado->joinAND(bajaANDbuenaANDinaceptable2, medianamentelogradoORnologrado2);

	FuzzyRuleConsequent* thenBaja10 = new FuzzyRuleConsequent();
	thenBaja10->addOutput(malaActuacion);

	FuzzyRule* regla41 = new FuzzyRule(41, bajaANDbuenaANDinaceptableANDmedianamentelogradoORnologrado, thenBaja10);
	fuzzy->addFuzzyRule(regla41);

	//Regla 42 => IF (Baja y Regular y Aceptable y No Logrado) THEN Baja

	FuzzyAntecedent* bajaANDregular4 = new FuzzyAntecedent();
	bajaANDregular4->joinAND(baja, regular);
	FuzzyAntecedent* aceptableANDnologrado6 = new FuzzyAntecedent();
	aceptableANDnologrado6->joinAND(aceptable, no_logrado);

	FuzzyAntecedent* bajaANDregularANDaceptableANDnologrado = new FuzzyAntecedent();
	bajaANDregularANDaceptableANDnologrado->joinAND(bajaANDregular4, aceptableANDnologrado6);

	FuzzyRuleConsequent* thenBaja11 = new FuzzyRuleConsequent();
	thenBaja11->addOutput(malaActuacion);

	FuzzyRule* regla42 = new FuzzyRule(42, bajaANDregularANDaceptableANDnologrado, thenBaja11);
	fuzzy->addFuzzyRule(regla42);

	//Regla 43 => IF (Baja y Regular y Moderada y No Logrado) THEN Baja

	FuzzyAntecedent* bajaANDregular5 = new FuzzyAntecedent();
	bajaANDregular5->joinAND(baja, regular);
	FuzzyAntecedent* moderadaANDnologrado3 = new FuzzyAntecedent();
	moderadaANDnologrado3->joinAND(moderada, no_logrado);

	FuzzyAntecedent* bajaANDregularANDmoderadaANDnologrado = new FuzzyAntecedent();
	bajaANDregularANDmoderadaANDnologrado->joinAND(bajaANDregular5, moderadaANDnologrado3);

	FuzzyRuleConsequent* thenBaja12 = new FuzzyRuleConsequent();
	thenBaja12->addOutput(malaActuacion);

	FuzzyRule* regla43 = new FuzzyRule(43, bajaANDregularANDmoderadaANDnologrado, thenBaja12);
	fuzzy->addFuzzyRule(regla43);

	//Regla 44 => IF (Baja y Regular y Inaceptable y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* bajaANDregular6 = new FuzzyAntecedent();
	bajaANDregular6->joinAND(baja, regular);
	FuzzyAntecedent* bajaANDregularANDinaceptable = new FuzzyAntecedent();
	bajaANDregularANDinaceptable->joinAND(bajaANDregular6, inaceptable);

	FuzzyAntecedent* logradoORmedianamentelogrado6 = new FuzzyAntecedent();
	logradoORmedianamentelogrado6->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORmedianamentelogradoORnologrado3 = new FuzzyAntecedent();
	logradoORmedianamentelogradoORnologrado3->joinOR(logradoORmedianamentelogrado6, no_logrado);


	FuzzyAntecedent* bajaANDregularANDinaceptableANDlogradoORmedianamentelogradoORnologrado = new FuzzyAntecedent();
	bajaANDregularANDinaceptableANDlogradoORmedianamentelogradoORnologrado->joinAND(bajaANDregularANDinaceptable, logradoORmedianamentelogradoORnologrado3);

	FuzzyRuleConsequent* thenBaja13 = new FuzzyRuleConsequent();
	thenBaja13->addOutput(malaActuacion);

	FuzzyRule* regla44 = new FuzzyRule(44, bajaANDregularANDinaceptableANDlogradoORmedianamentelogradoORnologrado, thenBaja13);
	fuzzy->addFuzzyRule(regla44);

	//Regla 45 => IF (Baja y Mala y Aceptable y (Logrado OR No Logrado) THEN Baja

	FuzzyAntecedent* bajaANDmala2 = new FuzzyAntecedent();
	bajaANDmala2->joinAND(baja, mala);
	FuzzyAntecedent* bajaANDmalaANDaceptable2 = new FuzzyAntecedent();
	bajaANDmalaANDaceptable2->joinAND(bajaANDmala2, aceptable);

	FuzzyAntecedent* logradoORnologrado4 = new FuzzyAntecedent();
	logradoORnologrado4->joinOR(logrado, no_logrado);

	FuzzyAntecedent* bajaANDmalaANDaceptableANDlogradoORnologrado = new FuzzyAntecedent();
	bajaANDmalaANDaceptableANDlogradoORnologrado->joinAND(bajaANDmalaANDaceptable2, logradoORnologrado4);

	FuzzyRuleConsequent* thenBaja14 = new FuzzyRuleConsequent();
	thenBaja14->addOutput(malaActuacion);

	FuzzyRule* regla45 = new FuzzyRule(45, bajaANDmalaANDaceptableANDlogradoORnologrado, thenBaja14);
	fuzzy->addFuzzyRule(regla45);

	//Regla 46 => IF (Baja y Mala y Moderada y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* bajaANDmala3 = new FuzzyAntecedent();
	bajaANDmala3->joinAND(baja, mala);
	FuzzyAntecedent* bajaANDmalaANDmoderada = new FuzzyAntecedent();
	bajaANDregularANDinaceptable->joinAND(bajaANDmala3, moderada);

	FuzzyAntecedent* logradoORmedianamentelogrado7 = new FuzzyAntecedent();
	logradoORmedianamentelogrado7->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORmedianamentelogradoORnologrado4 = new FuzzyAntecedent();
	logradoORmedianamentelogradoORnologrado4->joinOR(logradoORmedianamentelogrado7, no_logrado);


	FuzzyAntecedent* bajaANDmalaANDmoderadaANDlogradoORmedianamentelogradoORnologrado = new FuzzyAntecedent();
	bajaANDmalaANDmoderadaANDlogradoORmedianamentelogradoORnologrado->joinAND(bajaANDmalaANDmoderada, logradoORmedianamentelogradoORnologrado4);

	FuzzyRuleConsequent* thenBaja15 = new FuzzyRuleConsequent();
	thenBaja15->addOutput(malaActuacion);

	FuzzyRule* regla46 = new FuzzyRule(46, bajaANDmalaANDmoderadaANDlogradoORmedianamentelogradoORnologrado, thenBaja15);
	fuzzy->addFuzzyRule(regla46);

	//Regla 47 => IF (Baja y Mala y Inaceptable y (Logrado OR Medianamente Logrado OR No Logrado)) THEN Baja

	FuzzyAntecedent* bajaANDmala4 = new FuzzyAntecedent();
	bajaANDmala4->joinAND(baja, mala);
	FuzzyAntecedent* bajaANDmalaANDinaceptable = new FuzzyAntecedent();
	bajaANDmalaANDinaceptable->joinAND(bajaANDmala4, inaceptable);

	FuzzyAntecedent* logradoORmedianamentelogrado8 = new FuzzyAntecedent();
	logradoORmedianamentelogrado8->joinOR(logrado, medianamente_logrado);
	FuzzyAntecedent* logradoORmedianamentelogradoORnologrado5 = new FuzzyAntecedent();
	logradoORmedianamentelogradoORnologrado5->joinOR(logradoORmedianamentelogrado8, no_logrado);


	FuzzyAntecedent* bajaANDmalaANDinaceptableANDlogradoORmedianamentelogradoORnologrado = new FuzzyAntecedent();
	bajaANDmalaANDinaceptableANDlogradoORmedianamentelogradoORnologrado->joinAND(bajaANDmalaANDinaceptable, logradoORmedianamentelogradoORnologrado5);

	FuzzyRuleConsequent* thenBaja16 = new FuzzyRuleConsequent();
	thenBaja16->addOutput(malaActuacion);

	FuzzyRule* regla47 = new FuzzyRule(47, bajaANDmalaANDinaceptableANDlogradoORmedianamentelogradoORnologrado, thenBaja16);
	fuzzy->addFuzzyRule(regla47);

	//Crisp value input

	fuzzy->setInput(1, 1.0f);
	fuzzy->setInput(2, 1.0f);
	fuzzy->setInput(3, 140.0f);
	fuzzy->setInput(4, 4.0f);

	//Fusification

	fuzzy->fuzzify();

	cout << endl;
	cout << "Autonomia" << endl;
	cout << "Pertenencia Alta: " << alta->getPertinence() << " Pertenencia Media: " << media->getPertinence() << " Pertenencia Baja: " << baja->getPertinence() << endl;
	cout << endl;
	cout << "Eficacia" << endl;
	cout << "Pertenencia Buena: " << buena->getPertinence() << " Pertenencia Regular: " << regular->getPertinence() << " Pertenencia Mala: " << mala->getPertinence() << endl;
	cout << endl;
	cout << "Motivacion" << endl;
	cout << "Pertenencia Aceptable: " << aceptable->getPertinence() << " Pertenencia Moderada: " << moderada->getPertinence() << " Pertenencia Inaceptable: " << inaceptable->getPertinence() << endl;
	cout << endl;
	cout << "Desempeño" << endl;
	cout << "Pertenencia Logrado: " << logrado->getPertinence() << " Pertenencia Medianamente Logrado: " << medianamente_logrado->getPertinence() << " Pertenencia No Logrado: " << no_logrado->getPertinence() << endl;

	//Imprimo las reglas

	cout << "Valor Regla 1: " << regla1->getPowerOfRule() << "  Activacion: " << regla1->isFired() << endl;
	cout << "Valor Regla 2: " << regla2->getPowerOfRule() << "  Activacion: " << regla2->isFired() << endl;
	cout << "Valor Regla 3: " << regla3->getPowerOfRule() << "  Activacion: " << regla3->isFired() << endl;
	cout << "Valor Regla 4: " << regla4->getPowerOfRule() << "  Activacion: " << regla4->isFired() << endl;
	cout << "Valor Regla 5: " << regla5->getPowerOfRule() << "  Activacion: " << regla5->isFired() << endl;
	cout << "Valor Regla 6: " << regla6->getPowerOfRule() << "  Activacion: " << regla6->isFired() << endl;
	cout << "Valor Regla 7: " << regla7->getPowerOfRule() << "  Activacion: " << regla7->isFired() << endl;
	cout << "Valor Regla 8: " << regla8->getPowerOfRule() << "  Activacion: " << regla8->isFired() << endl;
	cout << "Valor Regla 9: " << regla9->getPowerOfRule() << "  Activacion: " << regla9->isFired() << endl;
	cout << "Valor Regla 10: " << regla10->getPowerOfRule() << "  Activacion: " << regla10->isFired() << endl;
	cout << "Valor Regla 11: " << regla11->getPowerOfRule() << "  Activacion: " << regla11->isFired() << endl;
	cout << "Valor Regla 12: " << regla12->getPowerOfRule() << "  Activacion: " << regla12->isFired() << endl;
	cout << "Valor Regla 13: " << regla13->getPowerOfRule() << "  Activacion: " << regla13->isFired() << endl;
	cout << "Valor Regla 14: " << regla14->getPowerOfRule() << "  Activacion: " << regla14->isFired() << endl;
	cout << "Valor Regla 15: " << regla15->getPowerOfRule() << "  Activacion: " << regla15->isFired() << endl;
	cout << "Valor Regla 16: " << regla16->getPowerOfRule() << "  Activacion: " << regla16->isFired() << endl;
	cout << "Valor Regla 17: " << regla17->getPowerOfRule() << "  Activacion: " << regla17->isFired() << endl;
	cout << "Valor Regla 18: " << regla18->getPowerOfRule() << "  Activacion: " << regla18->isFired() << endl;
	cout << "Valor Regla 19: " << regla19->getPowerOfRule() << "  Activacion: " << regla19->isFired() << endl;
	cout << "Valor Regla 20: " << regla20->getPowerOfRule() << "  Activacion: " << regla20->isFired() << endl;
	cout << "Valor Regla 21: " << regla21->getPowerOfRule() << "  Activacion: " << regla21->isFired() << endl;
	cout << "Valor Regla 22: " << regla22->getPowerOfRule() << "  Activacion: " << regla22->isFired() << endl;
	cout << "Valor Regla 23: " << regla23->getPowerOfRule() << "  Activacion: " << regla23->isFired() << endl;
	cout << "Valor Regla 24: " << regla24->getPowerOfRule() << "  Activacion: " << regla24->isFired() << endl;
	cout << "Valor Regla 25: " << regla25->getPowerOfRule() << "  Activacion: " << regla25->isFired() << endl;
	cout << "Valor Regla 26: " << regla26->getPowerOfRule() << "  Activacion: " << regla26->isFired() << endl;
	cout << "Valor Regla 27: " << regla27->getPowerOfRule() << "  Activacion: " << regla27->isFired() << endl;
	cout << "Valor Regla 28: " << regla28->getPowerOfRule() << "  Activacion: " << regla28->isFired() << endl;
	cout << "Valor Regla 29: " << regla29->getPowerOfRule() << "  Activacion: " << regla29->isFired() << endl;
	cout << "Valor Regla 30: " << regla30->getPowerOfRule() << "  Activacion: " << regla30->isFired() << endl;
	cout << "Valor Regla 31: " << regla31->getPowerOfRule() << "  Activacion: " << regla31->isFired() << endl;
	cout << "Valor Regla 32: " << regla32->getPowerOfRule() << "  Activacion: " << regla32->isFired() << endl;
	cout << "Valor Regla 33: " << regla33->getPowerOfRule() << "  Activacion: " << regla33->isFired() << endl;
	cout << "Valor Regla 34: " << regla34->getPowerOfRule() << "  Activacion: " << regla34->isFired() << endl;
	cout << "Valor Regla 35: " << regla35->getPowerOfRule() << "  Activacion: " << regla35->isFired() << endl;
	cout << "Valor Regla 36: " << regla36->getPowerOfRule() << "  Activacion: " << regla36->isFired() << endl;
	cout << "Valor Regla 37: " << regla37->getPowerOfRule() << "  Activacion: " << regla37->isFired() << endl;
	cout << "Valor Regla 38: " << regla38->getPowerOfRule() << "  Activacion: " << regla38->isFired() << endl;
	cout << "Valor Regla 39: " << regla39->getPowerOfRule() << "  Activacion: " << regla39->isFired() << endl;
	cout << "Valor Regla 40: " << regla40->getPowerOfRule() << "  Activacion: " << regla40->isFired() << endl;
	cout << "Valor Regla 41: " << regla41->getPowerOfRule() << "  Activacion: " << regla41->isFired() << endl;
	cout << "Valor Regla 42: " << regla42->getPowerOfRule() << "  Activacion: " << regla42->isFired() << endl;
	cout << "Valor Regla 43: " << regla43->getPowerOfRule() << "  Activacion: " << regla43->isFired() << endl;
	cout << "Valor Regla 44: " << regla44->getPowerOfRule() << "  Activacion: " << regla44->isFired() << endl;
	cout << "Valor Regla 45: " << regla45->getPowerOfRule() << "  Activacion: " << regla45->isFired() << endl;
	cout << "Valor Regla 46: " << regla46->getPowerOfRule() << "  Activacion: " << regla46->isFired() << endl;
	cout << "Valor Regla 47: " << regla47->getPowerOfRule() << "  Activacion: " << regla47->isFired() << endl;


	cout << endl;
	cout << "Pertenencias salida: " << endl;
	cout << "Pertenencia Buena: " << buenaActuacion->getPertinence() << "  Pertenencia Regular: " << mediaActuacion->getPertinence() << "  Pertenencia Mala: " << malaActuacion->getPertinence() << endl;

	//Defusification

	float output = fuzzy->defuzzify(1);

	cout << endl;
	cout << "Salida defusificada: " << output << endl;

	cin.get();
}

