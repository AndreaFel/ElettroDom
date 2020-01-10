class magazzino{
public:
	//costruttore vuoto(unico permesso)
	magazzino();

	//funzione "add" che aggiunge un certo numero(variabiie "pezzi") di componenti(ogni componente identificato dal relativo "id") nel megazzino
	void add(std::string id, int pezzi);

	//funzione "remove" che rimuove un certo numero(variabiie "pezzi") di componenti(ogni componente identificato dal relativo "id") dal megazzino
	//restituisce il numero di pezzi da ordinare oltre a quelli  rimossi
	//restituisce 0 se ci sono abbastanza elementi nel magazzino(non serve ordinare nessun elemento)
	//restituisce -1 se non e' presente il componente cercato
	int remove(std::string id, int pezzi);

	//funzione "checkEnough" che verifica che ci sia un numero di un certo componente(identificato da "id") maggiore o uguale a quanto indicato dal parametro "pezzi"
	//restituisce un int che rappresenta quanti pezzi ci sarebbero da ordinare se si decidesse di rimuovere dal magazzino un numero di componenti pari a pezzi
	//restituisce -1 se non e' presente il componente cercato
	//restituisce 0 se ci sono abbastanza elementi
	int checkEnough(std::string id, int pezzi);

	//funzione "check" che controlla se vi e' un certo componente nel magazzino
	//restituisce l'indice se presente, -1 se non presente
	int check(std::string id);

	//funzione "getId": restituisce l'id all'indice i, restituisce "indice non valido" se l'indice non e' valido
	std::string getId(int i)const;

	//funzione "getPezzi": restituisce il numero di componenti di indice i, restituisce -1 se l'indice non e' valido
	int getPezzi(int i)const;

	//funzione print che stampa i componenti nel magazzino con le relative quantita'
	void printMagazzino()const;
	

private:
	//classe privata Coppia per attribuire il numero di pezi del relativo componente
	struct Coppia{
		std::string id;
		int pezzi;
	};

	//funzione ricerca binaria privata
	int binSearchCoppie(const vector<Coppia>& a, int from, int to, std::string toFind);

	//funzione che restituisce un int che rappresenta quanti componenti bisogna ordinare oltre a quelli rimossi
	//restituisce -1 se non e' presente il componente cercato
	int daOridinareOltreAiRimossi(int pezzi, int index);

	//variabili membro
	std::vector<Coppia> oggetti;
};


