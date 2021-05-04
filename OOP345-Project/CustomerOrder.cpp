/* ------------------------------------------------------
Project - MS2
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		13 Nov 2020
-----------------------------------------------------------
Filename	CustomerOrder.cpp
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#include <string>
#include <iomanip>
#include <algorithm>

#include "CustomerOrder.h"
#include "Utilities.h"



// define class variable
size_t CustomerOrder::m_widthField = 0;

// custom constructor
// String Format: Customer Name | Product Name | list of items
CustomerOrder::CustomerOrder(const std::string& str) {

	Utilities util;

	size_t next_pos = 0;
	bool more = false;


	if (str.empty()) {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}
	else {

		// get customer's name
		m_name = util.extractToken(str, next_pos, more);

		// get product's name
		if (more) {
			m_product = util.extractToken(str, next_pos, more);
		}

		// get list of items
		std::string strItems = str.substr(next_pos, str.length() - next_pos);

		m_cntItem = std::count(strItems.begin(), strItems.end(), util.getDelimiter()) + 1; // Count items

		m_lstItem = new Item * [m_cntItem]; // allocate memory to the array of pointers

		// populate the array of pointers (list of items)
		for (auto i = 0u; i < m_cntItem && more; i++) {
			m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
		}
		// update widthField if neccessary
		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();
	}
}

// Copy constructor
CustomerOrder::CustomerOrder(const CustomerOrder&) {
	throw "ERROR: Cannot make copies.";
}

// Move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	m_lstItem = nullptr;
	m_cntItem = 0;
	*this = std::move(src);
}

// Move assignment
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {

	if (this != &src) {

		// deallocate current resources
		if (m_lstItem != nullptr) {
			for (auto i = 0u; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}

		// swap variable
		this->m_name = src.m_name;
		this->m_product = src.m_product;
		this->m_cntItem = src.m_cntItem;

		src.m_name = "";
		src.m_product = "";
		src.m_cntItem = 0;

		// swap addresses of resources
		this->m_lstItem = src.m_lstItem;
		src.m_lstItem = nullptr;
	}
	return *this;
}

// destructor
CustomerOrder::~CustomerOrder() {
	for (auto i = 0u; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
}

// check if all the items in the order have been filled
bool CustomerOrder::isOrderFilled() const {
	bool filled = true;
	for (auto i = 0u; i < m_cntItem; i++) {
		if (!m_lstItem[i]->m_isFilled) {
			filled = false;
		}
	}
	return filled;
}

// If the item doesn't exist in the order, return true
bool CustomerOrder::isItemFilled(const std::string& itemName) const {

	for (auto i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == itemName) {
			return m_lstItem[i]->m_isFilled;
		}
	}

	return true; // the item was not found
}

// fill the item in the current order
void CustomerOrder::fillItem(Station& theStation, std::ostream& os) {

	for (auto i = 0u; i < m_cntItem; i++) {
		if (theStation.getItemName() == m_lstItem[i]->m_itemName) {

			// indentation
			os << std::setw(4) << " ";

			if (theStation.getQuantity() > 0) {
				m_lstItem[i]->m_serialNumber = theStation.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				theStation.updateQuantity();

				//Filled NAME, PRODUCT [ITEM_NAME]
				os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else {
				//Unable to fill NAME, PRODUCT [ITEM_NAME]
				os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
}

// display customer orders
void CustomerOrder::display(std::ostream& os) const {

	// CUSTOMER_NAME - PRODUCT
	os << m_name << " - " << m_product << std::endl;

	// [SERIAL] ITEM_NAME - STATUS
	for (auto i = 0u; i < m_cntItem; i++) {
		os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::left << std::setfill(' ');
		os << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
		m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "MISSING";
		os << std::endl;
	}
}