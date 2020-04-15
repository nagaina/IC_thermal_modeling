#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "../core/triangle.hpp"
#include <parser_helper.hpp>

#include <QWidget>
#include <unordered_set>
#include "layer_gui.hpp"

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
	void onGenerateSpice(const QString&);
	void onLoadFile(const QString&);
	void onClear();
	void onDepthChange(int);
	void onLoadNetlist();

private:
	void mapPointToScale();
	void cutIntoTriangles(int, CTrianglePtr);
	void drawCells();

private:
	CLayersGallery*		m_pGallery = nullptr;
	int					m_nMaxDepth = 0;
};

#endif