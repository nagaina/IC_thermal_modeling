#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "../core/triangle.hpp"
#include <parser_helper.hpp>

#include <QWidget>
#include <unordered_set>

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
	void onDepthChange(int);

private:
	void mapPointToScale();
	void cutIntoTriangles(int, CTrianglePtr);
	void drawCells();

private:
	QGraphicsView*							m_view = nullptr;
	QGraphicsScene*							m_scene = nullptr;
	unsigned								m_id = 0;
	int										m_size = 1;
	std::vector<parser::ICnodePtr>			m_cells;
	std::unordered_set<CTrianglePtr>		m_triangles;
	int										m_nMaxDepth = 0;
};

#endif