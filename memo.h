#pragma once

void memo()
{
	LoadFile("C:/Users/Admin/source/repos/FileSystem/Data/SimpleData.txt"); // ���� ���
	LoadFile("Data/SimpleData.txt"); // ��� ���

	if (!ifs.good())
	{
		std::cerr << filename << " not found!" << std::endl;
	}

	while (true)
	{
		ifs.get(ch);

		if (ifs.eof())
		{
			std::cerr << "end of file!!" << std::endl;
			break;
		}
		if (ifs.fail())
		{
			std::cerr << "logical error!!" << std::endl;
			break;
		}
		if (ifs.bad())
		{
			std::cerr << "fatal error!!" << std::endl;
			break;
		}
		std::cout << ch;
	}
   // �����ϴ� ��� ������� try catch
	ifs.exceptions(std::ifstream::badbit);

	try
	{
		ifs.open(filename);

		char ch;

		while (ifs.get(ch))
		{
			// std::cout << ch;
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

}