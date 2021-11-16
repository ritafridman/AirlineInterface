#define _CRT_SECURE_NO_WARNINGS
#include <fstream>

#include "FlightCompany.h"
#include "FlightCompException.h"
#include "Flight.h"
#include "PlaneCrewFactory.h"

//c'tor with name
CFlightCompany::CFlightCompany(const char* name) : noPlanes(0) , noCrewMem(0) , noFlights(0)
{
	SetName(name);
}

// c'tor to file
CFlightCompany::CFlightCompany(const char* fileName, int x)
{
	ifstream inFile(fileName);
	if (inFile.fail())
		throw CCompFileException(fileName);
	char* compNameFromFile = new char[20];

	inFile >> compNameFromFile;
	SetName(compNameFromFile);

	//-------------- Read Crew ----------------------

	inFile >> noCrewMem;

	for (int i = 0; i < noCrewMem; i++)
	{
		comCrewMem[i] = CPlaneCrewFactory::GetCrewMemberFromFile(inFile);
	}

	//-------------- Read Plane ----------------------

	inFile >> noPlanes;
	
	for (int i = 0; i < noPlanes; i++)
	{
		comPlanes[i] = CPlaneCrewFactory::GetPlaneFromFile(inFile);
	}

	//-------------- Read Flight ----------------------

	inFile >> noFlights;

	int hasPlane;
	int planeSerial;
	int crewNum;

	for (int i = 0; i < noFlights; i++)
	{
		
		companyFlights[i] = CPlaneCrewFactory::GetFlightFromFile(inFile);
		inFile >> hasPlane;

		if (hasPlane == 1)
		{
			inFile >> planeSerial;
			companyFlights[i]->SetPlane(getBySerial(planeSerial));
		}

		//-------------- Read Crew Of Flight ----------------------
		inFile >> crewNum;

		for (int j = 0; j < crewNum; j++)
		{
			companyFlights[i]->operator+(CPlaneCrewFactory::GetCrewMemberFromFile(inFile));
		}
	}

	inFile.close();
}

// save to file
void CFlightCompany::SaveToFile(const char* fileName)
{
	ofstream outFile(fileName , ios::trunc);

	//---------------------- Company Name------------------------

	outFile << compName << endl;

	//---------------------- Crew number ------------------------

	outFile << noCrewMem << endl;


	//---------------------- Crew member ------------------------

	for (int i = 0; i < noCrewMem; i++)
	{
		comCrewMem[i]->Print(outFile);
	}
	//---------------------- Plane number ------------------------

	outFile << noPlanes << endl;

	//---------------------- Planes ------------------------

	for (int i = 0; i < noPlanes; i++)
	{
		comPlanes[i]->Print(outFile);
	}

	//---------------------- Flight number ------------------------

	outFile << noFlights << endl;

	//---------------------- Flights ------------------------
	
	for (int i = 0; i < noFlights; i++)
	{
		outFile << *companyFlights[i];

		int crewNo = companyFlights[i]->getCrewCount();

		outFile << crewNo << endl;

		for (int j = 0; j < crewNo; j++)
		{
			companyFlights[i]->getCrewArr(j).Print(outFile);
		}
	}
	outFile.close();
}

//d'tor
CFlightCompany::~CFlightCompany()
{
	delete[]compName;
}

//---------------------------- Flight Class get ---------------------

// get name
char* CFlightCompany::getCompName()
{
	return compName;
}

// get fligth by index
CFlight* CFlightCompany::getFlightByIndex(int index)
{
	if (index < 0 || index > noFlights)
		throw CCompLimitException(index);
	return this->companyFlights[index];
}

// get plane by index
CPlane& CFlightCompany::GetPlane(int numOfPlane)
{
	return *comPlanes[numOfPlane];
}

// get plane byn serial number
CPlane& CFlightCompany::getBySerial(int serial)
{
	if (serial < 0)
		throw CCompLimitException(serial);
	for (int i = 0; i < noPlanes; i++)
	{
		if (comPlanes[i]->getSerialNum() == serial)
			return *comPlanes[i];
	}
}

// get crew member by index
CCrewMember* CFlightCompany::GetCrewMember(int index)
{
	if (index<0 || index>noCrewMem)
		throw CCompLimitException(index);
	if (index + 1 <= noCrewMem)
		return comCrewMem[index];
	return nullptr;
}

// get flight by fligth number
CFlight& CFlightCompany::getFlight(int flight_num)
{
	for (int i = 0; i < noFlights; i++)
		if (companyFlights[i]->getFlightNum() == flight_num)
			return *companyFlights[i];
}

// get fligth by index
CFlight* CFlightCompany::GetFlightByNum(int num)
{
	for (int i = 0; i < noFlights; i++)
	{
		if (companyFlights[i]->getFlightNum() == num)
			return companyFlights[i];
	}
	return NULL;
}

// count cargo flights
int CFlightCompany::GetCargoCount()
{
	int count = 0;
	for (int i = 0; i < noPlanes; i++)
	{
		if (strcmp(typeid(*comPlanes[i]).name(), typeid(CCargo).name()) == 0)
			count++;
	}
	return count;
}

//---------------------------- Flight Class set ---------------------

// set crew number
void CFlightCompany::setCrewNum(int crewNum)
{
	this->noCrewMem = crewNum;
}

// set plane number
void CFlightCompany::setPlaneNum(int planeNum)
{
	this->noPlanes = planeNum;
}

// set flight number
void CFlightCompany::setFlightNum(int flightNum)
{
	this->noFlights = flightNum;
}

// set crew member
void CFlightCompany::setCrewMem(CCrewMember* c)
{
	this->comCrewMem[this->noCrewMem] = c;
}

// set plane
void CFlightCompany::setPlane(CPlane* p)
{
	this->comPlanes[this->noPlanes] = p;
}

// set flight
void CFlightCompany::setFlight(CFlight* f)
{
	this->companyFlights[this->noFlights] = f;
}

// set company name
bool CFlightCompany::SetName(const char* name)
{
	compName = new char[strlen(name) + 1];
	if (!compName)
		return false;
	strcpy(compName, name);
	return true;
}

//---------------------------- Flight Class functions ---------------------

// return plane by index
CPlane& CFlightCompany::operator[](int index)
{
	if (index > noPlanes)
		throw CCompLimitException(index);
	return *comPlanes[index];
}

// return plane by index
const CPlane& CFlightCompany::operator[](int index) const {
	if (index >= noPlanes)
		throw CCompLimitException(index);
	return *comPlanes[index];
}

// add crew member to plane
int CFlightCompany::AddCrewMember(CCrewMember& crewMem)
{
	if (noCrewMem == MAX_CREW)
		return ADD_FALIED;

	for (int i = 0; i < noCrewMem; i++)
	{
		if (*comCrewMem[i] == crewMem)
			return ADD_FALIED;
	}

	if (strcmp(typeid(crewMem).name(), typeid(CHost).name()) == 0)
		comCrewMem[noCrewMem] = new CHost((CHost&)crewMem);
	else
		comCrewMem[noCrewMem] = new CPilot((CPilot&)crewMem);
	noCrewMem++;
	return ADD_SUCCEED;
}

// add plane to company
int CFlightCompany::AddPlane(CPlane& plane)
{
	if (noPlanes == MAX_PLANES)
		return ADD_FALIED;

	for (int i = 0; i < noPlanes; i++)
	{
		if (comPlanes[i]->IsEqual(plane))
			return ADD_FALIED;
	}

	if (strcmp(typeid(plane).name(), typeid(CCargo).name()) == 0)
		comPlanes[noPlanes] = new CCargo((CCargo&)plane);
	else
		comPlanes[noPlanes] = new CPlane(plane);
	noPlanes++;
	return ADD_SUCCEED;
}

// add flight to company
int CFlightCompany::AddFlight(CFlight& flight)
{
	if (noFlights == MAX_FLIGHT)
		return ADD_FALIED;

	for (int i = 0; i < noFlights; i++)
	{
		if (*companyFlights[i] == (flight))
			return ADD_FALIED;
	}

	companyFlights[noFlights] = new CFlight(flight);
	noFlights++;
	return ADD_SUCCEED;
}

// crew get present
void CFlightCompany::CrewGetPresent()
{
	for (int i = 0; i < noCrewMem; i++)
	{
		cout << comCrewMem[i]->getEmpName() << " thanking the company for receiving the holiday gift" << endl;
		if (strcmp(typeid(*comCrewMem[i]).name(), typeid(CHost).name()) == 0)
			cout << "I was not expecting it" << endl;
	}
}

// call pilot to simulator
void CFlightCompany::PilotsToSimulator()
{
	for (int i = 0; i < noCrewMem; i++)
	{
		if (strcmp(typeid(*comCrewMem[i]).name(), typeid(CPilot).name()) == 0)
			cout << "Pilot " << comCrewMem[i]->getEmpName() << " got the message will come soon" << endl;
	}
}

// crew get uniform
void CFlightCompany::CrewGetUniform()
{
	for (int i = 0; i < noCrewMem; i++)
	{
		if (strcmp(typeid(*comCrewMem[i]).name(), typeid(CHost).name()) == 0)
			cout << comCrewMem[i]->getEmpName() << ": I think the new uniform is very nice!" << endl;
		else if (strcmp(typeid(*comCrewMem[i]).name(), typeid(CPilot).name()) == 0)
			cout << comCrewMem[i]->getEmpName() << ": this is the fifth time I get a new uniform, this is a waste of money!" << endl;

	}
}

//---------------------------- Flight Class output input ---------------------

// output
void CFlightCompany::Print(ostream& os)
{

	if (!compName || strcmp(compName, "") == 0) {
		const char* err = "Flight company must have a name!";
		throw CCompStringException(err);
	}
	os << "Flight company: " << compName << "\n";
	os << "There are " << noCrewMem << " Crew members:" << endl;

	for (int i = 0; i < noCrewMem; i++)
	{
		comCrewMem[i]->Print(os);
	}
	os << "There are " << noPlanes << " Planes:" << endl;
	for (int i = 0; i < noPlanes; i++)
	{
		comPlanes[i]->Print(os);
	}

	os << "There are " << noFlights << " Flights:" << endl;
	for (int i = 0; i < noFlights; i++)
	{
		cout << *companyFlights[i];

		int crewNo = companyFlights[i]->getCrewCount();
	
		for (int j = 0; j < crewNo; j++)
		{	
					companyFlights[i]->getCrewArr(j).Print(os);
		}
	}
}
























