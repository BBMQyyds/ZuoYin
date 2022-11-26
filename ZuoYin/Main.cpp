#include "Server.h"
#include "JsonUtils.h"
#include "OtherUtils.h"
#include <iostream>
#include "Class.h"
#include "TreeNode.h"
#include "Singleton.h"
#include "StringUtils.h"

int main() {
	
	/*
	//�������ݽṹ
	srand(time(NULL));
	std::vector<Pattern> patterns = {};
	std::vector<Layout> layouts = {};
	for (int i = 0; i < 10; i++) {
		std::vector<XY> xys = {};
		xys.push_back(*new XY(rand() % 3 + 2, rand() % 2 + 2));
		for (int j = 0; j < 10; j++) {
			xys.push_back(*new XY(rand() % 19, rand() % 19));
		}
		if (StringUtils::getInstance().getName(xys[0]) != "error") {
			patterns.push_back(*new Pattern(xys, StringUtils::getInstance().getName(xys[0]), "topleft-right"));
			layouts.push_back(*new Layout(xys, StringUtils::getInstance().getName(xys[0]), "topleft-right"));
		}
	}

	//д�빦��
	JsonUtils::getInstance().writeJsonFile(
		"pattern.json", JsonUtils::getInstance().PatternsToJson(patterns));
	JsonUtils::getInstance().writeJsonFile(
		"layout.json", JsonUtils::getInstance().LayoutsToJson(layouts));
	*/
	
	//��ȡ�ļ�
	Singleton::getInstance().patterns = JsonUtils::getInstance().PatternsFromJsonValue(
		JsonUtils::getInstance().readJsonFile("pattern.json"));
	Singleton::getInstance().layouts = JsonUtils::getInstance().LayoutsFromJsonValue(
		JsonUtils::getInstance().readJsonFile("layout.json"));
	Singleton::getInstance().buildPatternTree();

	//��ӡ
	std::cout << "patternTree ��ʽ��" << std::endl;
	printTreeNode(&Singleton::getInstance().patternhead, "");
	std::cout << "\npatterns ��ʽ����" << std::endl;
	OtherUtils::getInstance().printPatterns(Singleton::getInstance().patterns);
	std::cout << "\nlayouts ��������" << std::endl;
	OtherUtils::getInstance().printLayouts(Singleton::getInstance().layouts);

	//����������
	Server* server = new Server("localhost", 8088);
	//����������
	server->startListen();
	return 0;
}