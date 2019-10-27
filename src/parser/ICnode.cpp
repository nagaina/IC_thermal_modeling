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

void ICnode::setH(double h)
{
	m_H = h;
}

void ICnode::setP(double w)
{
	m_P = w;
}

void ICnode::setL(double l)
{
	m_L = l;
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

double ICnode::P() const
{
	return m_P;
}

double ICnode::H() const
{
	return m_H;
}

double ICnode::L() const
{
	return m_L;
}
}