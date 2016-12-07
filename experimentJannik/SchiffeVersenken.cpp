// Henning Reinarz und Jannik Guenther
// Programmieren in C++
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int FELDGROESSE = 10;

class CSchiff{
	private:
		int laenge = 999; 
		int xCoord = 999; 
		int yCoord = 999;
		int ausrichtung = 999; // 0 = Nach rechts, 1 = Nach unten
		int trefferCount = 0;
		
	public:
		CSchiff() {} 
		
		// piz = Punkt in Zone? Wert: 1 = JA; 0 = NEIN 
		bool piz(int puffer, int pX, int pY){
			if (pX >= (xCoord-puffer) && pX <= (getEndX()+puffer) &&
				pY >= (yCoord-puffer) && pY <= (getEndY()+puffer)){
					return 1;
				}
				else {return 0;}		 
		} 
		
		// Liegt das Schiff im Spielfeld?
		int isInBattlefield(int x, int y, int a, int l){ 
			int returnCode;
			switch(a){ 
				case(0):
					if(x+l<=FELDGROESSE && x>= 0 && y <= FELDGROESSE && y >= 0){
						return 0;
					} else{
						return 3; // Fehlercode 3: Schiff ragt aus X-Achse
					}
				case(1):
					if(x<=FELDGROESSE && x>= 0 && y+l <= FELDGROESSE && y >= 0){
						return 0;	
					} else{
						return 4; // Fehlercode 4: Schiff ragt aus Y-Achse
					}
				default:
					return 5; // Fehlercoe 5: Ungueltige Ausrichtung
			}	
		}
		
		// Setzt das Schiff auf das Spielfeld, sofern die Koordinaten im Spielfeld liegen.
		int setzeSchiff(int x, int y, int a, int l){
			if(isInBattlefield(x,y,a,l) == 0){
				xCoord = x;
				yCoord = y;
				ausrichtung = a;
				laenge = l;
				return 1;
			} else{
				return 0;
			}
		}
		
		// Wurde das Schiff getroffen bzw. versenkt? Wenn ja, zaehle den Treffercounter hoch
		int treffer(int x, int y){			
					if (piz(0, x, y) == 1){
						trefferCount++;
						if(trefferCount >= laenge){
							return 1; // Versenkt!
						} else{
							return 0; // Getroffen!
						}
					} else{
						return 2; // Fehlschuss!
					}
		}
	 
	 	// Fehlercodes: 0 = nicht blockiert; 1 = blockiert
	 	int blockiert(CSchiff anderesSchiff, int  puffer){
			//Funktioniert nur wenn die Schiffe der Größe nach gesetzt werden!		
			
			//Gleiche Ausrichtung (parallel)
			if (anderesSchiff.getAusrichtung() == ausrichtung){
					if (piz(1, anderesSchiff.getX(), anderesSchiff.getY()) == 1 ||
						piz(1, anderesSchiff.getEndX(), anderesSchiff.getEndY()) == 1){
							return 1;
						}
					else {return 0;}
			}
			//Ungleiche Ausrichtung (rechtwinkelig)
			else if (anderesSchiff.getAusrichtung() != ausrichtung){
				switch(ausrichtung){
					case 0:
						for (int xwalk = xCoord; xwalk <= getEndX(); xwalk++){
						if (anderesSchiff.piz(1, xwalk, yCoord)) {return 1;}
						}
						return 0;
						
					case 1:	
						for (int ywalk = xCoord; ywalk <= getEndY(); ywalk++){
						if (anderesSchiff.piz(1, xCoord, ywalk)) {return 1;}
						}
						return 0;
				}
			}
		}
		
		// Getter fuer Anfangs- und Endpunkt
		int getX() {return xCoord;}
		int getY() {return yCoord;}
		int getEndX(){return (ausrichtung == 0) ? xCoord+laenge : xCoord;}
		int getEndY(){return (ausrichtung == 1) ? yCoord+laenge : yCoord;}
	 	
	 	// Getter fuer sonstige Attribute
		int getLaenge() {return laenge;}
		int getAusrichtung() {return ausrichtung;}
		int getTreffer() {return trefferCount;}
		
		// Destruktor
		~CSchiff(){};
};

class CSpieler{
	private:
		CSchiff flotte[10];
		int schlachtfeld[FELDGROESSE][FELDGROESSE];
		//int schiffsGroessen[10]={5,4,4,3,3,3,2,2,2,2}; //Funktioniert nicht einwandfrei
		int schiffsGroessen[10]={1,1,1,1,1,1,1,1,1,1};
		int zerstoerteSchiffe = 0;
		
		// Erstelle das Schlachtfeld
		void erstelleSchlachtfeld(){
			for(int iy = 0; iy < FELDGROESSE; iy++){
				for(int ix = 0; ix < FELDGROESSE; ix++){
					schlachtfeld[iy][ix] = 0;
				}
			}
		}
		
	public:
		CSpieler(): flotte() {erstelleSchlachtfeld();} //copy Konstruktor
		
		// Verteilt der Reihe nach, per Zufall, alle Schiffe
		// WENN: ausrichtung ungueltig, nicht im Schlachtfeld oder durch ein anderes Schiff blockiert -> Wiederholung
		void schiffe_setzen(){
			cout << "Schiffspositionen ermitteln..." << endl;
			
			int x = 0;
			int y = 0;
			int a = 0;
			bool blockiert = false;
			int gesetzt;
			bool ausrichtung = true;
			int versuche = 0; // Wie oft muessen neue Zufallszahlen generiert werden, bis Schiff erfolgreich gesetzt wurde?
			
			// Setze die 10 Schiffe
			for(int schiff = 0; schiff < 10; schiff++){
				versuche = 0;	
				
				do{
					versuche++;
					srand(time(NULL));
					x = rand() % 10;
					y = rand() % 10;
					a = rand() % 2;
					ausrichtung = true;
					
					// Sezte Schiff. 0 = Nicht im Schlachtfeld, 1 = Erfolgreich
					gesetzt = flotte[schiff].setzeSchiff(x,y,a,schiffsGroessen[schiff]);
					
					// Wenn Schiff nicht erfolgreich gesetzt wurde ist die Ausrichtung ungueltig
					if(flotte[schiff].getAusrichtung() > 1){
						ausrichtung = false;
					}
					
					// Gehe alle bisher gesetzten Schiffe durch und teste, ob eines davon blockiert. Wenn ja, blockiert = true
					for(int blockSchiff = 0; blockSchiff < schiff; blockSchiff++){
						blockiert = flotte[schiff].blockiert(flotte[blockSchiff], 1);
						if(blockiert == true){
							break;	
						}
					}
				} while(blockiert == true || gesetzt == false || ausrichtung == false);
				
				// Trage die Koordinaten des erfolgreich gesetzten Schiffes in das Spielfeld ein
				// 0 = Leerzeichen, 4 = Schiffe anzeigen (Cheat Modus)
				switch(flotte[schiff].getAusrichtung()){
						case(0):
							for(int feld = flotte[schiff].getX(); feld < flotte[schiff].getX()+flotte[schiff].getLaenge(); feld++){
								schlachtfeld[flotte[schiff].getY()][feld] = 0;
							}
							break;
						case(1):
							for(int feld = flotte[schiff].getY(); feld < flotte[schiff].getY()+flotte[schiff].getLaenge();feld++){
								schlachtfeld[feld][flotte[schiff].getX()] = 0;	
							}
							break;
						default:
							cout << "Ungueltige Ausrichtung: " << flotte[schiff].getAusrichtung() << endl;
							ausrichtung = false;
							break;
					}
				
				//cout << "Schiff " << schiff <<": " << endl; //Debug Code
				if(schiff == 9){
					cout << "." << endl;	
				} else{
					cout << ".";
				}
				//anzeigen(); //Debug Code
			}
		}
		
		// Angriffsfunktion
		void attack(int x, int y){
			bool getroffen = false;
			
			// Wenn Schlachtfeldcode 1 (Getroffen),2 (Versenkt) oder 3 (Fehlschuss) ist, wurde das Feld schonmal beschossen
			if(schlachtfeld[y][x]>=1 && schlachtfeld[y][x]<=3){
				cout << endl << endl << "      ===== Diese Koordinaten wurden schon einmal beschossen! =====" << endl << endl;
				return;
			} else{
				// Gehe jedes Schiff durch und pruefe, ob es getroffen wurde
				for(int iSchiff = 0; iSchiff < 10; iSchiff++){
					switch(flotte[iSchiff].treffer(x,y)){ 
						case(0):
							schlachtfeld[y][x] = 1; //Treffer
							cout << endl << endl << "      ===== Getroffen! =====" << endl;
							getroffen = true;
							break;
						case(1):
							schlachtfeld[y][x] = 2; //Versenkt
							getroffen = true;
							cout << endl << endl << "      ===== VERSENKT! =====" << endl;
							zerstoerteSchiffe++; //Zerstoerte Schiffe + 1
							break;
						case(2):
							schlachtfeld[y][x] = 3; //Fehlschuss
							getroffen = false;
							break;
					}	
					if(getroffen == true){
						break;
					}
				}
				cout << endl;	
			}		
		}
		
		// Zeichne das Schlachtfeld
		void anzeigen(){
			cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
			cout << "    -------------------" << endl;
			for(int iy = 0; iy < FELDGROESSE; iy++){ // Y-Achse
				cout << iy << " | ";
				for(int ix = 0; ix < FELDGROESSE; ix++){ //X-Achse
					switch(schlachtfeld[iy][ix]){
						case(0): // Kein Schiff
							cout << " " << " "; 
							break;
						case(1): // Treffer
							cout << "x" << " ";
							break;
						case(2): // Zerstoert
							cout << "X" << " ";
							break;
						case(3): // Fehlschuss
							cout << "." << " ";
							break;
						case(4): // Schiff entdeckt
							cout << "S" << " ";
					}
				}
				cout << endl;
			}
		}
		
		// Schlachtfeld resetten
		void resetteSchlachtfeld(){
			for(int iy = 0; iy < FELDGROESSE; iy++){ // Y-Achse
				for(int ix = 0; ix < FELDGROESSE; ix++){ //X-Achse
					schlachtfeld[iy][ix] == 0;
				}
			}
		}
		
		// Getter fuer die Anzahl an zerstoerten Schiffen		
		int getZerstoerteSchiffe()	{return zerstoerteSchiffe;}
};

int main (void){
	
	CSpieler spieler1;
	int auswahl = 0;
	int xAuswahl = 0;
	int yAuswahl = 0;
	int ingameAuswahl = 0;

	
	while(auswahl != 3){
		// HAUPTMENUE
		cout << "===== SCHIFFE VERSENKEN - RUDERBOOT VERSION =====" << endl << endl;
		cout << "Hauptmenue" << endl;
		cout << "----------" << endl;
		cout << "1 Neues Spiel" << endl;
		cout << "2 Spielregeln" << endl;
		cout << "3 Beenden" << endl;
		
		cout << endl;
		cout << "Ihre Auswahl(1-3): ";
		cin >> auswahl;
	
		switch(auswahl){
			case(1): // Spielbeginn
				cout << endl << "Spielbeginn: " << endl << endl;
				spieler1.schiffe_setzen();
				
				// Solange, bis alle Schiffe zerstoert wurden
				while(spieler1.getZerstoerteSchiffe() < 10){
					spieler1.anzeigen();
					cout << "(Geben Sie 999 ein, um das Spiel abzubrechen)" << endl;
					cout << "Geben Sie die X-Koordinate ein, die Sie angreifen wollen: ";
					cin >> xAuswahl;
					// Aufgeben?
					if(xAuswahl == 999){
						break;
					}
					cout << "Geben Sie die Y-Koordinate ein, die Sie angreifen wollen: ";
					cin >> yAuswahl;
					if(yAuswahl == 999){
						break;
					}
					spieler1.attack(xAuswahl,yAuswahl);
				}
				
				// Gewonnen oder Verloren?
				if (spieler1.getZerstoerteSchiffe() >= 9){
					cout << "<<<<<< GEWONNEN! >>>>>>" << endl << endl;
				}else{
					cout << endl << "Aufgegeben!" << endl << endl << endl;
				}
				spieler1.resetteSchlachtfeld();
				break;
			case(2):
				cout << endl << "Spielregeln: " << endl << endl;
				cout << "Es gibt Regeln!" << endl << endl << endl;
				break;
			case(3):
				break;
		}	
	}
	return 0;
}

