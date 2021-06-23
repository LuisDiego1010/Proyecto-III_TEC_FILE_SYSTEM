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
#include <dirent.h>
#include "Parity.h"

void DiskNodes::create() {
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

    auto a = xml.FirstChildElement()->FirstChildElement();

//Set the xml data in the Socket and object
    Socket.setPort(a->FirstChild()->Value());
    a = a->NextSiblingElement();
    dir = a->FirstChild()->Value();
    mkdir(dir.data(), 0777);
    xml.Clear();
    count_dir();
//    Init Socket and wait for connect
    Socket.Init();
//    Socket.socket->set(zmq::sockopt::linger, 1000);
}

int DiskNodes::Write(std::string &msg, bool retry) {
    nlohmann::basic_json<> Json = nlohmann::basic_json<>::parse(msg);
    std::string towrite = Json["data"];
    std::string name = Json["name"];
    unsigned long int size = towrite.size();
    std::map<std::string, int> metadata;
    int bloks = std::ceil((float) size / (float) BlockSize - 1);
    if (bloks + elements > DiskSize) {
        return -3;
    }
    for (int i = 0; i <= bloks; ++i) {
        if (i == bloks) {
            metadata[name + std::to_string(i)] = (int) size;
            break;
        }
        metadata[name + std::to_string(i)] = BlockSize;
        size -= BlockSize - 1;
    }
    size = 0;
    for (const auto&[key, value]:metadata) {
        std::string tmp = towrite.substr(size * BlockSize, BlockSize);
        tmp = parityGenerator(tmp);
        std::ofstream out(dir + key + ".txt");
        out.seekp(BlockSize - value);
        out.write(tmp.data(), (long) tmp.size());
        if (out.rdstate() != std::ios_base::goodbit) {
            if (!retry) {
                return -1;
            }
            return DiskNodes::Write(msg, false);

        }
        size++;
    }
    nlohmann::basic_json<> JsonMeta;
    JsonMeta["name"] = name;
    JsonMeta["Nodes"] = metadata;
    JsonMeta["flag"] = Json["flag"];
    std::string tmp = to_string(JsonMeta);
    std::ofstream out(dir + name + ".data");
    out.write(tmp.data(), (long) tmp.size());
    out.seekp((long) tmp.size());
    out.write("\n", 1);
    out.seekp((long) (BlockSize));
    out.write("", 1);
    return 1;
}

void DiskNodes::Start() {
    DiskNodes disk;
    disk.create();
    auto socket = disk.Socket.self;
    while (true) {
        auto a = socket->recieve();
        std::cout << a;
        if (a == "stop") {
            break;
        }
        nlohmann::basic_json<> Json = nlohmann::basic_json<>::parse(a);
        if (Json["operation"] == 0) {
            int error_code = disk.Write(a);
            Json["error"] = error_code;
            Json["data"] = "";
            Json["parity"] = disk.parity;
            Json.erase("data");

            socket->send(to_string(Json));
        } else if (Json["operation"] == 1) {
            std::string StoragedData = disk.Read(a);
            socket->send(StoragedData);
        } else {
            std::string StoragedData = disk.list_dir();
            socket->send(StoragedData);
        }

    }
    exit(0);
}

std::string DiskNodes::Read(std::string &msg) {
    nlohmann::basic_json<> Json = nlohmann::basic_json<>::parse(msg);
    std::string name = Json["name"];
    std::string metadata;
    std::ifstream MetaDataFile(dir + name + ".txt");
    if (!MetaDataFile.good()) {
        Json["error"] = -4;
        return to_string(Json);
    }
    getline(MetaDataFile, metadata);
    nlohmann::basic_json<> Metadata = nlohmann::basic_json<>::parse(metadata);
    std::map<std::string, int> files = Metadata["Nodes"];
    parity=Metadata["flag"];
    std::string TEXT;
    for (const auto&[key, value]:files) {
        std::string tmp("", value + 1);
        std::ifstream in(dir + key + ".txt");
        if (!in.good()) {
            Json["error"] = -5;
            return to_string(Json);
        }
        in.seekg(BlockSize - value);
        in.read(tmp.data(), value + 1);
        tmp = parityChecker(tmp);
        if (tmp.size() != value || tmp == std::string("-2")) {
            Json["error"] = -2;
            return to_string(Json);
        }
        TEXT += tmp;
    }
    Json["data"]=TEXT;
    Json["flag"]=parity;
    return TEXT;
}

void DiskNodes::count_dir() {
    struct dirent **namelist;
    elements = scandir(dir.data(), &namelist, nullptr, alphasort);
    free(namelist);
}

std::string DiskNodes::list_dir() {
    struct dirent **namelist;
    elements = scandir(dir.data(), &namelist, filter, alphasort);
    std::vector<std::string> names;
    while (elements--) {
        names.push_back(std::string(namelist[elements]->d_name));
        free(namelist[elements]);
    }
    free(namelist);
    nlohmann::basic_json<> files;
    files["files"] = names;

    return to_string(files);
}

int DiskNodes::filter(const struct dirent *file) {
    std::string a = file->d_name;
    int value = (a.find(".data") == std::string::npos) ? 0 : 1;
    return value;
}


int main() {
    nlohmann::basic_json<> Json;
    Json["data"] = std::string(
            "En algun lugar de la mancha cuyo nombre \n no puedo recordar, Se encontraba Don Quijote, o algo asi, no recuerdo como empezaba el libro ya");
    Json["name"] = std::string("test");
    Json["name"] = std::string("test");
    Json["flag"] = 0; //Data 0, parity xor 1
    DiskNodes test;
    test.dir = "test/";
    std::string a = to_string(Json);
    test.count_dir();
    auto c = test.list_dir();
    test.Write(a);
    std::cout << test.Read(a);
    if (Json["data"] == test.Read(a)) {
        std::cout << "test estatico de lectura pasado";
    }
    DiskNodes::Start();
}