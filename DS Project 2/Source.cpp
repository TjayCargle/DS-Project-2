#include "HTable.h"
unsigned int myHash(const string &v)
{
	int yo = 0;
	yo = ((v[0] - 'a' - 1) * 26 + (v[1] - 'a' + 1) + (v[2] - 'a' + 4) * v.length()) % 676;
	return yo;
}

int main()
{
	
	HTable<string> myTable(676, myHash);
	myTable.loadDict("engldict.txt");
	//cout << myTable.find("faiths");
	//myTable.display();
	//myTable.printSomeStuff();
	myTable.GetRandWord();
	myTable.GetRandWord();
	myTable.GetRandWord();
	myTable.GetRandWord();
	myTable.GetRandWord();
	myTable.GetRandWord();
	return 0;
}