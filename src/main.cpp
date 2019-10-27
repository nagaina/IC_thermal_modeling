#include <iostream>

#include <RQtree.hpp>
#include <main_winodw.hpp>
#include "core/FEM.hpp"

#include <QApplication>

#include <type_traits>

template<typename T, typename = int>
struct has_id : std::false_type { };

template<typename T>
struct has_id<T, decltype(std::declval<T>().id)> : std::true_type { };

int fibonaci(int x, std::vector<int>& output)
{
	if (x == 0 || x == 1)
		return x;

	int o =  fibonaci(x - 2, output) + fibonaci(x - 1, output);
	output.push_back(o);
	return o;
}

int main(int argc, char** argv)
{
	std::vector<int> v;
	int count = 10;
	fibonaci(count, v);
	
	//for (int i = v.size() - count; i < v.size(); ++i)
	//	std::cout << v[i] << " ";

	QApplication app(argc, argv);
	MainWindow* window = new MainWindow;
	window->show();
	app.exec();
	return 0;
}

//int main(int argc, char *argv[])
//{
//	//if (argc != 3)
//	//{
//	//	std::cout << "usage: " << argv[0] << " <input file> <output file>\n";
//	//	return 1;
//	//}
//
//	//std::ifstream infile(argv[1]);
//	//std::ofstream outfile(argv[2]);
//
//	std::cout << "poissonRatio " << "youngModules " << std::endl;
//	float poissonRatio, youngModulus;
//	//infile >> poissonRatio >> youngModulus;
//	std::cin >> poissonRatio;
//	std::cin >> youngModulus;
//
//	Eigen::Matrix3f D;
//	D <<
//		1.0f, poissonRatio, 0.0f,
//		poissonRatio, 1.0, 0.0f,
//		0.0f, 0.0f, (1.0f - poissonRatio) / 2.0f;
//
//	D *= youngModulus / (1.0f - pow(poissonRatio, 2.0f));
//
//	//infile >> nodesCount;
//	std::cout << "nodesCount :";
//	std::cin >> nodesCount;
//	nodesX.resize(nodesCount);
//	nodesY.resize(nodesCount);
//
//	for (int i = 0; i < nodesCount; ++i)
//	{
//		std::cin >> nodesX[i] >> nodesY[i];
//	}
//
//	int elementCount;
//	std::cout << "elementCount :";
//	std::cin >> elementCount;
//
//	for (int i = 0; i < elementCount; ++i)
//	{
//		Element element;
//		std::cin >> element.nodesIds[0] >> element.nodesIds[1] >> element.nodesIds[2];
//		elements.push_back(element);
//	}
//
//	int constraintCount;
//	std::cout << "constraintCount :";
//	std::cin >> constraintCount;
//
//	for (int i = 0; i < constraintCount; ++i)
//	{
//		Constraint constraint;
//		int type;
//		std::cin >> constraint.node >> type;
//		constraint.type = static_cast<Constraint::Type>(type);
//		constraints.push_back(constraint);
//	}
//
//	loads.resize(2 * nodesCount);
//	loads.setZero();
//
//	int loadsCount;
//	std::cout << "loadsCount :";
//	std::cin >> loadsCount;
//	for (int i = 0; i < loadsCount; ++i)
//	{
//		int node;
//		float x, y;
//		std::cin >> node >> x >> y;
//		loads[2 * node + 0] = x;
//		loads[2 * node + 1] = y;
//	}
//
//	std::vector<Eigen::Triplet<float> > triplets;
//	for (std::vector<Element>::iterator it = elements.begin(); it != elements.end(); ++it)
//	{
//		it->CalculateStiffnessMatrix(D, triplets);
//	}
//
//	Eigen::SparseMatrix<float> globalK(2 * nodesCount, 2 * nodesCount);
//	globalK.setFromTriplets(triplets.begin(), triplets.end());
//
//	ApplyConstraints(globalK, constraints);
//
//	Eigen::SimplicialLDLT<Eigen::SparseMatrix<float> > solver(globalK);
//
//	Eigen::VectorXf displacements = solver.solve(loads);
//
//	std::cout << displacements << std::endl;
//
//	for (std::vector<Element>::iterator it = elements.begin(); it != elements.end(); ++it)
//	{
//		Eigen::Matrix<float, 6, 1> delta;
//		delta << displacements.segment<2>(2 * it->nodesIds[0]),
//			displacements.segment<2>(2 * it->nodesIds[1]),
//			displacements.segment<2>(2 * it->nodesIds[2]);
//
//		Eigen::Vector3f sigma = D * it->B * delta;
//		float sigma_mises = sqrt(sigma[0] * sigma[0] - sigma[0] * sigma[1] + sigma[1] * sigma[1] + 3.0f * sigma[2] * sigma[2]);
//
//		std::cout << sigma_mises << std::endl;
//	}
//
//	int a;
//	std::cin >> a;
//	return 0;
//}
