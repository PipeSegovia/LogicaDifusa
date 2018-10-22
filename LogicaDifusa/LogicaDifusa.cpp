#include "pch.h"
#include "FuzzyInput.h"
#include "FuzzySet.h"
#include "Fuzzy.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Logica Difusa" << endl;

	//Fuzzy: Clase que permite fusificar y defusificar
	Fuzzy* fuzzy = new Fuzzy();

	//Tipo de funcion de pertenencia
	int const L = 1;
	int const GAMMA = 2;
	int const TRAPEZOIDE = 3;


	//Ingreso las entradas difusas (FUZZY INPUT)
	FuzzyInput *tipoSonido = new FuzzyInput(1);
	FuzzyInput *duracion = new FuzzyInput(2);
	FuzzyInput *intensidad = new FuzzyInput(3);

	//Creo los conjuntos difusos (FuzzySet) y los añado a cada entrada difusa (FuzzyInput)

	//FuzzySet para Tipo sonido
	FuzzySet* otro = new FuzzySet(0.3f,0.4f,0.0f,0.0f,L);
	FuzzySet* humano = new FuzzySet(0.3f,0.4f,0.6f,0.8f,TRAPEZOIDE);
	FuzzySet* bebe = new FuzzySet(0.6f,0.8f,0.0,0.0,GAMMA);

	//Se agregan los conjuntos difusos a tipo sonido
	tipoSonido->addFuzzySet(otro);
	tipoSonido->addFuzzySet(humano);
	tipoSonido->addFuzzySet(bebe);

	//FuzzySet para duracion

	FuzzySet* puntual = new FuzzySet(0.1f,0.2f,0.0f,0.0f,L);
	FuzzySet* normal = new FuzzySet(0.1f,0.2f,0.5f,0.7f,TRAPEZOIDE);
	FuzzySet* continuo = new FuzzySet(0.5f,0.7f,0.0f,0.0f,GAMMA);

	//Se agregan los conjuntos difusos a duracion
	duracion->addFuzzySet(puntual);
	duracion->addFuzzySet(normal);
	duracion->addFuzzySet(continuo);

	//FuzzySet para intensidad
	FuzzySet* debil = new FuzzySet(0.4f,0.6f,0.0f,0.0f,L);
	FuzzySet* fuerte = new FuzzySet(0.4f,0.6f,0.0f,0.0f,GAMMA);

	//Se agregan los conjuntos difusos a intensidad
	intensidad->addFuzzySet(debil);
	intensidad->addFuzzySet(fuerte);

	//Ingreso las salidas difusas


	//Creo las reglas 

	

	//Agrego las entradas difusas a la clase Fuzzy
	fuzzy->addFuzzyInput(tipoSonido);
	fuzzy->addFuzzyInput(duracion);
	fuzzy->addFuzzyInput(intensidad);

	//Agrego las salidas difusas a la clase fuzzy

	//Ingreso los valores de entrada
	fuzzy->setInput(1, 0.75f);
	fuzzy->setInput(2, 0.57f);
	fuzzy->setInput(3, 0.54f);


	//Fusifico
	fuzzy->fuzzify();

	cout << "Pertenencia otro: " << otro->getPertinence() << "	Humano: " << humano->getPertinence() << "	bebe: " << bebe->getPertinence() << endl;
	cout << "Pertenencia puntual: " << puntual->getPertinence() << "	normal: " << normal->getPertinence() << "	continuo: " << continuo->getPertinence() << endl;
	cout << "Pertenencia debil: " << debil->getPertinence() << "	Fuerte: " << fuerte->getPertinence() << endl;

	

	cin.get();
}

