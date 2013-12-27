#include "Data2.h"
using namespace std;

Data2::Data2(int number){ // constructor
	num = number;
}

void Data2::setNumber(int number){ // change number
	num = number;
}
int Data2::getNumber(){ // fetch the private number
	return num;
}
