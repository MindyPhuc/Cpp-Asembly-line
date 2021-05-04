/* ------------------------------------------------------
Project - MS3
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		24 Nov 2020
-----------------------------------------------------------
Filename	Workstation.cpp
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#include <iostream>
#include <vector>
#include <deque>

#include "Workstation.h"

// custom constructor
Workstation::Workstation(const std::string str) : Station(str) {	
	m_pNextStation = nullptr;
}

// runs a single cycle of the assembly line for the current station
void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		m_orders.front().fillItem(*this, os);
	}
}

// if the order at the front of the queue doesn't require service at the current station
// move it to the next station on the assembly line
bool Workstation::moveOrder() {

	// does not have order
	if (m_orders.empty()) {
		return false;
	}
	
	if (m_orders.front().isItemFilled(this->getItemName()) && m_pNextStation != nullptr) {
		*m_pNextStation += std::move(m_orders.front());
		m_orders.pop_front();
		return true;
	}

	return false; // there is no moving
}

// set the next station
void Workstation::setNextStation(Workstation& station) {
	m_pNextStation = &station;
}

// return the next station in the asembly line
const Workstation* Workstation::getNextStation() const {
	return m_pNextStation;
}

// get the order if it is completed
bool Workstation::getIfCompleted(CustomerOrder& order) {
	if (!m_orders.empty() && m_orders.back().isOrderFilled()) {
		order = std::move(m_orders.front());
		m_orders.pop_front();
		return true;
	}
	else
		return false;	
}

// writes the name of the Item this Workstation is responsible for
void Workstation::display(std::ostream& os) const {
	os << this->getItemName() << " --> ";
	if (m_pNextStation == nullptr)
		os << "END OF LINE";
	else
		os << m_pNextStation->getItemName();		
	os << std::endl;
}

// moves the parameter onto the back of the CustomerOrder queue
Workstation& Workstation::operator+=(CustomerOrder&& order) {
	m_orders.push_back(std::move(order));
	return *this;
}