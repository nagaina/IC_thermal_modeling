#include "main_window.hpp"

#include "application_ribbon_gui.hpp"
#include "icons.hpp"
#include "canvas.hpp"

#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QEvent>
#include <QCoreApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QLayout>

#include <cassert>

//FIXME todo enhanced~! (from QApplication)
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	// for logging
	return QMainWindow::eventFilter(obj, event);
}

///////////////////////////////////////////////////////////////////////////////
//
// implemenation of class mainWindow 
//
MainWindow::MainWindow(QWidget* p)
        : QMainWindow(p)
{
	m_ribbonBar = new ApplicationRibbonGui(this);
	m_canvas = new Canvas(this);

	QDockWidget* w = new QDockWidget(this);
	w->setWidget(m_ribbonBar);
	w->setFeatures(QDockWidget::NoDockWidgetFeatures);
	w->setTitleBarWidget(new QWidget(this));
	w->setFixedHeight(127);
	addDockWidget(Qt::TopDockWidgetArea, w);

	setMinimumSize(1100, 700);
	setCentralWidget(m_canvas);

	make_connections();
	static QIcon main_window_icon(getIconDir() + "shapes_simple.png");
	setWindowIcon(main_window_icon);
	QCoreApplication::instance()->installEventFilter(this);
}

void MainWindow::make_connections()
{
	connect(m_ribbonBar, SIGNAL(calculate()), m_canvas, SLOT(onCalculate()));
	connect(m_ribbonBar, SIGNAL(clear()), m_canvas, SLOT(onClear()));
	connect(m_ribbonBar, SIGNAL(openFile(const QString&)), m_canvas, SLOT(onLoadFile(const QString&)));
}
