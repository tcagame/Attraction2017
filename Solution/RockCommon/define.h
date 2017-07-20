#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = ( SCREEN_WIDTH * 9 ) / 16;

const unsigned char STATE_NONE		= 0b00000000;
const unsigned char STATE_ENTRY		= 0b00000001;
const unsigned char STATE_STREET_1	= 0b00000010;
const unsigned char STATE_STREET_2	= 0b00000100;
const unsigned char STATE_STREET_3	= 0b00001000;
const unsigned char STATE_BOSS		= 0b00010000;
const unsigned char STATE_RESULT	= 0b00100000;
