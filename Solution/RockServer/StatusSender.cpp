#include "StatusSender.h"
#include "Device.h"
#include "Application.h"
#include "Server.h"

const int RESET_TIME = 15;//���̂����폜����


StatusSenderPtr StatusSender::getTask( ) {
	return std::dynamic_pointer_cast< StatusSender >( Application::getInstance( )->getTask( getTag( ) ) );
}

StatusSender::StatusSender( StatusPtr status ) :
_status( status ) {
}


StatusSender::~StatusSender( ) {
}

void StatusSender::update( ) {
	ServerPtr server( Server::getTask( ) );
	DevicePtr device( Device::getTask( ) );
	for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
		_status->getPlayer( i ).device_x = device->getDirX( i );
		_status->getPlayer( i ).device_y = device->getDirY( i );
		_status->getPlayer( i ).device_button = device->getButton( i );
	}

	updateFamily( );

	Server::getTask( )->sendUdp( _status );
	server->sendUdp( _status );
}

void StatusSender::updateFamily( ) {
	bool is_result = true;
	for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
		Status::Player player = _status->getPlayer( i );
		//�{�^�����Z�b�g
		if ( player.device_button == 15 ) {
			_reset_count[ i ]++;
		} else {
			_reset_count[ i ] = 0;
		}
		if ( _reset_count[ i ] > RESET_TIME &&
			 player.area != AREA_WAIT ) {
			_status->resetPlayer( i );
			player.area = AREA_WAIT;
		}
		//���U���g���f
		if ( player.area == AREA_RESULT ) {
			is_result = false;
		}
		// �X�s�[�h�_�E������
		if ( player.area == AREA_WAIT ||
			 player.area == AREA_ENTRY || 
			 player.area == AREA_RESULT ) {
			if ( player.item & SPEED_DOWN ) {
				player.item ^= SPEED_DOWN;
			}
		}
		// ����
		if ( player.power == 0 ) {
			//�@�n�[�g�L�@�����@�c�q��
			if ( player.item & ITEM_HEART &&
				 !( player.item & ITEM_DANGO ) ) {
				player.power = MAX_POWER;
				player.item ^= ITEM_HEART;
			}
			//�@�c�q�L
			if ( player.item & ITEM_DANGO ) {
				player.power = MAX_POWER / 2;
				player.item ^= ITEM_DANGO;
			}
			//�@�X�s�[�h�_�E������
			if ( player.item & SPEED_DOWN ) {
				player.item ^= SPEED_DOWN;
			}
		}
		_status->getPlayer( i ) = player;
	}
	
	// ���U���g�ֈړ�
	if ( is_result ) {
		for ( int i = 0; i < Status::PLAYER_NUM; i++ ) {
			if ( _status->getPlayer( i ).toku >= TRANSITION_TOKU_NUM ) {
				if ( _status->getPlayer( i ).area == AREA_STREET_3 ) {
					_status->getPlayer( i ).area = AREA_RESULT;
					break;
				}
			}
		}
	}
}

bool StatusSender::setContinueNum( int idx, int num ) {
	if ( idx < 0 || idx >= Status::PLAYER_NUM ) {
		return false;
	}
	_status->getPlayer( idx ).continue_num = num;
	return true;
}

bool StatusSender::setTokuNum( int idx, int num ) {
	if ( idx < 0 || idx >= Status::PLAYER_NUM ) {
		return false;
	}
	_status->getPlayer( idx ).toku = num;
	return true;
}

bool StatusSender::setPower( int idx, int power ) {
	if ( idx < 0 || idx >= Status::PLAYER_NUM ) {
		return false;
	}
	_status->getPlayer( idx ).power = power;
	return true;
}

bool StatusSender::setMoney( int idx, int money ) {
	if ( idx < 0 || idx >= Status::PLAYER_NUM ) {
		return false;
	}
	_status->getPlayer( idx ).money = money;
	return true;
}

bool StatusSender::setItem( int idx, int item ) {
	if ( idx < 0 || idx >= Status::PLAYER_NUM ) {
		return false;
	}
	_status->getPlayer( idx ).item = item;
	return true;
}

bool StatusSender::setArea( int idx, unsigned int area ) {
	if ( idx < 0 || idx >= Status::PLAYER_NUM ) {
		return false;
	}
	_status->getPlayer( idx ).area = area;
	return true;
}
