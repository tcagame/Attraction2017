#include "Exporter.h"
#include "Drawer.h"
#include "ace_define.h"
#include "ImageTarget.h"
#include "Data.h"
#include "ChipDrawer.h"

const int PROGRESS_WIDTH = 1000;
const int PROGRESS_HEIGHT= 100;
const std::string DIRECTORY = "../Resource/Ace/MapData/Img/";
const int FRONT_HEIGHT_NUM = MAP_HEIGHT - MAP_COVER_HEIGHT;

Exporter::Exporter( DataConstPtr data, ChipDrawerConstPtr chip_drawer ) :
_data( data ),
_chip_drawer( chip_drawer ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_export_front = ImageTargetPtr( new ImageTarget );
	_image_export_back = ImageTargetPtr( new ImageTarget );
	_image_export_front->create( GRAPH_SIZE, GRAPH_SIZE );
	_image_export_back->create( GRAPH_SIZE, GRAPH_SIZE );
	_image_progress = drawer->createImage( "export/progress.png" );
}


Exporter::~Exporter( ) {
}

void Exporter::start( ) {
	_max = _data->getPageNum( );
	_now = 0;
}

bool Exporter::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	{//back
		_image_export_front->clear( );
		drawer->setImageTarget( _image_export_front );
		for( int i = 0; i < MAP_COVER_HEIGHT; i++ ) {
			for ( int j = 0; j <= PAGE_CHIP_WIDTH_NUM; j++ ) {
				int gx = j;
				int gy = i;
				int mx = _now * PAGE_CHIP_WIDTH_NUM + gx;
				if ( mx >= _max * PAGE_CHIP_WIDTH_NUM ) {
					mx -= _max * PAGE_CHIP_WIDTH_NUM;
				}
				int my = gy;
				_chip_drawer->draw( mx, my, gx, gy );
			}
		}
		char buf[ 256 ];
		sprintf_s( buf, "back_%003d", _now );
		std::string filename = buf;
		_image_export_front->save( DIRECTORY + filename );
	}
	{//front
		_image_export_back->clear( );
		drawer->setImageTarget( _image_export_back );
		for ( int i = 0; i < FRONT_HEIGHT_NUM; i++ ) {
			for ( int j = 0; j <= PAGE_CHIP_WIDTH_NUM; j++ ) {
				int gx = j;
				int gy = i + MAP_COVER_HEIGHT;
				int mx = _now * PAGE_CHIP_WIDTH_NUM + gx;
				if ( mx >= _max * PAGE_CHIP_WIDTH_NUM ) {
					mx -= _max * PAGE_CHIP_WIDTH_NUM;
				}
				int my = gy;
				_chip_drawer->draw( mx, my, gx, gy );
			}
		}
		char buf[ 256 ];
		sprintf_s( buf, "front_%003d", _now );
		std::string filename = buf;
		_image_export_back->save( DIRECTORY + filename );
	}
	drawer->setImageTarget( );
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


