#pragma once

#ifndef POINTSPLAYER_HPP_
#define POINTSPLAYER_HPP_

#include "generate_point.hpp"

#include "marks_plot.hpp"
#include "qwt_plot_picker_ext.hpp"

#include "ui_main_window.h"
#include "ui_points_player.h"

#include <QTimer>
#include <QThread>
#include <QStandardItemModel>

namespace player {

class PointsPlayer : public QWidget, private Ui::PointsPlayer
{
	Q_OBJECT

public:
	explicit PointsPlayer( QWidget* parent = nullptr );
	~PointsPlayer();

	QWidget* azimuthWidget() const;
	QWidget* distanceWidget() const;

private slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_pauseButton_clicked();

	void setupConnections();
	void sliderValueUpdate( MarksPlot* plot, QwtPlotPickerExt* picker );
	void updateMax( MarksPlot* plot, QSpinBox* min, QSpinBox* max );
	void updateMin( MarksPlot* plot, QSpinBox* min, QSpinBox* max );

signals:
	void signalNewPoint();

private:
	void createInfoModel();
	void defaultSettings();
	void drawPoints( const QPointF& point );

	void splitter();
	void spinboxSize();
	void visiblePeriodsUpdate( MarksPlot* plot, QSpinBox* sb );

private:
	int m_rowNumber { 0 };

	QPointF m_currPoint;

	GeneratePoint m_exportPoint;

	MarksPlot* m_plotDistance;
	MarksPlot* m_plotAzimuth;

	QStandardItemModel* m_modelTable;

	QwtPlotCurve m_minDistanceLine;
	QwtPlotCurve m_midDistanceLine;
	QwtPlotCurve m_maxDistanceLine;

	QwtPlotPickerExt* m_pickerAzimuth;
	QwtPlotPickerExt* m_pickerDistance;

	QwtPlotPickerExt* createPicker( MarksPlot* plot );
	std::tuple< MarksPlot*, QwtPlotPickerExt* > createPlot( QWidget* parent, QLabel* coordsLabelX, QLabel* coordsLabelY );
}; // class PointsPlayer

} // namespace player
#endif // ifndef POINTSPLAYER_HPP_
