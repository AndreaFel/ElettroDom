using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include "cassa.h"
#include "magazzino.h"
#include "componente.h"
#include "componentiElettrodomestico.h"
#include "elettrodomestico.h"


int main (void)
{	cout << "**************TEST CASSA.CPP*****************\n";
	cout << "test costruttore, funzione printFondo()\n";
	cassa cassaTest{10000};
	cassaTest.printFondo();
	cout << "test getFondo()\n";
	cout << cassaTest.getFondo() <<'\n';
	cout << "quelli sopra devono essere uguali\n\n";

	cout << "test costrutt.50\n";
	cassa cassaCos{50};
	cassaCos.printFondo();
	cout << "test addFondo 100\n";
	cassaCos.addFondo(100);
	cassaCos.printFondo();
	cout << "test subtractFondo 5\n";
	cassaCos.subtractFondo(5);
	cassaCos.printFondo();
	cout << "prova bool check(100)\n";
	cout << cassaCos.check(100) << '\n';
	cout << "prova bool check(200)\n";
	cout << cassaCos.check(200) << '\n';





	cout << "\n\n**************TEST MAGAZZINO.CPP*****************\n";
	cout << "prova costruttore vuoto(unico permesso)\n";
	magazzino mag{};
	cout << "\nprova funzione add(acciaioInox, 10) e stampa\n";
	mag.add("acciaioInox", 10);
	mag.printMagazzino();
	cout << "\nprova funzione add(acciaioBello, 15) e stampa---ordine alfabetico----\n";
	mag.add("acciaioBello", 15);
	mag.printMagazzino();

	cout << "\nprova funzione remove(acciaioInox, 5) e stampa\n";
	mag.remove("acciaioInox", 5);
	mag.printMagazzino();
	cout << '\n';

	cout << "prova funzione remove(acciaioInox, 2) e stampa\n";
	int InoxOrdinare = mag.remove("acciaioInox", 2);
	mag.printMagazzino();
	cout << "inox da ordinare--->" << InoxOrdinare << '\n';
	cout << '\n';
	cout << "prova funzione remove(acciaioBello, 40) e stampa\n";
	int BelloDaOrdinare = mag.remove("acciaioBello", 40);
	mag.printMagazzino();
	cout << "bello da ordinare--->" << BelloDaOrdinare << '\n';
	cout << "\nprova funzione remove(nonPresente, 5) e stampa\n";
	int non = mag.remove("nonPresente", 5);
	mag.printMagazzino();
	cout << "Nn presente deve -1--->" << non << "\n\n";

	cout << "\n prova int checkEnogh(Inox, 15)\n";
	InoxOrdinare = mag.checkEnough("acciaioInox", 15);
	mag.printMagazzino();
	cout << "Inox che servirebbe in piu'----->" << InoxOrdinare << '\n';
	
	cout << "\n prova int checkEnogh(Inox, 2)\n";
	InoxOrdinare = mag.checkEnough("acciaioInox", 2);
	mag.printMagazzino();
	cout << "Inox che servirebbe in piu'----->" << InoxOrdinare << '\n';

	cout << "\n prova int checkEnogh(BOOO, 15)\n";
	InoxOrdinare = mag.checkEnough("BOOO", 15);
	mag.printMagazzino();
	cout << "BOOO che servirebbe in piu' deve -1----->" << InoxOrdinare << '\n';

	cout << "\n prova int check(acciaioBello)\n";
	int index = mag.check("acciaioBello");
	cout << "deve 0----->" << index << '\n';
	
	cout << "\n prova int check(acciaioInox)\n";
	index = mag.check("acciaioInox");
	cout << "deve 1----->" << index << '\n';

	cout << "\n prova int check(NOOOO)\n";
	index = mag.check("NOOOO");
	cout << "deve -1----->" << index << '\n';

	cout << "\n prova int getId(0)\n";
	cout << mag.getId(0) << '\n';

	cout << "\n prova int getId(1)\n";
	cout << mag.getId(1) << '\n';

	cout << "\n prova int getId(100) quindi -1\n";
	cout << mag.getId(100) << '\n';

	cout << "\n prova int getPezzi(0)\n";
	cout << mag.getPezzi(0) << '\n';

	cout << "\n prova int getPezzi(1)\n";
	cout << mag.getPezzi(1) << '\n';

	cout << "\n prova int getPezzi(100) deve -1\n";
	cout << mag.getPezzi(100) << "\n\n\n\n\n";

	cout << "\nstampaMagazzino\n";
	mag.printMagazzino();

	cout << "\n prova magazzinoToString\n";
	cout << mag.magazzinoToString() << '\n';




	cout << "\n\n**************TEST COMPONENTE.CPP*****************\n";
	cout << " prova costruttore\n";
	vector<double> vet{3,2,1};
	componente x{"XquestoId", "XquestoNome", 3 ,vet};	//3 sono i mesi
	cout << x.getId() << " || " << x.getNome() << " || mesi " << x.getMesi();
	cout << " || prezzo(7 pezzi) " << x.getPrezzo(7) << " || prezzo(11 pezzi) " << x.getPrezzo(11)<< " || prezzo(59 pezzi) " << x.getPrezzo(59) << " || prezzo(-6 pezzi) " << x.getPrezzo(-6) << '\n';
	cout << "\n\n\n\n\n";
	



	cout << "\n\n**************TEST COMPONENTIELETTRODOMESTICO.CPP*****************\n";
	cout << " prova costruttore mettendo X e 10 pezzi, e prova getComponente()-da usare y.getComponente.getId()- e getPezzi()\n";
	componentiElettrodomestico y{x, 10};
	cout << y.getComponente().getId() << " || " <<y.getComponente().getNome() << " || mesi di arrivo componente: " << y.getComponente().getMesi() << " || pezzi di X: " << y.getPezzi() <<'\n';
	cout << "quindi prezzo = y.getComponente().getPrezzo(y.getPezzi())--->" << y.getComponente().getPrezzo(y.getPezzi()) << '\n';
	cout << "\n\n\n\n\n";





	cout << "\n\n**************TEST ELETTRODOMESTICO.CPP*****************\n";
	//crezione elettrodomestico aspirapolvere
	cout << "   crezione elettrodomestico aspirapolvere\n";
	elettrodomestico aspirapolvere{"aspr","aspirapolvere", 200};
	
	//creazione componente metallo e sua aggiunta a aspirapolvere
	cout << "   \ncreazione componente metallo e sua aggiunta a aspirapolvere\n";
	vector<double> prezziMetallo {30, 20, 10};
	componente metallo{"metal", "metallo", 7, prezziMetallo};
	aspirapolvere.addComponentToLst(metallo, 15);
	
	//crezione e aggiunta di plastica
	cout << "  crezione e aggiunta di plastica\n";
	vector<double> prezziPlastica {35, 25, 15};
	componente plastica{"plastic", "plastica", 8, prezziPlastica};
	aspirapolvere.addComponentToLst(plastica, 40);

	//creazione lista di componenti di aspirapolvere
	cout << "	\ncreazione lista di componenti di aspirapolvere con metallo e plastica\n\n";
	vector<componentiElettrodomestico> listaComponentiAspirapolvere = aspirapolvere.getComponents();
	
	//stampa id nome prezzo acquisto e prezzo vendita
	cout << "idElettrodomestico: " << aspirapolvere.getId() << "|| nomeElettrodomestico: " << aspirapolvere.getNome() << " || PrezzoVenditaElettrodomestico: " << aspirapolvere.getPrezzoVendita() << '\n';
	cout << "\nSTAMPA LISTACOMPONENTI\n";
	for(int i=0; i<listaComponentiAspirapolvere.size(); i++)
	{	//stampa id componente
		cout << "idComponente: " << listaComponentiAspirapolvere[i].getComponente().getId() << " || ";
		//stampa nome componente
		cout << "nome componente: " << listaComponentiAspirapolvere[i].getComponente().getNome() << " || ";
		//stampa pezzi di tale componente
		cout << "numero pezzi: " << listaComponentiAspirapolvere[i].getPezzi() << '\n';
		cout << "prezzo con questi pezzi: " << listaComponentiAspirapolvere[i].getComponente().getPrezzo(listaComponentiAspirapolvere[i].getPezzi()) << '\n';
	}

	cout << "   \n\n\ncrezione elettrodomestico lavatrice\n";
	//crezione elettrodomestico lavatrice
	elettrodomestico lavatrice{"lavat","lavatrice", 1500};
	
	//creazione componente metallo2 e sua aggiunta a aspirapolvere2
	vector<double> prezziMetallo2 {302, 202, 102};
	componente metallo2{"metal2", "metallo2", 10, prezziMetallo2};
	lavatrice.addComponentToLst(metallo2, 152);
/*	
	//crezione e aggiunta di plastica2
	vector<double> prezziPlastica2 {152, 252, 352};
	componente plastica2{"plastic2", "plastica2", 11, prezziPlastica2};
	lavatrice.addComponentToLst(plastica2, 402);
*/
	lavatrice.addComponentToLst(plastica, 117);
	//creazione lista di componenti di aspirapolvere
	vector<componentiElettrodomestico> listaComponentilavatrice = lavatrice.getComponents();
	
	//stampa id nome prezzo acquisto e prezzo vendita
	cout << "idElettrodomestico: " << lavatrice.getId() << "|| nomeElettrodomestico: " << lavatrice.getNome() << " || ";
	cout << "PrezzoVenditaElettrodomestico: " << lavatrice.getPrezzoVendita() << '\n';
	cout << "\nSTAMPA LISTACOMPONENTI\n";
	for(int i=0; i<listaComponentilavatrice.size(); i++)
	{	//stampa id componente
		cout << "idComponente: " << listaComponentilavatrice[i].getComponente().getId() << " || ";
		//stampa nome componente
		cout << "nome componente: " << listaComponentilavatrice[i].getComponente().getNome() << " || ";
		//stampa pezzi di tale componente
		cout << "numero pezzi: " << listaComponentilavatrice[i].getPezzi() << '\n';
		//stampa il prezzo di tale componente in base ai suoi pezzi
		cout << "prezzo con questi pezzi: " << listaComponentilavatrice[i].getComponente().getPrezzo(listaComponentilavatrice[i].getPezzi()) << '\n';
		cout << "mesi per arrivo: " << listaComponentilavatrice[i].getComponente().getMesi() << '\n';
	}

	return 0;
}
