#pragma once
#include <string>

#include "common.h"

using namespace std;

// ---------------------------------------------------------------------||
// Class for getting levels from file and for saving / loading progress ||
// ---------------------------------------------------------------------||

struct LevelData
{
	char brick_table[BRICKS_X][BRICKS_Y] = {}; // the brick array
	int brick_fall_time = 30; // in seconds
	float ball_default_speed = 200.0f; // how fast can ball move
	float plate_default_width = 120.0f; // plate default width
};

struct ProgressData
{
	char stored_level_data[LEVELS] = {}; // level data bytes
	int highscore = 0; // highscore in endless mode
};

class LevelGetter
{
public:
	static LevelData getLevel(int level_id); // returns the level based on its id (negative ids are endless segments)
	static const ProgressData* getProgress(); // returns a const pointer to progress structure
	static void setLevelFlag(int level_id, unsigned char flag_id); // adds a flag (0-7) to level progress
	static bool isFlagSet(int level_id, unsigned char flag_id); // tells if a specific flag in level is on
	static void setEndlessHighscore(int score); // updates highscore from endless mode
	static int getEndlessHighscore(); // returns endless highscore value

	const static string levels_path; // path to level files
	const static string endless_path; // path to endless piece files
	const static string progress_path; // path to progress read/write folder

private:
	static void loadProgress(); // loads level progress
	static void saveProgress(); // saves level progress

	static bool has_progress;
	static ProgressData progress_data; // copy of progress data from file
};
