#pragma warning (disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#ifndef __ADDRESS_H
#define __ADDRESS_H

//---------------------------- Address Class ---------------------

class CAddress
{
private:
	char* cityName;													// city name
	char* streetName;												// street name
	int houseNum;													// house number
	const char* DEFAULT_CITY = "tel Aviv";							// deafault value for city

public:
	CAddress( int hNum,const char* sName);							// c'tor with default city value
	CAddress( int hNum,const char* sName,const char* cName );		// Full c'tor
	CAddress(const CAddress& a);									// copy c'tor
	~CAddress();													// d'tor

	//---------------------------- Address Class get ---------------------

	int getHouseNum();												// get house number
	char* getCityName();											// get city name
	char* getStreetName();											// get street name

	//---------------------------- Address Class set ---------------------

	void setHouseNum(int& houseNum);								// set house number
	void setCityName(char* cityName);								// set city name
	void setStreetName(char* streetName);							// set street name

	//---------------------------- Address Class functions ---------------------

	CAddress getCurrentAddress() { return *this; }								// returns address
	bool UpdateAddress(const char* cName, const char* sName, const int hNum);	// update address
	bool operator==(const CAddress& a);											// compaire between two addresses
	bool operator!=(const CAddress& a);											// check if different
	
	//---------------------------- Address Class output input ---------------------

	void Print(ostream& os);													// output function
	friend ostream& operator<<(ostream& os, const CAddress& address);			// output function
	friend istream& operator>>(istream& is, CAddress& address);					// input function



};


#endif //__ADDRESS_H