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

int main(){
	
	cTimestamp ts(28,8,1990,13,37);
	ts.print();
	
	cText txt1("Lol");
	txt1.print();
	
		
	return 0;
}
