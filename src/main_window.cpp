#include "main_window.hpp"

namespace player {

MainWindow::MainWindow( QMainWindow* parent ) :
	QMainWindow   ( parent ),
	Ui::MainWindow()
{
	setupUi( this );

	defaultSettings();
	connection();
	pointsTab->layout()->addWidget( &m_pointsPlayer );
	// showMaximized();
}


MainWindow::~MainWindow() = default;


void MainWindow::connection()
{
	connect( actionFirst,  &QAction::triggered, this, &MainWindow::graphDisplay );
	connect( actionSecond, &QAction::triggered, this, &MainWindow::graphDisplay );
	connect( actionExit, &QAction::triggered, this, &QApplication::quit );
} // MainWindow::connection


void MainWindow::graphDisplay()
{
	m_pointsPlayer.azimuthWidget()->setVisible( actionFirst->isChecked() );
	m_pointsPlayer.distanceWidget()->setVisible( actionSecond->isChecked() );
} // MainWindow::graphDisplay


void MainWindow::defaultSettings()
{
	actionFirst->setChecked( true );
	actionSecond->setChecked( true );
	actionExit->setShortcut( static_cast< int >( Qt::CTRL ) +
	                         static_cast< int >( Qt::Key_Q ) );
} // MainWindow::defaultSettings

} // namespace player
