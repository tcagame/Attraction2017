#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>
#include "ViewerDebug.h"

PTR( Family );
PTR( Player );
PTR( Character );
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
	bool isExistOnEvent( ) const;
	void pushDebugData( ViewerDebug::Data& data ) const;
	bool isModeVirtue( ) const;
	PlayerPtr getOverlappedPlayer( CharacterConstPtr target ) const;
	void setSynchronousData( ) const;
	void call( PlayerPtr player );
private:
	void updatePlayer( PLAYER taget );
	void updateCameraPos( );
	void shiftPos( );
	bool isInScrollRange( ) const;
private:
	int _camera_pos_x;
	std::array< PlayerPtr, MAX_PLAYER > _player;
	bool _updating_camera;
	MonmotaroPtr _monmotaro;
};

