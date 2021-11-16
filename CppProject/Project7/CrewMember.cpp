#define _CRT_SECURE_NO_WARNINGS

#include "CrewMember.h"

int CCrewMember::crewCounter = 1000;			// initialize counter

// c'tor receives name and air time 
CCrewMember::CCrewMember(const char* name, int totalAirTime ) :totalAirTime(totalAirTime) 
{
	if (name) {
		empName = new char[strlen(name) + 1];		// allocate name
		if (!empName)								// alloc failed
			return;
		strcpy(empName, name);						// copy name
	}
}

// c'tor receives name  
CCrewMember::CCrewMember(const char* name) :CCrewMember(name,0)
{

}

// c'tor
CCrewMember::CCrewMember() :CCrewMember(nullptr, 0)
{
}

// copy c'tor
CCrewMember::CCrewMember(const CCrewMember& m)
{
	empName = new char[strlen(m.empName) + 1];		// allocate name
	if (!empName)				
		return;
	strcpy(empName, m.empName);						// copy name

	totalAirTime = m.totalAirTime;					// place air time
}

// d'tor
CCrewMember::~CCrewMember()
{
	delete[]empName;		// free allocation
}

//---------------------------- Crew Member get ---------------------

// get air time
int CCrewMember::getAirTime()
{
	return totalAirTime;			// return air time
}

// get name
char* CCrewMember::getEmpName()
{
	return empName;					// return name
}


// set air time
void CCrewMember::setAirTime(int airTime)
{
	this->totalAirTime = airTime;	// place air time
}

//---------------------------- Crew Member set ---------------------

// set name
bool CCrewMember::setEmpName(const char* name)
{
	empName = new char[strlen(name) + 1];	// allocate name
	if (!empName)							//alloc failed
		return false;
	delete[] this->empName;					// free allocation
	strcpy(empName, name);					// copy name
	return true;
}

//---------------------------- Crew Member functions ---------------------

// update minuts
bool CCrewMember::UpdateMinutes(int time)
{
	if (time < 0)							// check negative value
		throw CCompLimitException(time);	//negative time

	totalAirTime += time;					// add time
	return true;
}

// compaire crew members
bool CCrewMember::operator==(const CCrewMember& m)
{
	if(strcmp(typeid(*this).name(),typeid(m).name())!=0)			// compaire faild
		return false;

	if (strcmp(typeid(*this).name(), typeid(CPilot).name())==0)		// compaire pilote
	{
		if (strcmp(this->empName, m.empName) == 0)
			return ((CPilot&)*this == (CPilot&)m);
	}
	else if(strcmp(typeid(*this).name(),typeid(CHost).name())==0)	// compaire host
	{
		if (strcmp(this->empName, m.empName )== 0)
			return true;
	}
	return false;
}

// add air time
bool CCrewMember::operator+=(int more)
{	
	if (more < 0)													// check negative value
		throw CCompLimitException(more);
	if (strcmp(typeid(*this).name(), typeid(CPilot).name()) == 0)	// check if pilot
	{
		bool isACaptain = ((CPilot&)*this).getIsACaptain();			// update if captain
		totalAirTime += calcNewAirTime(more, isACaptain);			//update air time
	}
	else totalAirTime += more;										// update air time for host and pilot
	return true; 
}

// calculate air time
int CCrewMember::calcNewAirTime(int flightTime , bool isaCaptain)
{
	int tmpcalc = 0;
	if (isaCaptain) {
		tmpcalc = flightTime * 0.1;
	}
	return (flightTime + tmpcalc);
}




