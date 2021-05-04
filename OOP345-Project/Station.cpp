/* ------------------------------------------------------
Project - MS1
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		6 Nov 2020
-----------------------------------------------------------
Filename	Station.cpp
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#include <iostream>
#include <string>
#include <iomanip>

#include "Station.h"
#include "Utilities.h"


// define static data members
size_t Station::id_generator = 0;
size_t Station::m_widthField = 0;

// custom constructor
Station::Station(const std::string str) {
	
	Utilities util;	

	size_t next_pos = 0;
	bool more = false;

	// generate id
	m_id = ++Station::id_generator;

	if (str.empty()) {
		m_itemName = "";
		m_serialNumber = 0;
		m_quantity = 0;
	}
	else {
		//get the item's name
		m_itemName = util.extractToken(str, next_pos, more);

		// get the serial number
		if (more) {
			m_serialNumber = stoi(util.extractToken(str, next_pos, more));
		}

		// get quantity
		if (more) {
			m_quantity = stoi(util.extractToken(str, next_pos, more));
		}

		// update widthField if neccessary
		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();

		// get the description
		if (more) {
			m_desc = util.extractToken(str, next_pos, more);
		}
	}	
	
}

// item name query
const std::string& Station::getItemName() const {
	return this->m_itemName;
}

// Next Serial Number query
unsigned int Station::getNextSerialNumber() {
	return this->m_serialNumber++;		// return the current serial number and then increment it
}

// quantity query
unsigned int Station::getQuantity() const {
	return this->m_quantity;
}

// update quantity
void Station::updateQuantity() {
	if (this->getQuantity() > 0) {
		m_quantity--;
	}
}

// display
void Station::display(std::ostream& os, bool full) const {
	os << std::right << "[" << std::setw(3) << std::setfill('0') << this->m_id << "] Item: ";
	os << std::left << std::setw(this->m_widthField) << std::setfill(' ') << this->getItemName();
	os << " [" << std::right << std::setw(6) << std::setfill('0') << this->m_serialNumber << "]";
	if (full) {
		os << " Quantity: " << std::left << std::setw(this->m_widthField) << std::setfill(' ') << this->getQuantity();
		os << " Description: " << this->m_desc;
	}
	os << std::endl;
}

