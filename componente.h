//Autore: Edoardo Bastianello , numero matricola: 1188629
//header "componente.h

#include <iostream>
	
class componente{
		
public:
	//costruttore vuoto non ammesso
	//costruttore: alla creazione vengono settati l'id, il nome, i mesi necessari per l'invio e i 3 prezzi (per l'acquisto di 1-10, 11-50 e 51+ pezzi)
	componente(std::string id, std::string nome, int mesi, std::vector<double> prezzi);		

	//funzioni di lettura
	std::string getId()const;
	std::string getNome()const;
	int getMesi()const;
	
	//ritorna -1 se le viene fornito come parametro un valore <0
	double getPrezzo(int pezzi)const;//ritorna il prezzo in base al numero di pezzi
	
private:
	//dati membro
	std::string id;
	std::string nome;
	int mesi;
	std::vector <double> prezzi;
};
