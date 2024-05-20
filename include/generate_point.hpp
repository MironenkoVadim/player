#ifndef GENERATE_POINT_HPP
#define GENERATE_POINT_HPP

#include <QThread>
#include <QPoint>
#include <QMutex>

class GeneratePoint : public QThread
{
	Q_OBJECT
	Q_PROPERTY( QPointF point READ point CONSTANT FINAL )
	Q_PROPERTY( bool running READ running WRITE setRunning NOTIFY runningChanged FINAL )

public:
	explicit GeneratePoint( QObject* parent = nullptr );

	~GeneratePoint();

	bool running() const;
	QPointF point() const;

	void setRunning( bool newRunning );

public slots:
	void run() override;

	void commandFromUI();

signals:
	void signalPoint( const QPointF& point );
	void runningChanged();

private:
    bool    m_running;
    QPointF m_point;
    QMutex  m_mutex;
}; // class GeneratePoint

#endif // GENERATE_POINT_HPP
