// Klasse Fuhrpark, Liste von Fahrrad, Liste von Auto. Instanzen von Fahrrad und Auto sollen nummeriert sein
// Der Fuhrpark sollte zu jeder Zeit Anzahl der Autos und Fahrraeder wissen.
// Klassen als .h file MIT include guard


#include <iostream>
#include <string>
#include "carPool.hpp"

using namespace std;

int CCar::counter=0;
int CCar::current=0;
int CBike::counter=0;
int CBike::current=0;

void CPool::add(string vehicleType, string vehicelName, string vehicelColor){
	if(vehicleType=="car"){
		tmpCar = cars;
		cars = new CCar(vehicelName,vehicelColor);
		cars->setNext(tmpCar);
	} else if(vehicleType=="bike"){
		tmpBike = bikes;
		bikes = new CBike(vehicelName,vehicelColor);
		bikes->setNext(tmpBike);
	} else{
		return;
	}
}

int main (void){
	CPool *fuhrpark;
	fuhrpark = new CPool();
	fuhrpark->add("car","Trabant","rosa");
	fuhrpark->add("car","Ferrari","schwarz");
	cout << "Gesamtzahl an Autos: " << fuhrpark->countCars() << endl;
	cout << "Gesamtzahl an Fahrraedern: " << fuhrpark->countBikes() << endl;
	delete fuhrpark;
	return 0;
}

