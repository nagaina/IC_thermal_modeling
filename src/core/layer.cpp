#include "layer.hpp"

#include <cassert>
#include <iostream>

CLayer::CLayer(unsigned id, unsigned height)
    : m_id(id)
    , m_height(height)
{
	for (unsigned i = 0; i < m_height; ++i) {
		m_cells.push_back(std::shared_ptr<ICnode>(new ICnode{}));
	}
}

unsigned CLayer::id() const
{
    return m_id;
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
            //std::shared_ptr<cell> c = m_cells[i][j];
            //assert(c != 0);
            //c->dump(s);
            //std::cout<<"Cell "<<i<<" "<<j<<std::endl;
    }
}

double CLayer::get_cell_value(unsigned r)
{
	assert(r < m_height);
	auto tc = m_cells[r];
	assert(tc != 0);
	return tc->Power();
}

void CLayer::set_cell_value(unsigned r, double v)
{
	assert(r < m_height);
	auto tc = m_cells[r];
	assert(tc != 0);
	tc->setPower(v);
	// todo
//	if (c < m_height && r < m_width)
//	{
//		auto tc = m_cells[c][r];
//		assert(tc != 0);
//		tc->setPower(v);
//	}
}

