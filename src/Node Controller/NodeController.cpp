//
// Created by isaac on 19/6/21.
//

#include <tinyxml2.h>
#include "NodeController.h"
#include <nlohmann/json.hpp>
#include <iostream>

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
            CESocket.send(a);
        }
        if (Json["operation"] == 1) {
            std::string a = Read(instruction);
            CESocket.send(a);
        }
        if (Json["operation"] == 2) {
            std::string a = DISKS[1]->comunicatte(instruction, 1000);
            if (a.empty()) {
                a = DISKS[0]->comunicatte(instruction, 1000);
            }

            CESocket.send(a);

        }

    }
}

std::string NodeController::Write(std::string &instruction) {
    nlohmann::basic_json<> Json = nlohmann::basic_json<>::parse(instruction);
    std::string data = Json["data"];
    unsigned long int DataSize = data.size();
    int NoDisk = (int) DISKS.size();
    int parity = std::rand() % NoDisk;
    long subDataLength = ceil(((double) DataSize / (NoDisk - 1)));
    std::vector<std::string> datas;
    while (NoDisk > 2) {
        datas.push_back(data.substr(0, subDataLength));
        data = data.substr(subDataLength);
        NoDisk--;
    }
    data += std::string("", subDataLength - data.size());
    datas.push_back(data);
    NoDisk--;
    data = "";
    XorBit(datas);
    for(int i = 0; i < DISKS.size()-1; i) {
        Json["flag"] = 0;
        Json["data"] = datas[i];
        if (i >= parity) {
            i++;
            Json["data"] = datas[i-1];
            std::string code = DISKS[i]->comunicatte(to_string(Json));
            nlohmann::basic_json<> verification = nlohmann::basic_json<>::parse(code);
            if (verification["error"] < 0) { std::cout << "error in the writing"; }
            continue;
        }
        std::string code = DISKS[i]->comunicatte(to_string(Json));
        nlohmann::basic_json<> verification = nlohmann::basic_json<>::parse(code);
        if (verification["error"] < 0) { std::cout << "error in the writing"; }
        i++;
    }
    Json["flag"] = 1;
    Json["data"] = datas.back();
    std::string code = DISKS[parity]->comunicatte(to_string(Json));
    nlohmann::basic_json<> verification = nlohmann::basic_json<>::parse(code);
    if (verification["error"] < 0) { std::cout << "error in the writing"; }

    return to_string(Json);
}

void NodeController::XorBit(std::vector<std::string> &datas) {
    unsigned long size = datas[0].size();
    std::string XOR("", size);
    while (size > 0) {
        char bit = datas[0][size - 1];
        for (int i = 1; i < datas.size(); ++i) {
            bit = (char) (bit ^ datas[i][size - 1]);
        }
        XOR.data()[size - 1] = bit;
        size--;
    }
    datas.push_back(XOR);
}

std::string NodeController::Read(std::string &instruction) {
    std::vector<std::string> recievedatas;
    std::vector<std::string> datas;
    std::string parity;
    std::string XOR;
    std::string data;
    int error = -1;
    for (int i = 0; i < DISKS.size(); ++i) {
        std::string tmp = DISKS[i]->comunicatte(instruction, 10000);
        if (tmp == "error1" || tmp == "error2") {
            error = i;
            continue;
        }
        nlohmann::basic_json<> tmpJson = nlohmann::basic_json<>::parse(tmp);
        if (tmpJson["flag"] == 1) {
            parity = tmpJson["data"];
            continue;
        }
        if (tmpJson.contains("error")) {
            if (tmpJson["error"] < 0) {
                int asd = tmpJson["error"];
                error = i;
                continue;
            }
        }
        recievedatas.push_back(tmpJson["data"]);
    }
    if (error != -1) {
        recievedatas.push_back(parity);
        XorBit(recievedatas);
        XOR = recievedatas.back();
        for (int i = 0; i < recievedatas.size() - 2; ++i) {
            if (i == error) {
                datas.push_back(XOR);
            }
            datas.push_back(recievedatas[i]);
        }
    } else {
        for (int i = 0; i < recievedatas.size(); ++i) {
            datas.push_back(recievedatas[i]);
        }
    }


    for (auto &i: datas) {
        data += i;
    }


    return data;
}

int main() {
    NodeController NODE;
    NODE.create();
    NODE.Start();
//std::vector<std::string> a;
//std::string a1("asd");
//std::string b1("QBV");
//std::string c1("asd");
//std::string d1("asd");
//a.push_back(a1);
//a.push_back(b1);
//a.push_back(c1);
//a.push_back(d1);
//NODE.XorBit(a);
//    nlohmann::basic_json<> tmpJson;
//    tmpJson["name"]="Ar";
//    tmpJson["operation"]=2;
//    std::string m=to_string(tmpJson);
//    std::string B= NODE.Read(a);
//    std::string a = NODE.DISKS[1]->comunicatte(m,1000);
//    if(a.empty()){
//        a = NODE.DISKS[0]->comunicatte(m,1000);
//    }
//    nlohmann::basic_json<> tmp = nlohmann::basic_json<>::parse(a);
//    std::vector<std::string> Oldlist=tmp["files"];
//    std::vector<std::string> list;
//    for (const auto& c:Oldlist) {
//        if(c.find(tmpJson["name"])!=std::string::npos){
//            list.push_back(c);
//        }
//    }
//    tmp["files"]=list;
//    m=to_string(tmpJson);

    exit(0);
}