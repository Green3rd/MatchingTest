//
//  main.cpp
//  MatchingTest
//
//  Created by Itthikorn Aunpanthong on 2/12/2560 BE.
//  Copyright © 2560 Green3rd. All rights reserved.
//

#include <iostream>
#include "ServiceRunner.hpp"
#include <unistd.h>
using namespace std;

/*
 1. Get the q.png on the log directory.
 2. half the size and crop to the interested area.
 3. Match the cropped image to the template (Picture/1/2/3lines) and find the best map.
 4. copy the cropped image to the matching folder along with the answer (a.jpg on Desktop).
 
 if set the variable showResult = true
 1. Get the q.jpg on Desktop as an image.
 2. Get the t.jpg on Desktop as a template.
 3. Showing the result of mapping t to q and print the matching value on the console.
 */

int main( int argc, char** argv )
{
    cout << "Start OpenCV Version: "<< CV_VERSION <<endl;
    ServiceRunner runner = ServiceRunner();
    runner.init();
    runner.run();
    cout << "Program ended." <<endl;
    return 1;
}

