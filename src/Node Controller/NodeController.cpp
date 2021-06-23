//
// Created by isaac on 19/6/21.
//

#include <tinyxml2.h>
#include "NodeController.h"
#include <nlohmann/json.hpp>

void NodeController::create() {
//    Get xml dir
    char *file = new char[150];
    FILE *doc = popen("zenity --file-selection", "r");
    fgets(file, 150, doc);
    std::string xmldir(file);
    xmldir.pop_back();
    pclose(doc);
//    Get the xml data
    tinyxml2::XMLDocument xml;
    auto error = xml.LoadFile(xmldir.data());
    auto root = xml.FirstChildElement();
    auto socket = root->FirstChildElement();
    while (socket != root->LastChild()) {
        auto *tmpSocket = new Socket_Client;
        //Set the xml data in the Socket and object
        tmpSocket->setPort(socket->FirstChild()->Value());
        DISKS.push_back(tmpSocket);
        socket = socket->NextSiblingElement();
        tmpSocket->Init();
    }
    auto *tmpSocket = new Socket_Client;
    //Set the xml data in the Socket and object
    tmpSocket->setPort(socket->FirstChild()->Value());
    DISKS.push_back(tmpSocket);
    tmpSocket->Init();

//  Init Sockets and wait for connect
    CESocket.Init();
}

void NodeController::Start() {
    while (true) {
        std::string instruction = CESocket.recieve();
        if (instruction == "stop") { break; }
        nlohmann::basic_json<> Json = nlohmann::basic_json<>::parse(instruction);
        if (Json["operation"] == 0) {
            std::string a = Write(instruction);
            CESocket.send("");
        }
        if (Json["operation"] == 1) {
//    Read
            CESocket.send("Readed // msg");
        }
        if (Json["operation"] == 2) {
//    DIR
            CESocket.send("Dir // List");

        }

    }
}

std::string NodeController::Write(std::string &instruction) {
    nlohmann::basic_json<> Json = nlohmann::basic_json<>::parse(instruction);
    std::string data = Json["data"];
    unsigned long int DataSize = data.size();
    int NoDisk = (int) DISKS.size();
    long subDataLength = floor(((double) DataSize / (NoDisk - 1)));
    std::vector<std::string> datas;
    while (NoDisk > 1) {
        datas.push_back(data.substr(0, subDataLength));
        data = data.substr(subDataLength);
        NoDisk--;
    }
    data += std::string("", subDataLength - data.size());
    datas.push_back(data);
    NoDisk--;
    data = "";
    XorBit(datas);


    return std::string();
}

void NodeController::XorBit(std::vector<std::string> &datas) {
    unsigned long size = datas[0].size();
    std::string XOR("", size);
    while (size > 0) {
        char bit = datas[0][size - 1];
        for (int i = 1; i < datas.size(); ++i) {
            bit = (char)(bit ^ datas[i][size - 1]);
        }
        XOR.data()[size-1]=bit;
        size--;
    }
    datas.push_back(XOR);
}

int main() {
    NodeController NODE;
//    a.create();
std::vector<std::string> a;
std::string a1("asd");
std::string b1("QBV");
std::string c1("asd");
std::string d1("asd");
a.push_back(a1);
a.push_back(b1);
a.push_back(c1);
a.push_back(d1);
NODE.XorBit(a);

}