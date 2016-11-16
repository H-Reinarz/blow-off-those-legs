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
Kunde* NeuerKunde(char name[50+1], int kundenNr){
	Kunde* kunde = (Kunde*) malloc(sizeof(Kunde));
	//kunde->name = name;
	strcpy(kunde->name, name);
	kunde->knr = kundenNr;
	kunde->next = NULL;
	return kunde;
};	

int main(void) {
	//Adressbuch anlegen
	//Adressbuch add = {NULL, NULL, NULL, NULL};
	printf("Neues Adressbuch:\n");
	
	return 0;
};
