// -*- C++ -*-
/**
 *  @file    main.cpp
 *  @details Entry point program
 */

#include "main_window.hpp"
#include <QApplication>

/**
 *  @fn $(fclass)::main
 *  @param argc Command Line Arguments
 *  @param argv Command Line Arguments
 *  @return Call app
 *  @details Entry point program.
 */
int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );

	player::MainWindow mw;
	mw.show();
	app.processEvents();
	return( app.exec() );
} // main


// EOF main.cpp
