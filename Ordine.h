//Autore: Andrea Felline , numero matricola: 1195927
//header "Ordine.h"

/*
La classe Ordine si occupa di gestire tutte le fasi degli ordini, da quando arrivano a quando vengono evasi o annullati.
Gli ordini vengono inizialmente caricati, attraverso la funzione addOrdine(), in un vettore di "ordini" (una struct con 
mese di arrivo, id dell'elettrodomestico, quantità e stato dell'ordine).
Gli ordini non ancora arrivati hanno lo stato a "futuro".
Quando arriva il mese giusto viene chiamata la funzione getOrdini() che riporta gli ordini del mese.
Per ogni ordine vengono aggiunti i componenti necessari a costruirlo e lo stato va in "inAttesa". Ogni componente ha un 
"timer" che indica quanti mesi mancano al suo arrivo. Quando arrivano tutti i componenti l'ordine va in "inProduzione" e il
mese dopo in "evaso". Se non ci sono abbastanza fondi nella cassa per acquistare tutti i componenti necessari, l'ordine viene 
rimandato al mese successivo con rimandaOrdine(). Se viene ordinato un modello non presente nel catalogo l'ordine viene
annullato attraverso "annullaOrdine()".
A ogni mese che passa viene chiamata la funzione aggiornaMese() che passa gli ordini "inProduzione" a "evaso" e decrementa il
timer di tutti i componenti non ancora arrivati. Inoltre riporta un vettore con gli id degli elettrodomestici venduti.
*/

#ifndef OrdineH
#define OrdineH

#include <vector>
#include <iostream>

enum stato{
	futuro, inAttesa, inProduzione, evaso, rimandato, annullato
	/*
		indicano rispettivamente le seguenti situzioni:
		- futuro: un ordine che deve ancora arrivare, ad es. uno che arriva il mese prossimo
		- inAttesa: un ordine arrivato e per il quale sono stati ordinati i componenti (ma non sono ancora arrivati)
		- inProduzione: un ordine per il quale sono arrivati tutti i componenti nel mese corrente (verrà evaso nel mese successivo)
		- evaso: un ordine per il quale è passato un mese da quando era in produzione
		- rimandato: un ordine per il quale non ci sono ancora abbastanza fondi per acquistarne i componenti
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
	void addOrdine(int mese, std::string id, int quantita);
	
	int getOrdine(int mese, std::string id, int quantita) const;//ritorna un ordine specifico (se non c'è ritorna un ordine con tutto a -1)
	std::vector<ordini> getOrdini(int mese) const;//ritorna gli ordini del mese (con stato "futuro" o "rimandato")
	std::vector<ordini> getInAttesa() const;//ritorna tutti gli ordini in attesa e rimandati
	std::vector<ordini> getInProduzione() const;//ritorna tutti gli ordini in produzione
	std::vector<ordini> getEvasi() const;//ritorna tutti gli ordini evasi
	int getMeseMax();
	
	//controllo componenti già presenti in magazzino o in arrivo, relativi a un certo ordine
	//utilizzo:	getPezziComp(getOrdine(int mese_ordine, string id_elettrodomestico, int quantità), string id_componente);
	int getPezziComp(int pos, std::string id); //in caso di più risultati riporta il risultato maggiore
	int getMesiComp(int pos, std::string id); //in caso di più risultati riporta il risultato maggiore 
	
	//N.B.:		in caso di ordini duplicati viene settato uno a caso (tra quelli non ancora annullati)
	//utilizzo:	annullaOrdine(getOrdine(int mese_ordine, string id_elettrodomestico, int quantità));
	void rimandaOrdine(int pos);//setta uno specifico ordine allo stato "rimandato" e ne setta il mese al successivo rispetto al corrente
	void annullaOrdine(int pos);//setta uno specifico ordine allo stato "annullato"
	
	//funzione per aggiungere i componenti già presenti in magazzino o in transito, relativi a un certo ordine
	//N.B.: 	se il componente è già presente (come id e mesi) non fa niente
	//utilizzo:	addComponent(getOrdine(int mese_ordine, string id_elettrodomestico, int quantita), string id_componente, int pezzi_componente, int mesi_mancanti);
	//WARNING: 	se non si inseriscono tutti i componenti di un ordine esso andrà comunque in produzione (non appena arrivano quelli inseriti)
	void addComponent(int pos, std::string id, int pezzi, int mesi);
	
	//funzioni di modifica del numero di pezzi e dei mesi mancanti di un componente
	//N.B.:		se ci sono più componenti con diversi valori di "mesi" le funzioni non fanno niente
	//utilizzo:	sumPezziComp(getOrdine(int mese_ordine, string id_elettrodomestico, int quantita), string id_componente, int differenza);
	void sumPezziComp(int pos, std::string id, int diff);//somma "diff" componenti (usare diff negativo per sottrarre)
	void setMesiComp(int pos, std::string id, int mesi);//setta i mesi (sovrascrive)

	//passa al mese successivo (portando tutti gli ordini "in produzione" a "evaso"). Aggiorna la situazione dei componenti in arrivo.
	//ritorna una booleana che indica se sono stati evasi degli ordini durante il mese (da riportare al main)
	std::vector<std::string> incrementaMese();
	
	//ritorna una stringa con i componenti in arrivo con il formato: ID: [id]	PEZZI: [pezzi]\n
	std::string printInArrivo();
	//ritorna una stringa con i componenti arrivati ma non ancora usati per produrre pezzi con il formato: ID componente: ID: [id]	PEZZI: [pezzi]\n
	std::string printNonUsati();
	
	bool endProgram();
private:
	int meseCorrente;//indica il mese corrente
	
	//vector di ordini ordinato in base al mese
	std::vector<ordini> ord {};
	
	//un vector di componenti per ogni ordine
	std::vector<std::vector<components>> comps{};
	
	int binarySearch(int mese) const; //restituisce l'indice del primo ordine del mese
};

#endif
