#include <iostream>
#include "class.h"
#include <string.h>

using namespace std;

void cZeit::set(int s, int m){
	if(s > 23){
		s = 0;
	}
	if(m > 59){
		m = 0;
	}
	
	stunde = s;
	minute = m;
}

void cDatum::set(int t, int m, int j){
	if(j < 1970 || j > 2099){
		j = 1970;
	}
	if(m < 1 || m > 12){
		m = 1;
	}
	if(t < 1 || t > 30){
		t = 1;
	}
	
	tag = t;
	monat = m;
	jahr = j;
}

void cTimestamp::print(){
	dat.print();
	cout << " ";
	zt.print();
}

cText::cText(char* t){
	len = strlen(t);
	txt = (char*)malloc(len+1);
	strcpy(txt,t);
}

cText::~cText(){
	free(txt);
}

cText::cText(const cText& s){
	len = s.len;
	txt = (char*) malloc(len+1);
	strcpy(txt, s.txt);
}

cText& cText::operator=(const cText& s){
	free(txt);
	len = s.len;
	txt = (char*)malloc(len+1);
	strcpy(txt,s.txt);
	return *this;
}

int cText::find(char* f){
	char* pos = strstr(txt, f); //gibt NULL zurück wenn f nicht in txt enthalten ist
	
	if(!pos)
		return -1;
	else
		return(pos - txt);
}

cText::cText(){
	len = strlen("leer");
	txt = (char*) malloc(len+1);
	strcpy(txt, "leer");
}

void cStr::setText(char* t){
	free(txt);
	len = strlen(t);
	txt = (char*) malloc(len + 1);
	strcpy(txt,t);
}

void cStr::print(){
	cout << "<<" << txt << ">>" << endl;
}

int main(){
	
	//cTimestamp ts(28,8,1990,13,37);
	//ts.print();
	
	cStr string2("Lolbert");
	string2.print();
	string2.setText("Dorschbert");
	string2.print();
	
	// Virtual testen:
	cText *t;
	t = new cText("Das ist ein cText.");
	t->print();
	cout << endl;
	cText *t2;
	t2 = new cStr("Das ist ein cStr.");
	t2->print();
		
	return 0;
}
