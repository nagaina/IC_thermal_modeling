#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

#include <QWidget>
#include <QLabel>

#include "../core/layer.hpp"

using namespace QtDataVisualization;

class viewer_3d : public QWidget
{
	Q_OBJECT
public:
	explicit viewer_3d(QWidget *parent = nullptr);

private:
	void init();

public:
	void set_draw_mode(QSurface3DSeries::DrawFlag);
	void fill_data(CLayer* l);
	void set_gradient(QLinearGradient gr);

	void toggle_mode_none();
	void toggle_mode_item();
	void toggle_mode_sliceRow();
	void toggle_mode_sliceColumn();

private:
	Q3DSurface* m_surface = 0;
	QSurface3DSeries* m_series = 0;
	QSurfaceDataProxy* m_data_proxy = 0;
	//core::layer* m_layer = 0;
	QLabel* m_label = 0;
	QSurface3DSeries::DrawFlag m_draw_mode = QSurface3DSeries::DrawSurfaceAndWireframe;
};


#endif