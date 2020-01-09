#include <vector>
#include <iostream>

//ordine rappresenta un singolo ordine
//il mese nel quale verrà ricevuto è dato dalla sua posizione nel vettore e l'anno dal valore di "anno"
struct ordine{
	int anno;//il primo anno è 1, il secondo 2, ...
	std::string id;//id elettrodomestico ordinato
	int pezzi;
};

class calendario{
	
public:
	//costruttore: setta mese a 0 e crea i 12 mesi (vuoti)
	calendario();
	
	/* per la fase di lettura da file e inserimento, per ogni ordine letto basta creare un ordine con anno, id e pezzi 
	 * e passarglielo ad add insieme al mese. Il mese deve essere compreso tra 1 e 12, 
	 * se va oltre 12 si aggiunge un anno e si tolgono 12 mesi */
	void add(ordine ordine, int mese);
	
	std::vector<ordine> increment();//passa al mese successivo e ritorna eventuli ordini (solo quelli del nuovo mese)
	int getCurrent();//ritorna il mese corrente (getMese)
	
private:
	std::vector< std::vector<ordine> > ordiniMensili;//calendario
	int mese;//mese corrente
	int anno;//anno corrente
};