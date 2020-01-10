#include <iostream>
#include <vector>
#include "elettrodomestico.h"
#include "magazzino.h"
#include "componente.h"
#include "cassa.h"

struct componenti
{
	std::string id;
	int pezzi;
	int timer; //tempo rimanente dall'arrivo dei componenti
};

class Gestione{

	public:

		Gestione();
		/* Il costruttore deve inizializzare
		- dal file component.dat i vari componenti. Tipologia riga: {[component_id] ; [component_name] ; [delivery_time (months)]}
		- dal file modelN.dat l'elettrodomestico corrispondente
			dalla prima riga {[model_id] ; [model_name]} -> Elettrodomestico.id, Elettrodomestico.nome
			dalle seguenti righe di tipo: {[component_id] ; [component_name] ; [quantity_needed]} il vettore di struct componenti
		- dal file order.dat il vector nella classe ordini. Tipologia riga: {[time_stamp] [model_id] [quantity]}
		*/

	
		//Funzioni di stampa, restituiscono una stringa per visualizzazione nel main
		std::string ordiniInArrivo(); //stampa gli acquisti effettuati ma non arrivati -> stampa vector<componenti>
		std::string inventario(); // stampa componenti in magazzino -> stampa vector<componenti> oggetti
		std::string ordiniEvasi(); //stampa gli ordini evasi, prendendoli con la funzione getEvasi() della classe ordini

		std::string stampaStato(); //chiama nell'ordine: ordiniInArrivo(), inventario(), ordiniEvasi()



	private:
		cassa cash;
		magazzino mag; //lista dei componenti che sono presenti in magazzino
		vector<componenti> inArrivo; //lista dei componenti ordinati, in arrivo
		ordini ord; //classe contenente un vettore ordinato di ordini in base al time_stamp
		elettrodomestico db[]; //"catalogo" degli elettrodomestici da noi prodotti
		int mese;

		void checkCassa(double d); //Verifica del fondo cassa prima di eseguire ordini

		void aggiornaMese(); //Funzione che blocca il programma per qualche secondo e poi passa alle operazioni del mese successivo
		
		void produzioneMese();
		/*
		- scorre la lista di ordini per ordini mese corrente
		- controllo pezzi in magazzino e li ordina eventualmente
		- setta in produzione l'ordine se ci sono i fondi necessari nella cassa

		*/


		
		void aggiornaArrivi(); 
		/* scorre il vettore di componenti in arrivo decrementando il timer, se è uguale a 0
		- aggiorna i pezzi in magazzino
		- rimuove l'elemento dal vector<componenti>
		*/


}
