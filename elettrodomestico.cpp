//Autore: Edoardo Bastianello , numero matricola: 1188629
//sorgente che contiene le definizioni delle funzioni della classe "elettrodomestico"

using namespace std;
#include <vector>
#include <string>
#include "componente.h"
#include "componentiElettrodomestico.h"
#include "elettrodomestico.h"

//costruttore
elettrodomestico::elettrodomestico(string idIns, string nomeIns, double prezzoVenditaIns)
	:id{idIns}, nome{nomeIns}, prezzoVendita{prezzoVenditaIns}, lstComponenti{}
{}

//funzioni di lettura
string elettrodomestico::getId()const
{	return id;
}

double elettrodomestico::getPrezzoVendita()const
{	return prezzoVendita;
}

string elettrodomestico::getNome()const
{	return nome;
}

vector<componentiElettrodomestico> elettrodomestico::getComponents()const
{	return lstComponenti;
}


//funzione addComponentToLst
void elettrodomestico::addComponentToLst(componente ins, int quantity)
{	componentiElettrodomestico inserito{ins, quantity};
	lstComponenti.push_back(inserito);
}

