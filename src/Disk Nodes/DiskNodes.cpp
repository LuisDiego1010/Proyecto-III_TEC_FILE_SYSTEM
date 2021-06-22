//
// Created by isaac on 19/6/21.
//

#include "DiskNodes.h"
#include <tinyxml2.h>
#include <cmath>
#include <iostream>
#include <sys/stat.h>
#include <cmath>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Parity.h"
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
    mkdir(dir.data(),0777);
    xml.Clear();
//    Init Socket and wait for connect
    Socket.Init();
}

void DiskNodes::Write(std::string& msg) {
    nlohmann::basic_json<> Json=nlohmann::basic_json<>::parse(msg);

    std::string towrite=Json["data"];
    std::string name=Json["name"];
    unsigned long int size=towrite.size();
    std::map<std::string,int> metadata;
    int bloks=std::ceil((float)size/(float)BlockSize-1);
    for (int i = 0; i <= bloks; ++i) {
        if(i==bloks){
            metadata[name+std::to_string(i)]=(int)size;
            break;
        }
        metadata[name+std::to_string(i)]=BlockSize;
        size-=BlockSize-1;
    }
    size=0;
    for (const auto&[key, value]:metadata) {
        std::string tmp=towrite.substr(size*BlockSize,BlockSize);
        tmp= parityGenerator(tmp);
        std::ofstream out(key+".txt");
        out.seekp(BlockSize-value);
        out.write(tmp.data(),tmp.size());
        size++;
    }
}

void DiskNodes::Start(){
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
int main(){
    nlohmann::basic_json<> Json;
    Json["data"]=std::string("En algun lugar de la mancha cuyo nombre no puedo recordar, Se encontraba Don Quijote, o algo asi, no recuerdo como empezaba el libro ya");
    Json["name"]=std::string("test");
    DiskNodes test;
    test.dir="test/";
    std::string a=to_string(Json);
    test.Write(a);
//    DiskNodes::Start();
}