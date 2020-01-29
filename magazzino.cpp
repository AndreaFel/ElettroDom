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
void magazzino::remove(string id, int pezzi)
{	int i = check(id);
	if(i<0)
		return; //elemento non presente
	//se non ci sono abbastanza pezzi
	if(oggetti[i].pezzi < pezzi)
		oggetti[i].pezzi = 0;
	
	else
		oggetti[i].pezzi -= pezzi; //ci sono abbastanza componenti
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
		return pezzi;	//ritorna quanti se ne toglierebbero
	return oggetti[i].pezzi; //andrebbero tolti tutti
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
			cout<<"ID: "<<oggetti[i].id<<"\tPEZZI: "<<oggetti[i].pezzi<<"\n";
}

//funzione magazzinoToString() che restituisce una stringa con i componenti nel magazzino con le relative quantita' in ordine alfabetico
std::string magazzino::magazzinoToString() const
{	string output = "";
	for(int i=0;i<oggetti.size();i++)
			output = output + "ID: " + oggetti[i].id + "\tPEZZI: " + to_string(oggetti[i].pezzi) + "\n";
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
