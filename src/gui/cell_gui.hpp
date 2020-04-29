#ifndef CELL_GUI_HPP
#define CELL_GUI_HPP

#include "../core/ICnode.hpp"
#include "../core/layer.hpp"

#include <QWidget>
#include <QString>

class QGraphicsView;
class QGraphicsScene;

class CCellGui : public QWidget
{
public:
    CCellGui(unsigned id, QWidget* p = nullptr);

private:
    void init();

public:
    void fillData(const std::vector<ICnodePtr>&);
    const QGraphicsScene* getScene() const;
    void dumpNetlist(QString&);
    CLayer* getLayer(int, int = 20);
	std::unordered_set<CTrianglePtr> getMesh() const;
	void initMesh(const std::unordered_set<CTrianglePtr>&);
	int getTriangleCount() const;

public:
    void fit();
	int calculate();
	void setMaxInterCount(int);

private:
    void dump_cells(QString&);

private:
    QGraphicsView* m_view = 0;
    QGraphicsScene* m_scene = 0;
    unsigned m_id = 0;
    int m_size = 1;
	std::vector<ICnodePtr>			m_cells;
	std::unordered_set<CTrianglePtr>		m_triangles;
	int m_nMaxDepth;
};

#endif // !CELL_GUI_HPP
