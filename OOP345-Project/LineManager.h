/* ------------------------------------------------------
Project - MS3
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		22 Nov 2020
-----------------------------------------------------------
Filename	LineManager.h
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <vector>
#include <deque>
#include "Workstation.h"

class LineManager {
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;

	Workstation* m_firstStation = nullptr;

public:
	LineManager(const std::string fileName, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};
#endif // !SDDS_LINEMANAGER_H
