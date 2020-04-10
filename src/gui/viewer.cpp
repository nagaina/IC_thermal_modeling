#include "viewer.hpp"

#include <QApplication>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRadioButton>
#include <QScreen>

#include <cassert>

#include <iostream>

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>

viewer_3d::viewer_3d(QWidget *parent) : QWidget(parent)
{
	init();
}

void viewer_3d::init()
{
	m_surface = new Q3DSurface();
	QWidget *container = QWidget::createWindowContainer(m_surface);

	if (!m_surface->hasContext())
	{
		QMessageBox msgBox;
		msgBox.setText("Couldn't initialize the OpenGL context.");
		msgBox.exec();
		return;
	}

	QSize screenSize = m_surface->screen()->size();
	//container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
	container->setMinimumSize(QSize(400, 400));
	container->setMaximumSize(screenSize);
	container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	container->setFocusPolicy(Qt::StrongFocus);

	m_surface->setAxisX(new QValue3DAxis);
	m_surface->setAxisY(new QValue3DAxis);
	m_surface->setAxisZ(new QValue3DAxis);
	m_surface->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetIsometricLeft);

	m_data_proxy = new QSurfaceDataProxy();
	m_series = new QSurface3DSeries(m_data_proxy);
	QVBoxLayout* l = new QVBoxLayout();
	m_label = new QLabel();
	l->setMargin(0);
	l->addWidget(m_label);
	l->addWidget(container);
	QHBoxLayout* hbl = new QHBoxLayout();
	hbl->addLayout(l);
	setLayout(hbl);
	QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

	QRadioButton *modeNoneRB = new QRadioButton();
	modeNoneRB->setText(QStringLiteral("No selection"));
	modeNoneRB->setChecked(false);

	QRadioButton *modeItemRB = new QRadioButton();
	modeItemRB->setText(QStringLiteral("Item"));
	modeItemRB->setChecked(false);

	QRadioButton *modeSliceRowRB = new QRadioButton();
	modeSliceRowRB->setText(QStringLiteral("Row Slice"));
	modeSliceRowRB->setChecked(false);

	QRadioButton *modeSliceColumnRB = new QRadioButton();
	modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
	modeSliceColumnRB->setChecked(false);

	QVBoxLayout *selectionVBox = new QVBoxLayout;
	selectionVBox->addWidget(modeNoneRB);
	selectionVBox->addWidget(modeItemRB);
	selectionVBox->addWidget(modeSliceRowRB);
	selectionVBox->addWidget(modeSliceColumnRB);
	selectionVBox->setAlignment(Qt::AlignTop);
	selectionGroupBox->setLayout(selectionVBox);
	hbl->addWidget(selectionGroupBox);

	QObject::connect(modeNoneRB, &QRadioButton::toggled,
					 this, &viewer_3d::toggle_mode_none);
	QObject::connect(modeItemRB, &QRadioButton::toggled,
					 this, &viewer_3d::toggle_mode_item);
	QObject::connect(modeSliceRowRB, &QRadioButton::toggled,
					 this, &viewer_3d::toggle_mode_sliceRow);
	QObject::connect(modeSliceColumnRB, &QRadioButton::toggled,
					 this, &viewer_3d::toggle_mode_sliceColumn);
	modeItemRB->setChecked(true);
}

void viewer_3d::toggle_mode_none()
{
	assert(m_surface != 0);
	m_surface->setSelectionMode(QAbstract3DGraph::SelectionNone);
}

void viewer_3d::toggle_mode_item()
{
	assert(m_surface != 0);
	m_surface->setSelectionMode(QAbstract3DGraph::SelectionItem);
}

void viewer_3d::toggle_mode_sliceRow()
{
	assert(m_surface != 0);
	m_surface->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
								| QAbstract3DGraph::SelectionSlice);
}
void viewer_3d::toggle_mode_sliceColumn()
{
	assert(m_surface != 0);
	m_surface->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
								| QAbstract3DGraph::SelectionSlice);
}

void viewer_3d::fill_data(CLayer* l)
{
	assert(m_label != 0);
	m_label->setText(QString::fromStdString("Layer " + std::to_string(l->id())));
	QSurfaceDataArray *dataArray = new QSurfaceDataArray;
	std::cout << l->height() << std::endl;
	dataArray->reserve(l->height());
	double max_value = 0;
	for (unsigned i = 0; i < l->height(); ++i)
	{
		QSurfaceDataRow *newRow = new QSurfaceDataRow;
		for (unsigned j = 0; j < l->width(); ++j)
		{
			double v = l->get_cell_value(i, j);
			if (max_value < v)
			{
				max_value = v;
			}
			(*newRow) << QVector3D(j, v, i);
	}
		*dataArray << newRow;
	}
	std::cout << dataArray->size() << std::endl;

	m_data_proxy->resetArray(dataArray);


	m_series->setDrawMode(m_draw_mode);
	//m_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
	 //m_series->setFlatShadingEnabled(true);

	m_surface->axisX()->setLabelFormat("%.2f");
	m_surface->axisZ()->setLabelFormat("%.2f");

	m_surface->axisZ()->setRange(0, l->height() - 1);
	m_surface->axisY()->setRange(0, max_value);
	m_surface->axisX()->setRange(0, l->width() - 1);

	m_surface->axisX()->setLabelAutoRotation(30);
	m_surface->axisY()->setLabelAutoRotation(90);
	m_surface->axisZ()->setLabelAutoRotation(30);



	m_surface->addSeries(m_series);
	//    m_series->setColorStyle(Q3DTheme::ColorStyleObjectGradient);

	m_surface->activeTheme()->setType(Q3DTheme::Theme(1));
}

void viewer_3d::set_draw_mode(QSurface3DSeries::DrawFlag df)
{
	assert(m_series != 0);
	m_series->setDrawMode(df);
	m_draw_mode = df;
}


void viewer_3d::set_gradient(QLinearGradient gr)
{
	m_series->setBaseGradient(gr);
	m_series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}
