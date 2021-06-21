//
// Created by isaac on 19/6/21.
//

#include "DiskNodes.h"
#include <tinyxml2.h>
#include <iostream>

void DiskNodes::create() {
//    Get xml dir
    char *file =new char[150];
    FILE *doc=popen("zenity --file-selection", "r");
    fgets(file,150,doc);
    std::string xmldir(file);
    xmldir.pop_back();
    pclose(doc);
//    Get the xml data
    tinyxml2::XMLDocument xml;
    auto error=xml.LoadFile(xmldir.data());
    auto a=xml.FirstChildElement()->FirstChildElement();

//Set the xml data in the Socket and object
    Socket.setPort(a->FirstChild()->Value());
    a=a->NextSiblingElement();
    dir=a->FirstChild()->Value();
    xml.Clear();
//    Create a tmp File to use
    Fdata=tmpfile();
//    Init Socket and wait for connect
    Socket.Init();
}
int main(){
    DiskNodes disk;
    disk.create();
    auto socket=disk.Socket.self;
    while(true){
        auto a=socket->recieve();
        std::cout<<a;
        if(a=="stop"){
            break;
        }
        socket->send(a+"a");
    }
    exit(0);
}