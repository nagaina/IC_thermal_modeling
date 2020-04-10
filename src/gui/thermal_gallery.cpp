#include "thermal_gallery.hpp"
#include "viewer.hpp"

#include <../core/ic.hpp>
#include <../core/layer.hpp>

#include <QGridLayout>

#include <cassert>

thermal_gallery::thermal_gallery(Cic* ic, QRectF bRect, int itStep,  QWidget *parent) : QWidget(parent)
{
    assert(ic != 0);
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkCyan);
    gr.setColorAt(0.3, Qt::darkGreen);
    gr.setColorAt(0.5, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    QPointF distPoint = QPoint(20,20);
    QRectF cbRect(bRect.topLeft()-distPoint, bRect.bottomRight()+distPoint);
    qreal factor =( cbRect.height()*cbRect.width())/(itStep*itStep);
    for (int i = 0; i < ic->layersCount(); ++i) {
        viewer_3d* tw = new viewer_3d(this);
        CLayer* l = ic->getLayer(i);
        assert(l != 0);
        for (unsigned i = 0; i < l->height(); ++i) {
            for (unsigned j = 0; j < l->width(); ++j) {
                l->set_cell_value(i, j, l->get_cell_value(i, j));
            }
        }
        tw->fill_data(l);
        tw->set_gradient(gr);
        m_layers.push_back(tw);
    }


//    int r = 0;
//    int c = 0;

    foreach (auto l, m_layers) {
        assert(l != 0);
        layout->addWidget(l);
/*        layout->addWidget(l, r, c);
        if (c + 1 < 2) {
            ++c;
        } else {
            c = 0;
            ++r;
        }*/
    }
}