#pragma once
#include <string>

class StringHelper
{
public:
	static std::wstring StringToWide(std::string str)
	{
		std::wstring wide_string(str.begin(), str.end());
		return wide_string;
	}

	static std::string GetFileExtension(const std::string& filename)
	{
		size_t off = filename.find_last_of('.');
		if (off == std::string::npos)
		{
			return {};
		}
		return std::string(filename.substr(off + 1));
	}

	static std::string GetDirectoryFromPath(const std::string& filepath)
	{
		size_t off1 = filepath.find_last_of('\\');
		size_t off2 = filepath.find_last_of('/');
		if (off1 == std::string::npos && off2 == std::string::npos)
		{
			return "";
		}
		if (off1 == std::string::npos)
		{
			return filepath.substr(0, off2);
		}
		if (off2 == std::string::npos)
		{
			return filepath.substr(0, off1);
		}

		return filepath.substr(0, max(off1, off2));
	}

	static std::string GetFileNameWithoutExtension(const std::string& filepath)
	{

		size_t slashOff1 = filepath.find_last_of('\\');
		size_t slashOff2 = filepath.find_last_of('/');
		size_t slashOff = (slashOff1 == std::string::npos) ?
			slashOff2 :
			((slashOff2 == std::string::npos) ? slashOff1 : max(slashOff1, slashOff2));

		std::string filenameWithExtension;
		if (slashOff == std::string::npos)
		{
			filenameWithExtension = filepath;
		}
		else
		{
			filenameWithExtension = filepath.substr(slashOff + 1);
		}


		size_t dotOff = filenameWithExtension.find_last_of('.');
		if (dotOff == std::string::npos)
		{

			return filenameWithExtension;
		}
		return filenameWithExtension.substr(0, dotOff);
	}

};

