#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Bereiche
enum Bundesland {HESSEN, NRW, BERLIN, HAMBURG};

// Kunde: Linked-List Node
typedef struct Kunde {
	int knr;
	char name[50+1];
	struct Kunde* next;
} Kunde;

// Bereichsliste: Linked-List Head
typedef struct {
	enum Bundesland bundesland;
	Kunde* kunde1;
} Bereichsliste;

// Adressbuch: array
typedef Bereichsliste* Adressbuch[4];

//Bereichsliste erstellen
Bereichsliste* erstelleBereichsliste (enum Bundesland Land){
	Bereichsliste* liste = (Bereichsliste*) malloc(sizeof(Bereichsliste));
	liste->bundesland = Land;
	return liste;
};

//Adressen einfügen
int NeuerKunde(char name[50+1], int kundenNr, Bereichsliste* Head){
	
	//Neue Node mit Inhalt in den Heap legen
	Kunde* kunde = (Kunde*) malloc(sizeof(Kunde));
	strcpy(kunde->name, name);
	kunde->knr = kundenNr;
	kunde->next = NULL;
	
	
	//Iteration
	//Kunde* Iterator, Previous;
	
		//Initialisierung
	Kunde* Iterator = Head->kunde1;
	Kunde* Previous = Head->kunde1;
	
	//Leere Liste	
	if (Iterator != NULL){
		//Schleife
		while (Iterator->next != NULL){
			//Sortierbedingung
			if (Iterator->knr < kundenNr){
				Previous = Iterator;
				Iterator = Iterator->next;
			}
			else if (Iterator->knr == kundenNr){
				//Kundennummer bereits vergeben
				return 1;
			}
			else {
				// EINFUEGEN
				kunde->next = Iterator;
				Previous->next = kunde;	
			}
		}
	}
	else {Head->kunde1 = kunde;}
}	

int main(void) {
	//Adressbuch anlegen
	Adressbuch add = {NULL, NULL, NULL, NULL};
	//printf("Neues Adressbuch:\n");
	
	return 0;
}
