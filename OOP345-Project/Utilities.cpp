/* ------------------------------------------------------
Project - MS1
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		6 Nov 2020
-----------------------------------------------------------
Filename	Utilities.cpp
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#include <iostream>
#include <string>

#include "Utilities.h"
	
//define class variable
char Utilities::m_delimiter = '\0';

// set field width
void Utilities::setFieldWidth(size_t newWidth) {
	this->m_widthField = newWidth;
}

// field width query
size_t Utilities::getFieldWidth() const {
	return this->m_widthField;
}

// trim function to remove all the leading and trailing spaces
void Utilities::trim(std::string& str) const {
	size_t i = 0u;
		
	for (i = 0u; i < str.length() && str[i] == ' '; i++);
	str = str.substr(i);
		
	for (i = str.length(); i > 0 && str[i - 1] == ' '; i--);
	str = str.substr(0, i);
}

// extract token
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	
	std::string token;

	if (next_pos <= str.length()) {
		size_t end_pos = str.find_first_of(this->getDelimiter(), next_pos);

		if (end_pos != std::string::npos) {
			trim(token = str.substr(next_pos, end_pos - next_pos));
			next_pos = end_pos + 1;
		}
		else { // end of line
			trim(token = str.substr(next_pos));
			next_pos = str.length() + 1;
		}

		if (token.empty() && (next_pos != str.length() + 1)) {
			more = false;
			throw str + " - ERROR: Cannot extract token";
		}
		// update widthField if neccessary
		if (token.length() > this->getFieldWidth()) {
			this->setFieldWidth(token.length());
		}

		more = next_pos <= str.length();
	}
	
	return token;
}

// set delimiter
void Utilities::setDelimiter(char newDelimiter) {
	m_delimiter = newDelimiter;
}

// dilimiter query
char Utilities::getDelimiter() {
	return m_delimiter;
}
