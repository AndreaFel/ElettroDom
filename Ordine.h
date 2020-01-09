#include<iostream>

 struct ordini{
      std::string id;
      bool evaso; //true se è gia stato evaso, false se è ancora da evadere
      int quantita;
    }
    
class ordine{

  public:
  
          ordine(ordini ord[]); //costruttore
          
          void addOrdine(std::string id, bool evaso, int quantita); //metodo per accedere alla lista di ordini
          int setEvaso(std::string id); /*ricerca dell'ordine in base all'id,
                                         * ritorna la posizione nell'array, -1 se la ricerca non è andata a buon fine */
                                         
          ordini() 
          
  private:
           ordini ord[];
   
       
}
