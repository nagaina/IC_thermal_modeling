#include "engine.hpp"

#include <unordered_map>
#include <iostream>

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
			QString name {QString::number(i)};
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

void Engine::generateMesh(std::unordered_set<CTrianglePtr>& aTriangles, int& nodeCount, std::vector<float>& nodeX, std::vector<float>& nodeY, QList<QGraphicsItem *> pItems, std::vector<ICnodePtr> cells, QRectF oFixedBoundar)
{
	float poissonRatio, youngModulus; // material properties

	// silicon
	poissonRatio = 0.27;
	youngModulus = 112;

	// Elasticy matrix
	Eigen::Matrix3f D;
	D <<
		1.0f, poissonRatio, 0.0f,
		poissonRatio, 1.0, 0.0f,
		0.0f, 0.0f, (1.0f - poissonRatio) / 2.0f;

	D *= youngModulus / (1.0f - pow(poissonRatio, 2.0f));

	// nodes
	int nodesCount = nodeCount;
	nodesX.resize(nodesCount);
	nodesY.resize(nodesCount);
	for (int i = 0; i < nodesCount; ++i)
	{
		nodesX[i] = nodeX[i];
		nodesY[i] = nodeY[i];
	}

	// elements
	int elementCount = aTriangles.size();
	for (auto it : aTriangles)
	{
		Element element;
		element.nodesIds[0] = it->getNode(0);
		element.nodesIds[1] = it->getNode(1);
		element.nodesIds[2] = it->getNode(2);
		elements.emplace_back(element);
	}


	// constarints
	int constrainCount = 2 * elementCount;
	constraints.resize(constrainCount);
	for (auto it : aTriangles)
	{
		int nNode = it->getNode(0);
		float load = it->getLoad(0);
		if (load != 0)
		{
			Constraint constraint;
			constraint.node = nNode;
			constraints[nNode] = constraint;
		}

		nNode = it->getNode(1);
		load = it->getLoad(1);
		if (load != 0)
		{
			Constraint constraint;
			constraint.node = nNode;
			constraints[nNode] = constraint;
		}

		nNode = it->getNode(2);
		load = it->getLoad(3);
		if (load != 0)
		{
			Constraint constraint;
			constraint.node = nNode;
			constraints[nNode] = constraint;
		}
	}

	for (int i = 0; i < constrainCount; ++i)
	{
	}

	// loads
	loads.resize(2 * nodesCount);
	loads.setZero();

	for (auto it : aTriangles)
	{
		int node = it->getNode(0);
		loads[2 * node + 0] = it->getLoad(0);
		loads[2 * node + 1] = it->getLoad(0);

		node = it->getNode(1);
		loads[2 * node + 0] = it->getLoad(1);
		loads[2 * node + 1] = it->getLoad(1);

		node = it->getNode(2);
		loads[2 * node + 0] = it->getLoad(2);
		loads[2 * node + 1] = it->getLoad(2);
	}
	
	// stiffnes matrix
	std::vector<Eigen::Triplet<float> > triplets;
	for (std::vector<Element>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		it->calculateStiffnesMatrix(D, triplets, *this);
	};

	// Apply constarints
	Eigen::SparseMatrix<float> globalK(2 * nodesCount, 2 * nodesCount);
	globalK.setFromTriplets(triplets.begin(), triplets.end());

	ApplyConstraints(globalK, constraints);

	// Solve
	Eigen::SimplicialLDLT<Eigen::SparseMatrix<float> > solver(globalK);

	Eigen::VectorXf displacements = solver.solve(loads);

	if (solver.info() != Eigen::Success)
		return;

	// Apply solution
	std::vector<float> sigmas;
	for (std::vector<Element>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		Eigen::Matrix<float, 6, 1> delta;
		delta << displacements.segment<2>(2 * it->nodesIds[0]),
			displacements.segment<2>(2 * it->nodesIds[1]),
			displacements.segment<2>(2 * it->nodesIds[2]);

		Eigen::Vector3f sigma = D * it->B * delta;
		float sigma_mises = sqrt(sigma[0] * sigma[0] - sigma[0] * sigma[1] + sigma[1] * sigma[1] + 3.0f * sigma[2] * sigma[2]);

		sigmas.emplace_back(sigma_mises);
		std::cout << sigma_mises << std::endl;
	}


	// Shape Function
	int _i = 0;
	std::unordered_set<CTrianglePtr> toReplace;
	for (auto it : aTriangles)
	{
		auto point1 = it->getLine1().p1();
		auto point2 = it->getLine1().p2();
		QPointF point3, point4;

		if (it->getLine2().p1() != point1 && it->getLine2().p1() != point2)
			point3 = it->getLine2().p1();
		else
			point3 = it->getLine2().p2();

		auto x = (point1.x() - point3.x())* sigmas[_i] + (point2.x() - point3.x())* sigmas[_i] + point3.x();
		auto y = (point1.y() - point3.y())* sigmas[_i] + (point2.y() - point3.y())* sigmas[_i] + point3.y();

		point4 = QPointF {x, y};
		nodeX.push_back(x);
		nodeY.push_back(y);
		int __i = 0;
		std::vector<float> loads{0, 0, 0, 0};
		for (auto it : pItems)
		{
			if (__i >= cells.size())
				break;
			auto rect = it->boundingRect();
			if (rect.contains(point1))
				loads[0] = cells[__i]->Power();

			if (rect.contains(point2))
				loads[1] = cells[__i]->Power();

			if (rect.contains(point3))
				loads[2] = cells[__i]->Power();
			
			if (rect.contains(point4))
				loads[3] = cells[__i]->Power();

			++__i;
		}

		{
			QLineF oLine1{point1, point2};
			QLineF oLine2{point4, point2};
			QLineF oLine3{point1, point4};
			auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
			pTriangle->setNode(0, it->getNode(0));
			pTriangle->setNode(1, it->getNode(1));
			pTriangle->setNode(2, nodeX.size() - 1);
			pTriangle->setLoad(0, loads[3]);
			pTriangle->setLoad(1, loads[0]);
			pTriangle->setLoad(2, loads[1]);
			toReplace.emplace(pTriangle);
		}

		{
			QLineF oLine1{point3, point4};
			QLineF oLine2{point4, point2};
			QLineF oLine3{point3, point2};
			auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
			pTriangle->setNode(0, it->getNode(1));
			pTriangle->setNode(1, it->getNode(2));
			pTriangle->setNode(2, nodeX.size() - 1);
			pTriangle->setLoad(0, loads[3]);
			pTriangle->setLoad(1, loads[1]);
			pTriangle->setLoad(2, loads[2]);
			toReplace.emplace(pTriangle);
		}

		{
			QLineF oLine1{point3, point4};
			QLineF oLine2{point4, point1};
			QLineF oLine3{point3, point1};
			auto pTriangle = std::shared_ptr<CTriangle>(new CTriangle(oLine1, oLine2, oLine3));
			pTriangle->setNode(0, it->getNode(0));
			pTriangle->setNode(1, it->getNode(2));
			pTriangle->setNode(2, nodeX.size() - 1);
			pTriangle->setLoad(0, loads[3]);
			pTriangle->setLoad(1, loads[0]);
			pTriangle->setLoad(2, loads[2]);
			toReplace.emplace(pTriangle);
		}
		++_i;
	}
	aTriangles = toReplace;
	nodeCount = nodeX.size();
}


void Engine::Element::calculateStiffnesMatrix(const Eigen::Matrix3f& D, std::vector<Eigen::Triplet<float>>& triplets, Engine& oEng)
{
	Eigen::Vector3f x, y;
	x << oEng.nodesX[nodesIds[0]], oEng.nodesX[nodesIds[1]], oEng.nodesX[nodesIds[2]];
	y << oEng.nodesY[nodesIds[0]], oEng.nodesY[nodesIds[1]], oEng.nodesY[nodesIds[2]];

	Eigen::Matrix3f C;
	C << Eigen::Vector3f(1.0f, 1.0f, 1.0f), x, y;

	Eigen::Matrix3f IC = C.inverse();

	for (int i = 0; i < 3; i++)
	{
		B(0, 2 * i + 0) = IC(1, i);
		B(0, 2 * i + 1) = 0.0f;
		B(1, 2 * i + 0) = 0.0f;
		B(1, 2 * i + 1) = IC(2, i);
		B(2, 2 * i + 0) = IC(2, i);
		B(2, 2 * i + 1) = IC(1, i);
	}
	Eigen::Matrix<float, 6, 6> K = B.transpose() * D * B * C.determinant() / 2.0f;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Eigen::Triplet<float> trplt11(2 * nodesIds[i] + 0, 2 * nodesIds[j] + 0, K(2 * i + 0, 2 * j + 0));
			Eigen::Triplet<float> trplt12(2 * nodesIds[i] + 0, 2 * nodesIds[j] + 1, K(2 * i + 0, 2 * j + 1));
			Eigen::Triplet<float> trplt21(2 * nodesIds[i] + 1, 2 * nodesIds[j] + 0, K(2 * i + 1, 2 * j + 0));
			Eigen::Triplet<float> trplt22(2 * nodesIds[i] + 1, 2 * nodesIds[j] + 1, K(2 * i + 1, 2 * j + 1));

			triplets.push_back(trplt11);
			triplets.push_back(trplt12);
			triplets.push_back(trplt21);
			triplets.push_back(trplt22);
		}
	}
}

namespace {
void SetConstraints(Eigen::SparseMatrix<float>::InnerIterator& it, int index)
{
	if (it.row() == index || it.col() == index)
	{
		it.valueRef() = it.row() == it.col() ? 1.0f : 0.0f;
	}
}
}

void Engine::ApplyConstraints(Eigen::SparseMatrix<float>& K, const std::vector<Constraint>& constraints)
{
	std::vector<int> indicesToConstraint;

	for (std::vector<Constraint>::const_iterator it = constraints.begin(); it != constraints.end(); ++it)
	{
		indicesToConstraint.push_back(2 * it->node + 0);
		indicesToConstraint.push_back(2 * it->node + 1);
		
	}

	for (int k = 0; k < K.outerSize(); ++k)
	{
		for (Eigen::SparseMatrix<float>::InnerIterator it(K, k); it; ++it)
		{
			for (std::vector<int>::iterator idit = indicesToConstraint.begin(); idit != indicesToConstraint.end(); ++idit)
			{
				SetConstraints(it, *idit);
			}
		}
	}
}
void Engine::dumpToNetlist(const std::unordered_set<CTrianglePtr>& aTriangles, QString& sNetlist)
{
	sNetlist = QString("\n\n.prot \n.lib '/remote/u/tigrangs/hspice/saed32nm.lib' TT \n.unprot \n \n");
	sNetlist += QString(".temp 25 \n");
	sNetlist += QString("vvdd vdd gnd dc = 1.2 \n");
	sNetlist += QString("vvss vss gnd dc = 0.0 \n");

	dumpDefinedValues(aTriangles, sNetlist);

	// dump cells
	for (auto it : aTriangles)
	{
		sNetlist += "\n";
		sNetlist += QString("\n* Cell %1 *\n").arg(it->getName());

		// dump I
		sNetlist += QString(".param i_%1_layer =%3 \n").arg(it->getName()).arg(it->getMidLoad());
		sNetlist += QString("i%1_layer vdd c_%1 dc = i_%1_layer ac = 0 \n").arg(it->getName());

		// dump R
		sNetlist += QString("rR_%1 c_%1 c_%1_s R=Ri \n").arg(it->getName());

		// dump for neighbors
		for (auto itN : it->getNeighbors())
		{
			sNetlist += QString("rR_%1_%2 c_%1 c_%1_%2 R=Rij \n").arg(it->getName()).arg(itN->getName());
		}
	}

	sNetlist += QString("\n.option post probe\n");
	sNetlist += QString("\n.global gnd");
	sNetlist += QString("\n.probe v(*) i(*)");
	sNetlist += QString("\n.tran 0.01u 1u");
	sNetlist += QString("\n.end\n");
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