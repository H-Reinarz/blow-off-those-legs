//
#include <stdlib.h>
#include <stdio.h>

// Aufzaehlung der Wochentage
enum Wochentag {MONTAG, DIENSTAG, MITTWOCH, DONNERSTAG, FREITAG};

// Temporaere Stringlaenge, bis "beschreibung" dynamisch wird. WIP
typedef char beschreibungP[20];

// Datentyp: Aufgabe
// Besteht aus "von, bis, prioritaet, beschreibung" und zusaetzlich aus einem initalisierten Zeiger der Groesse "Aufgabe", um den Speicher 
// fuer weitere Aufgaben zu reservieren.
typedef struct AufgabeTag{
	int von;
	int bis;
	int prioritaet;
	beschreibungP beschreibung;
	struct AufgabeTag *next;
} Aufgabe;

// Datentyp: Tagesliste und Zeiger zum Datentyp
// Besteht aus "kapazitaet, auslastung, Zeiger auf Aufgabe".
typedef struct{
	int kapazitaet;
	int auslastung;
	Aufgabe *aufgabe;
} Tagesliste, *TListPointer;

// Datentyp: TODOListe
typedef struct{
	
} TODOListe;

// Erstelle TagesListe mit Kapazitaetswert
Tagesliste *erstelleTagesListe(int kapazitaet2){
	// Speichere im Pointer neueListe vom Typ TListPointer die Adresse zum reservierten Speicher
	TListPointer neueListe = (TListPointer)malloc(sizeof(Tagesliste));
	// Fuege dort in die Kapazitaet, den übergebenen Wert sein
	neueListe -> kapazitaet = kapazitaet2;
	// Gebe den Pointer zurueck
	return neueListe;
}

// Loese Liste
void loescheTagesListe(Tagesliste *tl){
	free(tl);
}


void zeigeListe(TODOListe l){
	
}


int fuegeEin(Tagesliste *l, Aufgabe *a){
	l->aufgabe=a;
}

int main(void){
	
	Tagesliste test = *erstelleTagesListe(5);
	Aufgabe auftragen = {2,4,7,"Auftragen"};
	Aufgabe polieren = {9,9,9,"Polieren"};
	
	fuegeEin(&test,&polieren);
	printf("%d",test.aufgabe->bis);
	fuegeEin(&test,&auftragen);
	printf("%d",test.aufgabe->bis);
	
	
	
}


