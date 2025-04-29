#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Texture
{
public:
	static void init();
	static sf::Texture* GetTexture(const string& name);

private :
	static void LoadTexture(const string& name, const string& path);
	static map<string, sf::Texture> Textures;
};

