//https://de.wikibooks.org/wiki/C-Programmierung:_Verkettete_Listen
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Aufzaehlung der Wochentage
enum Wochentag {MONTAG, DIENSTAG, MITTWOCH, DONNERSTAG, FREITAG};

// Temporaere Stringlaenge, bis "beschreibung" dynamisch wird. WIP
typedef char beschreibungP[1024];

// Datentyp: Aufgabe
// Besteht aus "von, bis, prioritaet, beschreibung" und zusaetzlich aus einem initalisierten Zeiger der Groesse "Aufgabe", um den Speicher 
// fuer weitere Aufgaben zu reservieren.
typedef struct AufgabeTag{
	int von;
	int bis;
	int prioritaet;
	beschreibungP beschreibung;
	struct AufgabeTag *next;
} Aufgabe, *AufgabePointer;

// Datentyp: Tagesliste und Zeiger zum Datentyp
// Besteht aus "kapazitaet, auslastung, Zeiger auf Aufgabe".
typedef struct{
	int kapazitaet;
	int auslastung;
	Aufgabe *aufgabe;
} Tagesliste, *TListPointer;

// Datentyp: TODOListe
typedef struct{
	Tagesliste *tageslisten[7];
} TODOListe, *TODOPointer;

// Erstelle TagesListe mit Kapazitaetswert
Tagesliste *erstelleTagesListe(int kapazitaet2){
	// Speichere im Pointer neueListe vom Typ TListPointer die Adresse zum reservierten Speicher
	TListPointer neueListe = (TListPointer)malloc(sizeof(Tagesliste));
	// Fuege dort in die Kapazitaet, den übergebenen Wert sein
	neueListe -> kapazitaet = kapazitaet2;
	neueListe->aufgabe = NULL;
	// Gebe den Pointer zurueck
	return neueListe;
}

// Loese Liste
void loescheTagesListe(Tagesliste *tl){
	free(tl);
}

Aufgabe *erstelleAufgabe(){
	AufgabePointer neueAufgabe = (AufgabePointer)malloc(sizeof(Aufgabe));
	
	int von;
	int bis;
	int prioritaet;
	beschreibungP beschreibung;
	
	printf("Bitte Daten eingeben: \n");
	printf("Von: ");
	scanf("%d",&von);
	printf("Bis: ");
	scanf("%d",&bis);
	printf("Prioritaet (1-10): ");
	scanf("%d", &prioritaet);
	printf("Beschreibung: ");
	scanf("%s", &beschreibung);
	
	
	
	neueAufgabe->von = von;
	neueAufgabe->bis = bis;
	neueAufgabe->prioritaet = prioritaet;
	strcpy(neueAufgabe->beschreibung,beschreibung);
	
	return neueAufgabe;
	
}

void zeigeListe(TODOListe l){
	
}


int fuegeEin(Tagesliste *l, Aufgabe *a){
	

	Aufgabe *neueAufgabe;
	
	if(l->aufgabe == NULL){
		l->aufgabe = a;
		
		
	} else{
		
		neueAufgabe = l->aufgabe;
		
		while(neueAufgabe->next != NULL){
		
			neueAufgabe = neueAufgabe->next;
		}
		
		
		
		neueAufgabe->next = a;
	}
}
	
void printliste(Aufgabe *a){

    for( ; a != NULL ; a = a->next ){
    	printf("JA GG!");
    	printf("Von %d bis %d, Prioritaet: %d, %s\n\n", a->von,a->bis,a->prioritaet,a->beschreibung);
    }
}	
	
void printTodo(TODOListe *todo){
	
	for(int i = 0; i < 7; i++){
		
		if (todo->tageslisten[i] != NULL){
			printf("Wochentag: %d\n",i);
			printliste(todo->tageslisten[i]->aufgabe);	
		}
		
	}
	
}
	

	


int main(void){
	
	int auswahl = 0;
	int Tag = 0;
	TODOListe todoListe;
	
    todoListe.tageslisten[0] = NULL;
	todoListe.tageslisten[1] = NULL;
   	todoListe.tageslisten[2] = NULL;
   	todoListe.tageslisten[3] = NULL;
    todoListe.tageslisten[4] = NULL;
    todoListe.tageslisten[5] = NULL;
   	todoListe.tageslisten[6] = NULL;
	
	while(auswahl != 3){
		printf("1 - Aufgabe anlegen\n");
		printf("2 - Liste ausgeben\n");
		printf("3 - Programm beenden\n");
		scanf("%d",&auswahl);
		
		if(auswahl == 1){
			printf("\nWochentag (Mo=1, So=7): ");
			scanf("%d",&Tag);
			Tag--;
			
			if(todoListe.tageslisten[Tag] == NULL){
				todoListe.tageslisten[Tag] = &(*erstelleTagesListe(24));
				fuegeEin(todoListe.tageslisten[Tag],&(*erstelleAufgabe()));
			} else{
				fuegeEin(todoListe.tageslisten[Tag],&(*erstelleAufgabe()));
			}
			printf("\n");
			
		}
		
		if(auswahl == 2){
			printTodo(&todoListe);

		}	
	}		
}

