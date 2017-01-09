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
		char* id;
		//int id;
	public:
		
		cAbstractNetworkNode(int s, int e, char* idStr):
			startRange(s), endRange(e), id(idStr){count++;cout << "Instance Counter: " << count << " Objekt mit ID: " << id << " wurde erstellt" << endl;}
		
			
		void receivePacket(cPacket p);
		virtual void sendPacket(cPacket p);
		int getInstances(){return count;}
		char* getID(){return id;}
		void setSuccessor(cAbstractNetworkNode *suc){successor = suc;}
		
		~cAbstractNetworkNode(){}
};

class cIdentityNode : public cAbstractNetworkNode{
	public:
		cIdentityNode(int s, int e, char* idStr):cAbstractNetworkNode(s,e,idStr){}
		void sendPacket(cPacket p); 
};

class cConsoleLogNode : public cIdentityNode{
	public:
		cConsoleLogNode(int s, int e, char* idStr):cIdentityNode(s,e,idStr){}
		void sendPacket(cPacket p); 
};

class cEncryptionNode : public cAbstractNetworkNode{
	private:
		int shift;
	public:
		cEncryptionNode(int s, int e, char* idStr, int shiftNr):cAbstractNetworkNode(s,e,idStr), shift(shiftNr){}
		void sendPacket(cPacket p);
};

class cDataLoseNode : public cAbstractNetworkNode{
	public:
		cDataLoseNode(int s, int e, char* idStr):cAbstractNetworkNode(s,e,idStr){}
		void sendPacket(cPacket p);
};


#endif
