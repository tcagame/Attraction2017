#include "ViewerStatus.h"
#include "Drawer.h"
#include "ace_define.h"
#include "SynchronousData.h"
#include "Sound.h"

const int HP_GRAPH_HEIGHT = 16;
const int HP_GRAPH_WIDTH = 8;
const int BUSTUP_OX = 10;
const int BUSTUP_OY = 10;

ViewerStatus::ViewerStatus( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image_frame = drawer->createImage( "UI/status_plate.png" );
	_status_ui = drawer->createImage( "UI/ui.png" );
	_image_bustup[ PLAYER_TAROSUKE ] = drawer->createImage( "UI/ui_bustup_tarosuke.png" );
	_image_bustup[ PLAYER_TAROJIRO ] = drawer->createImage( "UI/ui_bustup_tarojiro.png" );
	_image_bustup[ PLAYER_GARISUKE ] = drawer->createImage( "UI/ui_bustup_garisuke.png" );
	_image_bustup[ PLAYER_TAROMI   ] = drawer->createImage( "UI/ui_bustup_taromi.png"   );
}

ViewerStatus::~ViewerStatus( ) {
}

void ViewerStatus::draw( PLAYER player, int sx, int sy ) const {

	SynchronousDataPtr data( SynchronousData::getTask( ) );

	_image_frame->setPos( sx, sy );
	_image_frame->draw( );
	drawBustup( player, sx, sy );
	drawPower(  data->getStatusPower( player ), sx, sy );
	drawMoney(  data->getStatusMoney( player ), sx, sy );
	drawVirtue( data->getStatusVirtue( player ), sx, sy );
	playSe( player );
}

void ViewerStatus::drawBustup( PLAYER player, int sx, int sy ) const {
	_image_bustup[ player ]->setPos( sx + BUSTUP_OX, sy + BUSTUP_OY );
	_image_bustup[ player ]->draw( );
}

void ViewerStatus::drawPower( int power, int sx, int sy ) const {
	int tw = HP_GRAPH_WIDTH * power;
	_status_ui->setRect( 0, 256, tw, HP_GRAPH_HEIGHT );
	sx += 160;
	sy +=  50;
	_status_ui->setPos( sx, sy );
	_status_ui->draw( );
}

void ViewerStatus::drawMoney( int money,  int sx, int sy ) const {
	sx += 160;
	sy += 105;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawString( sx, sy, "%15d", money );
}

void ViewerStatus::drawVirtue( int virtue, int sx, int sy ) const {
	sx += 280;
	sy += 180;
	DrawerPtr drawer( Drawer::getTask( ) );
	drawer->drawString( sx, sy, "%2d", virtue);
}

void ViewerStatus::playSe( PLAYER player ) const{
	SynchronousDataPtr data =SynchronousData::getTask( );
	SoundPtr sound = Sound::getTask( );
	if ( data->getStatusPower( player ) <= 4 ) {
		if( !sound->isPlayingSE( "yokai_se_02.wav" ) ) {
			sound->playSE( "yokai_se_02.wav" );
		}
	}
	if ( data->getStatusPower( player ) == 0 ) {
		bool stop = true;
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			if ( data->getStatusPower( ( PLAYER ) i ) <= 4 && 
				 player != i &&
				 data->getStatusPower( ( PLAYER ) i ) > 0 ) {
				stop = false;
			}
		}
		if ( stop ) {
			sound->stopSE( "yokai_se_02.wav" );
		}
	}
}