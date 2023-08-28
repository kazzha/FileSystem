#pragma once

void memo()
{
	LoadFile("C:/Users/Admin/source/repos/FileSystem/Data/SimpleData.txt"); // 절대 경로
	LoadFile("Data/SimpleData.txt"); // 상대 경로

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
   // 복잡하니 대신 생긴것이 try catch
}