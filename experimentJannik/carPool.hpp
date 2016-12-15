#include<string>
#include<iostream>
using namespace std;

class CCar{
	private:
	string name;
	string color;
	CCar *next = nullptr;
	static int counter;
	static int current;
	
	public:
	CCar(string n, string c)
		:name(n), color(c){
			counter++;current++;
			cout << n << " wurde hinzugefuegt mit ID: " << current << endl;}
	
	int getCounter(){return counter;}
	int getCurrent(){return current;}
	void setNext(CCar *nextCar){next=nextCar;}
	
	~CCar(){
		counter--;
		cout << "Auto mit ID " << current << " geloescht";
		if (next != nullptr){
			delete next;	
		}	
	}
};

class CBike{
	private:
	string name;
	string color;
	CBike *next = nullptr;
	static int counter;
	static int current;
	
	public:
	CBike(string n, string c)
		:name(n), color(c){counter++;current++;}	
	
	int getCounter(){return counter;}
	int getCurrent(){return current;}
	void setNext(CBike *nextBike){next=nextBike;}
	
	~CBike(){
	counter--;
	cout << "Fahrrad mit ID " << current << " geloescht";
	}
};

class CPool{
	private:
	CCar *cars = nullptr;
	CCar *tmpCar = nullptr;
	CBike *bikes = nullptr;
	CBike *tmpBike = nullptr;
	
	public:
	
	int countCars(){return cars->getCounter();}
	int countBikes(){return bikes->getCounter();}
	
	void add(string vehicleType, string vehicelName, string vehicelColor);
	
	~CPool(){delete cars; delete bikes;}
};
