#include "Exporter.h"
#include "Drawer.h"
#include "ace_define.h"
#include "ImageTarget.h"

const int PROGRESS_WIDTH = 1000;
const int PROGRESS_HEIGHT= 100;
const std::string DIRECTORY = "../Resource/Ace/MapData/Img/";

Exporter::Exporter( DataConstPtr data ) :
_data( data ) {
	DrawerPtr drawer = Drawer::getTask( );
	_image_export = ImageTargetPtr( new ImageTarget );
	_image_export->create( GRAPH_SIZE, GRAPH_SIZE );
	_image_export->save( DIRECTORY + "filename" );
	_image_progress = drawer->createImage( "export/progress.png" );
}


Exporter::~Exporter( ) {
}

void Exporter::start( ) {
	_max = 1000;
	_now = 0;
}

bool Exporter::update( ) {
	_now++;
	return _max > _now;
}

void Exporter::draw( ) {
	int sx = ( SCREEN_WIDTH  - PROGRESS_WIDTH  ) / 2;
	int sy = ( SCREEN_HEIGHT - PROGRESS_HEIGHT ) / 2;

	
	{
		_image_progress->setPos( sx, sy );
		_image_progress->setRect(  0, PROGRESS_HEIGHT, PROGRESS_WIDTH * _now / _max, PROGRESS_HEIGHT );
		_image_progress->draw( );
	}

	{
		_image_progress->setPos( sx, sy );
		_image_progress->setRect(  0, 0, PROGRESS_WIDTH, PROGRESS_HEIGHT );
		_image_progress->draw( );
	}
}


