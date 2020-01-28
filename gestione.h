//Autore: Simone Cecchinato , numero matricola: 1195817
//header "gestione.h"


#ifndef GestioneH
#define GestioneH

#include <vector>
#include <iostream>
#include "componente.h"
#include "componentiElettrodomestico.h"
#include "elettrodomestico.h"
#include "cassa.h"
#include "magazzino.h"
#include "Ordine.h"
#include "gestione.h"

struct addictional_components
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
		std::string componentiInArrivo(); //stampa gli acquisti effettuati ma non arrivati -> stampa vector<componenti>
		std::string inventario(); // stampa componenti in magazzino -> stampa vector<componenti> oggetti
		std::string ordiniEvasi(); //stampa gli ordini evasi, prendendoli con la funzione getEvasi() della classe ordini

		std::string stampaStato(); //chiama nell'ordine: ordiniInArrivo(), inventario(), ordiniEvasi()
		

		int PezziOttimizzati(int n);
		bool endProgram();

		bool aggiornaMese(); //Funzione che blocca il programma per qualche secondo e poi passa alle operazioni del mese successivo
							//scorre il vettore componenti in arrivo, decrementando il timer e mandando i pezzi in magazzino quando è uguale a 0
		
	private:
		cassa cash {0};
		magazzino mag; //lista dei componenti che sono presenti in magazzino
		std::vector<addictional_components> inArrivo; //lista dei componenti aggiuntivi ordinati, in arrivo
		Ordine ord; //istanza della classe ordine per utilizzare le sue funzioni
		std::vector<elettrodomestico> db; //"catalogo" degli elettrodomestici da noi prodotti; serve per verificare se il modello ordinato è in produzione nella nostra azienda
		int mese; //variabile per regolare time_stamp

		bool checkCassa(double d); //Verifica del fondo cassa prima di eseguire ordini

		

		void produzioneMese();
		/*
		- scorre la lista di ordini per ordini mese corrente
		- controllo pezzi in magazzino e li ordina eventualmente
		- setta in produzione l'ordine se ci sono i fondi necessari nella cassa

		*/


		std::vector<componente> FileComponenti();  //lettura da file "components_info.dat"
		void FileOrdini();	//lettura file "orders.dat"
		std::vector<std::string> FileModelli(); //lettura file "models.dat"
		void FileElettrodomestici(); //lettura vari file modelli elettrodomestici del database
		
};

#endif