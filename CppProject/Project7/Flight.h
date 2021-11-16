#pragma warning (disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "FlightInfo.h"
using namespace std;
#ifndef __FLIGHT_H
#define __FLIGHT_H
#include "Plane.h"
#include "CrewMember.h"
#include "Pilot.h"
#include "Host.h"
#include "Cargo.h"

//---------------------------- Flight Class ---------------------
class CFlight
{
private:
	CFlightInfo* flightInfo;				// flight information 
	CPlane* plane;							// plane
	CCrewMember* flightCrew[MAX_CREW];		// crew in flight
	int crewNum;							// number of crew
	int hostNum;							// number of host
	int hasPilot;							// check if has pilot

public:
	CFlight(CFlightInfo& f);				// c'tor with flight info
	CFlight(CFlightInfo& f, CPlane& plane);	// c'tor with flight info and plane
	CFlight(CFlightInfo f, CPlane* plane);	// c'tor with flight info and plane pointer
	CFlight(CFlight& f);					// copy c'tor

//---------------------------- Flight get ---------------------
	
	int getFlightNum();						// get number
	int getCrewCount();						// get number of crew
	int getHostNum();						// get host number

//---------------------------- Flight set ---------------------
	
	void setCrewNum(int crewNum);			// set crew number

//---------------------------- Flight functions ---------------------
	
	CCrewMember& getCrewArr(int index);		// set crew array
	CCrewMember* getCrew();					// get crew member
	void SetPlane(CPlane& plane);			// set plane
	void SetHostArr(const CHost* h);		// set host
	void SetPilot(const CPilot* p);			// set pilot
	// compaire flights
	bool operator==(const CFlight& flight) const { return this->flightInfo->compareFlights(flight.flightInfo->getFlightNum()); }
	void operator+(const CHost& h);			// add host to flight
	CFlightInfo GetFlightInfo();			// get flight info
	void operator+(const CCrewMember* c);	// add crew member to flight
	bool TakeOff();							// take off flight
	CPlane* getPlane();						// get plane

//---------------------------- Flight output input ---------------------
	//output flight
	friend ostream& operator<<(ostream& os, const CFlight& flight);

};


#endif //__FLIGHT_H
