#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <QLineF>
#include <memory>
#include <vector>
#include <QString>
#include <QColor>

class CTriangle;
using CTrianglePtr = std::shared_ptr<CTriangle>;

class CTriangle
{
public:
	CTriangle(QLineF, QLineF, QLineF);

public:
	QLineF getBiggestLine() const;

	QLineF getLine1() const;
	QLineF getLine2() const;
	QLineF getLine3() const;

	qreal getArea() const;

public:
	void addNeighbor(CTrianglePtr);
	bool isBounded(CTrianglePtr);
	std::vector<CTrianglePtr> getNeighbors() const;

	void setName(const QString&);
	QString getName() const;

	void setNode(int, int);
	int getNode(int) const;

	void setLoad(int, float);
	float getLoad(int) const;

	float getMidLoad();

	void setLayer(int);
	int getLayer() const;

	void setLoad(double);
	double getLoad() const;

	void setColor(const QColor&);
	QColor getColor() const;
	
	bool isCornerPoint(const QPointF&) const;
private:
	QLineF m_line1;
	QLineF m_line2;
	QLineF m_line3;

	int nodesIds[3];
	float loads[3] = {0.1};

	double m_calcLoad = 0;

	// for debug
	QString m_name;

	int m_layer = 0;

	QColor m_oColor;

	// keep the neigbor triangles for dumping into the file
	std::vector<CTrianglePtr> m_neighbors;
};


#endif