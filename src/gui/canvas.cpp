#include "canvas.hpp"
#include "thermal_gallery.hpp"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

Canvas::Canvas(QWidget* p)
	: QWidget(p)
{
    m_pGallery = new CLayersGallery(this);
	setObjectName("Canvas");
	QHBoxLayout* l = new QHBoxLayout();
	l->addWidget(m_pGallery);
	setLayout(l);
	m_pGallery->setStyleSheet("background-color:black;");
	setStyleSheet("background-color:black;");
}

void Canvas::mapPointToScale()
{
}

void Canvas::onCalculate()
{
	m_pGallery->calculate();
}

void Canvas::onGenerateSpice(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(this, tr("Unable to open file"),
			file.errorString());
		return;
	}

	QString sNetlist = QString();
	m_pGallery->generateSpice(sNetlist);

	file.write(sNetlist.toLatin1());
	file.close();

}

void Canvas::onLoadFile(const QString& file)
{
	onClear();

	parser::ParserHelper parser;
	auto pCells = parser.parseFile(file.toStdString());
	m_pGallery->fillLayers(pCells);
}

void Canvas::onClear()
{
	//update();
}

namespace {

int round(qreal x)
{
	return x + 0.5;
}
}

void Canvas::cutIntoTriangles(int depth, CTrianglePtr pT)
{
	/*std::queue<CTrianglePtr> triangles;
	triangles.push(pT);

	while (depth < m_nMaxDepth && !triangles.empty())
	{
		++depth;
		auto pTriangle = triangles.front();
		triangles.pop();

		//	remove current triangle
		m_triangles.extract(pTriangle);

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
		m_triangles.emplace(oPtr1);

		// cretae second rectangle
		line2.intersect(oMaxEdge, &oPoint);
		QLineF oNewLine2{oPoint, oRandIntersection};
		CTrianglePtr oPtr2 = std::shared_ptr<CTriangle>(new CTriangle(line2, oLine3, oNewLine2));
		m_triangles.emplace(oPtr2);

		triangles.push(oPtr1);
		triangles.push(oPtr2);
	}*/
}

void Canvas::onDepthChange(int n)
{
	m_pGallery->setMaxIterCount(n);
}

void Canvas::drawCells()
{
}

void Canvas::onLoadNetlist()
{
    QString f = QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.ic0");
    if (f.isEmpty()) {
        return;
    }

	parser::ParserHelper parser;
    Cic* ic = parser.parseNetlist(f.toStdString());
    if (ic == 0) {
        return;
    }
    assert(m_pGallery != 0);
    QRectF bRect = m_pGallery->getRect();
    //int itStep = m_gallery->get_grid_size();
	int itStep = 10;
    thermal_gallery* tg = new thermal_gallery(ic, bRect, itStep, nullptr, m_pGallery);
    tg->show();
}

