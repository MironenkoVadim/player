#include "qwt_plot_extcurve.hpp"
#include "qwt_series_data_ext.hpp"

#include <qwt/qwt_painter.h>
#include <qwt/qwt_scale_map.h>

#include <memory>

namespace player {

/*!
  Constructor
  \param title Title of the curve
*/
QwtPlotExtCurve::QwtPlotExtCurve( const QwtText& title ) :
	QwtPlotSeriesItem( title )
{
	init();
}


/*!
  Constructor
  \param title Title of the curve
*/
QwtPlotExtCurve::QwtPlotExtCurve( const QString& title ) :
	QwtPlotSeriesItem( QwtText( title ) ),
	m_colorRange     ( 0.0, 1.0 )
{
	init();
	m_colorMap = new QwtLinearColorMap();
}


//! Destructor
QwtPlotExtCurve::~QwtPlotExtCurve()
{
	delete m_colorMap;
}


/*!
  \brief Initialize data members
*/
void QwtPlotExtCurve::init()
{
	setItemAttribute( QwtPlotItem::Legend );
	setItemAttribute( QwtPlotItem::AutoScale );
}


//! \return QwtPlotItem::Rtti_PlotSpectroCurve
int QwtPlotExtCurve::rtti() const
{
	return( QwtPlotItem::Rtti_PlotCurve );
}


/*!
  Initialize data with an array of samples.
  \param samples Vector of points
*/
void QwtPlotExtCurve::setSamples( const QVector< QwtPointExt >& samples )
{
	std::unique_ptr< QwtPointExtSeriesData > qwtSamples
	        = std::make_unique< QwtPointExtSeriesData >( samples );
	setData( qwtSamples.get() );
}


/*!
  Assign a series of samples

  setSamples() is just a wrapper for setData() without any additional
  value - beside that it is easier to find for the developer.

  \param data Data
  \warning The item takes ownership of the data object, deleting
		   it when its not used anymore.
*/
void QwtPlotExtCurve::setSamples(
	QwtSeriesData< QwtPointExt >* data )
{
	setData( data );
}


/*!
  Change the color map

  Often it is useful to display the mapping between intensities and
  colors as an additional plot axis, showing a color bar.

  \param colorMap Color Map

  \sa colorMap(), setColorRange(), QwtColorMap::color(),
	  QwtScaleWidget::setColorBarEnabled(), QwtScaleWidget::setColorMap()
*/
void QwtPlotExtCurve::setColorMap( QwtColorMap* colorMap )
{
	if ( colorMap != m_colorMap ) {
		delete m_colorMap;
		m_colorMap = colorMap;
	}

	legendChanged();
	itemChanged();
}


/*!
   \return Color Map used for mapping the intensity values to colors
   \sa setColorMap(), setColorRange(), QwtColorMap::color()
*/
const QwtColorMap* QwtPlotExtCurve::colorMap() const
{
	return( m_colorMap );
}


/*!
   Set the value interval, that corresponds to the color map

   \param interval interval.minValue() corresponds to 0.0,
				   interval.maxValue() to 1.0 on the color map.

   \sa colorRange(), setColorMap(), QwtColorMap::color()
*/
void QwtPlotExtCurve::setColorRange( const QwtInterval& interval )
{
	if ( interval != m_colorRange ) {
		m_colorRange = interval;

		legendChanged();
		itemChanged();
	}
}


/*!
  Draw a subset of the points

  \param painter Painter
  \param xMap Maps x-values into pixel coordinates.
  \param yMap Maps y-values into pixel coordinates.
  \param canvasRect Contents rectangle of the canvas
  \param from Index of the first sample to be painted
  \param to Index of the last sample to be painted. If to < 0 the
		 series will be painted to its last sample.

  \sa drawDots()
*/
void QwtPlotExtCurve::drawSeries( QPainter* painter,
                                  const QwtScaleMap& xMap, const QwtScaleMap& yMap,
                                  const QRectF& canvasRect, int from, int to ) const
{
	if ( !painter || ( dataSize() <= 0 ) ) {
		return;
	}

	if ( to < 0 ) {
		to = static_cast< int >( dataSize() ) - 1;
	}

	if ( from < 0 ) {
		from = 0;
	}

	if ( from > to ) {
		return;
	}

	drawDots( painter, xMap, yMap, canvasRect, from, to );
} // QwtPlotExtCurve::drawSeries


/*!
  Draw a subset of the points

  \param painter Painter
  \param xMap Maps x-values into pixel coordinates.
  \param yMap Maps y-values into pixel coordinates.
  \param canvasRect Contents rectangle of the canvas
  \param from Index of the first sample to be painted
  \param to Index of the last sample to be painted. If to < 0 the
		 series will be painted to its last sample.

  \sa drawSeries()
*/
void QwtPlotExtCurve::drawDots( QPainter* painter,
                                const QwtScaleMap& xMap, const QwtScaleMap& yMap,
                                const QRectF& canvasRect, int from, int to ) const
{
	if ( !m_colorRange.isValid() ) {
		return;
	}

	const QwtSeriesData< QwtPointExt >* series = data();

	for ( int i = from; i <= to; i++ ) {
		const QwtPointExt sample = series->sample( i );

		double xi = xMap.transform( sample.x() );
		double yi = yMap.transform( sample.y() );

		if ( !canvasRect.contains( xi, yi ) ) {
			continue;
		}

		auto size  = sample.size();
		auto shift = size / 2;
		painter->setPen( QPen( QBrush( QColor::fromHsv( static_cast< int >( sample.color() * 240.0 ), 255, 255 ) ), size ) );
		QwtPainter::drawEllipse( painter, QRectF( xi - shift, yi - shift, size, size ) );
	}
} // QwtPlotExtCurve::drawDots

} // namespace player
