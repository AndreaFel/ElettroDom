
class elettrodomestico{

public:
	//costruttore(quello di default non e' definito
	elettrodomestico(string idIns, string nomeIns, double prezzoAcquistoIns, double prezzoVenditaIns);

	//funzioni di lettura
	std::string getId()const;
	std::string getNome()const;
	double getPrezzoAcquisto()const;
	double getPrezzoVendita()const;

	vector<componentiElettrodomestico> getComponents()const;
	
	

	//funzione di inserimento
	void addComponentToLst(componente ins, int quantity);

	



private:
	//variabili membro
	std::string id;
	string nome;
	double prezzoAcquisto;
	double prezzoVendita;

	vector<componentiElettrodomestico> lstComponenti;
};
