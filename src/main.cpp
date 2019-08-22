#include <iostream>

#include <RQtree.hpp>
#include <main_winodw.hpp>

#include <QApplication>

#include <type_traits>
#include <iostream>

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