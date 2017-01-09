#include <iostream>
#include "class.h"
#include <string>

using namespace std;

int cAbstractNetworkNode::count = 0;

bool cPacket::validate(){
	if(initCheck(data)==check){
		return true;
	} else{
		return false;
	}
}

int cPacket::initCheck(char* dat){
	int c = 0;
	for(int i = 0; i < length; i++) {
		c += int(*(dat+i));
	}
	return c;
}

void cAbstractNetworkNode::receivePacket(cPacket p){
	if(p.getDest() > endRange){
		cout << "Out of Range -> dropping Packet: " << p << " at ID: " << id << endl;
		return;
	} else if(p.validate() == 0){
		cout << "end: Not valid -> dropping Packet: " << p << " at ID: " << id << endl;
		return;
	} 
		if(successor != nullptr){
			sendPacket(p);
		}
		
}
	
	


void cAbstractNetworkNode::sendPacket(cPacket p){
	cout << "Fehler: Abstrakte Funktion wurde anstelle der ueberladenen Funktion aufgerufen." << endl;
}

void cIdentityNode::sendPacket(cPacket p){
	successor->receivePacket(p);
}

void cConsoleLogNode::sendPacket(cPacket p){
	cout << "ID: " << id << " processing Packet " << p;
	cout << " check code: " << p.getCheck() << " pass check: " << p.validate() << endl;
	successor->receivePacket(p);
}

void cEncryptionNode::sendPacket(cPacket p){
	
	char *crypt = p.getData();
	for(int i = 0; i < p.getLength(); i++) {
		crypt[i] = crypt[i]+(shift%26);
	}
	p.setCheck(p.initCheck(crypt));
	successor->receivePacket(p);
}

int main(){
	
	char s[] = "bob";
	//char* daten = s;
	

	cPacket p1(0,5,s);
	cout << p1.getCheck() << endl;
	cout << p1.validate();
	
	cout << endl << endl;
	//cAbstractNetworkNode network(1,5,0);
	cConsoleLogNode start(1,5);
	cEncryptionNode network1(1,5,2);
	cConsoleLogNode network2(1,5);
	cConsoleLogNode network3(1,5);

	start.setSuccessor(&network1);
	network1.setSuccessor(&network2);
	network2.setSuccessor(&network3);
	
	
	 start.sendPacket(p1);
	
	return 0;
}


