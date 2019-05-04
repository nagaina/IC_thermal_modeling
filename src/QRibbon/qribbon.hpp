#ifndef Q_RIBBON_H
#define Q_RIBBON_H

#include "qribbon_lib.hpp"

#include <QTabWidget>
#include <QEvent>

//	class QRibbon
//	represents the ribbon widgets in tab
class QRIBBON_EXPORT QRibbon : public QTabWidget
{
	Q_OBJECT

public:
	//	Constructor
	explicit QRibbon(QWidget* = 0);

	//	Destructor
	virtual ~QRibbon() {}

};

#endif