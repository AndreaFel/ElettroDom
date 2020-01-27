//Autore: Simone Cecchinato , numero matricola: 1195817
//sorgente che contiene le definizioni delle funzioni dichiarate nell'header "gestione.h"


#include <vector>
#include <iostream>
#include "componente.h"
#include "componentiElettrodomestico.h"
#include "elettrodomestico.h"
#include "cassa.h"
#include "magazzino.h"
#include "Ordine.h"
#include "gestione.h"
#include <fstream>
//#include <windows.h>
using namespace std;

Gestione::Gestione(){
	FileElettrodomestici();
	FileOrdini();
	mese=0;
}

string Gestione::componentiInArrivo(){
	string s="Sono stati ordinati i seguenti componenti:";
	s+= ord.printInArrivo();
	for(int i=0;i<inArrivo.size();i++){
		s+="ID: ";
		s+= inArrivo[i].id;
		s+= "\tPEZZI: ";
		s+=inArrivo[i].pezzi;
		s+= "\n";
	}
	return s;
}

string Gestione::inventario(){
	string s = "Inventario Magazzino:";
	s+= ord.printNonUsati();
	s+= mag.magazzinoToString();
	return s;
}

string Gestione::ordiniEvasi(){
	string s = "Sono stati evasi i seguenti ordini finora";
	vector<ordini> v = ord.getEvasi();
	for(int i=0;i<v.size();i++){
		s+= "ID MODELLO: ";
		s+= v[i].id;
		s+= "\tQTA': ";
		s+= to_String(v[i].quantita);
		s+= "\n";
	}
		
	return s;
}

string Gestione::stampaStato(){
	string s;
	s+= componentiInArrivo();
	s+= inventario();
	s+= ordiniEvasi();
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
			ord.addOrdine(time_stamp, model_id, quantita);
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
		int qta;
		double prezzo = 0;
		modelIn>>id>>nome>>prezzo;
		elettrodomestico e {id, nome, prezzo};
		if (modelIn.is_open()){
			while(!modelIn.eof()){
				//id name quant
				modelIn>>id>>nome>>qta;
				for(int j=0;j<comps.size();j++)
					if(comps[j].getId()==id){
						e.addComponentToLst(comps[j], qta);
						break;
					}
			}
		}
		db.push_back(e);
	}
}

bool Gestione::aggiornaMese(){
	//Sleep(3000);      //blocca il programma per 3 secondi e incrementa il mese
	mese++;
	produzioneMese();
	for(int i=0;i<inArrivo.size();i++)
	{
		inArrivo[i].timer --;
		if(inArrivo[i].timer == 0){
			mag.add(inArrivo[i].id,inArrivo[i].pezzi);
			inArrivo.erase(inArrivo.begin()+i);
		} 

	}
	return ord.incrementaMese();
}

bool Gestione::checkCassa(double d){
	return cash.check(d);
}

void Gestione::produzioneMese(){

	string model_id;
	int mese_ord = 0;
	int quantita = 0;

	vector<ordini> prod_mese = ord.getOrdini(mese);
	for(int i=0;i<prod_mese.size();i++)
	{
		model_id = prod_mese[i].id;
		quantita = prod_mese[i].quantita;
		mese_ord = prod_mese[i].mese;

		int pos = -1;
		for(int j=0;j<db.size();j++)
		{    //check presenza del modello di elettrodomestico che si vuole ordinare
			if(db[j].getId() == model_id)
			{
				pos = j;
				break;
			} 
		}

		if(pos == -1) ord.annullaOrdine(ord.getOrdine(mese_ord, model_id, quantita));  //se non viene trovato, l'ordine è annullato
		else
		{


					vector<componentiElettrodomestico> comp_nec = db[pos].getComponents();  //componenti necessari per la produzione dell'elettrodomestico

				double costo_produzione = 0;
				double costo_ottimizzato = 0;
				int comp_necessari;
				for(int i=0;i<comp_nec.size();i++)
				{
					comp_necessari = comp_nec[i].getPezzi()*quantita;
					int comp_sufficienti = comp_necessari - mag.checkEnough(comp_nec[i].getComponente().getId() , comp_necessari);

					costo_produzione += comp_sufficienti * comp_nec[i].getComponente().getPrezzo(comp_sufficienti);  //produzione standard

					costo_ottimizzato += PezziOttimizzati(comp_sufficienti) * comp_nec[i].getComponente().getPrezzo(PezziOttimizzati(comp_sufficienti));

				}


				if(cash.check(costo_ottimizzato))
				{
					for(int k=0;k<comp_nec.size();k++)
					{
						comp_necessari = comp_nec[i].getPezzi()*quantita;
						int comp_sufficienti = comp_necessari - mag.checkEnough(comp_nec[i].getComponente().getId() , comp_necessari);

						ord.addComponent(ord.getOrdine(mese_ord, model_id, quantita),comp_nec[i].getComponente().getId(),comp_sufficienti,comp_nec[i].getComponente().getMesi());

						int pezzi_aggiuntivi = PezziOttimizzati(comp_sufficienti) - comp_sufficienti;

						addictional_components c;
						c.id = comp_nec[i].getComponente().getId();
						c.pezzi = pezzi_aggiuntivi;
						c.timer = comp_nec[i].getComponente().getMesi();
						inArrivo.push_back(c);               //aggiunta nel vettore dei componenti in arrivo
					}

				}
				else if(cash.check(costo_produzione)){

					for(int k=0;k<comp_nec.size();k++)
					{
						comp_necessari = comp_nec[i].getPezzi()*quantita;
						int comp_sufficienti = comp_necessari - mag.checkEnough(comp_nec[i].getComponente().getId() , comp_necessari);

						ord.addComponent(ord.getOrdine(mese_ord, model_id, quantita),comp_nec[i].getComponente().getId(),comp_sufficienti,comp_nec[i].getComponente().getMesi());
					}

				}

				else {ord.annullaOrdine(ord.getOrdine(mese_ord, model_id, quantita));}

		
		}	
	}
}

int Gestione::PezziOttimizzati(int n){
	if(n>=8 && n<11) return 11;
	if(n>=47 && n<51) return 51;
	return n;
}

bool Gestione::endProgram(){
	return ord.endProgram();
}



int main()
{
	return 0;
}




