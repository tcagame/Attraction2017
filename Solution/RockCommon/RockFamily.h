#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"
#include "mathmatics.h"

PTR( RockFamily );
PTR( RockPlayer );
PTR( RockCharacter );
PTR( RockAncestors );
PTR( Status );
PTR( RockBubble );

class RockFamily : public Task {
public:
	static std::string getTag( ) { return "ROCKFAMILY"; };
	static RockFamilyPtr getTask( );
public:
	RockFamily( StatusPtr status, const Vector& base_pos );
	virtual ~RockFamily( );
public:
	void initialize( );
	void update( );
	void resetPos( const Vector& base_pos );
	RockPlayerPtr getPlayer( int id ) const;
	RockBubblePtr getBubble( int id ) const;
	RockAncestorsPtr getAncestors( int id ) const;
	Vector getCameraPos( ) const;
	RockPlayerPtr getOverLappedPlayer( RockCharacterPtr target ) const;
private:
	void updatePlayer( );
	void updateAncestors( );
	void updateBubble( );
	Vector getBeforeCameraPos( ) const;
private:
	std::array< bool, ROCK_PLAYER_NUM > _before_active;
	Vector _base_pos;
	std::array< RockPlayerPtr, ROCK_PLAYER_NUM > _player;
	std::array< RockBubblePtr, ROCK_PLAYER_NUM > _bubble;
	std::array< RockAncestorsPtr, ROCK_PLAYER_NUM > _ancestors;
};

