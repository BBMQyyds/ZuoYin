#include "JsonUtils.h"
#include "StringUtils.h"
#include <regex>
#include <string>
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include "json/json.h"

JsonUtils& JsonUtils::operator=(const JsonUtils&){
	return *this;
}

//���ļ�д���ַ���
void JsonUtils::writeFileFromString(const std::string& filename, const std::string& body)
{
	std::ofstream ofile(filename);
	ofile << body;
	ofile.close();
}

//���ļ���ȡ�ַ���
std::string JsonUtils::readFileIntoString(const char* filename)
{
	std::ifstream ifile(filename);
	if (!ifile.is_open()) {
		std::cerr << "�ļ��򿪴���";
	}
	std::ostringstream buf;
	std::string filestr;
	char ch;
	while (buf && ifile.get(ch)) {
		buf.put(ch);
	}
	filestr = buf.str();
	return filestr;
}

//���ļ���ȡ��json::value����
Json::Value JsonUtils::readJsonFile(const std::string& filename)
{
	//���ļ�
	std::ifstream ifile;
	ifile.open(filename);

	//����json����������
	Json::CharReaderBuilder ReaderBuilder;
	//utf-8
	ReaderBuilder["emitUTF8"] = true;

	//json����
	Json::Value root;

	//���ļ�ת��Ϊjson����
	std::string strerr;
	bool ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
	if (!ok) {
		//std::cerr << "json��������";
	}

	//����
	return root;
}

//���ַ�����ȡ��json::value����
Json::Value JsonUtils::readJsonFromString(const std::string& mystr)
{
	//������������
	Json::CharReaderBuilder ReaderBuilder;
	//utf8֧��
	ReaderBuilder["emitUTF8"] = true;
	//����json�Ķ�������
	std::unique_ptr<Json::CharReader> charread(ReaderBuilder.newCharReader());
	//����json����
	Json::Value root;
	//���ַ���ת��Ϊjson����
	std::string strerr;
	bool isok = charread->parse(mystr.c_str(), mystr.c_str() + mystr.size(), &root, &strerr);
	if (!isok || strerr.size() != 0) {
		//std::cerr << "json��������";
	}
	//5.����
	return root;
}

//��json::value����д���ļ�
void JsonUtils::writeJsonFile(const std::string& filename, const Json::Value& root) {
	//дjson�Ĺ�������
	Json::StreamWriterBuilder writebuild;
	//utf8֧��
	writebuild["emitUTF8"] = true;
	//��json����ת��Ϊ�ַ���
	std::string document = Json::writeString(writebuild, root);
	//д���ļ�
	writeFileFromString(filename, document);
}

//PatternsToJson
//��vector<Pattern>ת��Ϊjson::value����
Json::Value JsonUtils::PatternsToJson(std::vector<Pattern>& patterns) {
	Json::Value json;
	Json::Value jpatterns;
	for (int i = 0; i < patterns.size(); i++) {
		Json::Value child;
		child["Pname"] = patterns[i].Pname;
		child["Plocation"] = patterns[i].Plocation;
		Json::Value child2s;
		for (int j = 0; j < patterns[i].xys.size(); j++) {
			Json::Value child2;
			child2["x"] = patterns[i].xys[j].x;
			child2["y"] = patterns[i].xys[j].y;
			child2s.append(child2);
		}
		child["xys"] = child2s;
		jpatterns.append(child);
	}
	json["patterns"] = jpatterns;
	//����
	return json;
}

//PatternsFromJson::value
//��Json::Value����ת��Ϊvector<Pattern>
std::vector<Pattern> JsonUtils::PatternsFromJsonValue(const Json::Value& root) {
	std::vector<Pattern> patterns = {};
	Json::Value jpatterns = root["patterns"];

	for (unsigned int i = 0; i < jpatterns.size(); i++) {
		std::vector<XY> xys = {};
		Json::Value jxys = jpatterns[i]["xys"];

		for (unsigned int j = 0; j < jxys.size(); j++) {
			Json::Value xy = jxys[j];
			xys.push_back(*new XY(xy["x"].asInt(), xy["y"].asInt()));
		}

		patterns.push_back(*new Pattern(xys, jpatterns[i]["Pname"].asString(), jpatterns[i]["Plocation"].asString()));
	}
	return patterns;
}

//LayoutsToJson
//��vector<Layout>ת��ΪJson::Value����
Json::Value JsonUtils::LayoutsToJson(std::vector<Layout>& layouts) {
	Json::Value json;
	Json::Value jlayouts;
	for (int i = 0; i < layouts.size(); i++) {
		Json::Value child;
		child["Lname"] = layouts[i].Lname;
		child["Llocation"] = layouts[i].Llocation;
		Json::Value child2s;
		for (int j = 0; j < layouts[i].xys.size(); j++) {
			Json::Value child2;
			child2["x"] = layouts[i].xys[j].x;
			child2["y"] = layouts[i].xys[j].y;
			child2s.append(child2);
		}
		child["xys"] = child2s;
		jlayouts.append(child);
	}
	json["layouts"] = jlayouts;
	//����
	return json;
}

//LayoutsFromJson::value
//��Json::Value����ת��Ϊvector<Layout>
std::vector<Layout> JsonUtils::LayoutsFromJsonValue(const Json::Value& root) {
	std::vector<Layout> layouts = {};
	Json::Value jlayouts = root["layouts"];

	for (unsigned int i = 0; i < jlayouts.size(); i++) {
		std::vector<XY> xys = {};
		Json::Value jxys = jlayouts[i]["xys"];

		for (unsigned int j = 0; j < jxys.size(); j++) {
			Json::Value xy = jxys[j];

			xys.push_back(*new XY(xy["x"].asInt(), xy["y"].asInt()));
		}
		layouts.push_back(*new Layout(xys, jlayouts[i]["Lname"].asString(), jlayouts[i]["Llocation"].asString()));
	}
	return layouts;
}

ReceiveDataFromPlayer JsonUtils::ReceiveDataFromPlayerFromJsonValue(const Json::Value& root)
{
	Json::Value jcommand = root["command"];
	std::string degree = jcommand["degree"].asString();
	std::string type = jcommand["type"].asString();
	int x = jcommand["x"].asInt();
	int y = jcommand["y"].asInt();
	Command command = *new Command(type, x, y, degree);

	Json::Value jqizis = root["qizis"];
	std::vector<XY> qizis = {};
	for (unsigned int i = 0; i < jqizis.size(); i++) {
		Json::Value xy = jqizis[i];
		qizis.push_back(*new XY(xy["x"].asInt(), xy["y"].asInt()));
	}

	Json::Value jlayout_attribute = root["layout_attribute"];
	std::string name = jlayout_attribute["name"].asString();
	std::string location = jlayout_attribute["location"].asString();
	int index = jlayout_attribute["index"].asInt();
	LayoutAttribute layout_attribute = *new LayoutAttribute(name, location, index);


	return *new ReceiveDataFromPlayer(command, qizis, layout_attribute);
}

ReceiveDataFromSetter JsonUtils::ReceiveDataFromSetterFromJsonValue(const Json::Value& root)
{
	Json::Value jqizis = root["qizis"];
	std::vector<XY> qizis = {};
	for (unsigned int i = 0; i < jqizis.size(); i++) {
		Json::Value xy = jqizis[i];
		qizis.push_back(*new XY(xy["x"].asInt(), xy["y"].asInt()));
	}

	std::string type = root["type"].asString();

	return *new ReceiveDataFromSetter(qizis, type);
}

std::string JsonUtils::BackDataToString(BackData* data)
{
	Json::Value root;
	if (typeid(*data) == typeid(FlushBackData)) {
		FlushBackData* fdata = dynamic_cast<FlushBackData*>(data);
		//����
		root["type"] = fdata->type;
		//����
		Json::Value jxys;
		for (int i = 0; i < fdata->xys.size(); i++) {
			Json::Value jxy;
			jxy["x"] = fdata->xys[i].x;
			jxy["y"] = fdata->xys[i].y;
			jxys.append(jxy);
		}
		root["xys"] = jxys;
		//��������
		Json::Value jlayout_attribute;
		jlayout_attribute["name"] = fdata->layout_attribute.name;
		jlayout_attribute["location"] = fdata->layout_attribute.location;
		jlayout_attribute["index"] = fdata->layout_attribute.index;
		root["layout_attribute"] = jlayout_attribute;

	}
	else if (typeid(*data) == typeid(TipBackData)) {
		TipBackData* tdata = dynamic_cast<TipBackData*>(data);
		//����
		root["type"] = tdata->type;
		//��ʾ
		Json::Value jxys;
		for (int i = 0; i < tdata->xys.size(); i++) {
			Json::Value jxy;
			jxy["x"] = tdata->xys[i].x;
			jxy["y"] = tdata->xys[i].y;
			jxys.append(jxy);
		}
		root["xys"] = jxys;
	}
	else if (typeid(*data) == typeid(LuoziBackData)) {
		LuoziBackData* ldata = dynamic_cast<LuoziBackData*>(data);
		//����
		root["type"] = ldata->type;
		//����
		Json::Value jxy;
		jxy["x"] = ldata->xy.x;
		jxy["y"] = ldata->xy.y;
		root["xy"] = jxy;
	}
	else {
		//����
		root["type"] = data->type;
	}

	//json����
	Json::StreamWriterBuilder writebuild;
	//utf8
	writebuild["emitUTF8"] = true;
	//����
	std::string json = Json::writeString(writebuild, root);
	json = StringUtils::getInstance().replace_all(json, "\n", "");
	json = StringUtils::getInstance().replace_all(json, "\t", "");
	json = StringUtils::getInstance().replace_all(json, " ", "");
	return json;
}
