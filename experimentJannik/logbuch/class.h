#ifndef CLASS_H
#define CLASS_H

#include <iostream>
using namespace std; 


class cZeit{
	private:
		int stunde;
		int minute;
	public:
		cZeit(int s, int m) {set(s,m);}
		cZeit() {set(0,0);}
		
		int getStunde(){return stunde;}
		int getminute(){return minute;}
		void set(int s, int m);
		void print(){cout << stunde << ":" << minute;}
};

class cDatum{
	private:
		int jahr;
		int monat;
		int tag;
	public:
		cDatum(int t, int m, int j){set(t,m,j);}
		cDatum(){set(1,1,1970);}
		
		int getTag(){return tag;}
		int getMonat(){return monat;}
		int getJahr(){return jahr;}
		void set(int t, int m, int j);
		void print(){cout << tag << "." << monat << "." << jahr;}
};

class cTimestamp{
	private:
		cDatum dat;
		cZeit zt;
	public:
		cTimestamp(){}
		cTimestamp(int t, int m, int j): dat(t,m,j){}
		cTimestamp(int t, int m, int j, int s, int min):
			dat(t,m,j), zt(s,min){}
		
		cDatum getDatum(){return dat;}
		cZeit getZeit(){return zt;}
		void print();
};

class cText{
	protected:
		int len;
		char* txt;
	public:
		cText();
		cText(char* t);
		cText(const cText& s);
		~cText();
		cText& operator=(const cText&s);
		virtual void print(){cout << txt;}
		int find(char* f);
};

class cStr: public cText{
	public:
		cStr(char* t) : cText(t){}
		void setText(char* t);
		void print();
};

#endif
