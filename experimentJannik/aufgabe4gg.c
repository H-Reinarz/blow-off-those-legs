//https://de.wikibooks.org/wiki/C-Programmierung:_Verkettete_Listen
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Aufzaehlung der Wochentage
enum Wochentag {MONTAG, DIENSTAG, MITTWOCH, DONNERSTAG, FREITAG};

int mallocCall, freeCall;

// Temporaere Stringlaenge, bis "beschreibung" dynamisch wird. WIP
//typedef char beschreibungP[1024];

// Datentyp: Aufgabe
// Besteht aus "von, bis, prioritaet, beschreibung" und zusaetzlich aus einem initalisierten Zeiger der Groesse "Aufgabe", um den Speicher 
// fuer weitere Aufgaben zu reservieren.
typedef struct AufgabeTag{
	int von;
	int bis;
	int prioritaet;
	char *beschreibung;
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
typedef Tagesliste *TODOListe[7];


// Erstelle TagesListe mit Kapazitaetswert
Tagesliste *erstelleTagesListe(int kapazitaet2){
	// Speichere im Pointer neueListe vom Typ TListPointer die Adresse zum reservierten Speicher
	TListPointer neueListe = (TListPointer)malloc(sizeof(Tagesliste));
	mallocCall++;
	// Fuege dort in die Kapazitaet, den übergebenen Wert sein
	neueListe -> kapazitaet = kapazitaet2;
	neueListe->aufgabe = 0;
	// Gebe den Pointer zurueck
	return neueListe;
}

void loescheAufgabe(Aufgabe *aufgabe){
	
	if (aufgabe == NULL){
		return;
	}
	loescheAufgabe(aufgabe->next);
	free(aufgabe->beschreibung);
	free(aufgabe);
	freeCall++;

}

// Loese Liste
void loescheTagesListe(Tagesliste *tl){
	
	if(tl != NULL){
		loescheAufgabe(tl->aufgabe);
		free(tl);
		freeCall++;

	}
	
}



Aufgabe *erstelleAufgabe(){
	AufgabePointer neueAufgabe = (AufgabePointer)malloc(sizeof(Aufgabe));
	mallocCall++;
	
	
	printf("\nBitte Daten eingeben: \n");
	do{
		printf("Von: ");
		scanf("%d",&neueAufgabe->von);
	} while(neueAufgabe->von < 0 || neueAufgabe->von > 24);
	
	do{
		printf("Bis: ");
		scanf("%d",&neueAufgabe->bis);	
	} while(neueAufgabe->bis <= neueAufgabe->von || (neueAufgabe->bis < 0 || neueAufgabe->bis > 24));
	
	
	do{
		printf("Prioritaet (1-10): ");
		scanf("%d", &neueAufgabe->prioritaet);	
	} while(neueAufgabe->prioritaet < 1 || neueAufgabe->prioritaet > 10);
	
	// Reste der letzten Eingaben mit scanf löschen
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Beschreibung: ");
	char buffer[1024];
	fgets(buffer, 1024, stdin);				 
	                            neueAufgabe->beschreibung = malloc(strlen(buffer));
                                strcpy(neueAufgabe->beschreibung, buffer);
	neueAufgabe->next = NULL;	
	return neueAufgabe;
	
}

int fuegeEin(Tagesliste *l, Aufgabe *a){
	
	
	l->kapazitaet = l->kapazitaet - (a->bis - a->von);
	l->auslastung = l->auslastung + (a->bis - a->von);
	
	
	
	Aufgabe *pEintrag;
			for(pEintrag = l->aufgabe; pEintrag != NULL; pEintrag = pEintrag->next)
				if(pEintrag->von < a->bis && a->von < pEintrag->bis){
					loescheAufgabe(a)	;
					return 1; // Kollision gefunden -> Abbruch
					
					
				}
				
	
	
	Aufgabe *neueAufgabe;
	
	if(l->aufgabe == NULL && l->auslastung <= l->kapazitaet){
		l->aufgabe = a;
		
		return 0;	
	} 
	if(l->auslastung <= l->kapazitaet){
		
		neueAufgabe = l->aufgabe;
		
		while(neueAufgabe->next != NULL){
		
			neueAufgabe = neueAufgabe->next;
		}
		
		
		
		neueAufgabe->next = a;
		return 0;
	} 
	else{
	
		return 2;
	}
}
	
void printliste(Aufgabe *a){

    for( ; a != NULL ; a = a->next ){
    	
    	printf("Von %d bis %d, Prioritaet: %d, %s\n\n", a->von,a->bis,a->prioritaet,a->beschreibung);
    }
}	
	
void printTodo(TODOListe todo){
	
	for(int i = 0; i < 7; i++){
		
		if (todo[i] != NULL){
			printf("Wochentag: %d\n",i);
			printliste(todo[i]->aufgabe);	
		}
		
	}
	
}
	

	


int main(void){
	
	int auswahl = 0;
	int Tag = 0;
	TODOListe todoListe;
	todoListe[0]=NULL;
	todoListe[1]=NULL;
	todoListe[2]=NULL;
	todoListe[3]=NULL;
	todoListe[4]=NULL;
	todoListe[5]=NULL;
	todoListe[6]=NULL;
	
	while(auswahl != 4){
		printf("1 - Aufgabe anlegen\n");
		printf("2 - Liste ausgeben\n");
		printf("3 - Speicheranforderungen und -freigaben anzeigen (malloc & free)\n");
		printf("\n");
		printf("4 - Programm beenden\n");
		printf("====================\n");
		scanf("%d",&auswahl);
		
		if(auswahl == 1){
			do{
				printf("\nWochentag (Mo=1, So=7): ");
				scanf("%d",&Tag);
			} while(Tag > 7 ||Tag < 1);
			
			Tag--;
			
			if(todoListe[Tag] == NULL){
				todoListe[Tag] = erstelleTagesListe(12);
				//fuegeEin(todoListe[Tag],erstelleAufgabe());
				
				switch( fuegeEin(todoListe[Tag],erstelleAufgabe()) ) {
					
					case(1):
						printf("Aufgaben kollidieren miteinander! (Fehlercode: 1)\n\n");
						
						break;
					case(2):
						printf("\nTag hat nur 24 Stunden. Auslastung zu gross! (Fehlercode: 2)\n\n");
						loescheTagesListe(todoListe[Tag]);
						todoListe[Tag] = NULL;
						break;
				}
			} else{
				
				switch(fuegeEin(todoListe[Tag],erstelleAufgabe())){
					
					case(1):
						printf("Aufgaben kollidieren miteinander! (Fehlercode: 1) \n\n");
						break;
					case(2):
						printf("\nTag hat nur 24 Stunden. Auslastung zu gross! (Fehlercode: 2)\n\n");
						break;
				}
			}
			printf("\n");
			
		}
		
		if(auswahl == 2){
			printTodo(todoListe);

		}	
		
		if(auswahl == 3){
			printf("\nSpeicher angefordert: %d mal\n",mallocCall);
			printf("Groesse einer Anforderung: %d Bytes\n", sizeof(Aufgabe));
			printf("Angeforderter Speicher geloescht: %d mal\n\n",freeCall);
		}
	}
	for(int i = 0;i<7;i++){
		loescheTagesListe(todoListe[i]);
	}
	printf("Speicher angefordert: %d mal\n",mallocCall);
	printf("Angeforderter Speicher geloescht: %d mal\n",freeCall);
	
}
