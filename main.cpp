#include <iostream>
#include <fstream>
#include <vector>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:
	Monster(std::string name, int level, int hp, int mp) : mName{name}, mLevel (level), mHP(hp), mMP(mp)
	{}

	friend std::ostream& operator << (std::ostream& os, Monster m)
	{
		os << m.mName << " : " << m.mLevel << " , " << m.mHP << m.mMP;
		return os;
	}
};

bool LoadFile(const std::string& filename, std::vector<Monster>& m)
{
	// file stream
	std::ifstream ifs;

	

	ifs.exceptions(std::ifstream::badbit);

	try
	{
		ifs.open(filename);

		char ch;
		int i{};
		ifs.get(ch);
		while (ch != ',')
		{
			m->mName[i++] = ch;
		}
		i = 0;
		ifs.get(ch);
		while (ch != ',')
		{
			m->mLevel[i++] = ch;
		}

		ifs.close();
	}

	catch (std::ifstream::failure e)
	{
		std::cerr << std::endl << e.code() << " : " << e.what() << std::endl;
		ifs.close();
		return false;
	}
	return true;

	/*
	// file operator
	char ch;
	
	while (ifs >> ch)
	{
		std::cout << ch;
	}
	
	
	while (true)
	{
		ifs >> ch;
		if (ifs.eof()) {
			break;
		}
		std::cout << ch;
	}

	while (true)
	{
		ifs.get(ch);
		std::cout << ch;
	}
	
	char buffer[1024]; // 크기 대충 512 1024
	while (ifs.getline(buffer, 1024))
	{
		std::cout << buffer << std::endl;
	}
	
	*/

}

int main()
{
	std::vector<Monster> monsters;


	// path ( directory or folder, file )
	LoadFile("Data/SimpleData.txt", monsters); 

	for (const auto& e : monsters)
	{
		std::cout << e << std::endl;
	}
}