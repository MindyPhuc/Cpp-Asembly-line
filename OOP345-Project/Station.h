/* ------------------------------------------------------
Project - MS1
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		6 Nov 2020
-----------------------------------------------------------
Filename	Station.h
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>


class Station {

	size_t m_id = 0;
	std::string m_itemName = "";
	std::string m_desc = "";
	unsigned int m_serialNumber = 0;
	unsigned int m_quantity = 0;

	static size_t m_widthField;
	static size_t id_generator;

public:
	Station() = default;
	Station(const std::string str);	
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;

};


#endif // !SDDS_STATION_H
