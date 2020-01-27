#include <iostream>
#include "gestione.h"

using namespace std;

int main(){
	Gestione ElettroDom {};
	int mesiMancanti=2;
	while(!ElettroDom.endProgram()){
		if(ElettroDom.aggiornaMese())
			cout<<ElettroDom.stampaStato()<<endl;
		else
			cout<<"Nessun ordine evaso\n";
		
		cout<<"\n\n\t\tPassa un mese\n\n";
	}
	return 0;
}
