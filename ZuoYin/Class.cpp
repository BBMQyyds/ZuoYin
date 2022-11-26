#include "Class.h"
#include <iostream>

//����
XY::XY(int x, int y) {
	this->x = x;
	this->y = y;
}

//����
XY::XY()
{
	this->x = -1;
	this->y = -1;
}

//�ж������Ƿ����
bool XY::equals(XY& xy) {
	return xy.x == this->x && xy.y == this->y;
}

//tostring
std::string XY::toString()
{
	return std::to_string(this->x) + "," + std::to_string(this->y);
}

//���Խ��߷�ת
void XY::turnOverFront()
{
	int t = this->x;
	this->x = this->y;
	this->y = t;
}

//��Խ��߷�ת
void XY::turnOverBack()
{
	int t = this->x;
	this->x = 18 - this->y;
	this->y = 18 - t;
}

//��ת
void XY::rotate()
{
	int t = this->x;
	this->x = this->y;
	this->y = 18 - t;
}

//����
void XY::antiTurnOverFront()
{
	int t = this->x;
	this->x = this->y;
	this->y = t;
}

//����
void XY::antiTurnOverBack()
{
	int t = this->x;
	this->x = 18 - this->y;
	this->y = 18 - t;
}

//����
void XY::antiRotate()
{
	int t = this->y;
	this->y = this->x;
	this->x = 18 - t;
}

XY XY::disposeLocation(int location)
{
	XY xy = *new XY(this->x, this->y);
	switch (location)
	{
	case 0:
		break;
	case 1:
		xy.turnOverFront();
		break;
	case 2:
		xy.rotate();
		break;
	case 3:
		xy.rotate();
		xy.turnOverBack();
		break;
	case 4:
		xy.rotate();
		xy.rotate();
		break;
	case 5:
		xy.rotate();
		xy.rotate();
		xy.turnOverFront();
		break;
	case 6:
		xy.rotate();
		xy.rotate();
		xy.rotate();
		break;
	case 7:
		xy.rotate();
		xy.rotate();
		xy.rotate();
		xy.turnOverBack();
		break;
	default:
		break;
	}
	return xy;
}

XY XY::antiDisposeLocation(int location)
{
	XY xy = *new XY(this->x, this->y);
	switch (location)
	{
	case 0:
		break;
	case 1:
		xy.antiTurnOverFront();
		break;
	case 2:
		xy.antiRotate();
		break;
	case 3:
		xy.antiRotate();
		xy.antiTurnOverBack();
		break;
	case 4:
		xy.antiRotate();
		xy.antiRotate();
		break;
	case 5:
		xy.antiRotate();
		xy.antiRotate();
		xy.antiTurnOverFront();
		break;
	case 6:
		xy.antiRotate();
		xy.antiRotate();
		xy.antiRotate();
		break;
	case 7:
		xy.antiRotate();
		xy.antiRotate();
		xy.antiRotate();
		xy.antiTurnOverBack();
		break;
	default:
		break;
	}
	return xy;
}

//����
Command::Command(std::string& type, int x, int y, std::string& degree)
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->degree = degree;
}

//����
Command::Command()
{
	this->type = "null";
	this->x = -1;
	this->y = -1;
	this->degree = "null";
}

//����
Qipu::Qipu(std::vector<XY>& xys)
{
	this->xys = xys;
}

//����
Qipu::Qipu()
{
	this->xys = {};
}

//���Խ��߷�ת
void Qipu::turnOverFront()
{
	for (int i = 0; i < this->xys.size(); i++) {
		xys[i].turnOverFront();
	}
}

//��Խ��߷�ת
void Qipu::turnOverBack()
{
	for (int i = 0; i < this->xys.size(); i++) {
		xys[i].turnOverBack();
	}
}

//˳ʱ����ת
void Qipu::rotate()
{
	for (int i = 0; i < this->xys.size(); i++) {
		xys[i].rotate();
	}
}

//���֣����ף����֣�λ�ã�
Layout::Layout(std::vector<XY>& xys, const std::string& name, const std::string& location)
{
	this->xys = xys;
	this->Lname = name;
	this->Llocation = location;
}

//����
Layout::Layout()
{
	this->xys = {};
	this->Lname = "null";
	this->Llocation = "null";
}

//��ʽ�����ף����֣�λ�ã�
Pattern::Pattern(std::vector<XY>& xys, const std::string& name, const std::string& location)
{
	this->xys = xys;
	this->Pname = name;
	this->Plocation = location;
}

//��ʽ
Pattern::Pattern()
{
	this->xys = {};
	this->Pname = "null";
	this->Plocation = "null";
}

//��������
Qipan::Qipan(int(&qipan)[19][19])
{
	this->nums = {};
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			this->qipan[i][j] = qipan[i][j];
		}
	}
}

LayoutAttribute::LayoutAttribute(const std::string& name, const std::string& location, int index)
{
	this->name = name;
	this->location = location;
	this->index = index;
}

LayoutAttribute::LayoutAttribute()
{
	this->name = "null";
	this->location = "null";
	this->index = -1;
}

XYW::XYW(XY xy, int weight)
{
	this->xy = xy;
	this->weight = weight;
}

XYW::XYW()
{
	this->xy = *new XY(-1, -1);
	this->weight = 0;
}
