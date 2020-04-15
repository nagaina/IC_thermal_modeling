#ifndef IC_HPP
#define IC_HPP

#include <vector>
#include <QString>

class CLayer;

/// @class Intgarted Circuites
class Cic
{
public:
public:
	using CLayers = std::vector<CLayer*>;

public:
	Cic(const CLayers&);
	Cic(unsigned l, unsigned h);
	~Cic();

public:
	void dump(QString&) const;
	int layersCount() const;
	CLayer* getLayer(int) const;

private:
	CLayers m_aLayers;
};

#endif