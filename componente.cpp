//Autore: Edoardo Bastianello , numero matricola: 1188629
//sorgente che contiene le definizioni delle funzioni dichiarate nell'header "componente.h"


using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include "componente.h"

//costruttore
componente::componente(string idIns, string nomeIns, int mesiIns, vector<double> prezziIns)
	:id{idIns}, nome{nomeIns}, mesi{mesiIns}, prezzi{prezziIns}
{}

//funzioni di lettura
string componente::getId()const
{	return id;
}

string componente::getNome()const
{	return nome;
}

int componente::getMesi()const
{	return mesi;
}

//restituisce -1 se viene fornito un parametro minore di 1
double componente::getPrezzo(int pezzi)const
{	if(pezzi > 0 && pezzi < 11)
		return prezzi[0];
	if(pezzi >= 11 && pezzi < 51)
		return prezzi[1];
	if(pezzi >= 51)
		return prezzi[2];
	return -1;
}
