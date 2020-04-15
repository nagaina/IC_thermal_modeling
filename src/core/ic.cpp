#include "ic.hpp"
#include "layer.hpp"

#include <cassert>
#include <iostream>

Cic::Cic(const CLayers& aLayers)
{
	unsigned H = aLayers[0]->height();
	for (unsigned i = 1; i < aLayers.size(); ++i)
	{
		assert(aLayers[i]->height() == H);
	}
	m_aLayers = aLayers;
	//std::cout << "IC" << std::endl;
}

Cic::Cic(unsigned l, unsigned h)
{
	for (unsigned i = 0; i < l; ++i)
	{
		m_aLayers.emplace_back(new CLayer(i, h));
	}
}

Cic::~Cic()
{
	for (unsigned i = 0; i < m_aLayers.size(); ++i)
	{
		delete m_aLayers[i];
	}
}

void Cic::dump(QString& s) const
{
	for (unsigned i = 0; i < m_aLayers.size(); ++i)
	{
		auto l = m_aLayers[i];
		assert(l != 0);
		l->dump(s);
	}
}

int Cic::layersCount() const
{
	return m_aLayers.size();
}

CLayer* Cic::getLayer(int i) const
{
	//assert(i < m_aLayers.count());
	return m_aLayers[i];
}
