#include "marks_plot.hpp"
#include "qwt_plot_extcurve.hpp"
#include "qwt_series_data_ext.hpp"

#include <qwt/qwt_painter.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_canvas.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_directpainter.h>
#include <qwt/qwt_plot_layout.h>
#include <qwt/qwt_scale_draw.h>
#include <qwt/qwt_scale_widget.h>
#include <qwt/qwt_symbol.h>

namespace player {

class CurveData : public QwtPointExtSeriesData
{
public:
	CurveData()
	{}

	virtual QRectF boundingRect() const override
	{
		if ( d_boundingRect.width() < 0.0 ) {
			d_boundingRect = qwtBoundingRect( *this );
		}

		return( d_boundingRect );
	}

	inline void append( const QwtPointExt& point )
	{
		d_samples += point;
	}

	void clear()
	{
		d_samples.clear();
		d_samples.squeeze();
		d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
	}
}; // class CurveData


MarksPlot::MarksPlot( QLabel* labelX, QLabel* labelY, QWidget* parent ) :
	QwtPlot( parent )
{
	m_labelX = labelX;
	m_labelY = labelY;
	if ( m_labelX ) { m_labelX->setVisible( false ); }
	if ( m_labelY ) { m_labelY->setVisible( false ); }

	m_directPainter = new QwtPlotDirectPainter( this );

	if ( QwtPainter::isX11GraphicsSystem() ) {
		#if QT_VERSION < 0x050000
		canvas()->setAttribute( Qt::WA_PaintOutsidePaintEvent, true );
		#endif
		canvas()->setAttribute( Qt::WA_PaintOnScreen, true );
	}

	m_curve = new player::QwtPlotExtCurve( "Test Curve" );

	m_curve->setData( new CurveData() );
	m_curve->attach( this );

	m_y0Line = new QwtPlotCurve();
	double x1[2] = { 0, 1000 };
	double y1[2] = { 0, 0 };
	m_y0Line->setSamples( x1, y1, 2 );
	m_y0Line->setPen( QPen( QColor( Qt::black ), 0.5, Qt::SolidLine ) );
	m_y0Line->attach( this );

	auto axisFont = axisWidget( MarksPlot::xBottom )->font();
	axisFont.setPointSize( 8 );
	axisWidget( MarksPlot::yLeft )->setFont( axisFont );
	axisWidget( MarksPlot::xBottom )->setFont( axisFont );

	const QFontMetrics fm( axisWidget( MarksPlot::yLeft )->font() );
	axisScaleDraw( MarksPlot::yLeft )->setMinimumExtent( fm.width( "- 99999" ) );
	axisScaleDraw( MarksPlot::yLeft )->setMinimumExtent( fm.width( "- 99999" ) );
	axisScaleDraw( MarksPlot::yLeft )->setSpacing( 0 );
	axisScaleDraw( MarksPlot::xBottom )->setSpacing( 0 );

	axisWidget( MarksPlot::yLeft )->setMargin( 0 );
	axisWidget( MarksPlot::yLeft )->setSpacing( 0 );
	axisWidget( MarksPlot::xBottom )->setMargin( 0 );
	axisWidget( MarksPlot::xBottom )->setSpacing( 0 );

	plotLayout()->setSpacing( 0 );
	plotLayout()->setCanvasMargin( 0 );
	plotLayout()->setAlignCanvasToScales( true );

	setAutoReplot( false );
}


MarksPlot::~MarksPlot()
{
	delete m_directPainter;
	delete m_curve;
	delete m_y0Line;
}


void MarksPlot::appendPoint( const QwtPointExt& point )
{
	CurveData* curveData = static_cast< CurveData* >( m_curve->data() );
	curveData->append( point );

	const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
	if ( doClip ) {
		const QwtScaleMap xMap = canvasMap( m_curve->xAxis() );
		const QwtScaleMap yMap = canvasMap( m_curve->yAxis() );

		QRegion clipRegion;

		QRect r( 0, 0, static_cast< int >( point.size() + 2 ), static_cast< int >( point.size() + 2 ) );

		const QPointF center = QwtScaleMap::transform( xMap, yMap, point.toPoint() );
		r.moveCenter( center.toPoint() );
		clipRegion += r;

		m_directPainter->setClipRegion( clipRegion );
	}
	replot();
} // MarksPlot::appendPoint


void MarksPlot::clearPoints()
{
	CurveData* curveData = static_cast< CurveData* >( m_curve->data() );
	curveData->clear();

	replot();
}


void MarksPlot::enterEvent( QEvent* event )
{
	if ( m_labelX ) { m_labelX->setVisible( true ); }
	if ( m_labelY ) { m_labelY->setVisible( true ); }
	QWidget::leaveEvent( event );
}


void MarksPlot::leaveEvent( QEvent* event )
{
	if ( m_labelX ) { m_labelX->setVisible( false ); }
	if ( m_labelY ) { m_labelY->setVisible( false ); }
	QWidget::leaveEvent( event );
}

} // namespace player
