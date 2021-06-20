//
// Created by isaac on 19/6/21.
//

#include "DiskNodes.h"
#include <tinyxml2.h>
void DiskNodes::create() {
//    Get xml dir
    char *file =new char[150];
    FILE *image=popen("zenity --file-selection", "r");
    fgets(file,150,image);
    std::string xmldir(file);
    pclose(image);
//    Get the xml data
    tinyxml2::XMLDocument xml;
    xml.LoadFile(xmldir.data());
    tinyxml2::XMLText* a;
    tinyxml2::XMLText* b;
    a=xml.FirstChildElement()->FirstChildElement("DIR")->FirstChild()->ToText();
    b=xml.FirstChildElement()->FirstChildElement("PORT")->FirstChild()->ToText();
//Set the xml data in the Socket and object
    Socket.setPort(b->Value());
    dir=a->Value();
    xml.Clear();
//    Create a tmp File to use
    Fdata=tmpfile();

}
