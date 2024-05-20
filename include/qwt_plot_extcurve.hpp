#pragma once

#ifndef QWT_PLOT_EXTCURVE_HPP_
#define QWT_PLOT_EXTCURVE_HPP_

#include "qwt_point_ext.hpp"

#include <qwt/qwt_plot_seriesitem.h>
#include <qwt/qwt_series_data.h>
#include <qwt/qwt_color_map.h>

namespace player {

/*!
	\brief Curve that displays 3D points as dots, where the z coordinate is
		   mapped to a color.
*/
class QwtPlotExtCurve : public QwtPlotSeriesItem, public QwtSeriesStore< QwtPointExt >
{
public:

	explicit QwtPlotExtCurve( const QString& title = QString() );
	explicit QwtPlotExtCurve( const QwtText& title );

	virtual ~QwtPlotExtCurve();

	virtual int rtti() const override;

	void setSamples( const QVector< QwtPointExt >& );
	void setSamples( QwtSeriesData< QwtPointExt >* );

	void setColorMap( QwtColorMap* );
	const QwtColorMap* colorMap() const;

	void setColorRange( const QwtInterval& );
	QwtInterval& colorRange() const;

	virtual void drawSeries( QPainter*,
	                         const QwtScaleMap& xMap, const QwtScaleMap& yMap,
	                         const QRectF& canvasRect, int from, int to ) const override;

protected:
	virtual void drawDots( QPainter*,
	                       const QwtScaleMap& xMap, const QwtScaleMap& yMap,
	                       const QRectF& canvasRect, int from, int to ) const;

private:
	void init();

	QwtColorMap* m_colorMap;
	QwtInterval  m_colorRange;
}; // class QwtPlotExtCurve

} // namespace player

#endif // ifndef QWT_PLOT_EXTCURVE_HPP_
