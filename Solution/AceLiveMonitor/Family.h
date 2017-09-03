#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>

PTR( Family );
PTR( Player );
PTR( Monmotaro );

class Family : public Task {
public:
	static std::string getTag( ) { return "FAMILY"; };
	static FamilyPtr getTask( );
public:
	Family( );
	virtual ~Family( );
public:
	void initialize( );
	void update( );
	PlayerConstPtr getPlayer( int player_id ) const;
	PlayerPtr getPlayer( int player_id );
	int getCameraPosX( ) const;
	MonmotaroConstPtr getMonmotaro( ) const;
private:
	enum STATE {
		STATE_ENTRY,
		STATE_PLAY,
		STATE_CONTINUE
	};


private:
	void updateCameraPos( );
	void updateSettingDevice( );
	void setSynchronousData( ) const;
	bool isSettingDevice( int device_id ) const;
private:
	STATE _state[ MAX_PLAYER ];
	int _setting_device;
	double _camera_pos_x;
	std::array< PlayerPtr, MAX_PLAYER > _player;
	MonmotaroPtr _monmo;
};

