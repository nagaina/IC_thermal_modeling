#ifndef THERMAL_GALLERY_HPP
#define THERMAL_GALLERY_HPP

#include <QWidget>

class CChartGallery;
class Cic;

#include "layer_gui.hpp"

class thermal_gallery : public QWidget
{
    Q_OBJECT
public:
    explicit thermal_gallery(Cic*, QRectF, int, QWidget *parent = nullptr, CLayersGallery* = nullptr);

private:
    using layers = QList<CChartGallery*>;

private:
    layers m_layers = {};
};


#endif // THERMAL_GALLERY_HPP
