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

void cDataLoseNode::sendPacket(cPacket p){
	char* dat = p.getData();
	for(int i = 0; i < p.getLength(); i++) {
		if(i%2 == 0)
			dat[i] = 'b';
		else
			dat[i] = 'o';
	}
	successor->receivePacket(p);
}

int main(){
	
	char s[] = "Hallo I bims";
	cPacket p1(0,5,s);
	cPacket p2(0,150,s);
	
	//cAbstractNetworkNode network(1,5,0);
	cout << "Initialisiere Netzwerk..." << endl;
	cConsoleLogNode start(0,200,(char*)"start");
	cEncryptionNode enc(0,200,(char*)"enc",5);
	cConsoleLogNode afterEnc(0,200,(char*)"afterEnc");
	cEncryptionNode dec(0,200,(char*)"dec",-5);
	cConsoleLogNode afterDec(0,200,(char*)"afterDec");
	cDataLoseNode loose(0,50,(char*)"loose");
	cConsoleLogNode end(0,50,(char*)"end");
	cout << "Schicke Packet..." << endl << endl;
	
	
	start.setSuccessor(&enc);
	enc.setSuccessor(&afterEnc);
	afterEnc.setSuccessor(&dec);
	dec.setSuccessor(&afterDec);
	afterDec.setSuccessor(&loose);
	loose.setSuccessor(&end);
	
	 start.sendPacket(p2);
	
	return 0;
}


