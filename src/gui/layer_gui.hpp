#ifndef LAYER_GUI_HPP
#define LAYER_GUI_HPP

#include "../core/ICnode.hpp"
#include "cell_gui.hpp"
#include "../core/ic.hpp"

#include <QList>
#include <QWidget>
#include <QString>

class QGridLayout;

class CLayersGallery : public QWidget
{
    Q_OBJECT
public:
    explicit CLayersGallery(QWidget *parent = nullptr);

public:
    void fillLayers(const std::vector<ICnodePtr>&);
    QRectF getRect() const;
    QString dumpNetlist();
    Cic* getIC();

    void fit();

	int calculate();
	void generateSpice(QString&);
	void setMaxIterCount(int);

	CCellGui* getLayer(int);
private:
    void add_layers(const std::vector<ICnodePtr>&);
    void cleanup_layers();
    void layout_layers();

	void dumpDefinedValues(QString&);

private:
    using layers = QList<CCellGui*>;

private:
    layers m_layers = {};

    QGridLayout* m_layout = 0;
};


#endif // !LAYER_GUI_HPP
