//
//  FileHandler.cpp
//  FanPanTae
//
//  Created by Itthikorn Aunpanthong on 7/28/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#include "FileHandler.hpp"

void FileHandler::read(){
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    
    else{
        cout << "Unable to open file";
    }
}

string FileHandler::getString(string parameter){
    return getConfigData(parameter);
}

int FileHandler::getInt(string parameter){
    return std::stoi (getConfigData(parameter));
}

string FileHandler::getConfigData(string parameter){
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::size_t found = line.find(parameter);
            if (found == std::string::npos) continue;
            
            found = line.find('=');
            if (found == std::string::npos) continue;
            
            string returnValue = line.substr(found+1);
           // std::cout << parameter<< " found at: " << found+1 <<", return: "<< returnValue << '\n';
            return returnValue;
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file";
    }
    return "";
}

void FileHandler::write(string data){
    ofstream myfile (fileName);
    if (myfile.is_open())
    {
        myfile << data;
        myfile.close();
    }
    else cout << "Unable to open file";
}
/*
 void FileHandler::writeValue(string parameter, string data){
 ofstream myfile (fileName);
 if (myfile.is_open())
 {
 myfile << data << endl;
 myfile.close();
 }
 else cout << "Unable to open file";
 }*/
