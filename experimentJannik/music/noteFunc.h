#ifndef NOTEFUNC_H
#define NOTEFUNC

#include <string>
#include <iostream>
#include "header.h"

using namespace std;

int CNote::translateToInt(string nS){
	for(int i = 0; i < 12; i++){
		if(POSITIVE[i] == nS || NEGATIVE[i] == nS){
			return(i);
		}
	}
	return(999);
}

string CNote::translateToString(int nI){
	return(POSITIVE[nI]);
}

void CNote::setNote(string s){
		noteInt = translateToInt(s);
		majMin = checkMajMin(s);
}

int CNote::checkMajMin(string s){
	for(int i = 0; i < 7; i++){
		if(NEGATIVEcheck[i] == s){
			return(-1);
		}
	}
	for(int i = 0; i < 8; i++){
		if(POSITIVEcheck[i] == s){
			return(1);
		}
	}
	
	return (0);
}

void CScale::setScale(string r, int g){
	setSemiTones(g);
	setRoot(r);
	int cur = root.getNote();
	
	for(unsigned int i = 0; i < (sizeof(tones)/sizeof(*tones)); i++){
		tones[i] = cur;
		
		if(i == semiTones[0]-1 || i == semiTones[1]-1){
			if(cur+SEMITONE > 11){
				cur += SEMITONE;
				cur -= 12;
				cur = CHROMATIC[cur];
			}else{
				cur = CHROMATIC[cur+SEMITONE];		
			}
		} else{
			if(cur+TONE > 11){
				cur += TONE;
				cur -= 12;
				cur = CHROMATIC[cur];
			}else{
				cur = CHROMATIC[cur+TONE];		
			}
		}
	}
}

void CScale::setSemiTones(int g){
	switch(g){
		case(0): // Major
			semiTones[0] = 3;
			semiTones[1] = 7;
			break;
		case(1): // Minor
			semiTones[0] = 2;
			semiTones[1] = 5;
			break;
	}
}

void CScale::setRoot(string s){
	root.setNote(s);
}

void CScale::showScale(){
	for(unsigned int i = 0; i < (sizeof(tones)/sizeof(*tones)); i++){
		if(root.getMajMin() < 0){
			cout << NEGATIVE[tones[i]] << " ";	
		} else if(root.getMajMin() > 0){
				cout << POSITIVE[tones[i]] << " ";	
			}
	}
}

#endif
