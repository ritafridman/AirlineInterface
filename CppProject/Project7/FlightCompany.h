#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "CrewMember.h"
#include "Plane.h"
#include "Flight.h"
#include "Cargo.h"

#ifndef __FLIGHT_COMPANY_H
#define __FLIGHT_COMPANY_H

const int MAX_PLANES = 15;
const int MAX_FLIGHT = 15;
const int ADD_SUCCEED = 1;
const int ADD_FALIED = 0;

//---------------------------- Flight Company Class ---------------------
class CFlightCompany
{

private:
	char* compName;								// company name
	CPlane* comPlanes[MAX_PLANES];				// company planes
	int noPlanes;								// number of planes
	CCrewMember* comCrewMem[MAX_CREW];			// company crew members
	int noCrewMem;								// number of crew members
	CFlight* companyFlights[MAX_FLIGHT];		// company flights
	int noFlights;								// number of flights


public:
	CFlightCompany(const char* name);				//c'tor with name
	CFlightCompany(const char* fileName , int x);	// c'tor to file
	void SaveToFile(const char* fileName);			// save to file
	~CFlightCompany();								//d'tor

//---------------------------- Flight Class get ---------------------
	
	char* getCompName();							// get name
	CFlight* getFlightByIndex(int index);			// get fligth by index
	CPlane& GetPlane(int numOfPlane);				// get plane by index
	CPlane& getBySerial(int serial);				// get plane byn serial number
	CCrewMember* GetCrewMember(int index);			// get crew member by index
	CFlight& getFlight(const int flightNum);		// get flight by fligth number
	CFlight* GetFlightByNum(int num);				// get fligth by index
	int GetCargoCount();							// count cargo flights
	int GetCrewCount() { return noCrewMem; }		// get number of crew members

//---------------------------- Flight Class set ---------------------

	void setCrewNum(int crewNum);					// set crew number
	void setPlaneNum(int planeNum);					// set plane number
	void setFlightNum(int flightNum);				// set flight number
	void setCrewMem(CCrewMember* c);				// set crew member
	void setPlane(CPlane* p);						// set plane				
	void setFlight(CFlight* f);						// set flight
	bool SetName(const char* name);					// set company name

//---------------------------- Flight Class functions ---------------------

	CPlane& operator[](int index);					// return plane by index
	const CPlane& operator[](int index) const;		// return plane by index
	int AddCrewMember(CCrewMember& crewMem);		// add crew member to plane
	int AddPlane(CPlane& plane);					// add plane to company
	int AddFlight(CFlight& flight);					// add flight to company
	void CrewGetPresent();							// crew get present
	void PilotsToSimulator();						// call pilot to simulator
	void CrewGetUniform();							// crew get uniform

//---------------------------- Flight Class output input ---------------------

	void Print(ostream& os);						// output
};

#endif //__FLIGHT_COMPANY_H