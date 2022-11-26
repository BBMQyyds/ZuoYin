#pragma once
#include "Class.h"
#include "FeedbackData.h"

//�����������
class ReceiveDataFromPlayer {
public:
	Command command;
	std::vector<XY> qizis;
	LayoutAttribute layout_attribute;
	ReceiveDataFromPlayer(Command& command, std::vector<XY>& qizis, LayoutAttribute& layout_attribute);
	//��������
	BackData* disposeData();
};

//����setter����
class ReceiveDataFromSetter {
public:
	std::vector<XY> qizis;
	std::string type;
	ReceiveDataFromSetter(std::vector<XY>& qizis, std::string& type);
	//��������
	void disposeData();
};