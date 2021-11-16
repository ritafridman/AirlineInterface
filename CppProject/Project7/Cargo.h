#pragma warning (disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "FlightCompException.h"
using namespace std;
#ifndef __CARGO_H
#define __CARGO_H
#include "Plane.h"

//---------------------------- Cargo Class ---------------------
class CCargo : public CPlane
{

private:
	int maxKG;										// max kg
	int maxVolume;									// max volume
	int curKG;										// current kg
	int curVolume;									// current volume


public:

	CCargo(int seats, const char* degem, int maxKG, int maxVolume);			// full c'tor
	
	//---------------------------- Cargo Class get ---------------------

	int getKg();									// get max kg
	int getVolume();								// get max volum
	int getCurKg();									// get current kg
	int getCurVolum();								// get current volum

	//---------------------------- Cargo Class set ---------------------

	void setMaxKg(int maxKG);						// set max kg
	void setMaxVolume(int maxVolume);				// set max volum
	void setCurKg(int curKG);						// set current kg
	void setCurVolum(int curVolume);				// set current volum

	//---------------------------- Cargo Class functions ---------------------

	bool Load(int KG, int Volum);					// load plane function

	//---------------------------- Cargo Class output input ---------------------
	
	// output function
	virtual void toOs(ostream& os) const override {
		if (typeid(os) == typeid(ofstream))
			os << maxVolume << "   " << maxKG << "  " << curVolume << " " << curKG << endl;

		else
			os << "" << "Cargo M_vol " << maxVolume << " M_Kg " << maxKG << " C_vol " << curVolume << " C_Kg " << curKG << endl;
	}

};

#endif//__CARGO_H
