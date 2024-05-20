#include "main_window.hpp"

#include <qwt/qwt_picker_machine.h>

namespace player {

PointsPlayer::PointsPlayer( QWidget* parent ) :
	QWidget         ( parent ),
	Ui::PointsPlayer()
{
	setupUi( this );
	spinboxSize();
	splitter();
	defaultSettings();
	createInfoModel();

	setupConnections();

	connect( startButton, &QPushButton::clicked, &m_exportPoint, &GeneratePoint::commandFromUI );
	connect( &m_exportPoint, &GeneratePoint::signalPoint, this,  &PointsPlayer::drawPoints );
    connect( stopButton, &QPushButton::clicked, &m_exportPoint,  &GeneratePoint::quit );
    qDebug() << "MainWindow thread: " << QThread::currentThread();
}


PointsPlayer::~PointsPlayer()
{
	delete m_modelTable;
}


void PointsPlayer::setupConnections()
{
	connect( azimuthMax, QOverload< int >::of( &QSpinBox::valueChanged ), [=]( int i )
	{ updateMax( m_plotAzimuth, azimuthMin, azimuthMax ); } );
	connect( azimuthMin, QOverload< int >::of( &QSpinBox::valueChanged ), [=]( int i )
	{ updateMin( m_plotAzimuth, azimuthMin, azimuthMax ); } );
	connect( distanceMax, QOverload< int >::of( &QSpinBox::valueChanged ), [=]( int i )
	{ updateMax( m_plotDistance, distanceMin, distanceMax ); } );
	connect( distanceMin, QOverload< int >::of( &QSpinBox::valueChanged ), [=]( int i )
	{ updateMin( m_plotDistance, distanceMin, distanceMax ); } );

	connect( plotsBackground, QOverload< int >::of( &QSlider::valueChanged ), [=]
	{ sliderValueUpdate( m_plotAzimuth, m_pickerAzimuth ); } );
	connect( plotsBackground, QOverload< int >::of( &QSlider::valueChanged ), [=]
	{ sliderValueUpdate( m_plotDistance, m_pickerDistance ); } );

	connect( infoTableView->horizontalHeader(), QOverload< int >::of( &QHeaderView::sectionClicked ), [=]( int index ) {
		m_modelTable->sort( infoTableView->horizontalHeader()->sortIndicatorSection(), infoTableView->horizontalHeader()->sortIndicatorOrder() );
	} );
} // PointsPlayer::setupConnections


void PointsPlayer::spinboxSize()
{
	firstLabel->adjustSize();
	secondLabel->adjustSize();

	firstLabel->setMinimumSize( secondLabel->size() );
	secondLabel->setMinimumSize( secondLabel->size() );
} // PointsPlayer::spinboxSize


void PointsPlayer::sliderValueUpdate( MarksPlot* plot, QwtPlotPickerExt* picker )
{
	int sliderVal = plotsBackground->value();
	QBrush brush  = plot->canvasBackground();
	brush.setColor( QColor( sliderVal, sliderVal, sliderVal ) );
	plot->setCanvasBackground( brush );
	if ( sliderVal < 96 ) {
		picker->setRubberBandPen( QColor( Qt::white ) );
		picker->setTrackerPen( QColor( Qt::white ) );
		plot->y0Line()->setPen( QPen( QColor( Qt::white ), 0.5, Qt::SolidLine ) );
	}
	else {
		picker->setRubberBandPen( QColor( Qt::black ) );
		picker->setTrackerPen( QColor( Qt::black ) );
		plot->y0Line()->setPen( QPen( QColor( Qt::black ), 0.5, Qt::SolidLine ) );
	}

	plot->replot();
} // PointsPlayer::sliderValueUpdate


QWidget* PointsPlayer::azimuthWidget() const
{
	return( widgetGrAz );
}


QWidget* PointsPlayer::distanceWidget() const
{
	return( widgetGrDis );
}


void PointsPlayer::visiblePeriodsUpdate( MarksPlot* plot, QSpinBox* sb )
{
	int valueSB = sb->value();

	plot->setAxisScale( MarksPlot::xBottom, 0, valueSB, valueSB / 10 );
	plot->replot();
} // PointsPlayer::visiblePeriodsUpdate


void PointsPlayer::updateMax( MarksPlot* plot, QSpinBox* min, QSpinBox* max )
{
	int maxV = max->value();
	int minV = min->value();
	if ( maxV <= minV ) {
		max->setValue( minV + 1 /*+ 5*/ );
		max->setMinimum( minV );
		min->setMaximum( minV + 1 /*+ 5*/ );
	}
	else {
		max->setMinimum( minV );
	}
	if ( min->value() < 0 ) {
		plot->setAxisScale( MarksPlot::yLeft, min->value(), max->value(), ( max->value() - min->value() ) / 4 );
	}
	else {
		plot->setAxisScale( MarksPlot::yLeft, min->value(), max->value(), ( max->value() - min->value() ) / 5 );
	}
	plot->replot();
} // PointsPlayer::updateMax


void PointsPlayer::updateMin( MarksPlot* plot, QSpinBox* min, QSpinBox* max )
{
	int maxV = max->value();
	int minV = min->value();
	if ( maxV <= minV ) {
		min->setValue( maxV - 1 /*- 5*/ );
		min->setMaximum( maxV );
		max->setMinimum( maxV - 1 /*- 5*/ );
	}
	else {
		min->setMaximum( maxV );
	}

	if ( min->value() < 0 ) {
		plot->setAxisScale( MarksPlot::yLeft, min->value(), max->value(), ( max->value() - min->value() ) / 4 );
	}
	else {
		plot->setAxisScale( MarksPlot::yLeft, min->value(), max->value(), ( max->value() - min->value() ) / 5 );
	}
	plot->replot();
} // PointsPlayer::updateMin


void PointsPlayer::drawPoints( const QPointF& point )
{
	double velocityColor = point.x() / 100.0 + 0.5F;
	double sizeMarks     = point.x() / 10.0;

	m_plotAzimuth->appendPoint( QwtPointExt( point.x(), point.y(), velocityColor, sizeMarks ) );
	m_plotDistance->appendPoint( QwtPointExt( point.x(), point.y(), velocityColor, sizeMarks ) );

	QStandardItem* item_col_00 = new QStandardItem();
	QStandardItem* item_col_01 = new QStandardItem();
	QStandardItem* item_col_02 = new QStandardItem();

	m_rowNumber++;
	item_col_00->setText( QString::number( m_rowNumber ) );
	item_col_01->setText( QString::number( point.x() ) );
	item_col_02->setText( QString::number( point.y() ) );
	m_modelTable->appendRow( QList< QStandardItem* >() << item_col_00 << item_col_01 << item_col_02 );
} // PointsPlayer::drawPoints


void PointsPlayer::createInfoModel()
{
	QStringList horizontal;

	horizontal.append( tr( "№" ) );
	horizontal.append( tr( "X" ) );
	horizontal.append( tr( "Y" ) );

	m_modelTable = new QStandardItemModel;
	m_modelTable->setHorizontalHeaderLabels( horizontal );

	infoTableView->verticalHeader()->setVisible( false );
	infoTableView->setModel( m_modelTable );

	infoTableView->horizontalHeader()->setSortIndicatorShown( true );
	infoTableView->setColumnWidth( 0, infoTableView->fontMetrics().width( horizontal[0] + "WW" ) );
	infoTableView->setColumnWidth( 1, infoTableView->fontMetrics().width( horizontal[1] + "WW" ) );
	infoTableView->setColumnWidth( 2, infoTableView->fontMetrics().width( horizontal[2] + "WW" ) );
	infoTableView->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeMode::Stretch );
} // PointsPlayer::createInfoModel


void PointsPlayer::defaultSettings()
{
	QIcon sicon( ":/icon/play.png" );
	startButton->setIcon( sicon );
	QIcon picon( ":/icon/pause.png" );
	pauseButton->setIcon( picon );
	QIcon stopicon( ":/icon/stop.png" );
	stopButton->setIcon( stopicon );

	auto plotAzimuth = createPlot( widgetAzimuth, azimuthCoordsx, azimuthCoordsy );
	m_plotAzimuth   = std::get< 0 >( plotAzimuth );
	m_pickerAzimuth = std::get< 1 >( plotAzimuth );
	updateMax( m_plotAzimuth, azimuthMin, azimuthMax );
	updateMin( m_plotAzimuth, azimuthMin, azimuthMax );

	auto plotDistance = createPlot( widgetDistance, distanceCoordsx, distanceCoordsy );
	m_plotDistance   = std::get< 0 >( plotDistance );
	m_pickerDistance = std::get< 1 >( plotDistance );
	updateMax( m_plotDistance, distanceMin, distanceMax );
	updateMin( m_plotDistance, distanceMin, distanceMax );

	m_minDistanceLine.attach( m_plotDistance );
	m_midDistanceLine.attach( m_plotDistance );
	m_maxDistanceLine.attach( m_plotDistance );
} // PointsPlayer::defaultSettings


std::tuple< MarksPlot*, QwtPlotPickerExt* > PointsPlayer::createPlot( QWidget* parent, QLabel* coordsLabelX, QLabel* coordsLabelY )
{
	auto plot = new MarksPlot( coordsLabelX, coordsLabelY, parent );
	plot->setMinimumHeight( 1 );
	plot->setMinimumWidth( 1 );

	parent->layout()->addWidget( plot );
	auto picker = createPicker( plot );
	connect( picker, &QwtPlotPickerExt::mouseMoved, [=]( const QPoint& point ) {
		auto p = picker->point( point );
		coordsLabelX->setText( QString::number( p.x(), 'f', 1 ) );
		coordsLabelY->setText( QString::number( p.y(), 'f', 1 ) );
	} );
	// plot->setAxisScale( MarksPlot::xBottom, 0, visiblePeriods->value(), 100 );
	sliderValueUpdate( plot, picker );
	return( std::make_tuple( plot, picker ) );
} // PointsPlayer::createPlot


QwtPlotPickerExt* PointsPlayer::createPicker( MarksPlot* plot )
{
	auto picker = new QwtPlotPickerExt( QwtPlot::xBottom, QwtPlot::yLeft,
	                                    QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
	                                    plot->canvas() );
	picker->setStateMachine( new QwtPickerDragPointMachine() );
	picker->setRubberBand( QwtPicker::CrossRubberBand );
	return( picker );
} // PointsPlayer::createPicker


void PointsPlayer::splitter()
{
	QList< int > splitter = splitter_4->sizes();
	splitter.replace( 1, static_cast< int >( this->height() / 0.99 ) );
	splitter.replace( 0, static_cast< int >( this->height() / 0.01 ) );
	splitter_4->setSizes( splitter );

	QList< int > splitter12 = splitter_1->sizes();
	splitter12.replace( 1, static_cast< int >( this->height() / 0.5 ) );
	splitter12.replace( 0, static_cast< int >( this->height() / 0.5 ) );
	splitter_1->setSizes( splitter12 );
}


void PointsPlayer::on_startButton_clicked()
{
	m_exportPoint.setRunning( true );
}


void PointsPlayer::on_pauseButton_clicked()
{
	m_exportPoint.setRunning( false );
}


void PointsPlayer::on_stopButton_clicked()
{
	m_exportPoint.setRunning( false );

	m_plotAzimuth->clearPoints();
	m_plotDistance->clearPoints();
	m_rowNumber = 0;
	m_modelTable->removeRows( 0, m_modelTable->rowCount() );
}

} // namespace player
