#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Header
{
	int version{ 1 };
	int itemCoutn{};
};

class Monster
{
private:
	std::string mName{};
	int mLevel{};
	int mHP{};
	int mMP{};

public:
	Monster() = default;
	Monster(std::string name, int level, int hp, int mp) : mName{name}, mLevel (level), mHP(hp), mMP(mp)
	{}
	
	void SetName(string name) { mName = name; }
	void SetLevel(int level) { mLevel = level; }
	void SetHP(int hp) { mHP = hp; }
	void SetMP(int mp) { mMP = mp; }

	void ReadText(std::istream& is)
	{
		std::string line;

		try
		{
			std::getline(is, line, ',');
			mName = line;
			std::getline(is, line, ',');
			mLevel = std::stoi(line);
			std::getline(is, line, ',');
			mHP = std::stoi(line);
			std::getline(is, line);
			mMP = std::stoi(line);
		}
		catch (std::exception e)
		{
			std::cerr << "���� ������ �ùٸ��� �ʽ��ϴ�." << endl;
		}
	}

	void WriteText(std::ostream& os)
	{
		os << mName << " ," << mLevel << " ," << mHP << " ," << mMP << endl;
	}

	void WriteBinary(std::ostream& os)
	{
		int nameLen = static_cast<int>(mName.size());
		os.write(reinterpret_cast<char*>(&nameLen), sizeof(int)); //���ڿ��� ���̸� int�� ����
		os.write(mName.c_str(), nameLen); // �׸��� �� ���̸�ŭ ���ڿ� ����
		os.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
		os.write(reinterpret_cast<char*>(&mHP), sizeof(int));
		os.write(reinterpret_cast<char*>(&mMP), sizeof(int));
	}

	void ReadBinary(std::istream& is)
	{
		int nameLen{};
		is.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
		//is.read(reinterpret_cast<char*>(&mName), nameLen);
		is.read(&mName[0], nameLen);
		is.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
		is.read(reinterpret_cast<char*>(&mHP), sizeof(int));
		is.read(reinterpret_cast<char*>(&mMP), sizeof(int));
	}

	/*
	friend std::ostream& operator << (std::ostream& os, Monster m)
	{
		m.WriteText(os);
		m.WriteBinary(os);
		return os;
	}

	friend std::istream& operator >> (std::istream& is, Monster& m)
	{
		m.ReadText(is);
		m.ReadBinary(is);
		return is;
	}
	*/
};

bool LoadFile(const std::string& filename, std::vector<Monster>& monsters)
{
	// file stream
	std::ifstream ifs;

	

	ifs.exceptions(std::ifstream::badbit);

	try
	{
		ifs.open(filename);

		std::string line;
		
		std::getline(ifs, line);
		while (!ifs.eof())
		{
			Monster m;
			m.ReadText(ifs);

			monsters.push_back(m);
			// Pasing(�м�)-split by delimeter �����ڷ� �ɰ���
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
	
	char buffer[1024]; // ũ�� ���� 512 1024
	while (ifs.getline(buffer, 1024))
	{
		std::cout << buffer << std::endl;
	}
	
	*/

}

bool SaveFile(string filename, vector<Monster>& monsters)
{
	std::ofstream ofs;
	ofs.exceptions(std::ofstream::badbit);

	try
	{
		ofs.open(filename);

		ofs << "--- MONSTER DATA ---" << endl;
		for (auto& e : monsters)
		{
			e.WriteText(ofs);
		}
		ofs.close();
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << endl << e.code() << " - " << e.what() << endl;
		ofs.close();
		return false;
	}
	return true;
}
bool SaveFileBinary(string filename, vector<Monster>& monsters)
{
	std::ofstream ostream;

	ostream.exceptions(std::ofstream::badbit);

	try
	{
		ostream.open(filename, std::ofstream::binary);

		Header header{ 1, static_cast<int>(monsters.size()) };
		ostream.write(reinterpret_cast<char*>(& header), sizeof(Header));// or c��Ÿ�� (char*)&header
		for (auto& e : monsters)
		{
			e.WriteBinary(ostream);
		}
		ostream.close();
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << endl << e.code() << " - " << e.what() << endl;
		ostream.close();
	}
	return true;
}

bool LoadFileBinary(string filename, vector<Monster>& monsters)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::badbit);

	try
	{
		ifs.open(filename, std::ifstream::binary);

		Header header;
		ifs.read(reinterpret_cast<char*>(&header), sizeof(Header));
		for (int i = 0; i < header.itemCoutn; i++)
		{
			Monster m;
			m.ReadBinary(ifs);
			monsters.push_back(m);
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << endl << e.code() << " - " << e.what() << endl;
		ifs.close();
		return false;
	}
	
	return true;
}

int main()
{
	std::vector<Monster> monsters;


	// path ( directory or folder, file )
	LoadFile("Data/SimpleData.txt", monsters); 

	for (const auto& e : monsters)
	{
		
	}
	monsters.push_back(Monster("ORC", 15, 15, 15));
	SaveFile("Data/SimpleData_copy.txt", monsters);

	///////////////////////////////////////

	SaveFileBinary("Data/SimpleData.bin", monsters);
	vector<Monster> v;
	LoadFileBinary("Data/SimpleData.bin", v);
}