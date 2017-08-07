//
//  ServiceRunner.cpp
//  MatchingTest
//
//  Created by Itthikorn Aunpanthong on 7/10/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#include "ServiceRunner.hpp"



void ServiceRunner::init(){
    bot = new BotDriver(picturePath);
    bot->setAreaOfInterest(425,125,425,243);
    picturePath = bot->desktop_directory + "FanPanTae/";
    originalQuestionFile = bot->log_directory+"q.jpg";

    FileHandler *fh = new FileHandler();
    start_index_picture = fh->getInt("start_index_picture");
    start_index_1line = fh->getInt("start_index_1line");
    start_index_2lines = fh->getInt("start_index_2lines");
    start_index_3lines = fh->getInt("start_index_3lines");
}
void ServiceRunner::saveLatestIndexToFile(){
    cout << "Stop the program." << endl;
    cout << "Please set the variables of this program to the following" << endl;
    cout << "-----------ServiceRunner.cpp-----------" << endl;
    cout << "start_index_picture =" << start_index_picture << endl;
    cout << "start_index_1line =" << start_index_1line << endl;
    cout << "start_index_2lines =" << start_index_2lines  << endl;
    cout << "start_index_3lines =" << start_index_3lines << endl;
    cout << "--------------------" << endl;
    
    //Write the data to the config file.
    FileHandler *fh = new FileHandler();
    string newline = "\n";
    string output = "start_index_picture=" + std::to_string(start_index_picture) + newline
    + "start_index_1line=" + std::to_string(start_index_1line) + newline
    + "start_index_2lines=" + std::to_string(start_index_2lines) + newline
    + "start_index_3lines=" + std::to_string(start_index_3lines);
    fh->write(output);
}

void ServiceRunner::run(){
    bool isFirstRound = true;
    cout << "Type 'stop' to exit the program " << endl;
    while(true){
        string inputFromUser;
        cout << "Please enter any text: ";
        cin >> inputFromUser;
        if(inputFromUser == "stop" || inputFromUser == "exit") {
            saveLatestIndexToFile();
            break;
        }
        if(inputFromUser == "stopwithoutsave" || inputFromUser == "notsave") {
            break;
        }
        
        if(isFirstRound){
            cout << "Program Start, read the q.jpg from Log directory." << endl;
            if(showResult)
                cout << "Showing result mode." << endl;
            else
                cout << "Gathering Question mode." << endl;
            isFirstRound = false;
        }
        
        if(showResult){
            if(!bot->testMatching(imread(bot->desktop_directory + "q.jpg"), imread(bot->desktop_directory + "t.jpg"))) continue;
        }else{
            try{
                /// Load image and template
                cv::Mat img = getImage(originalQuestionFile);
                if(img.cols < 1) continue;
                cv::Mat templ = getTemplate(bot->desktop_directory + "FanPanTae/template/template_pic.jpg");
                if(templ.cols < 1) continue;
                
                int maxset = 5;
                double * minValueArray = new double[maxset];
                
                for(int i = 0 ; i < maxset ; i++){
                    string setNumber = "pic";
                    if(i != 0) setNumber = std::to_string(i);
                    string templateName = "/Users/Akamu/Desktop/FanPanTae/template/template_"+setNumber+".jpg";
                    minValueArray[i]  = bot->findTheImageMinValue(img, getTemplate(templateName));
                    printMinValue(setNumber,minValueArray[i]);
                }
                
                double minValue = minValueArray[0];
                int indexOfPicture = 0;
                //Finding the min value
                for(int a = 1; a < maxset; a++ ){
                    if(minValueArray[a] < minValue) {
                        minValue = minValueArray[a];
                        indexOfPicture = a;
                    }
                }
                cout << "The best matching picture is at index "<< indexOfPicture  <<endl;
                imwrite(bot->desktop_directory + "q_crop.jpg",img);
                saveAnswerFile(originalQuestionFile, inputFromUser);
                string filePath = getBestMatchingFilePath(indexOfPicture);
                int fileIndex = getBestMatchingFileIndex(indexOfPicture);
                if(!moveQuestionToTheFolder(filePath, fileIndex))continue;
                if(!moveAnswerToTheFolder(filePath,fileIndex))continue;
                updateIndex(indexOfPicture);
                //Delete the original question file on desktop.
                if (remove(originalQuestionFile.c_str( )) != 0)
                    cout<<"Cannot remove the original file."<<endl;
                
            }catch(...){
                cout << "Exception occurred";
                saveLatestIndexToFile();
            }
                    }
    }

}

void ServiceRunner::saveAnswerFile(string imagePath, string choiceNumber){
    Mat img_full = imread(imagePath, 1 );
    if(img_full.cols <= 0){
        cout << "Cannot read " << imagePath << ". Please check the file name na ja." << endl;
    }

    int value = atoi(choiceNumber.c_str());
    cv::Rect myROI(1200,125,512,52);//x,y,width,height
    
   
    switch (value) {
        case 1:
            myROI.y = 780;
            break;
        case 2:
            myROI.y = 904;
            break;
        case 3:
            myROI.y = 1028;
            break;
        case 4:
            myROI.y = 1160;
            break;
        case 5:
            myROI.y = 1288;
            break;
        case 6:
            myROI.y = 1408;
            break;
        default:
            return;//Cannot convert to number or invalid choice.
            break;
    }
    imwrite(bot->desktop_directory + "a.jpg", img_full(myROI));
}

string ServiceRunner::getBestMatchingFilePath(int bestMatch){
    string filePath = bot->desktop_directory;

    switch(bestMatch){
        case 0:
            filePath += "FanPanTae/Picture/";
            break;
        case 1:
            filePath += "FanPanTae/1Line/";
            break;
        case 2:
            filePath += "FanPanTae/2Lines/";
            break;
        case 3:
            filePath += "FanPanTae/3Lines/";
            break;
        default:
            cout << "Cannot find the folder of index "<< bestMatch <<". The file will be copied in desktop."<<endl;
            break;
    }
    return filePath;
}

int ServiceRunner::getBestMatchingFileIndex(int bestMatch){
    int fileIndex = 0;
    switch(bestMatch){
        case 0:
            fileIndex = start_index_picture;
            break;
        case 1:
            fileIndex = start_index_1line;
            break;
        case 2:
            fileIndex = start_index_2lines;
            break;
        case 3:
            fileIndex = start_index_3lines;
            break;
        default:
            cout << "Cannot find the folder of index "<< bestMatch <<". The file will be copied in desktop."<<endl;
            break;
    }
    return fileIndex;
}

void ServiceRunner::updateIndex(int bestMatch){
    switch(bestMatch){
        case 0:
            ++start_index_picture;
            break;
        case 1:
            ++start_index_1line;
            break;
        case 2:
            ++start_index_2lines;
            break;
        case 3:
            ++start_index_3lines;
            break;
    }
}
bool ServiceRunner::moveAnswerToTheFolder(string filePath,int fileIndex){
    string oldname = bot->desktop_directory + "a.jpg";
    string newname = filePath + "q"+to_string(fileIndex)+"_a.jpg";
    int result;
    result= rename( oldname.c_str() , newname.c_str() );
    if ( result == 0 ){
        //cout << "Copy answer file to " << filePath <<endl;
        return true;
    }
    else{
        cout << "Cannot put the answer file to the correct folder." <<endl;
        return false;
    }
}

bool ServiceRunner::moveQuestionToTheFolder(string filePath, int fileIndex){
    //string oldname = bot->desktop_directory + "q2.html";
    string oldname = bot->desktop_directory + "q_crop.jpg";
    string newname = filePath + "q"+to_string(fileIndex)+".jpg";
    int result;
    result= rename( oldname.c_str() , newname.c_str() );
    if ( result == 0 ){
        cout << "Copied cropped file to " << filePath <<endl;
        return true;
    }
    else{
        cout << "Cannot rename the cropped file."  <<endl;
        return false;
    }
}

void ServiceRunner::printMinValue(string name, double minValue){
    cout << name << ": "<<minValue <<endl;
}

Mat ServiceRunner::getImage(string imagePath){
    Mat returnImage;
    Mat img_full = imread(imagePath, 1 );
    if(img_full.cols <= 0){
        cout << "Cannot read " << imagePath << ". Please check the file name." << endl;
        //throw "Cannot find image";
        return returnImage;
    }
    //Resize the retina screenshot for better performance.
    resize(img_full, returnImage, returnImage.size(), 0.5, 0.5);
    //Cut the image to only point of interest (only question section).
    cv::Rect myROI(425,125,425,243);
    return returnImage(myROI);
}

Mat ServiceRunner::getTemplate(string targetPath){
    Mat returnImage;
    Mat templ_full = imread(targetPath, 1 ) ;
    if(templ_full.cols <= 0){
        cout << "Cannot read " << targetPath << ". Please check the file name." << endl;
        throw "Cannot find template";
    }
    //Resize the retina screenshot for better performance.
    resize(templ_full, returnImage, returnImage.size(), 0.5, 0.5);
    return returnImage;
}


