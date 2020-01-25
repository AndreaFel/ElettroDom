//Autore: Edoardo Bastianello , numero matricola: 1188629
//header "componentiElettrodomestico.h"
//un oggetto di tipo componentiElettrodomestico servira' per realizzare la classe elettrodomestico

#ifndef componentiElettrodomesticoH
#define componentiElettrodomesticoH

#include "componente.h"

class componentiElettrodomestico{

public:
	//costruttore vuoto non definito
	//costruttore, "num" rappresenta la quantità necessaria di un certo componente "in" per realizzare il rispettivo elettrodomestico
	componentiElettrodomestico(const componente& in, int num);
	
	//funzioni di accesso
	componente getComponente()const;
	int getPezzi()const;

private:
	//dati membro
	componente c;
	int pezzi;
};

#endif
