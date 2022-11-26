#pragma once
#include <vector>
#include <string>
#include "Class.h"

//��������
class BackData {
public:
	std::string type;
	BackData(std::string type);
	BackData();
	virtual std::string classID();
};

//ˢ������
class FlushBackData : public BackData {
public:
	std::vector<XY> xys;
	LayoutAttribute layout_attribute;
	FlushBackData(std::string type, std::vector<XY>& xys, LayoutAttribute& layout_attribute);
	virtual std::string classID();
};

//��ʾ����
class TipBackData : public BackData {
public:
	std::vector<XY> xys;
	TipBackData(std::string type, std::vector<XY>& xys);
	virtual std::string classID();
};

//��������
class LuoziBackData : public BackData {
public:
	XY xy;
	LuoziBackData(std::string type, XY xy);
	virtual std::string classID();
};