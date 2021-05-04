/* ------------------------------------------------------
Project - MS2
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		13 Nov 2020
-----------------------------------------------------------
Filename	CustomerOrder.h
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

struct Item {

	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {

	std::string m_name;			// customer name
	std::string m_product;		// name of product being assembled
	unsigned int m_cntItem;

	Item** m_lstItem;			// array of pointers

	static size_t m_widthField;

public:

	CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {};
	CustomerOrder(const std::string& str);

	CustomerOrder(const CustomerOrder&);	// will throw an exception
	CustomerOrder& operator=(const CustomerOrder&) = delete;

	CustomerOrder(CustomerOrder&& src) noexcept;
	CustomerOrder& operator=(CustomerOrder&& src) noexcept;

	~CustomerOrder();

	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& theStation, std::ostream& os);
	void display(std::ostream& os) const;
};
#endif // !SDDS_CUSTOMERORDER_H
