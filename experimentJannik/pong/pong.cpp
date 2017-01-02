#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class CBall{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	CBall(int posX, int posY){
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
		direction = STOP;
	}
	
	void Reset(){
		x =  originalX; y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d){
		direction = d;
	}
	void randomDirection(){
		direction = (eDir)((rand() % 6) + 1);
	}
	inline int getX(){return x;}
	inline int getY(){return y;}
	inline eDir getDirection(){return direction;}
	void Move(){
		switch(direction){
			case STOP:
				break;
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			case UPLEFT:
				x--; y--;
				break;
			case DOWNLEFT:
				x--; y++;
				break;
			case UPRIGHT:
				x++; y--;
				break;
			case DOWNRIGHT:
				x++; y++;
				break;
			default:
				break;
		}
	}
	friend ostream & operator<<(ostream & o, CBall c){
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};

class CPaddle{
private:
	int x,y;
	int originalX, originalY;
public:
	CPaddle(){
		x = y = 0;
	}
	CPaddle(int posX, int posY):CPaddle(){
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void reset(){x=originalX; y=originalY;}
	inline int getX(){return x;}
	inline int getY(){return y;}
	inline void moveUp(){y--;}
	inline void moveDown(){y++;}
	friend ostream & operator<<(ostream & o, CPaddle c){
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
	
};

class CGameManager{
private:
	int width, height;
	int score1, score2;
	char up1,down1, up2,down2;
	bool quit;
	CBall *ball;
	CPaddle *player1;
	CPaddle *player2;
public:
	CGameManager(int w, int h){
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i'; //arrow up
		down1 = 's'; down2 = 'k'; //arrow down
		score1 = score2 = 0;
		width = w; height = h;
		ball = new CBall(w/2, h/2);
		player1 = new CPaddle(1, h/2 - 3);
		player2 = new CPaddle(w-2, h/2 - 3);
	}
	~CGameManager()
	{
		delete ball, player1, player2;
	}
	
	void ScoreUp(CPaddle *player){
		if(player == player1)
			score1++;
		else if(player == player2)
			score2++;
		
		ball->Reset();
		player1->reset();
		player2->reset();
	}
	
	void Draw(){
		//system("cls");
		ClearScreen();
		for(int i = 0; i < width + 2; i++)
			cout << "\xB2"; //top
		cout << endl;
		
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();
				
				if(j == 0)
					cout << "\xB2"; // left
					
				if(ballx == j && bally == i)
					cout << "O"; // ball
				else if(player1x == j && player1y == i)
					cout << "\xDB"; // player1
				else if(player2x == j && player2y == i)
					cout << "\xDB"; // player2
					
				else if(player1x == j && player1y + 1 == i)
					cout << "\xDB"; // player1
				else if(player1x == j && player1y + 2 == i)
					cout << "\xDB"; // player1
				else if(player1x == j && player1y + 3 == i)
					cout << "\xDB"; // player1
					
				else if(player2x == j && player2y + 1 == i)
					cout << "\xDB"; // player2
				else if(player2x == j && player2y + 2 == i)
					cout << "\xDB"; // player2
				else if(player2x == j && player2y + 3 == i)
					cout << "\xDB"; // player2
					
				else
					cout << " ";
					
				if(j == width-1)
					cout << "\xB2"; // right
			}
			cout << endl;
		}
		
		for(int i = 0; i < width + 2; i++)
			cout << "\xB2"; // bottom
		cout << endl;
		
		cout << "Score 1: " << score1 << " 		W = Up, S = Down" << endl;
		cout << "Score 2: " << score2 << " 		I = Up, K = Down" << endl;
		cout << "q = Quit" << endl;
	}
	
	void Input(){
		ball->Move();
		
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();
		
		if(_kbhit()){
			char current = _getch();
			if(current == up1)
				if(player1y > 0)
					player1->moveUp();
			if(current == up2)
				if(player2y > 0)
					player2->moveUp();
			if(current == down1)
				if(player1y + 4 < height)
					player1->moveDown();
			if(current == down2)
				if(player2y + 4 < height)
					player2->moveDown();
			
			if(ball->getDirection() == STOP)
				ball->randomDirection();
			
			if(current == 'q')
				quit = true;
		}
	}
	
	void Logic(){
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();
		
		//left paddle
		for(int i = 0; i < 4; i++)
			if(ballx == player1x + 1)
				if(bally == player1y + i)
					ball->changeDirection((eDir)((rand()%3)+4));
					
		//right paddle
		for(int i = 0; i < 4; i++)
			if(ballx == player2x - 1)
				if(bally == player2y + i)
					ball->changeDirection((eDir)((rand()%3)+1));
		
		//bottom wall			
		if(bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top wall			
		if(bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width-1)
			ScoreUp(player1);
		//left wall
		if (ballx == 0)
			ScoreUp(player2);
	}	
	void Run(){
		while(!quit){
			Draw();
			Input();
			Logic();
			//Sleep(800);
		}
	}
	

	void ClearScreen()
	{
	    HANDLE hOut;
	    COORD Position;
	
	    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	    Position.X = 0;
	    Position.Y = 0;
	    SetConsoleCursorPosition(hOut, Position);
	}
	
};

int main(){
	CGameManager GM(40,20);
	GM.Run();
	
	
	return 0;
}
