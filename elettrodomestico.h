//Autore: Edoardo Bastianello , numero matricola: 1188629
//header "elettrodomestico.h"
#ifndef elettrodomesticoH
#define elettrodomesticoH

class elettrodomestico{

public:
	//costruttore(quello di default non e' definito)
	elettrodomestico(string idIns, string nomeIns, double prezzoVenditaIns);

	//funzioni di lettura
	std::string getId()const;
	std::string getNome()const;
	double getPrezzoVendita()const;
	vector<componentiElettrodomestico> getComponents()const;//restituisce un vector di componentiElettrodomestico
	
	

	//funzione di inserimento per aggiungere i componenti necessari per il relativo elettrodomestico
	void addComponentToLst(componente ins, int quantity);

	



private:
	//dati membro
	std::string id;
	string nome;
	double prezzoVendita;
	vector<componentiElettrodomestico> lstComponenti;
};

#endif
