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

//passa al mese successivo (portando tutti gli ordini "in produzione" a "evaso") e ritorna i nuovi ordini
//	NB: se si preferisce prendere i nuovi ordini separatamente, si può considerare questa funzione come void 
//		e poi chiamare "getOrdini" all'occorrenza
vector<ordini> Ordine::incrementaMese(){
	meseCorrente++;
	
	for(int i=0;i<ord.size();i++)
		if(ord[i].s==inProduzione)
			ord[i].s=evaso;
	
	return getOrdini(meseCorrente);
}
