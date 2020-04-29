#include "chart_gallery.hpp"
#include "cell_gui.hpp"

#include <QString>
#include <QPainter>
#include <QHBoxLayout>

CChartGallery::CChartGallery(QWidget* pParent)
	: QWidget(pParent)
{
	m_pChart = new QChart();
	m_pChart->legend()->hide();
	m_pChart->setTitle("Title");
	m_pChart->createDefaultAxes();

	m_pSeries = new QSplineSeries();
	m_pSeries->setName(QStringLiteral("Series"));

	m_pChartView = new QChartView(m_pChart);
	m_pChartView->setRenderHint(QPainter::Antialiasing);

	auto pLayout = new QHBoxLayout;
	pLayout->addWidget(m_pChartView);

	setLayout(pLayout);
}


void CChartGallery::addLayer(CLayer* pLayer, std::unordered_set<CTrianglePtr>& pTriangles)
{

	QSplineSeries* series = new QSplineSeries(this);
	series->setName(QStringLiteral("Series"));

	float nMax = 0, nMin = 0.1;
	for (auto i = 0; i < pLayer->height(); ++i)
	{
		double v = pLayer->get_cell_value(i);
		if (nMax < v)
			nMax = v;
		*series << QPointF(i, v);
	}


	QLinearGradient gr;
	gr.setStart(QPointF(0, 0));
    gr.setFinalStop(QPointF(0, 1));
    gr.setColorAt(0, Qt::red);
    gr.setColorAt(0.4, Qt::yellow);
    gr.setColorAt(0.7, Qt::green);
	gr.setCoordinateMode(QGradient::StretchToDeviceMode);
	QPen pen;
	pen.setWidth(2);
	pen.setBrush(gr);
	series->setPen(pen);

	nMax += 4;

	m_pChart->addSeries(series);
	m_pChart->createDefaultAxes();
	m_pChart->axes(Qt::Vertical).first()->setRange(nMin, nMax);
	m_pChart->setTitle("Thermal Map");
	m_pChart->axisX()->setTitleText("Triangle ID");
	m_pChart->axisY()->setTitleText("Temperature");

	// color the mesh
	for (auto it : pTriangles)
	{
		auto nName = it->getName().toInt();
		auto nVal = pLayer->get_cell_value(nName);
		it->setLoad(nVal);
	}

	auto pCell = new CCellGui(0, this);
	layout()->addWidget(pCell);
	pCell->initMesh(pTriangles);
}


