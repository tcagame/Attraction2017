#pragma once
#include "RockMapBoss.h"
#include <string>

class RockMapBossDrawer {
public:
	RockMapBossDrawer( RockMapBoss::STAGE stage );
	virtual ~RockMapBossDrawer( );
public:
	RockMapBoss::STAGE getStage( ) const;
private:
	void loadStage( const std::string map_filename, const std::string col_filename, const std::string back_ground_filename = "" );
	void loadRoomTree( ); // �{�X����(��)�̂݃��f�����o���o�����������߂̑Ή�
private:
	RockMapBoss::STAGE _stage;
};

