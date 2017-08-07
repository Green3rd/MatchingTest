//
//  ServiceRunner.hpp
//  MatchingTest
//
//  Created by Itthikorn Aunpanthong on 7/10/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#ifndef ServiceRunner_hpp
#define ServiceRunner_hpp

#include <stdio.h>
#include "BotDriver.hpp"
#include "FileHandler.hpp"

class ServiceRunner{
public:
    void init();
    void run();
private:
    //Configuration
    bool showResult = true;
    
    //Variables
    BotDriver* bot;
    string picturePath;
    int start_index_picture;
    int start_index_1line;
    int start_index_2lines;
    int start_index_3lines;
    string originalQuestionFile;
    
    //Method
    void updateIndex(int bestMatch);
    Mat getImage(string targetPath);
    Mat getTemplate(string targetPath);
    void printMinValue(string name, double minValue);
    bool moveQuestionToTheFolder(string filePath, int fileIndex);
    bool moveAnswerToTheFolder(string filePath,int fileIndex);
    string getBestMatchingFilePath(int bestMatch);
    int getBestMatchingFileIndex(int bestMatch);
    void saveAnswerFile(string imagePath, string choiceNumber);
    void saveLatestIndexToFile();
};

#endif /* ServiceRunner_hpp */
