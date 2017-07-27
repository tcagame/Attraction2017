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

	for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
		int camera_pos = (int)family->getCameraPos();

		PlayerConstPtr player = family->getPlayer( i );
		Vector pos = player->getPos( );
		Chip chip = player->getChip( );
		chip.sx1 -= ( int )family->getCameraPos( );
		chip.sx2 -= ( int )family->getCameraPos( );
		_image[ i ]->setRect( chip.tx, chip.ty, chip.size, chip.size );
		_image[ i ]->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
		_image[ i ]->draw( );
		//デバック用
		DrawerPtr drawer( Drawer::getTask( ) );
		drawer->drawCircle( Vector( player->getPos( ) + Vector( -camera_pos, -chip.size / 2) ), player->getRadius( ) );

		// 妖怪念力のチャージエフェクト
		int charge_count = player->getChargeCount( );
		if ( charge_count > 0 ) {
			Chip charge_chip = player->getChargeChip( );			
			charge_chip.sx1 -= ( int )family->getCameraPos( );
			charge_chip.sx2 -= ( int )family->getCameraPos( );
			{
				_shot->setRect( charge_chip.tx, charge_chip.ty, charge_chip.size, charge_chip.size );
				_shot->setPos( charge_chip.sx1, charge_chip.sy1, charge_chip.sx2, charge_chip.sy2 );
				_shot->draw( );
			}
		}
	}
}
