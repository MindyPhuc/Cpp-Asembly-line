/* ------------------------------------------------------
Project - MS3
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		22 Nov 2020
-----------------------------------------------------------
Filename	Workstation.cpp
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <iostream>

#include "CustomerOrder.h"
#include "Station.h"

class Workstation : public Station {
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;				// points to the next station on the assembly line

public:

	Workstation(const std::string str);

	//disable copy and move
	Workstation(const Workstation&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&&) = delete;

	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Workstation& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os) const;
	Workstation& operator+=(CustomerOrder&&);
};
#endif // !SDDS_WORKSTATION_H
