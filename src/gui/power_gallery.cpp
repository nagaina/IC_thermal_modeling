#include "power_gallery.hpp"
#include "viewer.hpp"

#include <../core/ic.hpp>
#include <../core/layer.hpp>

#include <QGridLayout>

#include <cassert>

power_gallery::power_gallery(Cic* ic, QWidget *parent) : QWidget(parent)
{
    assert(ic != 0);
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkBlue);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);
/*    for (int i = 0; i < ic->layers_count(); ++i) {
        viewer_3d* pw = new viewer_3d(this);
        core::layer* l = ic->get_layer(i);
        assert(l != 0);
        pw->set_draw_mode(QSurface3DSeries::DrawSurface);
        pw->fill_data(l);
        pw->set_gradient(gr);
        m_layers.push_back(pw);
    }
	*/

/*    int r = 0;
    int c = 0;*/

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
