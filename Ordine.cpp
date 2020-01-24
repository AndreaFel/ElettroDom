//Autore: Andrea Felline , numero matricola: 1195927
//header "Ordine.cpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <Ordine.h>
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
void Ordine::addOrdine(std::string id, int quantita, int mese){
	ordini o;
	o.mese=mese;
	o.id=id;
	o.quantita=quantita;
	o.s=futuro;
	ord.push_back(o);
	sort(ord.begin(), ord.end());
}

ordini Ordine::getOrdine(int mese, std::string id) const{//ritorna un ordine specifico (se non c'è ritorna un ordine con tutto a -1)
	int i=binarySearch(mese);//ricerca binaria in base al mese
	ordini o;
	o.id=-1; o.mese=-1; o.quantita=-1;
	if(i==-1){
		return o;
	}
	
	//ricerca sequenziale in base all'id
	for(;ord[i].id<=id && ord[i].mese==mese;i++)
		if(ord[i].id==id)
			return ord[i];
	return o;//se non trova niente ritorna un ordine vuoto (tutto a -1)
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

int Ordine::getPezziComp(ordini o, string id){
	int i=getPos(o);
	for(int j=0;j<comps[i].size();j++)
		if(comps[i][j].id==id)
			return comps[i][j].pezzi;
	return 0;
}

int Ordine::getMesiComp(ordini o, string id){
	int i=getPos(o);
	int mesi=-1;
	for(int j=0;j<comps[i].size();j++)
		if(comps[i][j].id==id && comps[i][j].mesi>mesi)
			mesi=comps[i][j].mesi;
	return mesi;
}

void Ordine::setInAttesa(int mese, std::string id){//setta uno specifico ordine allo stato "in attesa"
	int i=binarySearch(mese);//ricerca binaria in base al mese
	
	//ricerca sequenziale in base all'id
	for(;ord[i].id<=id && ord[i].mese==mese;i++)
		if(ord[i].id==id)
			ord[i].s=inAttesa;
}

void Ordine::setInProduzione(int mese,std::string id){//setta uno specifico ordine allo stato "in produzione"
	int i=binarySearch(mese);//ricerca binaria in base al mese
	
	//ricerca sequenziale in base all'id
	for(;ord[i].id<=id && ord[i].mese==mese;i++)
		if(ord[i].id==id)
			ord[i].s=inProduzione;
}

void Ordine::setEvaso(int mese, std::string id){//setta uno specifico ordine allo stato "evaso"
	int i=binarySearch(mese);//ricerca binaria in base al mese
	
	//ricerca sequenziale in base all'id
	for(;ord[i].id<=id && ord[i].mese==mese;i++)
		if(ord[i].id==id)
			ord[i].s=evaso;
}

void Ordine::annullaOrdine(std::string id){//setta uno specifico ordine allo stato "annullato"
	int i=binarySearch(meseCorrente);//ricerca binaria in base al mese
	
	//ricerca sequenziale in base all'id
	for(;ord[i].id<=id && ord[i].mese==meseCorrente;i++)
		if(ord[i].id==id)
			ord[i].s=annullato;
}

//aggiunge un componente alla lista dei componenti di un ordine (la posizione del componente in comps è la stessa dell'ordine in ord)
//se il componente c'è già e ha lo stesso numero di mesi setta il suo numero di pezzi col valore passato
void Ordine::addComponent(ordini ordine, string id, int pezzi, int mesi){
	int i=getPos(ordine);
	bool giaPresente=false;
	
	if(comps.size()<i+1){//modifica la dimensione dell'array (se serve)
		comps.resize(i+1);
	}
	else{//controlla se c'è già il componente e in caso ne setta il numero di pezzi
		for(int j=0;j<comps[i].size();j++)
			if(comps[i][j].id==id && comps[i][j].mesi==mesi){
				comps[i][j].pezzi=pezzi;
				giaPresente=true;
				break;
			}
	}
	
	if(!giaPresente){//se non era presente lo aggiunge
		components c;
		c.id=id;
		c.pezzi=pezzi;
		c.mesi=mesi;
		comps[i].push_back(c);
	}
}

void Ordine::sumPezziComp(ordini o, std::string id, int diff){//somma "diff" componenti
	int i=getPos(o);
	int y=-1;
	for(int j=0;j<comps[i].size();j++)
		if(comps[i][j].id==id && y==-1)
			y=j;
		else if(comps[i][j].id==id && y!=-1)
			return;
	if(y!=-1) comps[i][y].pezzi+=diff;
}

void Ordine::setMesiComp(ordini o, std::string id, int mesi){//setta i mesi (sovrascrive)
	int i=getPos(o);
	int y=-1;
	for(int j=0;j<comps[i].size();j++)
		if(comps[i][j].id==id && y==-1)
			y=j;
		else if(comps[i][j].id==id && y!=-1)
			return;
	if(y!=-1) comps[i][y].mesi=mesi;
}

//passa al mese successivo (portando tutti gli ordini "in produzione" a "evaso") e ritorna i nuovi ordini
//	NB: se si preferisce prendere i nuovi ordini separatamente, si può considerare questa funzione come void 
//		e poi chiamare "getOrdini" all'occorrenza
bool Ordine::incrementaMese(){
	meseCorrente++;
	bool evasi=false;
	
	for(int i=0;i<ord.size();i++)//aggiornamento ordini evasi
		if(ord[i].s==inProduzione){
			ord[i].s=evaso;
			evasi=true;
		}
	
	//tutti i mesi non a 0 vanno a mesi-1
	//se facendo ciò un ordine arriva ad avere tutti i componenti con i mesi a 0 va in produzione
	for(int i=0;i<comps.size();i++){
		bool monthTo0=true;
		for(int j=0;j<comps[i].size();j++)
			if(comps[i][j].mesi>0){
				comps[i][j].mesi--;
				if(comps[i][j]>0)//se uno dei componenti dell'ordine non è ancora a 0
					mothTo0=false;
			}
		
		if(mothTo0)
			ord[i].s=inProduzione;
	}
	
	return evasi;
}

int Ordine::getMeseMax(){
	return ord[ord.size()-1].mese;
}

int Ordine::getPos(ordini o){
	int i=binarySearch(o.mese);
	for(;ord[i].id<=o.id && ord[i].mese==o.mese;i++)
		if(ord[i].id==o.id)
			return i;
	return -1;
}
