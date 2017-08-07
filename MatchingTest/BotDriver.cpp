//
//  BotDriver.cpp
//  MatchingTest
//
//  Created by Itthikorn Aunpanthong on 7/10/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#include "BotDriver.hpp"


BotDriver::BotDriver(string path) {
    setPicturePath(path);
}

void BotDriver::setAreaOfInterest(int x, int y, int width, int height){
    cv::Rect myROI(x,y,width,height);
    areaOfInterest = myROI;
}

void BotDriver::setPicturePath(string path){
  //  desktop_directory = path;
}


double BotDriver::findTheImageMinValue(cv::Mat source, cv::Mat target){
    Mat result;
    int result_cols =  source.cols - target.cols + 1;
    int result_rows = source.rows - target.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    /// Do the Matching and Normalize
    matchTemplate( source, target, result, 1 );// match_method = 1
    /// Localizing the best match with minMaxLoc
    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    return minVal;
}

static int match_method;

bool BotDriver::testMatching(cv::Mat source, cv::Mat target){
    /// Create windows

    if(source.cols < 1) return false;
    if(target.cols < 1) return false;

    /// Source image to display
    Mat img_display;
    source.copyTo( img_display );
    
    /// Create the result matrix
    Mat result;
    int result_cols =  source.cols - target.cols + 1;
    int result_rows = source.rows - target.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    
    /// Do the Matching and Normalize
    matchTemplate( source, target, result, match_method );
    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    cv::Point matchLoc;
    
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    
    cout << "minVal: "<< minVal <<endl;
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    
    //minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }
    
    /// Show me what you got
    cv::Point clickedPoint = cv::Point( (matchLoc.x + target.cols/2) , (matchLoc.y + target.rows/2) );
    circle(img_display, clickedPoint, 15, Scalar( 0, 255, 0 ), -1);
    imwrite(desktop_directory + "test.jpg", img_display );
    return true;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 
void BotDriver::MatchingMethod( int, void* )
{
    /// Source image to display
    Mat img_display;
    img.copyTo( img_display );
    
    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    
    result.create( result_rows, result_cols, CV_32FC1 );
    
    /// Do the Matching and Normalize
    matchTemplate( img, templ, result, match_method );
    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    cv::Point matchLoc;
    
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    
    cout << "minVal: "<< minVal <<endl;
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    
    //minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }
    
    /// Show me what you got
    rectangle( img_display, matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    
    imshow( image_window, img_display );
    imshow( result_window, result );
    
    return;
}
*/
