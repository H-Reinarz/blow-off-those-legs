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
			source(s), dest(d), data(dat){
				length = strlen(dat);
				check = initCheck(dat);
			}
		
		bool validate();
		int initCheck(char* dat);
		inline int getCheck(){return check;}
		int getSource(){return source;}
		int getDest(){return dest;}
		char* getData(){return data;}
		int getLength(){return length;}
		void setCheck(int c){check = c;}
		friend ostream & operator<<(ostream &o, cPacket p){
			o << "from: " << p.getSource() << " dest: " << p.getDest() << " data: '" << p.getData() << "'";
			return o;
		}
		
		
	
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
		
		cAbstractNetworkNode(int s, int e):
			startRange(s), endRange(e){count++;cout << "Instance Counter: " << count << endl; id=count; cout << "Objekt mit ID: " << id << " wurde erstellt" << endl;}
		
			
		void receivePacket(cPacket p);
		virtual void sendPacket(cPacket p);
		int getInstances(){return count;}
		int getID(){return id;}
		void setSuccessor(cAbstractNetworkNode *suc){successor = suc;}
		
		~cAbstractNetworkNode(){}
};

class cIdentityNode : public cAbstractNetworkNode{
	public:
		cIdentityNode(int s, int e):cAbstractNetworkNode(s,e){}
		void sendPacket(cPacket p); 
};

class cConsoleLogNode : public cIdentityNode{
	public:
		cConsoleLogNode(int s, int e):cIdentityNode(s,e){}
		void sendPacket(cPacket p); 
};

class cEncryptionNode : public cAbstractNetworkNode{
	private:
		int shift;
	public:
		cEncryptionNode(int s, int e, int shiftNr):cAbstractNetworkNode(s,e), shift(shiftNr){}
		void sendPacket(cPacket p);
};


#endif
