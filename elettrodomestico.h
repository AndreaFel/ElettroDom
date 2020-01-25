//Autore: Edoardo Bastianello , numero matricola: 1188629
//header "elettrodomestico.h"
#ifndef elettrodomesticoH
#define elettrodomesticoH

#include <vector>
#include <iostream>
#include "componente.h"
#include "componentiElettrodomestico.h"

class elettrodomestico{

public:
	//costruttore(quello di default non e' definito)
	elettrodomestico(std::string idIns, std::string nomeIns, double prezzoVenditaIns);

	//funzioni di lettura
	std::string getId()const;
	std::string getNome()const;
	double getPrezzoVendita()const;
	std::vector<componentiElettrodomestico> getComponents()const;//restituisce un vector di componentiElettrodomestico
	
	

	//funzione di inserimento per aggiungere i componenti necessari per il relativo elettrodomestico
	void addComponentToLst(componente ins, int quantity);

	



private:
	//dati membro
	std::string id;
	std::string nome;
	double prezzoVendita;
	std::vector<componentiElettrodomestico> lstComponenti;
};

#endif
