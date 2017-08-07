//
//  FileHandler.hpp
//  FanPanTae
//
//  Created by Itthikorn Aunpanthong on 7/28/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#ifndef FileHandler_hpp
#define FileHandler_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileHandler{
public:
    string fileName = "/Users/Akamu/Desktop/FanPanTae/config/configfile.txt";
    void read();
    void write(string data);
    string getString(string parameter);
    int getInt(string parameter);
    //static void writeValue(string fileName, string parameter, string data);
private:
    string getConfigData(string parameter);
    
};


#endif /* FileHandler_hpp */
