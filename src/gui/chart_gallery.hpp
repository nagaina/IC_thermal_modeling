#ifndef CHART_GALLERY_HPP
#define CHART_GALLERY_CPP

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

#include "../core/layer.hpp"

class CChartGallery : public QWidget
{
	Q_OBJECT

public:
	CChartGallery(QWidget* pParent = nullptr);

	void addLayer(CLayer*, std::unordered_set<CTrianglePtr>&);

private:
	QChart*				m_pChart = nullptr;
	QSplineSeries*		m_pSeries = nullptr;
	QChartView*			m_pChartView = nullptr;
	
};
#endif
