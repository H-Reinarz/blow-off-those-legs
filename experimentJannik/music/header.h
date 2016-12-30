#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <iostream>

using namespace std;

const unsigned int TONE = 2;
const unsigned int SEMITONE = 1;
const unsigned int CHROMATIC[12] = {0,1,2,3,4,5,6,7,8,9,10,11}; // c,c#,d,d#,e,f,f#,g,g#,a,a#,b
const string POSITIVE[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
const string NEGATIVE[12] = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};

class CNote{
	private:
		int noteInt = 0;
		string noteString = "";
		const string POSITIVEcheck[8] = {"C","G","D","A","E","B","F#","C#"};
		const string NEGATIVEcheck[7] = {"F","Bb","Eb","Ab","Db","Gb","Cb"};
		int majMin = 0;
		
	public:
		CNote():CNote("C"){}
		CNote(string nS):noteString(nS){
			noteInt = translateToInt(nS);
			majMin = checkMajMin(nS);
		}
		CNote(int nI):noteInt(nI){
			noteString = translateToString(nI);
			majMin = checkMajMin(noteString);
		}
		
		int translateToInt(string nS);
		string translateToString(int nI);
		int getNote(){return noteInt;}
		string getString(){return noteString;}
		int checkMajMin(string s);
		int getMajMin(){return majMin;}
		void setNote(string s);
};

class CScale{
	private:
		CNote root;
		int tones[8] = {0,0,0,0,0,0,0,0};
		string genderString = "";
		int gender = 0; //0 = Major, 1 = Minor
		int semiTones[2] = {0,0};
	
	public:
		void setScale(string r, int g);
		void setSemiTones(int g);
		void setRoot(string r);
		void showScale();
};

#endif
