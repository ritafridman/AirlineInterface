#define _CRT_SECURE_NO_WARNINGS
#include "Flight.h"
#include <stdlib.h>


// c'tor with flight info
CFlight::CFlight(CFlightInfo& m): plane(nullptr) , crewNum(0) , hostNum(0) , hasPilot(0)
{
	this->flightInfo = &m;
}

// c'tor with flight info and plane
CFlight::CFlight(CFlightInfo& m, CPlane& plane): crewNum(0) , hostNum(0) , hasPilot(0)
{
	this->flightInfo = &m;
	this->plane = &plane;

}

// c'tor with flight info and plane pointer
CFlight::CFlight(CFlightInfo f, CPlane* plane) : crewNum(0), hostNum(0), hasPilot(0) , flightInfo(&f)
{
	this->plane = plane;
}

// copy c'tor
CFlight::CFlight(CFlight& f)
{
	flightInfo = new CFlightInfo(*f.flightInfo);	// new flight info
	if(f.plane != NULL)
	{ 
	if (strcmp(typeid(*f.plane).name(), typeid(CCargo).name()) == 0)	// check plane type
		plane = new CCargo((CCargo&)*f.plane);
	else
		plane = new CPlane(*f.plane);
	}
	for (int i = 0; i < MAX_CREW; i++)			// add crew member
		if (nullptr != f.flightCrew[i])
		{
			if (strcmp(typeid(*f.flightCrew[i]).name(), typeid(CHost).name()) == 0) flightCrew[i] = new CHost((CHost&)*f.flightCrew[i]);
			else
				flightCrew[i] = new CPilot((CPilot&)*f.flightCrew[i]);
		}
	crewNum = f.crewNum;
	hostNum = f.hostNum;
	hasPilot = f.hasPilot;
}

//---------------------------- Flight get ---------------------

// get flight num
int CFlight::getFlightNum()
{
	return flightInfo->getFlightNum();
}

// get number of crew
int CFlight::getCrewCount()
{
	return crewNum;
}

// get number of hosts in flight
int CFlight::getHostNum()
{
	return hostNum;
}

// get crew members array
CCrewMember& CFlight::getCrewArr(int index)
{
	return *flightCrew[index];
}

// get crew member
CCrewMember* CFlight::getCrew()
{
	return *flightCrew;
}

// get plane
CPlane* CFlight::getPlane()
{
	return this->plane;
}

//get flight info
CFlightInfo CFlight::GetFlightInfo()
{
	return *flightInfo;
}

//---------------------------- Flight set ---------------------

// set number of crew members in flight
void CFlight::setCrewNum(int crewNum)
{
	this->crewNum = crewNum;
}

// set plane
void CFlight::SetPlane(CPlane& plane)
{
	this->plane = &plane;
}

// set host 
void CFlight::SetHostArr(const CHost* h)
{

	flightCrew[crewNum] = (CHost*)h;
}

// set pilot
void CFlight::SetPilot(const CPilot* p)
{

	flightCrew[crewNum] = (CPilot*)p;
}

//---------------------------- Flight functions ---------------------

// add host to flight
void CFlight::operator+(const CHost& h)
{
	if (crewNum >= MAX_CREW)//flight is full
		return;

	for (int i = 0; i < crewNum; i++)
	{
		if (*flightCrew[i] == h)//crewMember already exists in flight
			return;
	}
	SetHostArr(&h);
}

// add crew member to flight
void CFlight::operator+(const CCrewMember* c)
{
	if (crewNum >= MAX_CREW)//flight is full
		return;

	for (int i = 0; i < crewNum; i++)
	{
		if (flightCrew[i] != nullptr) {
			if (*flightCrew[i] == *c)//crewMember already exists in flight
				return;

		}
	}
	if (strcmp(typeid(*c).name(), typeid(CHost).name()) == 0)
	{
		SetHostArr((CHost*)c);
		crewNum++;
		hostNum++;
	}
	else
	{
		SetPilot((CPilot*)c);
		crewNum++;

	}
}

// take off flight
bool CFlight::TakeOff()
{
	int countSuperHost = 0;
	int hasPilot = 0;
	int isCargo = 0;

	if (strcmp(typeid(*this->getPlane()).name(), typeid(CCargo).name()) == 0)
		isCargo = 1;
	if (this != NULL)
	{
		int addedAirTime = this->GetFlightInfo().getFlightTime();
		bool isACaptain = false;
		for (int i = 0; i < crewNum; i++)
		{
			if (strcmp(typeid(*flightCrew[i]).name(), typeid(CPilot).name()) == 0)
			{
				isACaptain = ((CPilot&)flightCrew[i]).getIsACaptain();
				hasPilot++;
			}

			else if (strcmp(((CHost&)flightCrew[i]).getType(), "Super") == 0)
			{
				countSuperHost++;
			}

		}

		if ((isCargo == 1 && hasPilot >= 1) || (isCargo = 0 && hasPilot == 1 && countSuperHost <= 1))
		{
			for (int i = 0; i < crewNum; i++)
			{
				if (strcmp(typeid(*flightCrew[i]).name(), typeid(CPilot).name()) == 0)
				{
					isACaptain = ((CPilot&)flightCrew[i]).getIsACaptain();
				}

				*flightCrew[i] += addedAirTime;
			}

			if (isCargo == 1)
				cout << "Need to add " << addedAirTime << " to my log book" << endl;
			return true;
		}

	}
	if (isCargo == 1 && hasPilot < 1)
		throw CCompStringException("Cargo flight must have at least one pilot");
	if (isCargo == 0 && hasPilot != 1)
		throw CCompStringException("Regular flight must have exacly one pilot");
	if (isCargo == 0 && hasPilot == 1 && countSuperHost > 1 || countSuperHost < 0)
		throw CCompStringException("Regular flight must have exacly one super host");
	return false;
}

//---------------------------- Flight output input ---------------------

// output flight
ostream& operator<<(ostream& os, const CFlight& flight)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << *flight.flightInfo;
		if (flight.plane != nullptr)
			os << "1 " << flight.plane->getSerialNum() << endl;
	}
	

	else
		os << "Flight " << *flight.flightInfo << *flight.plane << "There are " << flight.crewNum << " crew memebers in flight:" << endl;
	
	return os;
}






