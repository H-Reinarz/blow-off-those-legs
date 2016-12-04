#include <iostream>
#include <stdlib.h>
using namespace std;



class CSchiff{
	private:
		int laenge = 999; 
		int xCoord = 999; 
		int yCoord = 999;
		int ausrichtung = 999; // 0 = Nach rechts, 1 = Nach unten
		int trefferCount = 0;
		//int koordArray[3][2]; //Das muss ein Pointer sein
		
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
				//belegeKoordinaten(x,y,a,l);
				return 0;
			} else{
				cout << "Das Schiff befindet sich nicht im Schlachtfeld! Aendern Sie die Position!" << endl;
				return 1;
			}
		}
		
/* 		void belegeKoordinaten(int x,int y,int a,int l){
			switch(a){
				case(0):
					// Build CoordList
					for(int i = 0; i < l; i++){
						koordArray[i][0] = x+i;
						koordArray[i][1] = y;
					}
					break;
				case(1):
					for(int i = 0; i < l; i++){
						koordArray[i][0] = x;
						koordArray[i][1] = y+i;
					}
					break;
			}
		}
 */		
		
		
		int treffer(int x, int y){
			switch(ausrichtung){
				case(0):
					if (x >= xCoord && x<= xCoord+laenge && y == yCoord){
						trefferCount++;
						if(trefferCount >= laenge){
							cout << "Schiff wurde versenkt!" << endl;
							return 1;
						} else{
							cout << "Schiff wurde getroffen!" << endl;
							return 0;
						}
					} else{
						cout << "Nichts getroffen!" << endl;
						return 2;
					}
				case(1):
					if (x == xCoord && y >= yCoord && y<=laenge){
						trefferCount++;
						if(trefferCount >= laenge){
							cout << "Schiff wurde versenkt!" << endl;
							return 1;
						} else{
							cout << "Schiff wurde getroffen!" << endl;
							return 0;
						}
					} else{
						cout << "Kein Treffer!" << endl;
						return 2;
					}			
			}
		}
		
		// Fehlercodes: 1 = blockiert; 0 = nicht blockiert
	 	int blockiert(CSchiff anderesSchiff){
			
			//if gleicher Anfang
			
			if (anderesSchiff.getAusrichtung() == ausrichtung){
				switch(ausrichtung){
					case 0:
						// Dieses Schiff
						int anfang_ds = xCoord
						int ende_ds = xCoord + laenge
						// Anderes Schiff
						int anfang_as = anderesSchiff.getX()
						int ende_as = anderesSchiff.getX() + anderesSchiff.getLaenge()
						if ()
						break;
						
					case(1):
						//for
						break;		
						
				 }
			}
			else if {
				//mach wat anderet!
			}
			
			
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
		int schlachtschiff = 1;
		int kreuzer = 2;
		int zerstoerer = 3;
		int uboot = 4;
		
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
			
			int x = 0;
			int y = 0;
			int a = 0;
			
			for(int schiff = 0; schiff < 10; schiff++){
				
				int x = rand() % 10;
				int y = rand() % 10;
				int a = rand() % 2;
				
				while(flotte[schiff].spawnShip(x,y,a,2) == 1){ //Geht das so? Die Ueberpruefung und gleichzeitige Aufrufung der Funktion?
					int x = rand() % 10;
					int y = rand() % 10;
					int a = rand() % 2;
				}
				
				switch(flotte[schiff].getAusrichtung()){
					case(0):
						for(int feld = flotte[schiff].getX(); feld < flotte[schiff].getX()+flotte[schiff].getLaenge(); feld++){
							schlachtfeld[flotte[schiff].getY()][feld] = 4;
						}
						break;
					case(1):
						for(int feld = flotte[schiff].getY(); feld < flotte[schiff].getY()+flotte[schiff].getLaenge();feld++){
							schlachtfeld[feld][flotte[schiff].getX()] = 4;	
						}
						break;
					default:
						cout << "Ungueltige Ausrichtung" << endl;
						break;
				}
				
			}
			
		 
		}
		
		void attack(int x, int y){
			
			switch(3){ //Hier muessen theoretisch alle Schiffe durchlaufen werden, die sich auf dem Feld befinden
				case(0):
					schlachtfeld[y][x] = 1;
					break;
				case(1):
					schlachtfeld[y][x] = 2;
					break;
				case(2):
					schlachtfeld[y][x] = 3;
					break;
			}
		}
		
		void anzeigen(){
			for(int iy = 0; iy < 10; iy++){
				for(int ix = 0; ix < 10; ix++){
					switch(schlachtfeld[iy][ix]){
						case(0): // Kein Schiff
							cout << "~" << " "; 
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
		
		
		
		
			
	
};

int main (void){
	
	
	
	
	
	CSpieler spieler1;
	//spieler1.anzeigen();
	spieler1.schiffe_setzen();
	spieler1.anzeigen();
	
	
	
	
	return 0;
}

