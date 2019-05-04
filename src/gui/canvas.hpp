#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QPainter>

#include <vector>

#include <point.hpp>
#include <RQtree.hpp>

class Canvas : public QWidget
{
	Q_OBJECT

public:
	Canvas(QWidget* p = 0);

public:
	virtual void paintEvent(QPaintEvent*) override;

public slots:
	void calculate();
	void loadFile(const QString&);
	void clear();

private:
	void mapPointToScale();

private:
	QPainter* m_renderer = nullptr;
	int m_scale = 20;
	std::vector<rq::CPoint<int>> m_points;
	rq::RQtree<int> m_rq_plugin;
};

#endif