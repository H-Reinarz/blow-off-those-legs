#include <iostream>

using namespace std;

class CharStack{
	private:
		CharStackElement* first = nullptr;
	public:
		int getFirst(){return first;}
};

class CharStackElement{
	private:
		char character;
		CharStackElement* next = nullptr;
	public:
		CharStackElement(): CharStackElement('a'){}
		CharStackElement(char c)
			: character(c){}
		
		char getChar(){return character;}
		void setChar(char newChar){character = newChar;}
		int getNext(){return next;}
		void setNext(CharStackElement* element){next = element;}
		
};