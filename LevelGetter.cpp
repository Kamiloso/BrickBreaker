#include "LevelGetter.h"

#include <fstream>


const string LevelGetter::levels_path = "./InternalData/Levels/Basic/";
const string LevelGetter::endless_path = "./InternalData/Levels/Endless/";
const string LevelGetter::progress_path = "./InternalData/Progress/";

bool LevelGetter::has_progress = false;
ProgressData LevelGetter::progress_data = {};

LevelData LevelGetter::getLevel(int level_id)
{
	string file_name;
	if (level_id >= 0)
		file_name = levels_path + "level_" + to_string(level_id + 1) + ".bbk";
	else
		file_name = endless_path + "segment_" + to_string(-level_id) + ".bbk";

	LevelData construct{};

	ifstream f1;
	f1.open(file_name.c_str(), ios::binary);
	if(f1.is_open())
	{
		for (int y = 0; y < BRICKS_Y; y++)
		{
			for (int x = 0; x < BRICKS_X; x++)
			{
				f1 >> construct.brick_table[x][y];
			}
		}
		f1 >> construct.brick_fall_time;
		f1 >> construct.ball_max_speed;

		if (f1.eof())
		{
			f1.close();
			throw runtime_error("Couldn't load level from file!");
		}
		else
		{
			f1.close();
			return construct;
		}
	}
	else
	{
		throw runtime_error("Couldn't load level from file!");
	}
}

const ProgressData* LevelGetter::getProgress()
{
	loadProgress();

	return &progress_data;
}

void LevelGetter::setLevelFlag(int level_id, unsigned char flag_id)
{
	loadProgress();

	if (flag_id > 7)
		throw invalid_argument("Wrong flag ID!");

	if (level_id < 0 || level_id >= LEVELS)
		throw invalid_argument("Wrong level ID!");

	progress_data.stored_level_data[level_id] |= (1 << flag_id);

	saveProgress();
}

bool LevelGetter::isFlagSet(int level_id, unsigned char flag_id)
{
	loadProgress();

	if (flag_id > 7)
		throw invalid_argument("Wrong flag ID!");

	if (level_id < 0 || level_id >= LEVELS)
		throw invalid_argument("Wrong level ID!");

	return (progress_data.stored_level_data[level_id] & (1 << flag_id)) != 0;
}

void LevelGetter::setEndlessHighscore(int score)
{
	loadProgress();

	progress_data.highscore = score;

	saveProgress();
}

int LevelGetter::getEndlessHighscore()
{
	loadProgress();

	return progress_data.highscore;
}

void LevelGetter::loadProgress()
{
	if (has_progress)
		return; // Don't load if loaded already

	ifstream f1;
	f1.open((progress_path + "progress.bin").c_str(), ios::binary | ios::ate);
	if (f1.is_open())
	{
		streampos file_size = f1.tellg();
		if (file_size == sizeof(progress_data))
		{
			f1.seekg(0, ios::beg);
			f1.read(reinterpret_cast<char*>(&progress_data), sizeof(progress_data));
			has_progress = true;
		}
		f1.close();
	}

	// If wasn't able to load, save empty data to ensure having proper copy
	if (!has_progress)
	{
		saveProgress();
		has_progress = true;
	}
}

void LevelGetter::saveProgress()
{
	ofstream f1;
	f1.open((progress_path + "progress.bin").c_str(), ios::binary);
	if (f1.is_open())
	{
		f1.write(reinterpret_cast<char*>(&progress_data), sizeof(progress_data));
		f1.close();
	}
	else
	{
		throw runtime_error("Couldn't save progress!");
	}
}
