#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>

class Sprite
{
public:
	std::string n;
	int x;
	int y;
	int w;
	int h;
};

void LoadXML(const char* filename, std::vector<Sprite>& sprites)
{
	sprites.clear();

	std::ifstream file(filename, std::ifstream::binary);
	std::string line;
	std::regex pattern("\"([^\"]*)\"");

	while (!file.eof())
	{
		std::getline(file, line);

		size_t result = line.find("<sprite");
		if (result != std::string::npos) // 못찾으면 npos 값이 들어옴
		{
			std::sregex_iterator current(line.begin(), line.end(), pattern);
			std::sregex_iterator end;

			Sprite s;
			s.n = (*current)[1];
			current++;
			s.x = std::stoi((*current)[1]);
			current++;
			s.y= std::stoi((*current)[1]);
			current++;
			s.w = std::stoi((*current)[1]);
			current++;
			s.h = std::stoi((*current)[1]);

			sprites.push_back(s);
		}
	}
	file.close();
}

void XMLTest()
{
	std::vector<Sprite> sprites;

	LoadXML("Data/mydata.xml", sprites);
}