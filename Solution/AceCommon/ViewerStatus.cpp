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
}

ViewerStatus::~ViewerStatus( ) {
}

void ViewerStatus::draw( PLAYER player, int sx, int sy ) const {

	SynchronousDataPtr data( SynchronousData::getTask( ) );

	_image_frame->setPos( sx, sy );
	_image_frame->draw( );
	drawBustup( player, sx, sy );
	drawVirtue( data->getStatusVirtue( player ), sx, sy );
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
