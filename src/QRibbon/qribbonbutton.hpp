#ifndef QRIBBON_BUTTON_HPP
#define QRIBBON_BUTTON_HPP

#include "qribbon_lib.hpp"

#include <QToolButton>

class QRIBBON_EXPORT QRibbonButton : public QToolButton
{
	Q_OBJECT

public:
	QRibbonButton(QWidget* p = nullptr, const QString& = "", const QString& = "");
};

#endif