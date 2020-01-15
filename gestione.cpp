//Autore: Simone Cecchinato , numero matricola: 1195817
//sorgente che contiene le definizioni delle funzioni dichiarate nell'header "componente.h"


#include "Componente.h"
#include "elettrodomestico.h"
#include "gestione.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

Gestione::Gestione(){
	FileElettrodomestici();
	FileOrdini();
	mese=0;
}

string Gestione::ordiniInArrivo(){
	string s="Sono stati ordinati i seguenti componenti:";
	for(int i=0;i<inArrivo.size();i++){
		s<<"ID: "<<inArrivo[i].id<<" PEZZI: "<<inArrivo.pezzi<<"\n";
	}
	return s;
}

string Gestione::inventario(){
	string s = "Inventario Magazzino:";
	s<<mag.printMagazzino();
	return s;
}

string Gestione::ordiniEvasi(){
	string s = "Sono stati evasi i seguenti ordini finora";
	vector<ordini> v = ord.getEvasi();
	for(int i=0;i<v.size();i++)
		s<<"ID MODELLO: "<<v[i].id<<" QTA': "<<v[i].quantita<<"\n";
	return s;
}

vector<componente> Gestione::FileComponenti(){  //Lettura file "components_info.dat"
	string id, nome;
	int time_stamp = 0;
	vector<double> prezzi {3};
	vector<componente> comps;
	
	ifstream compIn (".//ElettroDom//components_info.dat");        //RIGA: [id] [nome] [timestamp] [prezzo1:10] [prezzo11:50] [prezzo51+]
	if (compIn.is_open()){
		while (!compIn.eof()){
			compIn>>id>>nome>>time_stamp>>prezzi[0]>>prezzi[1]>>prezzi[2];
			componente c {id,nome,time_stamp,prezzi};
			comps.push_back(c);                   //Memorizzazione dei componenti per poi inviarli alla classe Elettrodomestici dopo lettura altro file
		}
		compIn.close();
	}
	
	return comps;
}

//funzione fatta da Andrea Felline, matricola: 1195927
void Gestione::FileOrdini(){  //lettura file "orders.dat"
	string model_id;
	int time_stamp = 0, quantita = 0;
	
	ifstream ordersIn (".//ElettroDom//orders.dat");      //RIGA: [time_stamp] [model_id] [quantity]
	if (ordersIn.is_open()){
		double fondo;
		ordersIn>>fondo;
		cash.addFondo(fondo);
		while (!ordersIn.eof()){
			ordersIn>>time_stamp>>model_id>>quantita;
			ord.addOrdine(model_id, quantita, time_stamp);
		}
		ordersIn.close();
	}
}


vector<string> Gestione::FileModelli(){
	vector<string> models;
	ifstream modelsIn (".//ElettroDom//models.dat");
	if (modelsIn.is_open()){
		while (!modelsIn.eof()){
			string model;
			modelsIn>>model;
			models.push_back(model);
		}
		modelsIn.close();
	}
	return models;
}

void Gestione::FileElettrodomestici(){  //lettura file "modelx.dat"
	vector<componente> comps = FileComponenti();
	vector<string> models=FileModelli();
	
	for(int i=0;i<models.size();i++){
		ifstream modelIn (".//ElettroDom//"+models[i]);
		
		string id, nome;
		int tmp;
		modelIn>>id>>nome>>tmp;
		elettrodomestico e {id, nome, tmp};
		if (modelIn.is_open()){
			while(!modelIn.eof()){
				//id name quant
				modelIn>>id>>nome>>tmp;
				for(int j=0;j<comps.size();j++)
					if(comps[j].getId()==id){
						e.addComponentToLst(comps[j], tmp);
						break;
					}
			}
		}
		db.push_back(e);
	}
}

void Gestione::aggiornaMese(){
	Sleep(3000);      //blocca il programma per 3 secondi e incrementa il mese
	mese++;
}

bool Gestione::checkCassa(double d){
	return cash.check(d);
}

void Gestione::ProduzioneMese(){

	string model_id;
	int quantita = 0;

	vector<ordini> prod_mese = ord.getOrdini(mese);
	for(int i=0;i<prod_mese.size();i++){
		model_id = prod_mese[i].id;
		quantita = prod_mese[i].quantita;
		mese_ord = prod_mese[i].mese;

		int pos = -1;
		for(int j=0;j<db.size();j++){    //check presenza del modello di elettrodomestico che si vuole ordinare
			if(db[j].getId() == model_id){
				pos = j;
				break;
			} 
		}

		if(pos == -1) ord.annullaOrdine(model_id);  //se non viene trovato, l'ordine è annullato
		else{
			if(!cash.Check(db[pos].getCostoProduzione)) ord.annullaOrdine(prod_mese[i].id); //check costo di produzione dell'elettrodomestico
			else{
				vector<componentiElettrodomestico> comp_nec = db[pos].getComponents();
				vector<componenti> da_ordinare;
				for(int k=0;k<comp_nec.size();k++){
					if(mag.checkEnough(comp_nec.getComponente().getId(),comp_nec.getPezzi()*quantita)!=0){
						da_ordinare.push_back(componenti())
					}

				}


			}


		}

		
	}
}
