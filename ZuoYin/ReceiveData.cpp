#include "Class.h"
#include "ReceiveData.h"
#include "Singleton.h"

//���յ����ݣ�������ף����֣���ʽ��
ReceiveDataFromPlayer::ReceiveDataFromPlayer(Command& command, std::vector<XY>& qizis, LayoutAttribute& layout_attribute)
{
	this->command = command;
	this->qizis = qizis;
	this->layout_attribute = layout_attribute;
}

//��������
BackData* ReceiveDataFromPlayer::disposeData()
{
	return Singleton::getInstance().disposePlayerData(*this);
}

//�������������ݣ���ʽ/���֣����ף�
ReceiveDataFromSetter::ReceiveDataFromSetter(std::vector<XY>& qizis, std::string& type)
{
	this->qizis = qizis;
	this->type = type;
}

//��������
void ReceiveDataFromSetter::disposeData()
{
	Singleton::getInstance().disposeSetterData(*this);
}
