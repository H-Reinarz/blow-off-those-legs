#include <stdio.h>
#include <stdlib.h>

typedef char Name[1024];

typedef struct AdresseTag{
	Name kundenamen;
	int alter;
	struct AdresseTag *next;
}Adresse, *AdressePointer;

typedef struct{
	int bereich;
	Adresse *adresse;
}Bereich,*BereichPointer;

Bereich *erstelleBereich(int bereichNr){
	BereichPointer neuerBereich = (BereichPointer)malloc(sizeof(Bereich));
	neuerBereich->bereich = bereichNr;
	neuerBereich->adresse = NULL;
	return neuerBereich;
}

void fuegeAdresse (Bereich *bereichName, Adresse *adresseAdd){
	AdressePointer aktuelleAdresse;
	
	if (bereichName->adresse == NULL){
		bereichName->adresse = adresseAdd;
	} else {
		
		if(bereichName->adresse->alter < adresseAdd->alter){
			adresseAdd->next = bereichName->adresse;
			bereichName->adresse = adresseAdd;
		} else{
			AdressePointer vorgaengerAdresse = bereichName->adresse;
			aktuelleAdresse = bereichName->adresse;
		
			while(adresseAdd->alter < aktuelleAdresse->alter && aktuelleAdresse->next != NULL){
				vorgaengerAdresse = aktuelleAdresse;
				aktuelleAdresse = aktuelleAdresse->next;
			}
			
			adresseAdd->next = aktuelleAdresse;
			vorgaengerAdresse->next = aktuelleAdresse;
		
			
		}
		
		
		
		
		
		
		
	//	while(neueAdresse->next != NULL){
	//		neueAdresse = neueAdresse->next;
	//	}
	//	neueAdresse->next = adresseAdd;
	}
}

void printKunden(Bereich *bereichPrint){
	AdressePointer adressenListe = bereichPrint->adresse;
	
	printf("BereichsNr. %d ", bereichPrint->bereich);
	switch(bereichPrint->bereich){
		case 1: printf("(Marketing)\n");break;
		case 2: printf("(Boolshit)\n");break;
		default: printf("Keinen bereich angegeben\n");break;
	}
	
	
	for(;adressenListe != NULL; adressenListe = adressenListe->next){
		printf("%s; TeleNr. %d\n",adressenListe->kundenamen,adressenListe->alter);
	}
}


int main (void){
	
	Bereich marketing = *erstelleBereich(1);
	Bereich boolshit = *erstelleBereich(2);
	Adresse Kunde1 = {"Bob Bobmann",8};
	Adresse Kunde2 = {"Donald Trump",71};
	Adresse Kunde3 = {"Christian Wulff",33};
	Adresse Kunde4 = {"Guenther Oettinger",72};
	
	fuegeAdresse(&marketing,&Kunde1);
	fuegeAdresse(&marketing,&Kunde2);
	fuegeAdresse(&marketing,&Kunde3);
	fuegeAdresse(&marketing,&Kunde4);
	
	printKunden(&marketing);
	//printKunden(&boolshit);
	
	
	return 0;
}
