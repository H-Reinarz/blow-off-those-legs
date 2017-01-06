#include <iostream>
#include "class.h"
#include <string>

using namespace std;

bool cPacket::validate(int code){
	if(code==check){
		return true;
	} else{
		return false;
	}
}

void cPacket::initCheck(){
	check = 0;
	for(int i = 0; i < length; i++) {
		check += int(*(data+i));
	}
}

void cAbstractNetworkNode::receivePacket(){

}

void cAbstractNetworkNode::sendPacket(){
}

int main(){
	
	char s[] = "bob";
	char* daten = s;

	cPacket p1(0,0,s,3);
	p1.initCheck();
	cout << p1.getCheck() << endl;
	cout << p1.validate(307);
	
	
	return 0;
}
