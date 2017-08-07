//
//  BotDriver.hpp
//  MatchingTest
//
//  Created by Itthikorn Aunpanthong on 7/10/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#ifndef BotDriver_hpp
#define BotDriver_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CoreGraphics/CGWindow.h"
#include "ApplicationServices/ApplicationServices.h"

using namespace std;
using namespace cv;

class BotDriver{
    
public:
    string const desktop_directory = "/Users/Akamu/Desktop/";
    string const log_directory = "/Users/Akamu/Desktop/FanPanTae/log/";
    BotDriver(string path="");
    
    bool testMatching(cv::Mat source, cv::Mat target);

    cv::Point findTheImagePoint(string targetPath, bool isQuestion = false, bool useScreenshotFromGlobal=false);
    cv::Point findTheImagePointForAnswer(string targetPath);
    Mat getTemplate(string targetPath, bool isResize = true);
    void setPicturePath(string picturePath);
    double findTheImageMinValue(cv::Mat source, cv::Mat target);

    void setAreaOfInterest(int x, int y, int width, int height);

    static void MatchingMethod( int, void* );
    
private:
    cv::Rect areaOfInterest;   
    int max_Trackbar = 5;

};

#endif /* BotDriver_hpp */
