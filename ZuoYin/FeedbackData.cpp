#include "Class.h"
#include "FeedbackData.h"

//���������ݣ����ͣ�
BackData::BackData(std::string type)
{
	this->type = type;
}

//����������
BackData::BackData()
{
	this->type = "null";
}

std::string BackData::classID()
{
	return "BackData";
}

//ˢ�·��������ͺ����ף�
FlushBackData::FlushBackData(std::string type, std::vector<XY>& xys, LayoutAttribute& layout_attribute)
{
	this->type = type;
	this->xys = xys;
	this->layout_attribute = layout_attribute;
}

std::string FlushBackData::classID()
{
	return "FlushBackData";
}

//��ʾ���������ͺ���ʾ��
TipBackData::TipBackData(std::string type, std::vector<XY>& xys)
{
	this->type = type;
	this->xys = xys;
}

std::string TipBackData::classID()
{
	return "TipBackData";
}

//���ӷ��������ͺ����꣩
LuoziBackData::LuoziBackData(std::string type, XY xy)
{
	this->type = type;
	this->xy = xy;
}

std::string LuoziBackData::classID()
{
	return "LuoziBackData";
}
