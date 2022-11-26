#pragma once
#include <string>
#include <vector>
#include "Class.h"

class OtherUtils
{
private:
	OtherUtils() { };
	~OtherUtils() { };
	OtherUtils(const OtherUtils&);
	OtherUtils& operator=(const OtherUtils&);
public:
	static OtherUtils& getInstance()
	{
		static OtherUtils instance;
		return instance;
	}

	//��ӡ��ʽ
	void printPatterns(std::vector<Pattern>& qipus);

	//��ӡ����
	void printLayouts(std::vector<Layout>& qipus);

	//��ӡ����
	void printXYs(std::vector<XY>& xys);
};