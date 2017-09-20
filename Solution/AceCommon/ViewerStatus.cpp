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
const int ITEM_OX = 0;
const int ITEM_OY = 162;
const int ITEM_PITCH = 33;
const int VIRTUE_OX = 230;
const int VIRTUE_OY = ITEM_OY;
const int MONEY_OX = 280;
const int MONEY_OY = 127;

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
	
	_image_item[ 0 ] = drawer->createImage( "UI/ui_item_dango.png" );
	_image_item[ 1 ] = drawer->createImage( "UI/ui_item_heart.png" );
	_image_item[ 2 ] = drawer->createImage( "UI/ui_item_hypertrophy.png" );
	_image_item[ 3 ] = drawer->createImage( "UI/ui_item_shortening.png" );
	_image_item[ 4 ] = drawer->createImage( "UI/ui_item_wood.png" );
	_image_item[ 5 ] = drawer->createImage( "UI/ui_item_flame.png" );
	_image_item[ 6 ] = drawer->createImage( "UI/ui_item_mineral.png" );

	_image_virtue = drawer->createImage( "UI/ui_item_virtue.png" );
	_image_virtue_number = drawer->createImage( "UI/ui_virtue_number.png" );
	_image_money_number = drawer->createImage( "UI/ui_money_number.png" );

	_image_item_effect = drawer->createImage( "Effect/impact.png" );
	_image_redo = drawer->createImage( "UI/ui_continue_picture.png" );
}

ViewerStatus::~ViewerStatus( ) {
}

void ViewerStatus::draw( PLAYER player, int sx, int sy ) const {

	SynchronousDataPtr data( SynchronousData::getTask( ) );

	_image_frame->setPos( sx, sy );
	_image_frame->draw( );
	drawBustup( player, sx, sy );
	drawPower( data->getStatusPower( player ), sx, sy );
	drawMoney( data->getStatusMoney( player ), sx, sy );
	drawItem( player, sx, sy );
	drawVirtue( data->getStatusVirtue( player ), sx, sy );
	drawRedo( data->getStatusRedo( player ), sx, sy );
}

void ViewerStatus::drawPower( int power, int sx, int sy ) const {
	for ( int i = 0; i < power; i++ ) {
		_image_power[ i ]->setPos( sx + i * 8 + POWER_OX, sy + POWER_OY );
		_image_power[ i ]->draw( );
	}
}

void ViewerStatus::drawMoney( int money, int sx, int sy ) const {
	int pos = 0;
	do {
		int n = money % 10;
		_image_money_number->setRect( n * 10, 0, 10, 12 );
		_image_money_number->setPos( sx + MONEY_OX - pos * 10, sy + MONEY_OY );
		_image_money_number->draw( );
		money /= 10;
		pos++;
	} while ( money > 0 );
}

void ViewerStatus::drawBustup( PLAYER player, int sx, int sy ) const {
	_image_bustup[ player ]->setPos( sx + BUSTUP_OX, sy + BUSTUP_OY );
	_image_bustup[ player ]->draw( );
	_image_name[ player ]->setPos( sx + NAME_OX, sy + NAME_OY );
	_image_name[ player ]->draw( );
}

void ViewerStatus::drawItem( PLAYER player, int sx, int sy ) const {
	std::array< bool, 8 > item;
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	item[ 0 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_DANGO );
	item[ 1 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_HEART );
	item[ 2 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_HYPERTROPHY );
	item[ 3 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_SHORTENING );
	item[ 4 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_WOOD );
	item[ 5 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_FLAME );
	item[ 6 ] = data->isInProssessionOfStatusItem( player, SynchronousData::ITEM_MINERAL );
	
	for ( int i = 0; i < 7; i++ ) {
		if ( !item[ i ] ) {
			continue;
		}

		int x = sx + ITEM_OX + i * ITEM_PITCH + ( i == 0 ) * 12;
		int y = sy + ITEM_OY;
		_image_item[ i ]->setPos( x, y );
		_image_item[ i ]->draw( );
	}

	int target = -1;
	switch ( data->getStatusProgressType( player ) ) {
	case SynchronousData::PROGRESS_ITEM_DANGO      : target = 0; break;
	case SynchronousData::PROGRESS_ITEM_HEART      : target = 1; break;
	case SynchronousData::PROGRESS_ITEM_HYPERTROPHY: target = 2; break;
	case SynchronousData::PROGRESS_ITEM_SHORTENING : target = 3; break;
	case SynchronousData::PROGRESS_ITEM_WOOD       : target = 4; break;
	case SynchronousData::PROGRESS_ITEM_FLAME      : target = 5; break;
	case SynchronousData::PROGRESS_ITEM_MINERAL    : target = 6; break;
	}

	int count = data->getStatusProgressCount( player );
	if ( target >= 0 ) {
		int x = sx + ITEM_OX + target * ITEM_PITCH + ( target == 0 ) * 12 - 16;
		int y = sy + ITEM_OY - 16;
		int n = count * 13 / 100;
		_image_item_effect->setRect( n % 4 * 128, n / 4 * 128, 128, 128 );
		_image_item_effect->setPos( x, y, x + 64, y + 64 );
		_image_item_effect->draw( );
	}
}

void ViewerStatus::drawVirtue( int virtue, int sx, int sy ) const {
	if ( virtue == 0 ) {
		return;
	}
	
	_image_virtue->setPos( sx + VIRTUE_OX, sy + VIRTUE_OY );
	_image_virtue->draw( );

	_image_virtue_number->setRect( virtue * 32, 0, 32, 32 );
	_image_virtue_number->setPos( sx + VIRTUE_OX + 40, sy + VIRTUE_OY );
	_image_virtue_number->draw( );
}

void ViewerStatus::drawRedo( int redo, int sx, int sy ) const {
	static int count = 0;
	count++;

	for ( int i = 0; i < redo; i++ ) {
		int add = ( int )( sin( PI2 * ( count + i * 10 ) / 160 ) * 10 );
		if ( add < 0 ) {
			add = 0;
		}
		_image_redo->setPos( sx + i * 10 + BUSTUP_OX, sy + BUSTUP_OY + add );
		_image_redo->draw( );
	}
}