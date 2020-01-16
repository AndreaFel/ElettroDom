//Autore: Edoardo Bastianello , numero matricola: 1188629
//sorgente con le definizioni delle funzioni della classe "magazzino.h"

using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include "magazzino.h"

//costruttore
magazzino::magazzino()
	:oggetti{}
{}

//funzione add
void magazzino::add(string id, int pezzi)
{	//creazione oggetto da inserire
	Coppia nuova{};
	nuova.id = id;
	nuova.pezzi = pezzi;
	//controllo se e' gia' presente il componente in magazzino
	//se e' gia presente aggiungo un numero di componenti pari a "pezzi" a quelli gia' presenti in magazzino
	int i = -1;
	i = check(id);
	if(i>-1)
	{	oggetti[i].pezzi += pezzi;
		return;
	}
	//se non e' presente creo una nuova cella per il relativo componente e ordino il vettore in ordine alfabetico secondo "id"
	//insertion sort
	int j = 0;
	Coppia x{};
	oggetti.push_back(x);
	for(j = oggetti.size()-1; j>0 && id<oggetti[j-1].id; j--)
		oggetti[j] = oggetti[j-1];
	oggetti[j] = nuova;
}


//funzione remove
int magazzino::remove(string id, int pezzi)
{	int daOrdinare = 0;
	int i = check(id);
	if(i<0)
		return -1; //elemento non presente
	//se non ci sono abbastanza pezzi
	if(oggetti[i].pezzi < pezzi)
	{	daOrdinare = daOridinareOltreAiRimossi(pezzi, i);
		oggetti[i].pezzi = 0;
		return daOrdinare;	//restituisce il numero di componenti da ordinare
	}
	oggetti[i].pezzi -= pezzi;
	return daOrdinare; //ci sono abbastanza componenti
}


//funzione check
int magazzino::check(string id)
{	int index = binSearchCoppie(oggetti, 0, oggetti.size()-1, id);
	return index;	//restituisce l'indice del componente cercato, restituisce -1 se non presente
}


//funzione checkEnough
int magazzino::checkEnough(string id, int pezzi)
{	int i = check(id);
	if(i<0)
		return -1;
	if(oggetti[i].pezzi > pezzi)
		return 0;	//non serve ordinare altri pezzi
	return pezzi - oggetti[i].pezzi; //numero di pezzi da ordinare oltre a quelli presenti in magazzino
}

//funzioni di lettura
string magazzino::getId(int i)const
{	if(i<0 || i>=oggetti.size())
		return "indice non valido";
	return oggetti[i].id;
}

int magazzino::getPezzi(int i)const
{	if(i<0 || i>=oggetti.size())
		return -1;
	return oggetti[i].pezzi;
}

//funzione di stampa
void magazzino::printMagazzino()const
{	for(int i=0;i<oggetti.size();i++)
			cout<<"ID componente: "<<oggetti[i].id<<" || numero di tale componente: "<<oggetti[i].pezzi<<"\n";
}

//funzione magazzinoToString() che restituisce una stringa con i componenti nel magazzino con le relative quantita' in ordine alfabetico
std::string magazzino::magazzinoToString() const
{	string output = "";
	for(int i=0;i<oggetti.size();i++)
			output = output + "ID componente: " + oggetti[i].id + " || numero di tale componente: " + to_string(oggetti[i].pezzi) + "\n";
	return output;
}

//***********************************************************************************************
//funzioni private della classe magazzino
int magazzino::binSearchCoppie(const vector<Coppia>& a, int from, int to, string toFind)
{	if(from>to) return -1;	//non trovato
	int mid = (from+to)/2;
	string middle = oggetti[mid].id;
	if(middle == toFind)
		return mid;
	if(middle<toFind)
		return binSearchCoppie(a, mid+1, to, toFind);
	return binSearchCoppie(a, from, mid-1, toFind);
}

int magazzino::daOridinareOltreAiRimossi(int pezzi, int index)
{	if(oggetti[index].pezzi > pezzi)
		return 0;	//non serve ordinare altri pezzi
	return pezzi - oggetti[index].pezzi; //numero di pezzi da ordinare oltre a quelli rimossi dal magazzino
}
