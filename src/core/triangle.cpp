#include "triangle.hpp"

#include <QtGlobal>

CTriangle::CTriangle(QLineF l1, QLineF l2, QLineF l3)
	: m_line1(l1), m_line2(l2), m_line3(l3)
{
}

QLineF CTriangle::getBiggestLine() const
{
	auto lenght1 = m_line1.length();
	auto lenght2 = m_line2.length();
	auto lenght3 = m_line3.length();
	if (lenght1 < lenght2)
	{
		if (lenght2 < lenght3)
			return m_line3;
		else 
			return m_line2;
	}
	else
	{
		if (lenght1 < lenght3)
			return m_line3;
		else 
			return m_line1;
	}
	return QLineF{};
}

QLineF CTriangle::getLine1() const
{
	return m_line1;
}

QLineF CTriangle::getLine2() const
{
	return m_line2;
}

QLineF CTriangle::getLine3() const
{
	return m_line3;
}
