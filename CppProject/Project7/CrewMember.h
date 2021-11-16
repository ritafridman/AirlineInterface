#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

#include "Address.h"
#include "Pilot.h"
#include "Host.h"
#include "FlightCompException.h"

#ifndef __CREW_MEMBER_H
#define __CREW_MEMBER_H

const int MAX_CREW = 15;						// max number of crew

//---------------------------- Crew Member Class ---------------------
class CCrewMember
{
private:
	static int crewCounter;						// crew counter
	char* empName;								// crew name
	int totalAirTime;							// crew air time
	
public:
	CCrewMember();										// c'tor 
	CCrewMember(const char* name);						// c'tor receives name
	CCrewMember(const char* name, int totalAirTime);	// c'tor receives name and air time
	CCrewMember(const CCrewMember& m);					//copy c'tor
	~CCrewMember();										//d'tor

//---------------------------- Crew Member get ---------------------
	
	int getAirTime();						// get air time
	char* getEmpName();						// get crew name

//---------------------------- Crew Member set ---------------------
	
	void setAirTime(int airTime);			// set air time
	bool setEmpName(const char* name);		// set crew name

//---------------------------- Crew Member functions ---------------------
	
	bool operator+= (int more);								// add time
	int calcNewAirTime(int flightTime , bool isaCaptain);	//calculate air time
	bool UpdateMinutes(int time);							// update minuts
	bool operator==(const CCrewMember& m);					// compare between crew membres

//---------------------------- Crew Member Class output input ---------------------
	
// output function
	virtual void Print(ostream& os) const = 0
	{
		if (typeid(os) == typeid(ofstream))
		{
			os << empName << " " << totalAirTime << " ";
		}
		else
		{
			os << empName << " minutes " << totalAirTime;
			
		}
		

	}

};

#endif// __CREW_MEMBER_H
