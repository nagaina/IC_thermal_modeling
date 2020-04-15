#ifndef APPLICATION_RIBBON_GUI_HPP 
#define APPLICATION_RIBBON_GUI_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Includes
//
// Qt
class QVBoxLayout;
class QRadioButton;
class QPushButton;
class QFileDialog;

#include <QWidget>

class QRibbonWidget;

///////////////////////////////////////////////////////////////////////////////
//
// @class ApplicationRibbonGui : Assistant for creating objects 
//
class ApplicationRibbonGui : public QWidget
{
	Q_OBJECT

public:
	ApplicationRibbonGui(QWidget* = 0);

signals:
	void calculate();
	void spice(const QString&);
	void openFile(const QString&);
	void clear();
	void depthChange(int);
	void loadNetlist();

private slots:
	void openFileDialog();
	void openSaveFileDialog();

private:
	void buildHomePage(QRibbonWidget*);

private:
	QFileDialog* m_dialog;
};

#endif
