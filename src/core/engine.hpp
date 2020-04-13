#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <unordered_set>
#include "triangle.hpp"

//	FEM 
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <string>
#include <vector>

// Qt
#include <QGraphicsItem>

// Parser
#include "ICnode.hpp"

class Engine
{
public:
	void calculateNeighbors(std::unordered_set<CTrianglePtr>&) const;

	void dumpToTxt(const std::unordered_set<CTrianglePtr>&) const;

	///	@brief Generates mash using Eigen lib
	void generateMesh(std::unordered_set<CTrianglePtr>&, int&, std::vector<float>&, std::vector<float>&, QList<QGraphicsItem *> pItems, std::vector<ICnodePtr> cells, QRectF);

	void dumpToNetlist(const std::unordered_set<CTrianglePtr>&, QString&);

	void cutIntoTriangles(int, CTrianglePtr, int, std::unordered_set<CTrianglePtr>&, QList<QGraphicsItem *> pItems, std::vector<ICnodePtr> cells) const;

protected:
	// helper
	void dumpDefinedValues(const std::unordered_set<CTrianglePtr>&, QString&);

private:
	struct Element
	{
		void calculateStiffnesMatrix(const Eigen::Matrix3f&, std::vector<Eigen::Triplet<float>>&, Engine&);

		Eigen::Matrix<float, 3, 6> B;
		int nodesIds[3];
	};

	struct Constraint
	{
		int node;
	};

private:
	void ApplyConstraints(Eigen::SparseMatrix<float>& K, const std::vector<Constraint>& constraints);

private:
	Eigen::VectorXf				nodesX;
	Eigen::VectorXf				nodesY;
	Eigen::VectorXf				loads;
	std::vector< Element >		elements;
	std::vector< Constraint >	constraints;
	int							nodesCount;
};

#endif