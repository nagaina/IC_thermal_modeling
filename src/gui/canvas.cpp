#include "canvas.hpp"
#include "../core/engine.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QtMath>
#include <QRandomGenerator>

#include <queue>
static const int POWER = 0;

inline qreal round(qreal val, int step)
{
	int tmp = int(val) + step / 2;
	tmp -= tmp % step;
	return qreal(tmp);
}

class scene : public QGraphicsScene
{
public:
	void show_grid(bool b)
	{
		m_show_grid = b;
		update();
	}
public:
	void set_grid_size(int s)
	{
		m_grid_step = s;
		update();
	}

public:
	int get_grid_size() const
	{
		return m_grid_step;
	}

protected:
	void drawForeground(QPainter *painter, const QRectF &rect) override
	{
		if (!m_show_grid)
		{
			return;
		}
		/*QRectF r = rect;
		painter->setRenderHint(QPainter::Antialiasing, true);
		painter->setPen(QPen(Qt::white,Qt::SolidLine));
		int max_X = r.width();
		int max_y = r.height();
		qDebug()<<r;
		for(int i = r.x() + cells_window::s_grid_step; i< max_X ; i += cells_window::s_grid_step) {
			painter->drawLine(QPointF(r.y() + cells_window::s_grid_step, i), QPointF(max_y, i));
		}
		for(int j = r.y() + cells_window::s_grid_step; j< max_y; j += cells_window::s_grid_step) {
			painter->drawLine(QPointF(j, r.x() + cells_window::s_grid_step), QPointF(j, max_X));
		}*/
		int step = m_grid_step;
		painter->setPen(QPen(QColor(Qt::white)));

		// draw horizontal grid.
		qreal start = round(rect.top(), step);
		if (start > rect.top())
		{
			start -= step;
		}

		for (qreal y = start - step; y < rect.bottom();)
		{
			y += step;
			painter->drawLine(rect.left(), y, rect.right(), y);
		}

		// Draw vertical grid.
		start = round(rect.left(), step);
		if (start > rect.left())
		{
			start -= step;
		}

		for (qreal x = start - step; x < rect.right();)
		{
			x += step;
			painter->drawLine(x, rect.top(), x, rect.bottom());
		}
	}

private:
	bool m_show_grid = false;
	int m_grid_step = 1;
};


Canvas::Canvas(QWidget* p)
	: QWidget(p)
{
	setFocusPolicy(Qt::StrongFocus);
	setObjectName("Canvas");
	m_lMain = new QHBoxLayout();
	//  first and main scene
	scene* sceneMain = new scene;
	m_scenes.append(sceneMain);
	QGraphicsView* viewMain = new QGraphicsView(sceneMain);
	m_views.append(viewMain);
	m_lMain->addWidget(viewMain);
	setLayout(m_lMain);
	viewMain->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	viewMain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	viewMain->setBackgroundBrush(QBrush(Qt::black));
}

void Canvas::mapPointToScale()
{
}

void Canvas::onCalculate()
{
	for (auto scene : m_scenes)
		scene->clear();

	std::unordered_set<CTrianglePtr> triangles;
	drawCells();

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	pen.setColor(QColor(Qt::white));
	for (auto scene : m_scenes)
	{
		triangles.clear();
		auto oBoundingRect = scene->itemsBoundingRect();
		//	create two rectangles
		{
			QLineF oLine1{ oBoundingRect.bottomLeft(), oBoundingRect.bottomRight() };
			QLineF oLine2{ oBoundingRect.topLeft(), oBoundingRect.bottomRight() };
			QLineF oLine3{ oBoundingRect.topLeft(), oBoundingRect.bottomLeft() };
			auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
			triangles.emplace(pTriangle);
			int depth = 0;
			cutIntoTriangles(depth, pTriangle, triangles);
		}
		{
			QLineF oLine1{ oBoundingRect.topLeft(), oBoundingRect.topRight() };
			QLineF oLine2{ oBoundingRect.topRight(), oBoundingRect.bottomRight() };
			QLineF oLine3{ oBoundingRect.topLeft(), oBoundingRect.bottomRight() };
			auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
			triangles.emplace(pTriangle);
			int depth = 0;
			cutIntoTriangles(depth, pTriangle, triangles);
		}

		for (auto it : triangles)
		{
			auto line1 = it->getLine1();
			auto line2 = it->getLine2();
			auto line3 = it->getLine3();
			QVector<QPointF> lstVec{ line1.p1(), line1.p2(), line2.p1(), line2.p2(), line3.p1(), line3.p2() };
			QPolygonF p(lstVec);
			QGraphicsItem* pPoly = scene->addPolygon(p, pen);
			QGraphicsItem* pItem = scene->itemAt(line1.p1(), QTransform());

			if (pItem != nullptr)
			{
				QRectF pItemRect = pItem->boundingRect();
				QRectF pPolyRect = pPoly->boundingRect();
				QRectF pInterRect = pPolyRect.intersected(pItemRect);
				int tiv = pInterRect.height() * pInterRect.width();
			}
			//m_scene->addLine(line1, pen);
			//m_scene->addLine(line2, pen);
			//m_scene->addLine(line3, pen);
		}

		// calculate Neighors
		Engine oEngine;
		oEngine.calculateNeighbors(triangles);
		// save trianges
		m_lstTriangles.append(triangles);
		// for debugging
		// dump into file
		oEngine.dumpToTxt(triangles);

		// dump netlist
	}
}

void Canvas::onLoadFile(const QString& file)
{
	onClear();

	parser::ParserHelper parser;
	m_cells = parser.parseFile(file.toStdString());
	drawCells();

	int nCnt = m_scenes.count();
	for (int nidx = 0; nidx < nCnt; ++nidx)
	{
		QGraphicsScene* sc = m_scenes.at(nidx);
		QGraphicsView* view = m_views.at(nidx);
		QRectF br = sc->itemsBoundingRect();

		QRectF sr = view->contentsRect();
		qreal blength = br.width() < br.height() ? br.height() : br.width();
		qreal length = sr.width() < sr.height() ? sr.height() : sr.width();
		qreal length_factor = length / (blength*1.5);

		//view->scale(length_factor, length_factor);
		view->setAlignment(Qt::AlignCenter);
		view->centerOn(br.center().x(), br.center().y());
		sc->setSceneRect(br);
	}
}

void Canvas::onClear()
{
	for(auto sc : m_scenes)
		sc->clear();
	m_cells.clear();
	for(auto tr : m_lstTriangles)
		tr.clear();
	//update();
}

namespace {

int round(qreal x)
{
	return x + 0.5;
}
}

void Canvas::cutIntoTriangles(int depth, CTrianglePtr pT, std::unordered_set<CTrianglePtr>& trInput)
{
	std::queue<CTrianglePtr> triangles;
	triangles.push(pT);

	while (depth < m_nMaxDepth && !triangles.empty())
	{
		++depth;
		auto pTriangle = triangles.front();
		triangles.pop();

		//	remove current triangle
		trInput.extract(pTriangle);

		// randomly choose to cup this one or not
		auto oMaxEdge = pTriangle->getBiggestLine();
		// get two other lines
		auto line1 = pTriangle->getLine1();
		if (line1 == oMaxEdge)
			line1 = pTriangle->getLine3();
		auto line2 = pTriangle->getLine2();
		if (line2 == oMaxEdge)
			line2 = pTriangle->getLine3();

		QPointF oRandIntersection;

		// covert to int with rounding
		int n1 = qRound(oMaxEdge.x1() + 0.05);
		int n2 = qRound(oMaxEdge.x2() + 0.05);
		// find random point in the biggest line
		if (n1 != n2)
		{
			//auto p = (oMaxEdge.x1() + oMaxEdge.x2()) / 2;
			auto oXMax = qMax(oMaxEdge.x1(), oMaxEdge.x2());
			auto oXMin = qMin(oMaxEdge.x1(), oMaxEdge.x2());
			auto per = (oXMax - oXMin) / 4;
			double p = QRandomGenerator::global()->bounded(qRound(oXMin + per), qRound(oXMax - per));
			if (int(p) == n1)
				p = (oMaxEdge.x1() + oMaxEdge.x2()) / 2;
			if (int(p) == n2)
				p = (oMaxEdge.x1() + oMaxEdge.x2()) / 2;
			auto oYMax = qMax(oMaxEdge.y2(), oMaxEdge.y1());
			auto oYMin = qMin(oMaxEdge.y1(), oMaxEdge.y2());
			oMaxEdge.intersect(QLineF(p, oYMin, p, oYMax * 2), &oRandIntersection);
		}
		else
		{
			//auto p = (oMaxEdge.y1() + oMaxEdge.y2()) /2;
			auto oXMax = qMax(oMaxEdge.y1(), oMaxEdge.y2());
			auto oXMin = qMin(oMaxEdge.y1(), oMaxEdge.y2());
			auto per = (oXMax - oXMin) / 4;
			double p = QRandomGenerator::global()->bounded(qRound(oXMin + per), qRound(oXMax - per));
			auto oYMin = qMin(oMaxEdge.x1(), oMaxEdge.x2());
			oMaxEdge.intersect(QLineF(oYMin, p, oYMin * 2, p), &oRandIntersection);
		}

		//	find intersection of line1 and line2
		QPointF oPoint;
		line1.intersect(line2, &oPoint);

		// create 3rd line
		QLineF oLine3{oPoint, oRandIntersection};

		//	find intersacion of line1 and oMaxEdge
		line1.intersect(oMaxEdge, &oPoint);

		QLineF oNewLine1{oPoint, oRandIntersection};
		CTrianglePtr oPtr1 = std::shared_ptr<CTriangle>(new CTriangle(line1, oLine3, oNewLine1));
		trInput.emplace(oPtr1);

		// cretae second rectangle
		line2.intersect(oMaxEdge, &oPoint);
		QLineF oNewLine2{oPoint, oRandIntersection};
		CTrianglePtr oPtr2 = std::shared_ptr<CTriangle>(new CTriangle(line2, oLine3, oNewLine2));
		trInput.emplace(oPtr2);

		triangles.push(oPtr1);
		triangles.push(oPtr2);
	}
}

void Canvas::onDepthChange(int n)
{
	m_nMaxDepth = n;
}

void Canvas::createScene()
{
	//  new scene
	scene* sc= new scene;
	m_scenes.append(sc);
	QGraphicsView* vw= new QGraphicsView(sc);
	m_views.append(vw);
	m_lMain->addWidget(vw);
	vw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	vw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	vw->setBackgroundBrush(QBrush(Qt::black));
}

void Canvas::drawCells()
{
	//	Draw
	double maxPow = 0;
	foreach(auto i, m_cells)
	{
		if (maxPow < i->Power())
			maxPow = i->Power();
	}
	assert(maxPow != 0);

	foreach(auto i, m_cells)
	{
		QRectF r(QPoint(i->X() * 15, i->Y() * 15),
			QSize(qreal(i->Width() * 15), qreal(i->Height() * 15)));
		QPen pen;
		//pen.setStyle(Qt::SolidLine);
		//pen.setWidth(1);
		//pen.setColor(QColor(Qt::white));
		QColor color;
		qreal h = i->Power() / maxPow * 256;
		color.setHsl(256 - h, 240, 140);
		QBrush br(color);
		int layer = i->Layer(); // piti int lini 0.5 layery vorna?
		if (layer >= m_scenes.count())
			createScene();
		assert(layer <= m_scenes.count());
		QGraphicsRectItem* ri = m_scenes.at(layer)->addRect(r, pen, br); // TODO add QPen and QBrush
/*        QGraphicsItem* ti = m_scene->addText(QString::fromStdString(i.name()), QFont("Times", 30));
		ti->setPos(r.center());*/
		ri->setToolTip(QString(i->Name().c_str()));
		ri->setData(POWER, i->Power());
		//ri->setData(FREQUENCY, i.frequency());
		ri->setFlags(QGraphicsItem::ItemIsMovable |
			QGraphicsItem::ItemIsSelectable |
			QGraphicsItem::ItemSendsGeometryChanges |
			QGraphicsItem::ItemSendsScenePositionChanges);
	}

	//int ncnt = m_scenes.count();
	//for (int nidx = 0; nidx < ncnt; ++nidx)
	//{
	//	QRectF br = m_scenes.at(nidx)->itemsBoundingRect();

	//	QRectF sr = m_views.at(nidx)->contentsRect();
	//	qreal blength = br.width() < br.height() ? br.height() : br.width();
	//	qreal length = sr.width() < sr.height() ? sr.height() : sr.width();
	//	qreal length_factor = length / (blength*1.5);

	//	//m_view->scale(length_factor, length_factor);
	//	m_views.at(nidx)->setAlignment(Qt::AlignCenter);
	//	//m_view->centerOn(br.center().x(), br.center().y());
	//	m_scenes.at(nidx)->setSceneRect(br);
	//}
}

