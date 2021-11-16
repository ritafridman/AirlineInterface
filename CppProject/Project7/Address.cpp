#define _CRT_SECURE_NO_WARNINGS

#include "Address.h"
#include <fstream>


// c'tor with default city value
CAddress::CAddress(int hNum,const char* sName):CAddress(hNum,sName,"Tel Aviv")
{
}

// Full c'tor
CAddress::CAddress(int hNum,const char* sName ,const char* cName) 
{
	cityName = new char[strlen(cName) + 1];						// allocate city
	if (!cityName)
		return;
	streetName = new char[strlen(sName) + 1];					// allocate street
	if (!streetName)
		return;
	strcpy(cityName,cName);										// copy city
	strcpy(streetName, sName);									// copy street
	houseNum = hNum;											// place house number
}

// copy c'tor
CAddress::CAddress(const CAddress& a) //copy c'tor
{
	delete[] this->cityName;									// free allocation
	delete[] this->streetName;									// free allocation
	cityName = strdup(a.cityName);								// copy city name
	streetName = strdup(a.streetName);							// copy street name
	houseNum = a.houseNum;										// place house number
}

// d'tor
CAddress::~CAddress()
{
	delete[]cityName;											// free city name
	delete[]streetName;											// free street name
}

//---------------------------- Address Class get ---------------------

// get house number
int CAddress:: getHouseNum()
{
	return houseNum;											// return house number
}

// get city name
char* CAddress::getCityName()
{
	return cityName;											// return city name
}

// get street name
char* CAddress::getStreetName()
{
	return streetName;											// return street name
}

//---------------------------- Address Class set ---------------------

// set house number
void CAddress::setHouseNum(int& houseNum)
{
	this->houseNum = houseNum;									// place house number
}

// set city name
void CAddress::setCityName(char* cityName)
{
	delete[] this->cityName;									// free allocation
	this->cityName = new char[100];								// allocate new city
	strcpy(this->cityName,cityName);							// copy received city
}

// set street name
void CAddress::setStreetName(char* streetName)
{
	delete[] this->streetName;									// free allocation
	this->streetName = new char[100];							// allocate new street						
	strcpy(this->streetName,streetName);						// copy received street
}

//---------------------------- Address Class functions ---------------------

// update address
bool CAddress::UpdateAddress(const char* cName, const char* sName, const int hNum)
{
	delete[] this->cityName;									// free allocation
	delete[] this->streetName;									// free allocation
	cityName = new char[strlen(cName) + 1];						// allocate new city
	streetName = new char[strlen(sName) + 1];					// allocate new street

	strcpy(cityName, cName);									// copy received city
	strcpy(streetName, sName);									// copy received street
	houseNum = hNum;											// place house number
	return true;
}

// compaire between two addresses
bool CAddress::operator==(const CAddress& a)
{
	if (this->houseNum == a.houseNum)							// compaire house number
		if (strcmp(this->cityName, a.cityName) == 0)			// compaire city name 
			if (strcmp(this->streetName, a.streetName) == 0)	// compaire street name 
				return true;
	return false;
}

// check if different
bool CAddress::operator!=(const CAddress& a)
{
	return !(*this == a);										
}

//---------------------------- Address Class output input ---------------------

// output function
void CAddress::Print(ostream& os)
{
	os << streetName << " " << houseNum << ", " << cityName << endl;
}

// output function
ostream& operator<<(ostream& os, const CAddress& caddress)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << caddress.houseNum << "  " << caddress.streetName << " " << caddress.cityName ;
	}
	else
	{
		os << "Home " << caddress.streetName << " " << caddress.houseNum << " " << caddress.cityName;

	}
	return os;
}

// input function
istream& operator>>(istream& is, CAddress& caddress)
{
	char* cityName = new char[100];								// allocate new city		
	char* streetName = new char[100];							// allocate new street name	
	int houseN;													// place house number	

	cout << "Please enter house number street name and city name:\n";

	is >> houseN;												// get house number
	is >> streetName;											// get street name
	is >> cityName;												// get city name
	
	caddress.setHouseNum(houseN);								// set house number
	caddress.setCityName(cityName);								// set city name
	caddress.setStreetName(streetName);							// set street name

	return is;
}

