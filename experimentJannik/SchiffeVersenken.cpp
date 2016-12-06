#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;



class CSchiff{
	private:
		int laenge = 999; 
		int xCoord = 999; 
		int yCoord = 999;
		int ausrichtung = 999; // 0 = Nach rechts, 1 = Nach unten
		int trefferCount = 0;

		
		//int set(int l){ //Setter, vom Konstruktor aufgerufen
		//	laenge = l;
		//}
		
	public:
		CSchiff() { // Konstruktor //Ist das so legitim?
			//set(l);	                
		}  
		
		int isInBattlefield(int x, int y, int a, int l){ // liegt das Schiff im Spielfeld 10x10?
			int returnCode;
			switch(a){ 
				case(0):
					if(x+l<=10 && x>= 0 && y <= 10 && y >= 0){
						returnCode = 0;
						break;
					} else{
						returnCode = 3; // Fehlercode 3: Schiff ragt aus X-Achse
						break;
					}
				case(1):
					if(x<=10 && x>= 0 && y+l <= 10 && y >= 0){
						returnCode = 0;	
						break;
					} else{
						returnCode = 4; // Fehlercode 4: Schiff ragt aus Y-Achse
						break;
					}
				default:
					returnCode = 5; // Fehlercoe 5: Ungueltige Ausrichtung
					break;	
			}	
			//cout << returnCode << endl;
			return returnCode;	
		}
		
		int spawnShip(int x, int y, int a, int l){
			if(isInBattlefield(x,y,a,l) == 0){
				xCoord = x;
				yCoord = y;
				ausrichtung = a;
				laenge = l;
				//cout << "Schiff wird gesetzt" << endl;
				return 0;
			} else{
				//cout << "Das Schiff befindet sich nicht im Schlachtfeld! Aendern Sie die Position!" << endl;
				return 1;
			}
		}
		
		
		
		int treffer(int x, int y){
			switch(ausrichtung){
				case(0):
					if (x >= xCoord && x<= xCoord+laenge && y == yCoord){
						trefferCount++;
						if(trefferCount >= laenge){
							//cout << "Schiff wurde versenkt!" << endl;
							return 1;
						} else{
							//cout << "Schiff wurde getroffen!" << endl;
							return 0;
						}
					} else{
						//cout << "Nichts getroffen!" << endl;
						return 2;
					}
				case(1):
					if (x == xCoord && y >= yCoord && y <= yCoord+laenge){
						trefferCount++;
						if(trefferCount >= laenge){
							//cout << "Schiff wurde versenkt!" << endl;
							return 1;
						} else{
							//cout << "Schiff wurde getroffen!" << endl;
							return 0;
						}
					} else{
						//cout << "Kein Treffer!" << endl;
						return 2;
					}			
			}
		}
	 
	 	bool blockiert(CSchiff anderesSchiff){
	 		
	 			int koordArray1[laenge][2];
	 			int koordArray2[anderesSchiff.getLaenge()][2];
	 			
	 		    switch(ausrichtung){
				case(0):
					// Build CoordList
					for(int i = 0; i < laenge; i++){
						koordArray1[i][0] = xCoord+i;
						koordArray1[i][1] = yCoord;
					}
					break;
				case(1):
					for(int i = 0; i < laenge; i++){
						koordArray1[i][0] = xCoord;
						koordArray1[i][1] = yCoord+i;
					}
					break;
				}
				
				switch(anderesSchiff.ausrichtung){
				case(0):
					// Build CoordList
					for(int i = 0; i < anderesSchiff.getLaenge(); i++){
						koordArray2[i][0] = anderesSchiff.getX()+i;
						koordArray2[i][1] = anderesSchiff.getY();
					}
					break;
				case(1):
					for(int i = 0; i < anderesSchiff.getLaenge(); i++){
						koordArray2[i][0] = anderesSchiff.getX();
						koordArray2[i][1] = anderesSchiff.getY()+i;
					}
					break;
				}
	 		
	 			bool blockiert = false;
				for(int i = 0; i < laenge; i++){
					for(int j = 0; j < anderesSchiff.getLaenge(); j++){
						if (koordArray1[i][0] == koordArray2[j][0] && koordArray1[i][1] == koordArray2[j][1]){
							blockiert = true;
							break;
						}
					}
					if(blockiert == true){
						return true;
					}
				}
				return false;
		 }
	 
		int getLaenge() {return laenge;}
		int getX() {return xCoord;}
		int getY() {return yCoord;}
		int getAusrichtung() {return ausrichtung;}
		int getTreffer() {return trefferCount;}
		
		
		~CSchiff(){}; // Destruktor
};

class CSpieler{
	private:
		CSchiff flotte[10];
		int schlachtfeld[10][10];
		int schiffsGroessen[10]={5,4,4,3,3,3,2,2,2,2};
		int zerstoerteSchiffe = 0;
		
		void createBattlefield(){
			for(int iy = 0; iy < 10; iy++){
				for(int ix = 0; ix < 10; ix++){
					schlachtfeld[iy][ix] = 0;
				}
			}
		}
		
	public:
		CSpieler(): flotte() {createBattlefield();} //copy Konstruktor
		
		
		void schiffe_setzen(){
			cout << "Schiffspositionen berechnen..." << endl;
			int x = 0;
			int y = 0;
			int a = 0;
			bool blockiert = false;
			int bereich;
			bool ausrichtung = true;
			int tryCounter = 0;
			
			for(int schiff = 0; schiff < 10; schiff++){
				
				if(schiff == 9){
					cout << "." << tryCounter << endl;;	
				} else{
					cout << "." << tryCounter << " ";
				}
				tryCounter = 0;	
				
				ausrichtung = true;
				do{
					tryCounter++;
					srand(time(NULL));
					x = rand() % 10;
					y = rand() % 10;
					a = rand() % 2;
					
					bereich = flotte[schiff].spawnShip(x,y,a,schiffsGroessen[schiff]);
				
					for(int blockSchiff = 0; blockSchiff < schiff; blockSchiff++){
						blockiert = flotte[schiff].blockiert(flotte[blockSchiff]);
						if(blockiert == true){
							break;	
						}
					}
					
					switch(flotte[schiff].getAusrichtung()){
						case(0):
							for(int feld = flotte[schiff].getX(); feld < flotte[schiff].getX()+flotte[schiff].getLaenge(); feld++){
								schlachtfeld[flotte[schiff].getY()][feld] = 4;
								//cout << schlachtfeld[flotte[schiff].getY()][feld] << endl;
							}
							break;
						case(1):
							for(int feld = flotte[schiff].getY(); feld < flotte[schiff].getY()+flotte[schiff].getLaenge();feld++){
								schlachtfeld[feld][flotte[schiff].getX()] = 4;
								//cout << schlachtfeld[feld][flotte[schiff].getX()] << endl;	
							}
							break;
						default:
							cout << "Ungueltige Ausrichtung: " << flotte[schiff].getAusrichtung() << endl;
							ausrichtung = false;
							break;
					}
				} while(blockiert == true || bereich == 1 || ausrichtung == false);
				
				
				
				
				
				/*
				while(flotte[schiff].spawnShip(x,y,a,2) == 1 || (blockiert == true && schiff > 0)){ //Geht das so? Die Ueberpruefung und gleichzeitige Aufrufung der Funktion?
					cout << "While ausgelöst" << endl;
					
					x = rand() % 10;
					y = rand() % 10;
					a = rand() % 2;
					
					for(int blockSchiff = 0; blockSchiff < schiff; blockSchiff++){
						cout << "Blockiert es?2" << endl;
						blockiert = flotte[schiff].blockiert(flotte[blockSchiff]);
						if(blockiert == true){
							cout << "Es blockiert" << endl;
							break;	
						}
					}
				}
				cout << "Random Numbers (X,Y,A): " << x << ", " << y << ", " << a << ", " << endl;
				*/
				
				
				
			}
			
		 
		}
		
		void attack(int x, int y){
			
			bool getroffen = false;
			
			if(schlachtfeld[y][x]>=1 && schlachtfeld[y][x]<=3){
				cout << endl << endl << "      ===== Diese Koordinaten wurden schon einmal beschossen! =====" << endl << endl;
				return;
			} else{
				for(int iSchiff = 0; iSchiff < 10; iSchiff++){
					switch(flotte[iSchiff].treffer(x,y)){ 
						case(0):
							schlachtfeld[y][x] = 1; //Treffer
							cout << endl << endl << "      ===== Getroffen! =====" << endl << endl;
							getroffen = true;
							break;
						case(1):
							schlachtfeld[y][x] = 2; //Versenkt
							getroffen = true;
							cout << endl << endl << "      ===== VERSENKT! =====" << endl << endl;
							zerstoerteSchiffe++;
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
			}
			
			
			
		}
		
		void anzeigen(){
			cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
			cout << "    -------------------" << endl;
			for(int iy = 0; iy < 10; iy++){
				cout << iy << " | ";
				for(int ix = 0; ix < 10; ix++){
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
		
		
	int getZerstoerteSchiffe()	{return zerstoerteSchiffe;}
		
			
	
};

int main (void){
	
	CSpieler spieler1;
	int auswahl = 0;
	int xAuswahl = 0;
	int yAuswahl = 0;
	int ingameAuswahl = 0;
	//spieler1.anzeigen();
	
	while(auswahl != 3){
		cout << "===== SCHIFFE VERSENKEN - ALPHA VERSION =====" << endl << endl;
		cout << "Hauptmenue" << endl;
		cout << "----------" << endl;
		cout << "1 Neues Spiel" << endl;
		cout << "2 Spielregeln" << endl;
		cout << "3 Beenden" << endl;
		
		cout << endl;
		cout << "Ihre Auswahl(1-3): ";
		cin >> auswahl;
	
		switch(auswahl){
			case(1):
				cout << endl << "Spielbeginn: " << endl << endl;
				spieler1.schiffe_setzen();
				
				while(spieler1.getZerstoerteSchiffe() < 9){
					spieler1.anzeigen();
					cout << "(Geben Sie eine Zahl groesser/gleich 10 ein, um das Spiel abzubrechen)" << endl;
					cout << "Geben Sie die X-Koordinate ein, die Sie angreifen wollen: ";
					cin >> xAuswahl;
					if(xAuswahl >= 10){
						break;
					}
					cout << "Geben Sie die Y-Koordinate ein, die Sie angreifen wollen: ";
					cin >> yAuswahl;
					if(yAuswahl >= 10){
						break;
					}
					spieler1.attack(xAuswahl,yAuswahl);
				}
				
				if (spieler1.getZerstoerteSchiffe() >= 9){
					cout << "<<<<<< GEWONNEN! >>>>>>" << endl << endl;
				}
				cout << endl << "Aufgegeben!" << endl << endl << endl;
				break;
			case(2):
				cout << endl << "Spielregeln: " << endl << endl;
				cout << "Ja moin!" << endl << endl << endl;
				break;
			case(3):
				break;
		}
		
		
	}
	
	
	//spieler1.schiffe_setzen();
	//spieler1.anzeigen();
	/*
	bool bob;
	CSchiff schiff1;
	schiff1.spawnShip(4,2,0,3);
	CSchiff schiff2;
	schiff2.spawnShip(2,2,0,3);
	bob = schiff2.blockiert(schiff1);
	*/
	
	
	
	
	return 0;
}

