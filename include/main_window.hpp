#pragma once

#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include "marks_plot.hpp"
#include "points_player.hpp"
#include "qwt_plot_extcurve.hpp"

#include "ui_main_window.h"

namespace player {

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	explicit MainWindow( QMainWindow* parent = nullptr );
	~MainWindow();

private:
	void defaultSettings();
	Q_SLOT void graphDisplay();
	Q_SLOT void connection();

private:
	PointsPlayer m_pointsPlayer;
}; // class MainWindow

} // namespace player
#endif // ifndef MAIN_WINDOW_HPP_
