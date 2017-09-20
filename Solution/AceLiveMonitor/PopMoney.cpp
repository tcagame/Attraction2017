#include "PopMoney.h"
#include "Storage.h"


PopMoney::PopMoney( const Vector& pos, unsigned char type ) :
Pop( pos ),
_type( type ) {
}


PopMoney::~PopMoney( ) {
}

void PopMoney::create( ) {
	Storage::getTask( )->add( ItemPtr( new ItemMoney( getPos( ), _type, AREA_STREET ) ) );
}
