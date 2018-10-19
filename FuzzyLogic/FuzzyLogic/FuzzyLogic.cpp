// FuzzyLogic.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include "FuzzyInput.h"
#include "FuzzySet.h"

using namespace std;

int main()
{
	int const L = 1;
	int const GAMMA = 2;
	int const TRAPEZOIDAL = 3;

    cout << "Proyecto de Logica Difusa" << endl;
	cout << "Creado por: Felipe Segovia Rodriguez" << endl;
	cout << endl;
	cout << endl;

	//Creo las variables de entrada en la clase FuzzyInput
	FuzzyInput *tipoSonido = new FuzzyInput(1);
	
	FuzzySet* otro = new FuzzySet(0.3f,0.4f,0.0f,0.0f,L);
	tipoSonido->addFuzzySet(otro);
	FuzzySet* bebe = new FuzzySet(0.3f,0.4f,0.6f,0.8f,TRAPEZOIDAL);
	tipoSonido->addFuzzySet(otro);
	FuzzySet* humano = new FuzzySet(0.6f,0.8f,0.0f,0.0f,GAMMA);
	tipoSonido->addFuzzySet(otro);

	FuzzyInput *intensidad = new FuzzyInput(2);

	FuzzySet* debil = new FuzzySet(0.4f,0.6f,0.0f,0.0f,L);
	intensidad->addFuzzySet(debil);
	FuzzySet* fuerte = new FuzzySet(0.4f,0.6f,0.0f,0.0f,GAMMA);
	intensidad->addFuzzySet(fuerte);

	FuzzyInput *duracion = new FuzzyInput(3);

	FuzzySet *puntual = new FuzzySet(0.1f,0.2f,0.0f,0.0f,L);
	duracion->addFuzzySet(puntual);
	FuzzySet *natural = new FuzzySet(0.1f,0.2f,0.5f,0.7f,TRAPEZOIDAL);
	duracion->addFuzzySet(natural);
	FuzzySet *continuo = new FuzzySet(0.5f,0.7f,0.0f,0.0f,GAMMA);
	duracion->addFuzzySet(continuo);

	cin.get();
}
