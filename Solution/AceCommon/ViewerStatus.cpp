#include "ViewerStatus.h"
#include "Drawer.h"
#include "ace_define.h"
#include "SynchronousData.h"
#include "Sound.h"

const int HP_GRAPH_HEIGHT = 16;
const int HP_GRAPH_WIDTH = 8;
const int BUSTUP_OX = 20;
const int BUSTUP_OY = 10;
const int NAME_OX = 145;
const int NAME_OY = 5;
const int POWER_OX = 166;
const int POWER_OY = 78;

ViewerStatus::ViewerStatus( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_frame = drawer->createImage( "UI/status_plate.png" );
	_image_bustup[ PLAYER_TAROSUKE ] = drawer->createImage( "UI/ui_bustup_tarosuke.png" );
	_image_bustup[ PLAYER_TAROJIRO ] = drawer->createImage( "UI/ui_bustup_tarojiro.png" );
	_image_bustup[ PLAYER_GARISUKE ] = drawer->createImage( "UI/ui_bustup_garisuke.png" );
	_image_bustup[ PLAYER_TAROMI   ] = drawer->createImage( "UI/ui_bustup_taromi.png"   );
	_image_name[ PLAYER_TAROSUKE ] = drawer->createImage( "UI/ui_name_tarosuke.png" );
	_image_name[ PLAYER_TAROJIRO ] = drawer->createImage( "UI/ui_name_tarojiro.png" );
	_image_name[ PLAYER_GARISUKE ] = drawer->createImage( "UI/ui_name_garisuke.png" );
	_image_name[ PLAYER_TAROMI   ] = drawer->createImage( "UI/ui_name_taromi.png"   );

	ImagePtr image_power_bit01 = drawer->createImage( "UI/ui_power_bit01.png"   );
	ImagePtr image_power_bit02 = drawer->createImage( "UI/ui_power_bit02.png"   );
	ImagePtr image_power_bit03 = drawer->createImage( "UI/ui_power_bit03.png"   );
	ImagePtr image_power_bit04 = drawer->createImage( "UI/ui_power_bit04.png"   );
	ImagePtr image_power_bit05 = drawer->createImage( "UI/ui_power_bit05.png"   );
	ImagePtr image_power_bit06 = drawer->createImage( "UI/ui_power_bit06.png"   );

	_image_power[  0 ] = image_power_bit01;
	_image_power[  1 ] = image_power_bit01;
	_image_power[  2 ] = image_power_bit02;
	_image_power[  3 ] = image_power_bit02;
	_image_power[  4 ] = image_power_bit03;
	_image_power[  5 ] = image_power_bit03;
	_image_power[  6 ] = image_power_bit04;
	_image_power[  7 ] = image_power_bit04;
	_image_power[  8 ] = image_power_bit05;
	_image_power[  9 ] = image_power_bit05;
	_image_power[ 10 ] = image_power_bit05;
	_image_power[ 11 ] = image_power_bit05;
	_image_power[ 12 ] = image_power_bit06;
	_image_power[ 13 ] = image_power_bit06;
	_image_power[ 14 ] = image_power_bit06;
	_image_power[ 15 ] = image_power_bit06;
}

ViewerStatus::~ViewerStatus( ) {
}

void ViewerStatus::draw( PLAYER player, int sx, int sy ) const {

	SynchronousDataPtr data( SynchronousData::getTask( ) );

	_image_frame->setPos( sx, sy );
	_image_frame->draw( );
	drawBustup( player, sx, sy );
	drawPower( data->getStatusPower( player ), sx, sy );
	drawVirtue( data->getStatusVirtue( player ), sx, sy );
}

void ViewerStatus::drawPower( int power, int sx, int sy ) const {
	for ( int i = 0; i < power; i++ ) {
		_image_power[ i ]->setPos( sx + i * 8 + POWER_OX, sy + POWER_OY );
		_image_power[ i ]->draw( );
	}
}

void ViewerStatus::drawBustup( PLAYER player, int sx, int sy ) const {
	_image_bustup[ player ]->setPos( sx + BUSTUP_OX, sy + BUSTUP_OY );
	_image_bustup[ player ]->draw( );
	_image_name[ player ]->setPos( sx + NAME_OX, sy + NAME_OY );
	_image_name[ player ]->draw( );
}

void ViewerStatus::drawVirtue( int virtue, int sx, int sy ) const {
	sx += 280;
	sy += 180;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawString( sx, sy, "%2d", virtue);
}
