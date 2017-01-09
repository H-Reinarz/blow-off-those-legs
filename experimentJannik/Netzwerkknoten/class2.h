#ifndef CLASS_H
#define CLASS_H

#include <string.h>
#include <iostream>
using namespace std;

class cPacket{
	private:
		int source;
		int dest;
		char *data;
		int length;
		int check;
	public:
		cPacket(){}
		cPacket(int s, int d, char* dat):
			source(s), dest(d),data(dat){
				length = strlen(dat);
				check = 0;
			}
		
		bool validate(int code);
		void initCheck();
		inline int getCheck(){return check;}
	
};

class cAbstractNetworkNode{
	private:
		static int count;
	protected:
		int startRange;
		int endRange;
		cAbstractNetworkNode *successor = nullptr;
		//char* id;
		int id;
	public:
		cAbstractNetworkNode(int s, int e, int i):
			startRange(s), endRange(e){
				id = i;
				if(id < endRange){
					successor = new cAbstractNetworkNode(s,e,i+1);
					successor->successor = nullptr;
					cout << "Netzwerkknoten initialisiert mit ID: " << id << endl;
				}
			}
		cAbstractNetworkNode(int s, int e):
			startRange(s), endRange(e){count++;cout << "Instance Counter: " << count << endl;}
		
		void createNetwork(){
			id = startRange;
			cout << "Netzwerkknoten initalisiert mit ID: " << id << endl;
			
			successor = new cAbstractNetworkNode(startRange, endRange);
			cAbstractNetworkNode *current = successor;
			current->id = id+1;
			cout << "Netzwerkknoten initalisiert mit ID: " << id+1 << endl;
			
			for(int i = startRange+2; i <= endRange; i++){
				cout << i << endl;
				current->successor = new cAbstractNetworkNode(startRange, endRange);
				current->successor->id = i;
				cout << "Netzwerkknoten initalisiert mit ID: " << i << endl;
				current = current->successor;
			}
			current->successor = nullptr;
		}
			
		void receivePacket(cPacket p);
		void sendPacket(cPacket p);
		int getInstances(){return count;}
		int getID(){return id;}
		
		~cAbstractNetworkNode(){
			delete successor;
		}
};

class cIdentityNode : public cAbstractNetworkNode{
	
};


#endif
