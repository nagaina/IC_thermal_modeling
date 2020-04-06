#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <unordered_set>
#include "triangle.hpp"

class Engine
{
public:
	void calculateNeighbors(std::unordered_set<CTrianglePtr>&) const;

	void dumpToTxt(const std::unordered_set<CTrianglePtr>&) const;

	void dumpToNetlist(const std::unordered_set<CTrianglePtr>&, QString&);

protected:
	// helper
	void dumpDefinedValues(const std::unordered_set<CTrianglePtr>&, QString&);
};

#endif