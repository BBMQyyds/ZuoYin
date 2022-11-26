#pragma once
#include <vector>
#include <string>

//����
class XY {
public:
	int x;
	int y;
	XY(int x, int y);
	XY();
	bool equals(XY& xy);
	std::string toString();

	//���ر任������
	XY disposeLocation(int location);
	//���ر任ǰ����
	XY antiDisposeLocation(int location);
	//�����Խ��߷�ת
	void turnOverFront();
	//�ط��Խ��߷�ת
	void turnOverBack();
	//��ת
	void rotate();
	//�����Խ��߷�ת
	void antiTurnOverFront();
	//�淴�Խ��߷�ת
	void antiTurnOverBack();
	//����ת
	void antiRotate();
};

//����+Ȩ��
class XYW {
public:
	XY xy;
	int weight;
	XYW(XY xy, int weight);
	XYW();
};

//ָ��
class Command {
public:
	std::string type;
	int x;
	int y;
	std::string degree;
	Command(std::string& type, int x, int y, std::string& degree);
	Command();
};

//����
class Qipu {
public:
	std::vector<XY> xys;
	Qipu(std::vector<XY>& xys);
	Qipu();
	//���Խ��߷�ת
	void turnOverFront();
	//���Խ��߷�ת
	void turnOverBack();
	//��ת
	void rotate();
};

//����
class Layout : public Qipu {
public:
	std::string Lname;
	std::string Llocation;
	Layout(std::vector<XY>& xys, const std::string& name, const std::string& location);
	Layout();
};

//��������
class LayoutAttribute {
public:
	std::string name;
	std::string location;
	int index;
	LayoutAttribute(const std::string& name, const std::string& location, int index);
	LayoutAttribute();
};

//��ʽ
class Pattern : public Qipu {
public:
	std::string Pname;
	std::string Plocation;
	Pattern(std::vector<XY>& xys, const std::string& name, const std::string& location);
	Pattern();
};

//����
class Qipan {
public:
	std::vector<int> nums;
	int qipan[19][19];
	int opposite;
	Qipan(int(&qipan)[19][19]);
};