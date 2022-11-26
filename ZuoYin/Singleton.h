#pragma once
#include "TreeNode.h"
#include "FeedbackData.h"
#include "ReceiveData.h"
//����ģʽ��
class Singleton
{
private:
	Singleton() { };
	~Singleton() { };
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
public:

	//��ͷ���
	struct node patternhead;
	//��������
	std::vector<Layout> layouts;
	//��ʽ����
	std::vector<Pattern> patterns;

	static Singleton& getInstance()
	{
		static Singleton instance;
		return instance;
	}

	//������ʽ��
	void buildPatternTree();

	//���¶�ʽ������
	void updateTree(std::vector<XY>& xys);

	//��ת/��ת����
	std::string disposeLocation(int location, Qipu& qipu);

	//����λ��
	int getLocation(std::string& location);

	//����name
	std::string getName(XY xy);

	//�����Ѷ�ָ��
	int getDegree(std::string& degree);

	//������������
	XY getXY(std::vector<XYW>& xyws, int degree);

	//��������
	BackData* disposePlayerData(ReceiveDataFromPlayer& data);

	//��������
	bool disposeSetterData(ReceiveDataFromSetter& data);
};