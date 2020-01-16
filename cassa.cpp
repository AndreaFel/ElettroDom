//Autore: Edoardo Bastianello , numero matricola: 1188629
//sorgente che contiene le definizioni delle funzioni della classe "cassa.h"

using namespace std;
#include <iostream>
#include "cassa.h"

//costruttore
cassa::cassa(double start)
	:fondo{start}
{}

//funzione addFondo
void cassa::addFondo(double vendita)
{	fondo += vendita;
}

//funzione subtractFondo
//lancia Invalid{} se il saldo richesto e' maggiore del fondo
void cassa::subtractFondo(double price)
{	if(!check(price))
		throw new Invalid{};
	fondo -= price;
}

//funzione di stampa
void cassa::printFondo()const
{	cout << fondo << '\n';
}

//funzione getFondo
double cassa::getFondo()const
{	return fondo;
}

//funzione check
bool cassa::check(double price)
{	if(price > fondo)
		return false;
	return true;
}
