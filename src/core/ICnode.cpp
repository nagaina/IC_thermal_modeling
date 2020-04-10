#include "ICnode.hpp"

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

void ICnode::setWidth(double w)
{
	m_W = w;
}

void ICnode::setHeight(double h)
{
	m_H = h;
}

void ICnode::setPower(double w)
{
	m_P = w;
}

void ICnode::setLayer(double l)
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

double ICnode::Width() const
{
	return m_W;
}

double ICnode::Power() const
{
	return m_P;
}

double ICnode::Height() const
{
	return m_H;
}

double ICnode::Layer() const
{
	return m_L;
}

void ICnode::setName(const std::string& n)
{
	m_name = n;
}

std::string ICnode::Name() const
{
	return m_name;
}