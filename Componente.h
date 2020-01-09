#include <iostream>

class componente{
	
public:
	//costruttore: alla creazione vengono settati l'id, il nome e i 3 prezzi (per l'acquisto di 1-10, 11-50 e 51+ pezzi)
	componente(std::string id, std::string nome, float prezzi[]);
	
	//get
	Prezzo(int pezzi);//ritorna il prezzo in base al numero di pezzi
	Nome();
	Id();
	
private:
	std::string id;
	std::string nome;
	float prezzi[];
};
