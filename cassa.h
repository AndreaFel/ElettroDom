class cassa{
public:
	//costruttore vuoto che inizializza il fondo a 10000
	cassa();

	//costruttore non vuoto
	cassa(double start);

	//funzione "addFondo" che aggiunge un saldo al fondo della cassa
	void addFondo(double vendita);

	//funzione "subtractFondo" che rimuove un saldo dal fondo della cassa
	//lancia Invalid{} se il saldo richesto e' maggiore del fondo
	void subtractFondo(double price);

	//funzione di stampa
	void printFondo();

	//funzione check che controlla se il prezzo e' maggiore del fondo della cassa
	//restituisce false se il fondo e' minore di price, true altrimenti
	bool check(double price);	
	

private:
	//classe interna per lancio eccezioni
	class Invalid{};

	//variabile membro
	double fondo;
};

