//
// Created by isaac on 19/6/21.
//

#include <tinyxml2.h>
#include "NodeController.h"

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

//    Init Sockets and wait for connect
    CESocket.Init();
}

int main() {
NodeController a;
a.create();
}