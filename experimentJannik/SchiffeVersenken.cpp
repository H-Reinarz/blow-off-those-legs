#include <iostream>
using namespace std;



class CSchiff{
	private:
		int laenge; 
		int xCoord = 999; 
		int yCoord = 999;
		int ausrichtung = 999; // 0 = Nach rechts, 1 = Nach unten
		int trefferCount = 0;
		
		int set(int l){ //Setter, vom Konstruktor aufgerufen
			laenge = l;
		}
		
	public:
		CSchiff(int l) { // Konstruktor
			set(l);	                
		}  
		
		int isInBattlefield(int x, int y, int a) { // liegt das Schiff im Spielfeld 10x10?
			int returnCode;
			switch(a){ 
				case(0):
					if(x+laenge<=10 && x>= 0 && y <= 10 && y >= 0){
						returnCode = 0;
						break;
					} else{
						returnCode = 3; // Fehlercode 3: Schiff ragt aus X-Achse
						break;
					}
				case(1):
					if(x<=10 && x>= 0 && y+laenge <= 10 && y >= 0){
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
		
		int spawnShip(int x, int y, int a){
			if(isInBattlefield(x,y,a) == 0){
				xCoord = x;
				yCoord = y;
				ausrichtung = a;
			} else{
				cout << "Das Schiff befindet sich nicht im Schlachtfeld! Aendern Sie die Position!" << endl;
			}
		}
		
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
	 
	 	int blockiert(CSchiff anderesSchiff){
	 		switch(ausrichtung){
	 			case(0):
	 				break;
	 				
	 			case(1):
	 				break;		
	 				
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
		CSchiff schlachtschiff;
		CSchiff kreuzer;
		CSchiff zerstoerer;
		CSchiff uboot;
		int schlachtfeld[10][10];
		
		void createBattlefield(){
			for(int iy = 0; iy < 10; iy++){
				for(int ix = 0; ix < 10; ix++){
					schlachtfeld[iy][ix] = 0;
				}
			}
		}
		
	public:
		CSpieler(): schlachtschiff(5), kreuzer(4), zerstoerer(3), uboot(2) {createBattlefield();} //copy Konstruktor
		
		
		void schiffe_setzen(){
			kreuzer.spawnShip(0,0,0); //Hier muessen alle Schiffe gesetzt werden
			
			switch(kreuzer.getAusrichtung()){
				case(0):
					for(int feld = kreuzer.getX(); feld < kreuzer.getX()+kreuzer.getLaenge(); feld++){
						schlachtfeld[kreuzer.getY()][feld] = 4;
					}
					break;
			} 
		}
		
		void attack(int x, int y){
			
			switch(kreuzer.treffer(x,y)){ //Hier muessen theoretisch alle Schiffe durchlaufen werden, die sich auf dem Feld befinden
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
		
		
		
		
			
	
};

int main (void){
	
	
	
	
	
	CSpieler spieler1;
	spieler1.anzeigen();
	spieler1.schiffe_setzen();
	spieler1.attack(2,0);
	spieler1.attack(2,4);
	spieler1.attack(0,0);
	spieler1.attack(1,0);	
	spieler1.attack(3,0);
	spieler1.anzeigen();
	
	
	
	
	return 0;
}

