#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool pred(double nr){
	if(nr > 0){
		return true;
	} else{
		return false;
	}
}

void select(string inFile, string outFile){
	ifstream MeineDatei(inFile, ios::in);
	ofstream Ziel(outFile, ios::out);
	
	if(!MeineDatei){
		cout << "File reading Error!";
	} else{
		cout << "File reading successful" << endl;	
	}
	
	string s;
	double nr;
	int line = 0;
		
	while(!MeineDatei.eof()){
		MeineDatei >> nr;
		if(line == 0){
			line++;
			continue;
		}
		if(pred(nr)){
			Ziel << nr << " ";	
		} else{
			break;
		}
		
	}
	
	if(!MeineDatei.eof() || Ziel.bad())
		cout << "File writing Error!\n";
	else cout << "File writing successful\n";
	
	MeineDatei.close();
	Ziel.close();
}

int main(){
	
	select("example.bob","ausgabe.bob");
	
	return 0;
}
