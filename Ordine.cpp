//Autore: Andrea Felline , numero matricola: 1195927
//file "Ordine.cpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include "Ordine.h"
using namespace std;

bool ordini::operator < (const ordini& o) const{
	if(mese < o.mese) return true;
	if(mese == o.mese){
		if(id <= o.id) return true;
		if(id > o.id) return false;
	}
	return false;// >
}

//costruttore: setta il mese corrente a 0 e inizializza il std::vector ord
Ordine::Ordine(){
	meseCorrente=0;
}

//ritorna il primo ordine del mese
int Ordine::binarySearch(int mese) const{
	int i, inizio, fine;
    i=inizio=0; fine=ord.size()-1;
    while (inizio<=fine) {
        i=int((inizio+fine)/2);
        if (mese==ord[i].mese) {
			//ricerca sequenziale
			for(;;i--)
				if(ord[i].mese!=mese || i==-1)
					return i+1;
		} else {
            if (mese<ord[i].mese) fine=i-1;
            else inizio=i+1;
        }
    }
	return -1;
}

//aggiunge un ordine con id, quantità e mese passati per parametro e stato "futuro"
void Ordine::addOrdine(int mese, std::string id, int quantita){
	ordini o;
	o.mese=mese;
	o.id=id;
	o.quantita=quantita;
	o.s=futuro;
	ord.push_back(o);
	sort(ord.begin(), ord.end());
}

int Ordine::getOrdine(int mese, std::string id, int quantita) const{//ritorna la posizione un ordine specifico (se non c'è ritorna -1)
	int i=binarySearch(mese);//ricerca binaria in base al mese
	
	//ricerca sequenziale in base all'id
	for(;i>=0 && ord[i].id<=id && ord[i].mese==mese;i++)
		if(ord[i].id==id && ord[i].quantita==quantita)
			return i;
	return -1;//se non trova niente ritorna un ordine vuoto (tutto a -1)
}

vector<ordini> Ordine::getOrdini(int mese) const{//ritorna gli ordini del mese (con stato "futuro")
	int i=binarySearch(mese);//ricerca binaria in base al mese
	vector<ordini> v {};
	
	//ricerca sequenziale fino al cambio del mese
	for(;ord[i].mese==mese;i++)
		if(ord[i].s==futuro)
			v.push_back(ord[i]);
	return v;//se non trova niente ritorna un vettore vuoto
}

vector<ordini> Ordine::getInAttesa() const{//ritorna tutti gli ordini in attesa
	vector<ordini> v {};
	
	//ricerca sequenziale
	for(int i=0;i<ord.size();i++)
		if(ord[i].s==inAttesa)
			v.push_back(ord[i]);
	return v;//se non trova niente ritorna un vettore vuoto
}

vector<ordini> Ordine::getInProduzione() const{//ritorna tutti gli ordini in produzione
	vector<ordini> v {};
	
	//ricerca sequenziale
	for(int i=0;i<ord.size();i++)
		if(ord[i].s==inProduzione)
			v.push_back(ord[i]);
	return v;//se non trova niente ritorna un vettore vuoto
}

vector<ordini> Ordine::getEvasi() const{//ritorna tutti gli ordini evasi
	vector<ordini> v {};
	
	//ricerca sequenziale
	for(int i=0;i<ord.size();i++)
		if(ord[i].s==evaso)
			v.push_back(ord[i]);
	return v;//se non trova niente ritorna un vettore vuoto
}

int Ordine::getPezziComp(int pos, string id){
	if(pos<0) return -1;
	int pezzi=-1;
	for(int i=0;i<comps[pos].size();i++)
		if(comps[pos][i].id==id && comps[pos][i].pezzi>pezzi)
			pezzi=comps[pos][i].pezzi;
	return pezzi;
}

int Ordine::getMesiComp(int pos, string id){
	if(pos<0) return -1;
	int mesi=-1;
	for(int i=0;i<comps[pos].size();i++)
		if(comps[pos][i].id==id && comps[pos][i].mesi>mesi)
			mesi=comps[pos][i].mesi;
	return mesi;
}

void Ordine::annullaOrdine(int pos){//setta uno specifico ordine allo stato "annullato"
	if(pos<0) return;
	ord[pos].s=annullato;
	
	//svuota i relativi componenti in arrivo
	comps[pos].erase(comps[pos].begin(), comps[pos].end());
}

//aggiunge un componente alla lista dei componenti di un ordine (la posizione del componente in comps è la stessa dell'ordine in ord)
//se il componente c'è già e ha lo stesso numero di mesi setta il suo numero di pezzi col valore passato
void Ordine::addComponent(int pos, string id, int pezzi, int mesi){
	if(pos<0) return;
	
	//controllo se ci sono più ordini uguali
	vector<int> indexes {1};
	indexes[0]=pos;
	for(int i=pos-1;ord[i].id==ord[pos].id && ord[i].mese==ord[pos].mese;i--)//controllo verso dietro
		if(ord[i].quantita==ord[pos].quantita)
			indexes.push_back(i);
	for(int i=pos+1;ord[i].id==ord[pos].id && ord[i].mese==ord[pos].mese;i++)//controllo verso avanti
		if(ord[i].quantita==ord[pos].quantita)
			indexes.push_back(i);
	
	if(comps.size()<pos+1){//modifica la dimensione dell'array (se serve)
		comps.resize(pos+1);
	}
	else{//controlla se c'è già il componente e in caso ne setta il numero di pezzi
		for(int i=0;i<indexes.size();i++)
			for(int j=0;j<comps[pos].size();j++)
				if(comps[pos][j].id==id && comps[pos][j].mesi==mesi){
					indexes.erase(indexes.begin()+i);
					break;
				}
	}
	
	if(indexes.size()>0){//se non era presente almeno in uno degli ordini identici, lo aggiunge a uno a caso tra quelli
		components c;
		c.id=id;
		c.pezzi=pezzi;
		c.mesi=mesi;
		comps[pos].push_back(c);
	}
	
	//setta il corrispondente ordine in attesa
	ord[pos].s=inAttesa;
}

void Ordine::sumPezziComp(int pos, std::string id, int diff){//somma "diff" componenti
	if(pos<0) return;
	int y=-1;
	for(int i=0;i<comps[pos].size();i++)
		if(comps[pos][i].id==id && y==-1)
			y=i;
		else if(comps[pos][i].id==id && y!=-1)
			return;
	if(y!=-1) comps[pos][y].pezzi+=diff;
}

void Ordine::setMesiComp(int pos, std::string id, int mesi){//setta i mesi (sovrascrive)
	if(pos<0) return;
	int y=-1;
	for(int i=0;i<comps[pos].size();i++)
		if(comps[pos][i].id==id && y==-1)
			y=i;
		else if(comps[pos][i].id==id && y!=-1)
			return;
	if(y!=-1) comps[pos][y].mesi=mesi;
}

//passa al mese successivo (portando tutti gli ordini "in produzione" a "evaso") e ritorna i nuovi ordini
//	NB: se si preferisce prendere i nuovi ordini separatamente, si può considerare questa funzione come void 
//		e poi chiamare "getOrdini" all'occorrenza
bool Ordine::incrementaMese(){
	meseCorrente++;
	bool evasi=false;
	
	for(int i=0;i<ord.size();i++)//aggiornamento ordini evasi
		if(ord[i].s==stato::inProduzione){
			ord[i].s=stato::evaso;
			evasi=true;
		}
	
	//tutti i mesi non a 0 vanno a mesi-1
	//se facendo ciò un ordine arriva ad avere tutti i componenti con i mesi a 0 va in produzione
	for(int i=0;i<comps.size();i++){
		bool monthTo0=false;
		for(int j=0;j<comps[i].size();j++)
			if(comps[i][j].mesi>0){
				comps[i][j].mesi--;
				monthTo0=true;
				if(comps[i][j].mesi>0)//se uno dei componenti dell'ordine non è ancora a 0
					monthTo0=false;
			}
		
		if(monthTo0)
			ord[i].s=inProduzione;
	}
	
	return evasi;
}

int Ordine::getMeseMax(){
	return ord[ord.size()-1].mese;
}

string Ordine::printInArrivo(){//stampa tutti i componenti in arrivo, ossia i componenti con mesi>0 di ordini con stato inAttesa
	string s="\n";
	for(int i=0;i<ord.size();i++)
		if(ord[i].s==inAttesa)
			for(int j=0;j<comps[i].size();j++)
				if(comps[i][j].mesi>0){
					s+="ID: ";
					s+=comps[i][j].id;
					s+="\tPEZZI: ";
					s+=to_string(comps[i][j].pezzi);
					s+="\n";
				}
	return s;
}

string Ordine::printNonUsati(){//stampa tutti i componenti arrivati ma non usati, quindi mesi=0 e stato inAttesa
	string s="\n";
	for(int i=0;i<ord.size();i++)
		if(ord[i].s==inAttesa)
			for(int j=0;j<comps[i].size();j++)
				if(comps[i][j].mesi==0){
					s+="ID: ";
					s+=comps[i][j].id;
					s+="\tPEZZI: ";
					s+=to_string(comps[i][j].pezzi);
					s+="\n";
				}
	return s;
}

bool Ordine::endProgram(){
	bool end=true;
	for(int i=0;i<ord.size();i++){
		if(ord[i].s!=evaso && ord[i].s!=annullato)
			end=false;
	}
	return end;
}
