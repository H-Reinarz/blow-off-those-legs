#include <iostream>
#include <string>
#include "soldier.hpp"

using namespace std;

int CSoldier::counter = 0;

void CArmy::addSoldier(CSoldier newSold){
	tmp = leader;
	leader = new CSoldier(newSold);
	leader->setNext(tmp);
}

void CArmy::newSoldier(string newName, string newWeapon){
	tmp = leader;
	leader = new CSoldier(newName, newWeapon);
	leader->setNext(tmp);
}

void CArmy::anzeigen(){
	if (leader == nullptr){
		cout << "Es ist kein Soldat in der Armee!" << endl;
	} else{
		tmp = leader;
		while(tmp != nullptr){
			cout << "Name: " << tmp->getName() << endl;
			cout << "Waffe: " << tmp->getWeapon() << endl << endl;
			tmp = tmp->getNext();
		}
	}
}

int main (void){
	CArmy battleBros;
	battleBros.anzeigen();
	battleBros.newSoldier("Fabian Siegismund", "M4");
	battleBros.anzeigen();
	CSoldier Marco("Marco", "Flammenwerfer");
	battleBros.addSoldier(Marco);
	battleBros.anzeigen();
	
	return 0;
}
