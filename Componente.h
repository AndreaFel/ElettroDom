#include <iostream>

class componente{
	
public:
	//costruttore: alla creazione vengono settati l'id, il nome e i 3 prezzi (per l'acquisto di 1-10, 11-50 e 51+ pezzi)
	componente(std::string id, std::string nome, int mesi, double prezzi[]);
	
	//get
	getPrezzo(int pezzi) const;//ritorna il prezzo in base al numero di pezzi
	getNome() const;
	getId() const;
	getMesi() const;
private:
	std::string id;
	std::string nome;
	int mesi;
	double prezzi[];
};
