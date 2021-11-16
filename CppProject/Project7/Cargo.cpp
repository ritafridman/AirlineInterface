#define _CRT_SECURE_NO_WARNINGS

#include "Cargo.h"

// full c'tor
CCargo::CCargo(int seats, const char* degem, int maxKG, int maxVolume) : CPlane(seats,degem)
{
	setMaxVolume(maxVolume);
	setMaxKg(maxKG);
	setCurKg(0);
	setCurVolum(0);
}

//---------------------------- Cargo Class get ---------------------

// get max kg
int CCargo::getKg()
{
	return this->maxKG;								// return max kg
}

// get max volum
int CCargo::getVolume()
{
	return this->maxVolume;							// return max volum
}

// get current kg
int CCargo::getCurKg()
{
	return this->curKG;								// return current kg
}

// get current volum
int CCargo::getCurVolum()
{
	return this->curVolume;							// return current volum
}

//---------------------------- Cargo Class set ---------------------

// set max kg
void CCargo::setMaxKg(int maxKG)
{
	if (maxKG < 0)				// check negative value
	{
		CPlane::counter--;
		throw CCompStringException("Maximum weight can't be negative");		

	}
	this->maxKG = maxKG;		// place kg
}

// set current kg
void CCargo::setCurKg(int curKG)
{
	if (curKG < 0)				// check negative value					
	{
		CPlane::counter--;
		throw CCompStringException("Cargo weight can't be negative");
	}
	this->curKG = curKG;		// place kg
}

// set max volum
void CCargo::setMaxVolume(int maxVolume)
{
	if (maxVolume < 0)			// check negative value	
	{
		CPlane::counter--;
		throw CCompStringException("Maximum volume can't be negative");
	}
	this->maxVolume = maxVolume;		// place volume
}

// set current volum
void CCargo::setCurVolum(int curVolume)
{
	if (curVolume < 0)			// check negative value	
	{
		CPlane::counter--;
		throw CCompStringException("Cargo volume can't be negative");
	}
	this->curVolume = curVolume;	// place volume
}

//---------------------------- Cargo Class functions ---------------------

// load plane function
bool CCargo::Load(int KG, int Volume)
{
	if (maxKG >= curKG+KG || maxVolume >= curVolume+Volume)		// check if maximum
	{
		CCargo::setCurKg(curKG+KG);								// set kg
		CCargo::setCurVolum(curVolume+Volume);					// set volum
		return true;
	}
	throw CCompStringException("Invalid cargo weight/volume entered");
	
	return false;
}


