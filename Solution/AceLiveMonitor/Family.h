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
	void updatePlayer( PLAYER taget );
	void updateCameraPos( );
	void updateEvent( );
	void setSynchronousData( ) const;
	void onEventReddaemon( PLAYER target );
	void onEventFlame( PLAYER target );
	void onEventWood( PLAYER target );
	void onEventMineral( PLAYER target );
	void onEventShop( PLAYER target );
	void onEventRyugu( PLAYER target );
	void onEventLake( PLAYER target );
private:
	double _camera_pos_x;
	std::array< PlayerPtr, MAX_PLAYER > _player;
	MonmotaroPtr _monmo;
	bool _updating_camera;
};

