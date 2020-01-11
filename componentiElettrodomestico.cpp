//Autore: Edoardo Bastianello , numero matricola: 1188629
//sorgente che ddefinisce le funzioni dichiarate nell'header "cassa.h"

using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include "componente.h"
#include "componentiElettrodomestico.h"

componentiElettrodomestico::componentiElettrodomestico(const componente& in, int num)
	:c{in}, pezzi{num}
{}

componente componentiElettrodomestico::getComponente()const
{	return c;
}

int componentiElettrodomestico::getPezzi()const
{	return pezzi;
}
