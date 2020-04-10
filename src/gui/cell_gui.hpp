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

public:
    void fit();
	void calculate();
	void setMaxInterCount(int);

private:
    void dump_defined_values(std::string&);
    void dump_cells(std::string&);

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
