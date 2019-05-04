#include "canvas.hpp"

#include <parser_helper.hpp>

Canvas::Canvas(QWidget* p)
	: QWidget(p)
{
	setFocusPolicy(Qt::StrongFocus);
	setObjectName("Canvas");

	m_renderer = new QPainter(this);
}

void Canvas::paintEvent(QPaintEvent* event)
{
	m_renderer->begin(this);

	// draw the black canvas
	QRect blackHole(QPoint(0, 0), size());
	QBrush blackBrush(Qt::black);
	m_renderer->setBrush(blackBrush);
	m_renderer->drawRect(blackHole);

	// draw the grid
	QPen whitePen(Qt::white);
	whitePen.setWidth(3);
	whitePen.setCapStyle(Qt::RoundCap);
	m_renderer->setPen(whitePen);
	int _height = height();
	int _width = width();
	for (int i = 0; i < _width; i += m_scale)
		for (int j = 0; j < _height; j += m_scale)
			m_renderer->drawPoint(i, j);

	// vor keteery nkarven :D
	// draw the rq tree
	if (!m_rq_plugin.empty())
	{
		QPen yellowPen(Qt::yellow);
		yellowPen.setWidth(3);
		yellowPen.setCapStyle(Qt::RoundCap);
		m_renderer->setPen(yellowPen);
		for (auto point : m_points)
		{
			std::vector<rq::CPoint<int>> nearests = m_rq_plugin.nearest_points(point);
			for (auto i : nearests)
				m_renderer->drawLine(QPoint(point.x(), point.y()), QPoint(i.x(), i.y()));
		}
	}

	// draw the points parsed from the file
	QPen redPen(Qt::red);
	redPen.setWidth(7);
	redPen.setCapStyle(Qt::RoundCap);
	m_renderer->setPen(redPen);
	for (auto point : m_points)
		m_renderer->drawPoint(point.x(), point.y());

	m_renderer->end();
}

void Canvas::mapPointToScale()
{
	for (auto& point : m_points)
	{
		point.setX(point.x() * m_scale);
		point.setY(point.y() * m_scale);
	}
}

void Canvas::calculate()
{
	rq::RQtree<int> newTree(m_points);
	m_rq_plugin = newTree;
	update();
}

void Canvas::loadFile(const QString& file)
{
	parser::ParserHelper p;

	std::vector<parser::ICnodePtr>  output = p.parseFile(file.toStdString());

	std::vector<rq::CPoint<int>> points;

	for (auto i : output)
	{
		points.push_back(rq::CPoint<int>(i->X(), i->Y()));
	}

	m_points = points;
	mapPointToScale();
}

void Canvas::clear()
{
	m_points.clear();
	rq::RQtree<int> newTree(m_points);
	m_rq_plugin = newTree;
	update();

}