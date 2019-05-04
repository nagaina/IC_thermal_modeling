#include <iostream>

#include <RQtree.hpp>
#include <main_winodw.hpp>

#include <QApplication>

#include <type_traits>

template<typename T, typename = int>
struct has_id : std::false_type { };

template<typename T>
struct has_id<T, decltype(std::declval<T>().id)> : std::true_type { };

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow* window = new MainWindow;
	window->show();
	app.exec();
	return 0;
}