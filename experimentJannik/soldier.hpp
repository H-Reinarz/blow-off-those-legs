#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream>
#include <string>

using namespace std;

class CSoldier{
	private:
		string name;
		string weapon;
		static int counter;
		CSoldier *next = nullptr;
	public:
		CSoldier(): CSoldier("Unkown Soldier","Spaten"){}
		
		CSoldier(string n, string w)
			: name(n),weapon(w){counter++;}
		
		CSoldier(const CSoldier& s)
			: name(s.name), weapon(s.weapon){counter++;}
		
		string getName(){return name;}
		string getWeapon(){return weapon;}
		int getCounter(){return counter;}
		void setNext(CSoldier *nextSoldier){next=nextSoldier;}
		CSoldier *getNext(){return next;}
		
		~CSoldier(){counter--; delete next;}
};

class CArmy{
	private:
		CSoldier *leader = nullptr;
		CSoldier *tmp = nullptr;
	public:
		void addSoldier(CSoldier newSold);
		void newSoldier(string newName, string newWeapon);
		void anzeigen();
		
		~CArmy(){delete leader;}
};

#endif
