#include "ViewerFamily.h"
#include "Family.h"
#include "Player.h"
#include "Drawer.h"


ViewerFamily::ViewerFamily( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_image[ 0 ] = drawer->createImage( "Family/tarosuke.png" );
	_image[ 1 ] = drawer->createImage( "Family/tarojiro.png" );
	_image[ 2 ] = drawer->createImage( "Family/garisuke.png" );
	_image[ 3 ] = drawer->createImage( "Family/taromi.png" );
	_shot = drawer->createImage( "Effect/psychic.png" );
}


ViewerFamily::~ViewerFamily( ) {

}

void ViewerFamily::draw( ) const {
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = (int)family->getCameraPos( );

	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		PlayerConstPtr player = family->getPlayer( i );
		Player::STATE state = player->getState( );
		int add_sy = 0;
		int add_sx = 0;
		switch ( state ) {
		case Player::STATE_MAIN:
			add_sy = VIEW_STREET_Y;
			add_sx = -camera_pos;
			break;
		case Player::STATE_EVENT:
			add_sy = VIEW_EVEMT_Y;
			add_sx = 0;
			break;
		}
		Vector pos = player->getPos( );
		Chip chip = player->getChip( );
		chip.sx1 += add_sx;
		chip.sx2 += add_sx;
		chip.sy1 += add_sy;
		chip.sy2 += add_sy;
		_image[ i ]->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image[ i ]->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image[ i ]->draw( );
		// 妖怪念力のチャージエフェクト
		int charge_count = player->getChargeCount( );
		if ( charge_count > 0 ) {
			Chip charge_chip = player->getChargeChip( );			
			charge_chip.sx1 += add_sx;
			charge_chip.sx2 += add_sx;
			charge_chip.sy1 += add_sy;
			charge_chip.sy2 += add_sy;
			{
				_shot->setRect( charge_chip.tx, charge_chip.ty, charge_chip.size, charge_chip.size );
				_shot->setPos( charge_chip.sx1, charge_chip.sy1, charge_chip.sx2, charge_chip.sy2 );
				_shot->draw( );
			}
		}
	}
}
