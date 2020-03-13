#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <QLineF>
#include <memory>

class CTriangle
{
public:
	CTriangle(QLineF, QLineF, QLineF);

public:
	QLineF getBiggestLine() const;

	QLineF getLine1() const;
	QLineF getLine2() const;
	QLineF getLine3() const;

private:
	QLineF m_line1;
	QLineF m_line2;
	QLineF m_line3;
};

using CTrianglePtr = std::shared_ptr<CTriangle>;

#endif