//un oggetto di tipo componentiElettrodomestico servira' per rappresentare un oggetto di tipo elettrodomestico

class componentiElettrodomestico{

public:
	componentiElettrodomestico(componente in, int num);
	
	//funzioni di accesso
	componente getComponente()const;
	int getPezzi()const;

private:
	componente c;
	int pezzi;
};
