#pragma once
#include <string>
#include "Class.h"

class StringUtils
{
private:
	StringUtils() { };
	~StringUtils() { };
	StringUtils(const StringUtils&);
	StringUtils& operator=(const StringUtils&);
public:
	static StringUtils& getInstance()
	{
		static StringUtils instance;
		return instance;
	}

	//�滻�Ӵ�
	std::string& replace_all(std::string& src, const std::string& old_value, const std::string& new_value);

	//��ȡ
	std::string midstr(std::string& oldstr, std::string startstr, std::string endstr);
};