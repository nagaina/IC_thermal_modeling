#include "layer_gui.hpp"

#include <QGraphicsScene>
#include <QGridLayout>
#include <QMultiHash>
#include <QtAlgorithms>

#include <cassert>
#include <iostream>
#include <set>

CLayersGallery::CLayersGallery(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QGridLayout;
    setLayout(m_layout);
//    m_layout->setSizeConstraint(QLayout::SetFixedSize);
//    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void CLayersGallery::fillLayers(const std::vector<ICnodePtr>& cells)
{
    cleanup_layers();
    add_layers(cells);
    layout_layers();
}

void CLayersGallery::add_layers(const std::vector<ICnodePtr>& cells)
{
    QMultiHash<unsigned, ICnodePtr> hash;
    foreach (auto c, cells) {
        hash.insertMulti(c->Layer(), c);
    }
    QList<unsigned> layers_ids = hash.uniqueKeys();
    qSort(layers_ids);
    foreach (unsigned i, layers_ids) {
        CCellGui* cw = new CCellGui(i);
        QList<ICnodePtr> cls = hash.values(i);
        std::vector<ICnodePtr> fppc;
        foreach (auto d, cls) {
            fppc.push_back(d);
        }
        cw->fillData(fppc);
        m_layers.push_back(cw);
    }
}

void CLayersGallery::cleanup_layers()
{
foreach (auto l, m_layers) {
	l->deleteLater();
}
m_layers.clear();
}

void CLayersGallery::layout_layers()
{
    assert(m_layout != 0);
    int r = 0;
    int c = 0;

    foreach (auto l, m_layers) {
        assert(l != 0);
        m_layout->addWidget(l, r, c);
        if (c + 1 < 2) {
            ++c;
        } else {
            c = 0;
            ++r;
        }
    }
}

void CLayersGallery::fit()
{
    foreach (auto l, m_layers) {
        assert(l != 0);
        l->fit();
    }
}


QString CLayersGallery::dumpNetlist()
{
    // TODO
    QString content;
    content += "***********************************************************************\n";
    content += "***********************************************************************\n\n\n";
    content += ".prot\n";
    content += ".lib '/remote/u/tigrangs/hspice/saed32nm.lib' TT\n";
    content += ".unprot\n\n";
    content += ".temp 25\n";
    content += "vvdd vdd gnd dc = 1.2\n";
    content += "vvss vss gnd dc = 0.0\n";
    content += "***********************************************************************\n";
  
	// dump defined values
	dumpDefinedValues(content);

	//  dump each
	foreach (auto l, m_layers) {
        assert(l != 0);
        l->dumpNetlist(content);
    }

    content += "\n\n.option post probe\n\n";
    content += ".global gnd\n";
    content += ".probe v(*) i(*)\n";
    content += ".tran 0.01u 1u\n\n";
    content += ".end";
    return content;
}

QRectF CLayersGallery::getRect() const
{
    return m_layers[0]->getScene()->itemsBoundingRect();
}

Cic* CLayersGallery::getIC()
{
    //std::cout<<"GET_IC"<<std::endl;
    std::vector<CLayer*> layers;
    foreach (auto l, m_layers) {
        assert(l != 0);
        //layers.push_back(l->getLayer(get_grid_size(), 0));
        //std::cout<<"GET_IC_layer "<<layers.back()->id()<<std::endl;
    }
    return new Cic(layers);
}

void CLayersGallery::calculate()
{
	for (auto it : m_layers)
		it->calculate();
}

void CLayersGallery::generateSpice(QString& sNet)
{
	sNet += dumpNetlist();
}

void CLayersGallery::setMaxIterCount(int n)
{
	for (auto it : m_layers)
		it->setMaxInterCount(n);
}

CCellGui* CLayersGallery::getLayer(int i)
{
	return m_layers[i];
}

void CLayersGallery::dumpDefinedValues(QString& sNetlist)
{
	// calc triangle count
	int nTrCnt = 0;
	for (auto it : m_layers)
		nTrCnt += it->getTriangleCount();

	///////////////////////////     Rij       //////////////////////////////////////////
	const qreal lambda = 0.000233;
	qreal subThickness = 2.88;
	qreal h = 23.8;
	const qreal C = 20.16;
	const qreal r = 2329;

	qreal S = nTrCnt; // count of triangles 
	// Rij
	qreal Rij = 1 / (lambda * h);
	sNetlist += QString(".param Rij = %1\n").arg(Rij);

	// rij
	qreal rij = 1 / (lambda * subThickness);
	sNetlist += QString(".param rij = %1\n").arg(rij);
}
