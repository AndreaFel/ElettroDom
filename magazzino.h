//Autore: Edoardo Bastianello , numero matricola: 1188629
//header "magazzino.h"
//il magazzino contiene i componenti ordinati in piu' del necessario. Ad esempio:
//al posto di ordinare 10 componenti, se ne ordinano 11 per avere lo sconto; il componente in eccesso, una volta arrivato, viene inserito nel magazzino
//il magazzino e' stato realizzato come un dizionario

#ifndef magazzinoH
#define magazzinoH

#include <vector>
#include <iostream>

class magazzino{
public:
	//costruttore vuoto(unico permesso)
	magazzino();

	//funzione "add" che aggiunge un certo numero(variabiie "pezzi") di "id" del relativo componente nel megazzino
	//inserimento in ordine alfabetico per poter garantire il corretto funzionamento della ricerca binaria
	void add(std::string id, int pezzi);

	//funzione "remove" che rimuove un certo numero(variabiie "pezzi") di componenti(raprresentati dal relativo "id") dal megazzino
	//se si cercano di togliere piu' pezzi di quelli presenti, si tolgono tutti i pezzi
	void remove(std::string id, int pezzi);

	//funzione "checkEnough" che verifica che ci sia un numero di un certo componente(raprresentato da "id") maggiore o uguale a quanto indicato dal parametro "pezzi"
	//restituisce un int che rappresenta quanti pezzi andrebbero tolti dal magazzino se si orindasse un numero di pezzi pari a "pezzi"
	//restituisce -1 se non e' presente il componente cercato
	//restituisce 0 se andrebbe orinato un numero di pezzi maggiore o uguale a quelli presenti
	int checkEnough(std::string id, int pezzi);

	//funzione "check" che controlla se vi e' un certo componente nel magazzino
	//restituisce l'indice se presente, -1 se non presente
	int check(std::string id);

	//funzione "getId": restituisce l'id all'indice i, restituisce "indice non valido" se l'indice non e' valido
	std::string getId(int i)const;

	//funzione "getPezzi": restituisce il numero di componenti di indice i, restituisce -1 se l'indice non e' valido
	int getPezzi(int i)const;

	//funzione print che stampa i componenti nel magazzino con le relative quantita' in ordine alfabetico
	void printMagazzino()const;

	//funzione magazzinoToString() che restituisce una stringa con i componenti nel magazzino con le relative quantita' in ordine alfabetico
	std::string magazzinoToString() const;

private:
	//struct privata Coppia per attribuire il numero di pezzi al relativo id del componente
	struct Coppia{
		std::string id;
		int pezzi;
	};

	//funzione ricerca binaria privata
	//dovendo effettuare molte ricerche e pochi inserimenti, la ricerca binaria risulta piu' efficiente
	int binSearchCoppie(const std::vector<Coppia>& a, int from, int to, std::string toFind);

	//membro
	std::vector<Coppia> oggetti;
};

#endif
