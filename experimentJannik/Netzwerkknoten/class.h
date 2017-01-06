#ifndef CLASS_H
#define CLASS_H

class cPacket{
	private:
		int source;
		int dest;
		char *data;
		int length;
		int check;
	public:
		cPacket(){}
		cPacket(int s, int d, char* dat, int l):
			source(s), dest(d),data(dat), length(l){
				check = 0;
			}
		
		bool validate(int code);
		void initCheck();
		inline int getCheck(){return check;}
	
};

class cAbstractNetworkNode{
	protected:
		int startRange;
		int endRange;
		cAbstractNetworkNode* successor;
		char* id;
	public:
		void receivePacket(cPacket p);
		void sendPacket(cPacket p);
};

#endif
