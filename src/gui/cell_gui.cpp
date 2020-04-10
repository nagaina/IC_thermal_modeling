#include "cell_gui.hpp"
#include "../core/engine.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QtMath>

#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <QFile>
#include <queue>

#include <cassert>
#include <iostream>

static const int POWER = 0;
static const int FREQUENCY = 1;

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
	
	}

private:
	bool m_show_grid = false;
	int m_grid_step = 1;
};


CCellGui::CCellGui(unsigned id, QWidget *p)
	: QWidget(p)
	, m_id(id)
{
	init();
}

void CCellGui::init()
{
	QHBoxLayout* l = new QHBoxLayout();
	m_scene = new scene;
	m_view = new QGraphicsView(m_scene);
	l->addWidget(m_view);
	setLayout(l);
	m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	//    m_view->setBackgroundBrush(QBrush(QColor(240,240,240,82)/*, Qt::Dense1Pattern)*/));
	m_view->setBackgroundBrush(QBrush(Qt::black));
}

void CCellGui::fillData(const std::vector<ICnodePtr>& cells)
{
	m_cells = cells;
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
		QGraphicsRectItem* ri = m_scene->addRect(r, pen, br); // TODO add QPen and QBrush
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
	assert(m_scene != 0);
	assert(m_view != 0);
	QRectF br = m_scene->itemsBoundingRect();

	QRectF sr = m_view->contentsRect();
	qreal blength = br.width() < br.height() ? br.height() : br.width();
	qreal length = sr.width() < sr.height() ? sr.height() : sr.width();
	qreal length_factor = length / (blength*1.5);

	//m_view->scale(length_factor, length_factor);
	m_view->setAlignment(Qt::AlignCenter);
	//m_view->centerOn(br.center().x(), br.center().y());
	m_scene->setSceneRect(br);
}

void CCellGui::fit()
{
	QRectF br = m_scene->itemsBoundingRect();

	/*    QRectF sr = m_view->contentsRect();
		qreal blength = br.width() < br.height() ? br.height() : br.width();
		qreal length = sr.width() < sr.height() ? sr.height() : sr.width();
		qreal length_factor = length/(blength*1.5);*/

		//    m_view->scale(1/length_factor,1/length_factor);
	m_view->setAlignment(Qt::AlignCenter);
	m_view->centerOn(br.center().x(), br.center().y());
	m_scene->setSceneRect(br);
}

const QGraphicsScene* CCellGui::getScene() const
{
	return m_scene;
}

void CCellGui::dumpNetlist(QString& netlist)
{
	//if (m_id == 0)
	//{
	//	dump_defined_values(netlist);
	//}
	//dump_cells(netlist);
}

void CCellGui::dump_defined_values(std::string& netlist)
{
	scene* sc = static_cast<scene*>(m_scene);
	assert(sc != 0);
	int step = sc->get_grid_size();

	///////////////////////////     Rij       //////////////////////////////////////////
	const qreal lambda = 0.000233;
	qreal subThickness = 2.88;
	qreal h = 23.8;
	const qreal C = 20.16;
	const qreal r = 2329;

	qreal S = qPow(step, 2);
	qreal Rij = 1 / (lambda * h);
	netlist += QString(".param Rij = %1\n").arg(Rij).toStdString();

	///////////////////////////     rij       //////////////////////////////////////////
	S = step * subThickness;
	qreal rij = 1 / (lambda * subThickness);
	netlist += QString(".param rij = %1\n").arg(rij).toStdString();

	///////////////////////////     Ri       //////////////////////////////////////////
	S = qPow(step, 2);
	qreal Ri = h / (lambda * S);

	netlist += QString(".param Ri = %1\n").arg(Ri).toStdString();

	///////////////////////////     Rsub       //////////////////////////////////////////
	S = qPow(step, 2);
	qreal Rsub = subThickness / (lambda * S);

	netlist += QString(".param Rsub = %1\n").arg(Rsub).toStdString();

	///////////////////////////     Ci       //////////////////////////////////////////
	S = qPow(step, 2);
	qreal Ci = C * r*S*h;
	Ci = 600; //forced

	netlist += QString(".param Ci = %1p\n").arg(Ci).toStdString();
}

CLayer* CCellGui::getLayer(int itStep, int offset)
{
	/*
	assert(m_scene != 0);
	QRectF bRect = m_scene->itemsBoundingRect();
	QPointF distPoint = QPoint(offset, offset);
	QRectF cbRect(bRect.topLeft() - distPoint, bRect.bottomRight() + distPoint);

	qreal xStart = cbRect.topLeft().x();
	qreal xEnd = cbRect.topRight().x() - itStep;
	qreal yStart = cbRect.topLeft().y();
	qreal yEnd = cbRect.bottomLeft().y() - itStep;


	unsigned w = static_cast<unsigned>((xEnd - xStart) / itStep) + 1;
	unsigned h = static_cast<unsigned>((yEnd - yStart) / itStep) + 1;
	qDebug() << QString::fromStdString("matrix size");
	qDebug() << QString::number(w);
	qDebug() << QString::number(h);
	core::layer* layer = new controller::matrix_layer(m_id, h, w);
	//core::layer* layer = new core::layer(m_id, h, w);
	std::cout << "created_matrix_layer" << std::endl;
	qreal theIPower = 0.2;

	int row = 0;
	for (qreal x = xStart; x <= xEnd; x += itStep)
	{
		int column = 0;
		for (qreal y = yStart; y <= yEnd; y += itStep)
		{
			QRectF gridRect(x, y, itStep, itStep);
			QGraphicsRectItem* gridItem = new  QGraphicsRectItem(gridRect);

			m_scene->addItem(gridItem);
			qreal intersectP = 0;
			qreal intersectFR = 0;

			double max_value = 0;
			QList<QGraphicsItem *>  collidingItemsList = gridItem->collidingItems();
			QGraphicsRectItem* max_item = collidingItemsList.size() != 0 ? dynamic_cast<QGraphicsRectItem*>(collidingItemsList[0]) : 0;
			foreach(QGraphicsItem* item, collidingItemsList)
			{
				QGraphicsRectItem* ri = dynamic_cast<QGraphicsRectItem*>(item);
				if (ri)
				{
					QRectF bRect = ri->boundingRect();
					QRectF intersectRect = gridItem->rect().intersected(bRect);
					QVariant v = ri->data(POWER);
					assert(v.isValid());
					double pv = v.toDouble();
					///intersectP += intersectRect.height() * intersectRect.width() * node->getPower() / S;

					double value = intersectRect.height() * intersectRect.width() * pv / (gridItem->rect().height()* gridItem->rect().width());
					if (value > max_value)
					{
						max_value = value;
						max_item = ri;
					}
					intersectP += value;
					//333 intersectP += intersectRect.height() * intersectRect.width() * node->getPower();

					v = ri->data(FREQUENCY);
					assert(v.isValid());
					double fr = v.toDouble();
					if (fr < 0)
					{
						continue;
					}
					intersectFR += intersectRect.height() * intersectRect.width() * fr / (gridItem->rect().height()* gridItem->rect().width());
				}
			}
			m_scene->removeItem(gridItem);

			if (!intersectP)
			{
				intersectP = theIPower / 2;
			}
			else
			{
				theIPower = intersectP;
			}
			std::cout << "set_value " << row << " " << column << std::endl;
			layer->set_cell_value(row, column, intersectP);
			layer->set_cell_value_1(row, column, intersectFR == 0 ? -1 : intersectFR);
			std::shared_ptr<controller::matrix_cell> cell =
				std::static_pointer_cast<controller::matrix_cell>(layer->get_cell(row, column));
			if (max_item != 0)
			{
				/*qDebug()<<QString::number(column);
				qDebug()<<QString::number(row);
				qDebug()<<QString::fromStdString("ITEM_was_added");*/
		/*		cell->add_item(max_item);
			}
			cell->set_source_position(row, column);
			++column;
		}
		++row;
	}
	return layer;*/
	return nullptr;

}

void CCellGui::dump_cells(std::string& netlist)
{
	/*cene* sc = static_cast<scene*>(m_scene);
	assert(sc != 0);

	core::layer* layer = get_layer(sc->get_grid_size());
	assert(layer != 0);
	layer->dump(netlist);
	delete layer;*/
}

void CCellGui::calculate()
{
	m_triangles.clear();
	//m_scene->clear();
	//drawCells();

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	pen.setColor(QColor(Qt::white));
	auto oBoundingRect = m_scene->itemsBoundingRect();

	int nodeCount = 4;
	std::vector<float> nodesX, nodesY;
	std::vector<float> loads{0, 0, 0, 0};
	nodesX.resize(nodeCount);
	nodesY.resize(nodeCount);

	auto point1 = oBoundingRect.bottomLeft();
	auto point2 = oBoundingRect.bottomRight();
	auto point3 = oBoundingRect.topLeft();
	auto point4 = oBoundingRect.topRight();

	nodesX[0] = point1.x();
	nodesY[0] = point1.y();

	nodesX[1] = point2.x();
	nodesY[1] = point2.y();

	nodesX[2] = point3.x();
	nodesY[2] = point3.y();

	nodesX[3] = point4.x();
	nodesY[3] = point4.y();

	int _i = 0;
	for (auto it : m_scene->items())
	{
		if (_i >= m_cells.size())
			break;

		auto rect = it->boundingRect();
		if (rect.contains(point1))
			loads[0] = m_cells[_i]->Power();

		if (rect.contains(point2))
			loads[1] = m_cells[_i]->Power();

		if (rect.contains(point3))
			loads[2] = m_cells[_i]->Power();

		if (rect.contains(point4))
			loads[3] = m_cells[_i]->Power();

		++_i;
	}

	//	create two rectangles
	{
		QLineF oLine1{point1, point2};
		QLineF oLine2{point3, point2};
		QLineF oLine3{point3, point1};
		auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
		pTriangle->setNode(0, 0);
		pTriangle->setNode(1, 1);
		pTriangle->setNode(2, 2);
		pTriangle->setLoad(0, loads[0]);
		pTriangle->setLoad(1, loads[1]);
		pTriangle->setLoad(2, loads[2]);
		m_triangles.emplace(pTriangle);
		int depth = 0;
		//cutIntoTriangles(depth, pTriangle);
	}
	{
		QLineF oLine1{point3, point4};
		QLineF oLine2{point4, point2};
		QLineF oLine3{point3, point2};
		auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
		pTriangle->setNode(0, 3);
		pTriangle->setNode(1, 1);
		pTriangle->setNode(2, 2);
		pTriangle->setLoad(0, loads[3]);
		pTriangle->setLoad(1, loads[1]);
		pTriangle->setLoad(2, loads[2]);
		m_triangles.emplace(pTriangle);
		int depth = 0;
		//cutIntoTriangles(depth, pTriangle);
	}

	Engine oEngine;
	for (auto i = 0; i < m_nMaxDepth; ++i)
		oEngine.generateMesh(m_triangles, nodeCount, nodesX, nodesY, m_scene->items(), m_cells, oBoundingRect);

	for (auto it : m_triangles)
	{
		auto line1 = it->getLine1();
		auto line2 = it->getLine2();
		auto line3 = it->getLine3();
		m_scene->addLine(line1, pen);
		m_scene->addLine(line2, pen);
		m_scene->addLine(line3, pen);
	}

	// calculate Neighors
	oEngine.calculateNeighbors(m_triangles);

	// for debugging
	// dump into file
	oEngine.dumpToTxt(m_triangles);
	QString sNet;
	oEngine.dumpToNetlist(m_triangles, sNet);

	// dump netlist
	QFile oFile(QStringLiteral("netlist.sp"));
	oFile.open(QIODevice::WriteOnly);
	oFile.write(sNet.toLatin1());
	oFile.close();
	update();
}

void CCellGui::setMaxInterCount(int n)
{
	m_nMaxDepth = n;
}