#ifndef LAYER_HPP
#define LAYER_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include <QString>

#include "triangle.hpp"
#include "ICnode.hpp"

class CLayer
{
	 using cells = std::vector<ICnodePtr>;

public:
	CLayer(unsigned id, unsigned height);
	virtual ~CLayer() = default;

public:
	unsigned id() const;
	unsigned height() const;

	void set_cell_value(unsigned r, double v);
    double get_cell_value(unsigned r);

public:
	void dump(QString&) const;

private:
	unsigned m_id;
	unsigned m_height;

private:
	cells m_cells;
};

#endif

