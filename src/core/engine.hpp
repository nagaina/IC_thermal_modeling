#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <unordered_set>
#include "triangle.hpp"

class Engine
{
public:
	void calculateNeighbors(std::unordered_set<CTrianglePtr>&) const;

	void dumpToTxt(const std::unordered_set<CTrianglePtr>&) const;
};

#endif