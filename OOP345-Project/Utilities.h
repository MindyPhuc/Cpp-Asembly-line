/* ------------------------------------------------------
Project - MS1
Name		Thi My Phuc Huynh (Mindy)
ID			149792186
User		tmphuynh
-----------------------------------------------------------
Date		6 Nov 2020
-----------------------------------------------------------
Filename	Utilities.h
-----------------------------------------------------------*/
/*=================================================================
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments
====================================================================*/
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>

class Utilities {

	size_t m_widthField = 1;

	static char m_delimiter;

	void trim(std::string& str) const;

public:
	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	
	static void setDelimiter(char newDelimiter);
	static char getDelimiter();
};



#endif // !SDDS_UTILITIES_H
