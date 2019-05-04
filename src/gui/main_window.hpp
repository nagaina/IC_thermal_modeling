#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "gui.hpp"

// Qt
#include <QMainWindow>

class Canvas;
class ApplicationRibbonGui;

///////////////////////////////////////////////////////////////////////////////
//
// @class mainWindow 
//
class GUI_EXPORT MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* = 0 );
	bool eventFilter(QObject *object, QEvent *event);

private:
	void make_connections();

private:
	Canvas* m_canvas = nullptr;
	ApplicationRibbonGui* m_ribbonBar = nullptr;
};

#endif
