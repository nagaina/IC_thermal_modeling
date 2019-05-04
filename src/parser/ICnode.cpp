#include "ICnode.hpp"

namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class ICNode
//
void ICnode::setX(double x)
{
	m_X = x;
}

void ICnode::setY(double y)
{
	m_Y = y;
}

void ICnode::setW(double w)
{
	m_W = w;
}

double ICnode::X() const
{
	return m_X;
}

double ICnode::Y() const
{
	return m_Y;
}

double ICnode::W() const
{
	return m_W;
}
}