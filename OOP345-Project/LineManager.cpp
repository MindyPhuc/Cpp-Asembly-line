/* ------------------------------------------------------
Project - MS3
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		24 Nov 2020
-----------------------------------------------------------
Filename	LineManager.cpp
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

#include "LineManager.h"
#include "Utilities.h"

// custom constructor
LineManager::LineManager(const std::string fileName, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders) {
	
	// open the file for reading	
	std::ifstream file(fileName);
	if (!file)
		throw std::string("Unable to open [") + std::string(fileName) + std::string("] file.");

	std::string record = "";
	Utilities util;
	size_t next_pos;
	bool more = true;
	
	std::string currentStationToken = "";
	std::string nextStationToken = "";
	
	//read the records from file
	while (!file.eof())
	{		
		next_pos = 0;
		std::getline(file, record);

		currentStationToken = util.extractToken(record, next_pos, more);

		if (more)
			nextStationToken = util.extractToken(record, next_pos, more);
		else 
			nextStationToken = "";

		//setup all the m_pNextStation references in the Workstation objects
		for (auto i = 0u; i < stations.size(); i++) {
			if (stations[i]->getItemName() == currentStationToken) {
				for (auto j = 0u; j < stations.size(); j++) {
					if (stations[j]->getItemName() == nextStationToken) {
						stations[i]->setNextStation(*stations[j]);
						break;
					}
				}

				// identify the first station
				if (m_firstStation == nullptr) {
					m_firstStation = stations[i];
				}
			}
		}		
	}
	file.close();

	//Move all the CustomerOrder objects onto the back of the ToBeFilled queue
	std::for_each(orders.begin(), orders.end(), [&](CustomerOrder& order) {
		ToBeFilled.push_back(std::move(order));
	});

	// store the number of orders
	m_cntCustomerOrder = ToBeFilled.size();

	//Copy all the Workstation objects into the AssemblyLine container
	AssemblyLine = stations;
}

// performs one cycle of operations on the assembly line
bool LineManager::run(std::ostream& os) {
	
	// count how many times the function has been called by the client
	static size_t count = 0;	
	os << "Line Manager Iteration: " << ++count << std::endl;

	// If there are any CustomerOrder objects in the ToBeFilled queue
	// move the one at the front of the queue onto the starting point of the AssemblyLine	
	if (!ToBeFilled.empty()) {
		*m_firstStation += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	// Loop through all stations on the assembly line and run one cycle of the station's process
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}	

	// Loop through all stations on the assembly line and move the CustomerOrder objects down the line.
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->moveOrder();

		// move completed orders into the Completed queue
		CustomerOrder order;
		if (AssemblyLine[i]->getIfCompleted(order))
			Completed.push_back(std::move(order));
	}	

	// return true if all customer orders have been filled, otherwise return false
	if (Completed.size() == m_cntCustomerOrder)
		return true;
	else
		return false;

}

// displays all the orders that were completed
void LineManager::displayCompletedOrders(std::ostream& os) const {
	std::for_each(Completed.begin(), Completed.end(), [&] (const CustomerOrder& order) {
		order.display(os);
	});
}

// display all stations on the assembly line in the order they were received from the client
void LineManager::displayStations() const {
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->display(std::cout);
	}	
}

// display all stations on the assembly line in the order they are linked
void LineManager::displayStationsSorted() const {

	const  Workstation* station = m_firstStation;

	// display from the first station until the last station (which has the nextStation is nullptr)
	while (station != nullptr) {
		station->display(std::cout);
		station = station->getNextStation();
	}
}