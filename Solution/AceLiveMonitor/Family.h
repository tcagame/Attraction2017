#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>
#include "ViewerDebug.h"

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
	bool isExistOnEvent( ) const;
	void pushDebugData( ViewerDebug::Data& data ) const;
	bool isModeVirtue( ) const;
private:
	void updatePlayer( PLAYER taget );
	void updateCameraPos( );
	void setSynchronousData( ) const;
	void shiftPos( );
private:
	double _camera_pos_x;
	std::array< PlayerPtr, MAX_PLAYER > _player;
	MonmotaroPtr _monmo;
	bool _updating_camera;
};

