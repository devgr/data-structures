/** Data.cpp
George Darling 9/12/2013

Implimentation of the generic Data class
*/
#include "Data.h"
using namespace std;

Data::Data(int num){ // constructor
	number = num;
}

void Data::setNumber(int num){ // change number
	number = num;
}
int Data::getNumber(){ // fetch the private number
	return number;
}