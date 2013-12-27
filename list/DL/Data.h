/** Data.h 
George Darling 9/12/2013

A generic data class, meant to illustrate the application of
the linked list - to hold pointers to some advanced data type
*/

using namespace std;

class Data{
	private:
		int number; // Put all your other data!
	public:
		Data(int);
		void setNumber(int);
		int getNumber();
};