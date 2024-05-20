#include "generate_point.hpp"
#include <QDebug>
#include <QThread>


GeneratePoint::GeneratePoint( QObject* parent ) :
	QThread  { parent },
	m_running{ false }
{}


GeneratePoint::~GeneratePoint()
{
	m_running = false;
    wait();
    quit();
}


void GeneratePoint::commandFromUI()
{
	start();
}


void GeneratePoint::run()
{
    qDebug() << "GeneratePoint thread: " << QThread::currentThread();
	while ( m_running ) {
		m_mutex.lock();
		m_point.setX( rand() % 100 );
		m_point.setY( rand() % 100 );
		m_mutex.unlock();
		emit signalPoint( m_point );
        QThread::sleep( 1 );
	}
} // GeneratePoint::run


bool GeneratePoint::running() const
{
	return( m_running );
}


void GeneratePoint::setRunning( bool newRunning )
{
	if ( m_running == newRunning ) {
		return;
	}
	m_running = newRunning;
	emit runningChanged();
}


QPointF GeneratePoint::point() const
{
	return( m_point );
}
