#include "engine.hpp"

#include <unordered_map>

#include <QFile>

void Engine::calculateNeighbors(std::unordered_set<CTrianglePtr>& aTriangles) const
{
	std::unordered_map<CTrianglePtr, bool> aVisited;

	for (auto i : aTriangles)
	{
		for (auto j : aTriangles)
		{
			// the same triangle
			if (i == j)
				continue;
			auto it =  aVisited.find(j);
			// already visited
			if (it != aVisited.end() && it->second == true)
				continue;
			// add neighbours
			if (i->isBounded(j))
			{
				i->addNeighbor(j);
				j->addNeighbor(i);
			}
		}
		aVisited[i] = true;
	}
}

void Engine::dumpToTxt(const std::unordered_set<CTrianglePtr>& aTriangles) const
{
	// supply names all triangles
	int i = 0;
	for (auto it : aTriangles)
	{
		auto name = it->getName();
		if (name.isEmpty())
		{
			QString name {"tr : " + QString::number(i)};
			it->setName(name);
			++i;
		}
	}

	QFile oFile(QStringLiteral("debug.trialngles.txt"));
	oFile.open(QIODevice::WriteOnly);

	for (auto it : aTriangles)
	{
		auto n = it->getNeighbors();
		oFile.write("Current triangle : ");
		oFile.write(it->getName().toLatin1());
		oFile.write(" Neighbors : ");
		for (auto i : n)
		{
			oFile.write(i->getName().toLatin1());
			oFile.write(" , ");
		}

		oFile.write("\n");
	}

	oFile.close();
}