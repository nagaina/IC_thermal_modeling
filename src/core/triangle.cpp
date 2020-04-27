#include "triangle.hpp"

#include <QtGlobal>

#include <QRectF>

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

qreal CTriangle::getArea() const
{
	qreal a = m_line1.length();
	qreal b = m_line2.length();
	qreal c = m_line3.length();

	qreal tiv = (a + b + c) / 2;
	return std::sqrt(tiv * (tiv - a) * (tiv - b) * (tiv - c));
}

void CTriangle::addNeighbor(CTrianglePtr oNeighbor)
{
	m_neighbors.emplace_back(oNeighbor);
}

bool CTriangle::isBounded(CTrianglePtr oTriangle)
{
	auto oLine = oTriangle->getLine1();
	QPointF oPoint;
	qreal oAngle;
	(oLine.intersect(m_line1, &oPoint));
	{
		oAngle = oLine.angleTo(m_line1);
		if ((oAngle == 0 || oAngle == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line1.p1().x() && oLine.p1().x() >= m_line1.p2().x()
				|| oLine.p1().x() >= m_line1.p1().x() && oLine.p1().x() <= m_line1.p2().x()
				||	oLine.p2().x() <= m_line1.p1().x() && oLine.p2().x() >= m_line1.p2().x()
				|| oLine.p2().x() >= m_line1.p1().x() && oLine.p2().x() <= m_line1.p2().x() )
			if (oLine.p1().y() <= m_line1.p1().y() && oLine.p1().y() >= m_line1.p2().y()
				|| oLine.p1().y() >= m_line1.p1().y() && oLine.p1().y() <= m_line1.p2().y()
				|| oLine.p2().y() <= m_line1.p1().y() && oLine.p2().y() >= m_line1.p2().y()
				|| oLine.p2().y() >= m_line1.p1().y() && oLine.p2().y() <= m_line1.p2().y())
				return true;
	}
	(oLine.intersect(m_line2, &oPoint));
	{
		oAngle = oLine.angleTo(m_line2);
		if ((oAngle == 0  || oAngle  == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line2.p1().x() && oLine.p1().x() >= m_line2.p2().x()
				|| oLine.p1().x() >= m_line2.p1().x() && oLine.p1().x() <= m_line2.p2().x()
				||	oLine.p2().x() <= m_line2.p1().x() && oLine.p2().x() >= m_line2.p2().x()
				|| oLine.p2().x() >= m_line2.p1().x() && oLine.p2().x() <= m_line2.p2().x() )
			if (oLine.p1().y() <= m_line2.p1().y() && oLine.p1().y() >= m_line2.p2().y()
				|| oLine.p1().y() >= m_line2.p1().y() && oLine.p1().y() <= m_line2.p2().y()
				|| oLine.p2().y() <= m_line2.p1().y() && oLine.p2().y() >= m_line2.p2().y()
				|| oLine.p2().y() >= m_line2.p1().y() && oLine.p2().y() <= m_line2.p2().y())
				return true;
	}
	(oLine.intersect(m_line3, &oPoint));
	{
		oAngle = oLine.angleTo(m_line3);
		if ((oAngle == 0  || oAngle  == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line3.p1().x() && oLine.p1().x() >= m_line3.p2().x()
				|| oLine.p1().x() >= m_line3.p1().x() && oLine.p1().x() <= m_line3.p2().x()
				||	oLine.p2().x() <= m_line3.p1().x() && oLine.p2().x() >= m_line3.p2().x()
				|| oLine.p2().x() >= m_line3.p1().x() && oLine.p2().x() <= m_line3.p2().x() )
			if (oLine.p1().y() <= m_line3.p1().y() && oLine.p1().y() >= m_line3.p2().y()
				|| oLine.p1().y() >= m_line3.p1().y() && oLine.p1().y() <= m_line3.p2().y()
				|| oLine.p2().y() <= m_line3.p1().y() && oLine.p2().y() >= m_line3.p2().y()
				|| oLine.p2().y() >= m_line3.p1().y() && oLine.p2().y() <= m_line3.p2().y())
				return true;
	}

	oLine = oTriangle->getLine2();
	(oLine.intersect(m_line1, &oPoint));
	{
		oAngle = oLine.angleTo(m_line1);
		if ((oAngle == 0 || oAngle == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line1.p1().x() && oLine.p1().x() >= m_line1.p2().x()
				|| oLine.p1().x() >= m_line1.p1().x() && oLine.p1().x() <= m_line1.p2().x()
				||	oLine.p2().x() <= m_line1.p1().x() && oLine.p2().x() >= m_line1.p2().x()
				|| oLine.p2().x() >= m_line1.p1().x() && oLine.p2().x() <= m_line1.p2().x() )
			if (oLine.p1().y() <= m_line1.p1().y() && oLine.p1().y() >= m_line1.p2().y()
				|| oLine.p1().y() >= m_line1.p1().y() && oLine.p1().y() <= m_line1.p2().y()
				|| oLine.p2().y() <= m_line1.p1().y() && oLine.p2().y() >= m_line1.p2().y()
				|| oLine.p2().y() >= m_line1.p1().y() && oLine.p2().y() <= m_line1.p2().y())
				return true;
	}
	(oLine.intersect(m_line2, &oPoint));
	{
		oAngle = oLine.angleTo(m_line2);
		if ((oAngle == 0  || oAngle  == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line2.p1().x() && oLine.p1().x() >= m_line2.p2().x()
				|| oLine.p1().x() >= m_line2.p1().x() && oLine.p1().x() <= m_line2.p2().x()
				||	oLine.p2().x() <= m_line2.p1().x() && oLine.p2().x() >= m_line2.p2().x()
				|| oLine.p2().x() >= m_line2.p1().x() && oLine.p2().x() <= m_line2.p2().x() )
			if (oLine.p1().y() <= m_line2.p1().y() && oLine.p1().y() >= m_line2.p2().y()
				|| oLine.p1().y() >= m_line2.p1().y() && oLine.p1().y() <= m_line2.p2().y()
				|| oLine.p2().y() <= m_line2.p1().y() && oLine.p2().y() >= m_line2.p2().y()
				|| oLine.p2().y() >= m_line2.p1().y() && oLine.p2().y() <= m_line2.p2().y())
				return true;
	}
	(oLine.intersect(m_line3, &oPoint));
	{
		oAngle = oLine.angleTo(m_line3);
		if ((oAngle == 0  || oAngle  == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line3.p1().x() && oLine.p1().x() >= m_line3.p2().x()
				|| oLine.p1().x() >= m_line3.p1().x() && oLine.p1().x() <= m_line3.p2().x()
				||	oLine.p2().x() <= m_line3.p1().x() && oLine.p2().x() >= m_line3.p2().x()
				|| oLine.p2().x() >= m_line3.p1().x() && oLine.p2().x() <= m_line3.p2().x() )
			if (oLine.p1().y() <= m_line3.p1().y() && oLine.p1().y() >= m_line3.p2().y()
				|| oLine.p1().y() >= m_line3.p1().y() && oLine.p1().y() <= m_line3.p2().y()
				|| oLine.p2().y() <= m_line3.p1().y() && oLine.p2().y() >= m_line3.p2().y()
				|| oLine.p2().y() >= m_line3.p1().y() && oLine.p2().y() <= m_line3.p2().y())
				return true;
	}

	oLine = oTriangle->getLine3();
	(oLine.intersect(m_line1, &oPoint));
	{
		oAngle = oLine.angleTo(m_line1);
		if ((oAngle == 0 || oAngle == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line1.p1().x() && oLine.p1().x() >= m_line1.p2().x()
				|| oLine.p1().x() >= m_line1.p1().x() && oLine.p1().x() <= m_line1.p2().x()
				||	oLine.p2().x() <= m_line1.p1().x() && oLine.p2().x() >= m_line1.p2().x()
				|| oLine.p2().x() >= m_line1.p1().x() && oLine.p2().x() <= m_line1.p2().x() )
			if (oLine.p1().y() <= m_line1.p1().y() && oLine.p1().y() >= m_line1.p2().y()
				|| oLine.p1().y() >= m_line1.p1().y() && oLine.p1().y() <= m_line1.p2().y()
				|| oLine.p2().y() <= m_line1.p1().y() && oLine.p2().y() >= m_line1.p2().y()
				|| oLine.p2().y() >= m_line1.p1().y() && oLine.p2().y() <= m_line1.p2().y())
				return true;
	}
	(oLine.intersect(m_line2, &oPoint));
	{
		oAngle = oLine.angleTo(m_line2);
		if ((oAngle == 0  || oAngle  == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line2.p1().x() && oLine.p1().x() >= m_line2.p2().x()
				|| oLine.p1().x() >= m_line2.p1().x() && oLine.p1().x() <= m_line2.p2().x()
				||	oLine.p2().x() <= m_line2.p1().x() && oLine.p2().x() >= m_line2.p2().x()
				|| oLine.p2().x() >= m_line2.p1().x() && oLine.p2().x() <= m_line2.p2().x() )
			if (oLine.p1().y() <= m_line2.p1().y() && oLine.p1().y() >= m_line2.p2().y()
				|| oLine.p1().y() >= m_line2.p1().y() && oLine.p1().y() <= m_line2.p2().y()
				|| oLine.p2().y() <= m_line2.p1().y() && oLine.p2().y() >= m_line2.p2().y()
				|| oLine.p2().y() >= m_line2.p1().y() && oLine.p2().y() <= m_line2.p2().y())
				return true;
	}
	(oLine.intersect(m_line3, &oPoint));
	{
		oAngle = oLine.angleTo(m_line3);
		if ((oAngle == 0  || oAngle  == 360 || oAngle == 180) && !oPoint.isNull())
			if (oLine.p1().x() <= m_line3.p1().x() && oLine.p1().x() >= m_line3.p2().x()
				|| oLine.p1().x() >= m_line3.p1().x() && oLine.p1().x() <= m_line3.p2().x()
				||	oLine.p2().x() <= m_line3.p1().x() && oLine.p2().x() >= m_line3.p2().x()
				|| oLine.p2().x() >= m_line3.p1().x() && oLine.p2().x() <= m_line3.p2().x() )
			if (oLine.p1().y() <= m_line3.p1().y() && oLine.p1().y() >= m_line3.p2().y()
				|| oLine.p1().y() >= m_line3.p1().y() && oLine.p1().y() <= m_line3.p2().y()
				|| oLine.p2().y() <= m_line3.p1().y() && oLine.p2().y() >= m_line3.p2().y()
				|| oLine.p2().y() >= m_line3.p1().y() && oLine.p2().y() <= m_line3.p2().y())
				return true;
	}

	return false;
}

std::vector<CTrianglePtr> CTriangle::getNeighbors() const
{
	return m_neighbors;
}

void CTriangle::setName(const QString& name)
{
	m_name = name;
}

QString CTriangle::getName() const
{
	return m_name;
}

void CTriangle::setNode(int i, int id)
{
	nodesIds[i] = id;
}

int CTriangle::getNode(int i) const
{
	return nodesIds[i];
}

void CTriangle::setLoad(int i, float load)
{
	loads[i] = load;
}

float CTriangle::getLoad(int i) const
{
	return loads[i];
}

float CTriangle::getMidLoad()
{
	return (loads[0] + loads[1] + loads[2]) / 3;
}

void CTriangle::setLayer(int n)
{
	m_layer = n;
}

int CTriangle::getLayer() const
{
	return m_layer;
}

void CTriangle::setLoad(double l)
{
	m_calcLoad = l;
}

double CTriangle::getLoad() const
{
	return m_calcLoad;
}

void CTriangle::setColor(const QColor& oClr)
{
	m_oColor = oClr;
}

QColor CTriangle::getColor() const
{
	return m_oColor;
}

namespace {
bool contains(QLineF const& oLine, QPointF const& oPoint)
{
	QPointF p1 = oLine.p1();
	QPointF p2 = oLine.p2();
	QRectF bbox(p1, p2);
	if (!bbox.contains(oPoint))
		// vertical and horizontal case
		return oPoint.x() == p1.x() || oPoint.x() == p2.x() || oPoint.y() == p1.y() || oPoint.y() == p2.y();
	float x = (float) (oPoint.x() - p1.x()) / (p2.x() - p1.x());
	float y = (float) (oPoint.y() - p1.y()) / (p2.y() - p1.y());
	float out =  x / y  * 100000 / 100000;
	bool b = out > 0.95 && out < 1.25;
	if (!b)
		// vertical and horizontal case
		return oPoint.x() == p1.x() || oPoint.x() == p2.x() || oPoint.y() == p1.y() || oPoint.y() == p2.y();
	return b;
}
}

bool CTriangle::isCornerPoint(const QPointF& oPoint) const
{
	//return (m_line1.p1() == oPoint || m_line1.p2() == oPoint ||
	//		m_line2.p1() == oPoint || m_line2.p2() == oPoint ||
	//		m_line3.p1() == oPoint || m_line3.p2() == oPoint); 
	return contains(m_line1, oPoint) || contains(m_line2, oPoint) || contains(m_line2, oPoint);
	
}

