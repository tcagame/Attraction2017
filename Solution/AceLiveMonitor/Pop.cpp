#include "Pop.h"
#include "ace_define.h"
#include "Family.h"

static const int POP_INTERVAL_COUNT = 600;
static const int MAX_PAGE = SCREEN_WIDTH / GRAPH_SIZE;

Pop::Pop( const Vector& pos ) :
_pos( pos ),
_count( POP_INTERVAL_COUNT ) {
}

Pop::~Pop( ) {
}

void Pop::update( ) {
	if ( _count > POP_INTERVAL_COUNT ) {
		if ( isInScreen( ) ) {
			//�G�l�~�[���o��������
			create( );
			_count = 0;
		}
	}
	_count++;
}

bool Pop::isInScreen( ) const {
	bool result = true;
	//�G�l�~�[�̈ʒu
	int enemy_page = ( ( int )_pos.x - ( int )Family::getTask( )->getCameraPos( ) ) / GRAPH_SIZE;
	//�G�l�~�[����ʊO�ɂ��邩�ǂ���
	if ( enemy_page < 0 ||
		 enemy_page > MAX_PAGE ) {
		result = false;
	}
	return result;
}

Vector Pop::getPos( ) const {
	return _pos;
}
