//Autore: Simone Cecchinato , numero matricola: 1195817
//sorgente che contiene le definizioni delle funzioni dichiarate nell'header "componente.h"


#include "gestione.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

Gestione::Gestione(){
  FileComponenti();

}

void Gestione::FileComponenti(){  //Lettura file "components_info.dat"

	string id,nome,aux;
	int delivery = 0;
  vector<double> prezzi;


	ifstream myfile ("components_info.dat");        //RIGA: [id] [nome] [timestamp] [prezzo1:10] [prezzo11:50] [prezzo51+]
	if (myfile.is_open())
  {
    while (!myfile.eof())
    {

      getline( myfile, id, ' ');
      getline( myfile, nome, ' ');
      getline( myfile, aux, ' ');
      delivery = stoi(aux);

      getline( myfile, aux, ' ');
      prezzi[0] = stod(aux);
      getline( myfile, aux, ' ');
      prezzi[1] = stod(aux);
      getline( myfile, aux, ' ');
      prezzi[2] = stod(aux);

      componente c{id,nome,time_stamp,prezzi};  
      database_c.push_back(c);                    //Memorizzazione dei componenti per poi inviarli alla classe Elettrodomestici dopo lettura altro file

    }
    myfile.close();
  }

}

void Gestione::FileOrdini(){  //lettura file "orders.dat"

 string model_id,aux;
  int time_stamp = 0, quantita = 1;

  ifstream myfile ("orders.dat");      //RIGA: [time_stamp] [model_id] [quantity]
  if (myfile.is_open())
  {
    while (!myfile.eof())
    {
      getline( myfile, aux, ' ');
      time_stamp = stoi(aux);
      getline( myfile, model_id, ' ');
      getline( myfile, aux, ' ');
      quantita = stoi(aux);

      ordine ord{};
      ord.addOrdine( time_stamp, model_id, quantita );
    }
  }
}

void Gestione::FileElettrodomestici(){  //lettura file "modelx.dat"

  string model_id,model_name,aux
string component_id,comp_name;

  double prezzo_acq = 0, prezzo_vend = 0;
  int quantita = 0;

  for(int i=0;i<3;i++)                      //Dimensione catalogo modificabile?
  {
    ifstream myfile (catalogo[i]);       //scorro il catalogo per leggere i file dei vari modelli da noi prodotti
    if (myfile.is_open())
  {
    getline( myfile, model_id, ' ');
    getline( myfile, model_nome, ' ');    //PRIMA RIGA FILE: [model_id] [model_name] [prezzo_acquisto] [prezzo_vendita]
    getline( myfile, aux, ' ');
    prezzo_acq = stod(aux);
    getline( myfile, aux, ' ');
    prezzo_vend = stod(aux);

    elettrodomestico el{ model_id, model_nome, prezzo_acq, prezzo_vend };
 db.push_back(el);              //creazione elettrodomestico e aggiornamento database

    while (!myfile.eof())    //lettura vari componenti
    {
      getline( myfile, component_id, ' ');     //RIGA: [component_id] [component_name] [quantity_needed]
      getline( myfile, comp_name, ' ');        
      getline( myfile, aux, ' ');
      quantita = stoi(aux);

      int pos = -1;
      for(int i=0;i<database_c.size();i++)       //ricerca nel database componenti in base all'id, se trovato aggiunta componente-quantità necessaria
        if(database_c[i].getId == component_id) pos = i;

      if(pos!=-1) el.addComponentToList(database_c[pos],quantita)
    }
  }


  }                          
}
