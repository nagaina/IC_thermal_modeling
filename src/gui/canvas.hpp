#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <parser_helper.hpp>

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;

class Canvas final : public QWidget
{
	Q_OBJECT

public:
	explicit Canvas(QWidget* p = nullptr);

public:
	
public slots:
	void onCalculate();
	void onLoadFile(const QString&);
	void onClear();

private:
	void mapPointToScale();

private:
	QGraphicsView*					m_view = nullptr;
	QGraphicsScene*					m_scene = nullptr;
	unsigned						m_id = 0;
	int								m_size = 1;
	std::vector<parser::ICnodePtr>	m_cells;
};

#endif