#include "layer.hpp"

#include <cassert>
#include <iostream>

CLayer::CLayer(unsigned id, unsigned width, unsigned height)
    : m_id(id)
    , m_width(width)
    , m_height(height)
{
	for (unsigned i = 0; i < m_height; ++i) {
		m_cells.push_back({std::vector<ICnodePtr>(m_width, 0)});
		//m_cells.back().reserve(m_width);
		for (unsigned j = 0; j < m_width; ++j) {
			m_cells.back()[j] = ICnodePtr(new ICnode());
		}
	}
}

unsigned CLayer::id() const
{
    return m_id;
}

unsigned CLayer::width() const
{
    return m_width;
}

unsigned CLayer::height() const
{
	return m_height;
}

void CLayer::dump(QString& s) const
{
    s += "\n";
   // s += "******************* Layer " + std::to_string(m_id) + " **********************";
    for (unsigned i = 0; i < m_height; ++i) {
        for (unsigned j = 0; j < m_width; ++j) {
            //std::shared_ptr<cell> c = m_cells[i][j];
            //assert(c != 0);
            //c->dump(s);
            //std::cout<<"Cell "<<i<<" "<<j<<std::endl;
        }
    }
}

double CLayer::get_cell_value(unsigned r, unsigned c)
{
	assert(r < m_height);
	assert(c < m_width);
	auto tc = m_cells[r][c];
	assert(tc != 0);
	return tc->Power();
}

void CLayer::set_cell_value(unsigned r, unsigned c, double v)
{
	assert(r < m_height);
	assert(c < m_width);
	auto tc = m_cells[r][c];
	assert(tc != 0);
	tc->setPower(v);
}

double CLayer::get_cell_value_1(unsigned r, unsigned c)
{
	assert(r < m_height);
	assert(c < m_width);
	auto tc = m_cells[r][c];
	assert(tc != 0);
	return tc->Power();
}

void CLayer::set_cell_value_1(unsigned r, unsigned c, double v)
{
	assert(r < m_height);
	assert(c < m_width);
	auto tc = m_cells[r][c];
	assert(tc != 0);
	tc->setPower(v);
}
