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
//il mese nel quale verrà ricevuto è dato dalla sua posizione nel vettore e l'anno dal valore di "anno"
struct ordini{
	int mese;
	std::string id;//id elettrodomestico ordinato
	int quantita;
	stato s;
};

class Ordine{
	
public:
	//costruttore: setta il mese corrente a 0 e inizializza il std::vector ord
	Ordine();
	
	//aggiunge un ordine con id, quantità e mese passati per parametro e stato "futuro"
	void addOrdine(std::string id, int quantita, int mese);
	
	ordini getOrdine(int mese, std::string id) const;//ritorna un ordine specifico
	std::vector<ordini> getOrdini(int mese) const;//ritorna gli ordini del mese (con stato "futuro")
	std::vector<ordini> getInAttesa() const;//ritorna tutti gli ordini in attesa
	std::vector<ordini> getInProduzione() const;//ritorna tutti gli ordini in produzione
	std::vector<ordini> getEvasi() const;//ritorna tutti gli ordini evasi
	
	void setInAttesa(int mese, std::string id);//setta uno specifico ordine allo stato "in attesa"
	void setInProduzione(int mese,std::string id);//setta uno specifico ordine allo stato "in produzione"
	void setEvaso(int mese, std::string id);//setta uno specifico ordine allo stato "evaso"
	void annullaOrdine(std::string id);//setta uno specifico ordine allo stato "annullato"

	//passa al mese successivo (portando tutti gli ordini "in produzione" a "evaso") e ritorna i nuovi ordini
	//	NB: se si preferisce prendere i nuovi ordini separatamente, si può considerare questa funzione come void 
	//		e poi chiamare "getOrdini" all'occorrenza
	std::vector<ordini> incrementaMese();
private:
	int meseCorrente;//indica il mese corrente
	
	//std::vector di ordini ordinato in base al mese
	std::vector<ordini> ord;
	
};
