#pragma once

/*
This header is not meant to be connected to any .cpp file. It stores global essentials and
constants for the project.
*/

// SCREEN CONSTANTS
constexpr int RX = 1280;	// physical screen width (not resolution)
constexpr int RY = 720;		// physical screen height (not resolution)

// SIMPLE STRUCTURES
struct InputData
{
	float mouse_x = 0.0f; // mouse x position
	float mouse_y = 0.0f; // mouse y position

	bool click_left_start = false; // was left button clicked in this frame at least once?
	bool click_left_now = false; // is left mouse button clicked in this exact moment?
	bool click_left = false; // is left button clicked? (the best check for most cases)

	bool space_start = false; // was space clicked in this frame at least once?
	bool space_now = false; // is space clicked in this exact moment?
	bool space = false; // is space clicked? (the best check for most cases)
	
	// Add more if you need it
};
