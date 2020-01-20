//Autore: Andrea Felline , numero matricola: 1195927
//header "Ordine.cpp"

#ifndef OrdineH
#define OrdineH

#include <vector>
#include <iostream>

enum stato{
	futuro, inAttesa, inProduzione, evaso, annullato
	/*
		indicano rispettivamente le seguenti situzioni:
		- futuro: un ordine che deve ancora arrivare, ad es. uno che arriva il mese prossimo
		- inAttesa: un ordine arrivato e per il quale sono stati ordinati i componenti (ma non sono ancora arrivati)
		- inProduzione: un ordine per il quale sono arrivati tutti i componenti nel mese corrente (verrà evaso nel mese successivo)
		- evaso: un ordine per il quale è passato un mese da quando era in produzione
		- annullato: un ordine per il quale non si hanno abbastanza fondi
	*/
};

//ordine rappresenta un singolo ordine
struct ordini{
	int mese;
	std::string id;//id elettrodomestico ordinato
	int quantita;
	stato s;
	
	bool operator < (const ordini& o) const;//definisce un ordine nella struct (in base al mese, a parità di mese in base all'id)
};

struct components{
	std::string id;
	int pezzi;
	int mesi; //mesi mancanti all'arrivo del componente
};

class Ordine{
	
public:
	//costruttore: setta il mese corrente a 0
	Ordine();
	
	//aggiunge un ordine con id, quantità e mese passati per parametro e stato "futuro"
	void addOrdine(std::string id, int quantita, int mese);
	
	ordini getOrdine(int mese, std::string id) const;//ritorna un ordine specifico (se non c'è ritorna un ordine con tutto a -1)
	std::vector<ordini> getOrdini(int mese) const;//ritorna gli ordini del mese (con stato "futuro")
	std::vector<ordini> getInAttesa() const;//ritorna tutti gli ordini in attesa
	std::vector<ordini> getInProduzione() const;//ritorna tutti gli ordini in produzione
	std::vector<ordini> getEvasi() const;//ritorna tutti gli ordini evasi
	int getMeseMax();
	
	//controllo componenti già presenti in magazzino o in arrivo, relativi a un certo ordine
	//utilizzo consigliato: getPezziComp(getOrdine(int mese_ordine, string id_elettrodomestico), string id_componente);
	int getPezziComp(ordini o, std::string id);
	int getMesiComp(ordini o, std::string id); //in caso di più ordini riporta il risultato maggiore 
	
	void setInAttesa(int mese, std::string id);//setta uno specifico ordine allo stato "in attesa"
	void setInProduzione(int mese,std::string id);//setta uno specifico ordine allo stato "in produzione"
	void setEvaso(int mese, std::string id);//setta uno specifico ordine allo stato "evaso"
	void annullaOrdine(std::string id);//setta uno specifico ordine allo stato "annullato"
	
	//funzione per aggiungere i componenti già presenti in magazzino o in transito, relativi a un certo ordine
	//se il componente è già presente (a parità di mesi) ne setta il numero di pezzi (sovrascrive)
	//utilizzo consigliato: addComponent(getOrdine(int mese_ordine, string id_elettrodomestico), string id_componente, int pezzi_componente, int mesi_mancanti);
	void addComponent(ordini ordine, std::string id, int pezzi, int mesi);
	
	//funzioni di modifica del numero di pezzi e dei mesi mancanti di un componente
	//se ci sono più componenti con diversi valori di "mesi" le funzioni non fanno niente
	//utilizzo consigliato: subPezziComp(getOrdine(int mese_ordine, string id_elettrodomestico), string id_componente, int differenza);
	void sumPezziComp(ordini o, std::string id, int diff);//somma "diff" componenti (usare diff negativo per sottrarre)
	void setMesiComp(ordini o, std::string id, int mesi);//setta i mesi (sovrascrive)

	//passa al mese successivo (portando tutti gli ordini "in produzione" a "evaso"). Aggiorna la situazione dei componenti in arrivo.
	//ritorna una booleana che indica se sono stati evasi degli ordini durante il mese (da riportare al main)
	bool incrementaMese();
private:
	int meseCorrente;//indica il mese corrente
	
	//vector di ordini ordinato in base al mese
	std::vector<ordini> ord {};
	
	//un vector di componenti per ogni ordine
	std::vector<std::vector<components>> comps{};
	
	int binarySearch(int mese) const; //restituisce l'indice del primo ordine del mese
	int getPos(ordini o);
};

#endif
