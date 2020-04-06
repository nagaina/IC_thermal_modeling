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

void Engine::dumpToNetlist(const std::unordered_set<CTrianglePtr>& aTriangles, QString& sNetlist)
{
	dumpDefinedValues(aTriangles, sNetlist);
	
	// dump cells
	for (auto it : aTriangles)
	{
		sNetlist += "\n";
		sNetlist += QString("]n* Cell %1 *\n").arg(it->getName());

		// dump I
		sNetlist += QString(".param i_%1 = %2 \n").arg(it->getName());
	}
}

// protected
void Engine::dumpDefinedValues(const std::unordered_set<CTrianglePtr>& aTriangles, QString& sNetlist)
{
	///////////////////////////     Rij       //////////////////////////////////////////
	const qreal lambda = 0.000233;
	qreal subThickness = 2.88;
	qreal h = 23.8;
	const qreal C = 20.16;
	const qreal r = 2329;

	qreal S = aTriangles.size(); // count of triangles 
	// Rij
	qreal Rij = 1 / (lambda * h);
	sNetlist += QString(".param Rij = %1\n").arg(Rij);

	// rij
	qreal rij = 1 / (lambda * subThickness);
	sNetlist += QString(".param rij = %1\n").arg(rij);

	// Ri
	qreal Ri = h / (lambda * S);
	sNetlist += QString(".param Ri = %1\n").arg(Ri);

	// Rsub     
	qreal Rsub = subThickness / (lambda * S);
	sNetlist += QString(".param Rsub = %1\n").arg(Rsub);
}