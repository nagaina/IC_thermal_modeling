#ifndef THERMAL_GALLERY_HPP
#define THERMAL_GALLERY_HPP

#include <QWidget>

class viewer_3d;
class Cic;

class thermal_gallery : public QWidget
{
    Q_OBJECT
public:
    explicit thermal_gallery(Cic*, QRectF, int, QWidget *parent = nullptr);

private:
    using layers = QList<viewer_3d*>;

private:
    layers m_layers = {};
};


#endif // THERMAL_GALLERY_HPP
