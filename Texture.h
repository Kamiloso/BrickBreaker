#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

using namespace std;

class Texture
{
public:
	static void init();
	static const sf::Texture* GetTexture(const string& name);
	static sf::Color GetMainColor(const sf::Texture* const_texture_ptr);

private:
	static void LoadTexture(const string& name, const string& path, bool smooth = true);
	static sf::Image ScaleImageBilinear(const sf::Image& src, unsigned newWidth, unsigned newHeight);
	static map<string, sf::Texture> Textures;
};
