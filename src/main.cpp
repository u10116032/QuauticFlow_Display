//
//  main.cpp
//  QuauticFlow_Display
//
//  Created by 王瀚磊 on 2017/7/17.
//  Copyright © 2017年 王瀚磊. All rights reserved.
//

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "Display.hpp"

int main(int argc, const char * argv[]) {
    
    Display* display = new Display(5,1);
    display->Start();
    
    while(true){
        if(display->isComposeUpdate()){
            cv::imshow("result", (display->getResult()));
            cv::waitKey(1);
        }
    }

    
    
    
//    cv::VideoCapture vc("/Users/halley/Desktop/test.mov");
//    cv::VideoWriter writer;
//    writer.open("/Users/halley/Desktop/result.avi", CV_FOURCC('M', 'J', 'P', 'G'), 60, cv::Size(128,72));
//    vc.set(CV_CAP_PROP_FPS, 120);
//    //vc.set(CV_CAP_PROP_CONVERT_RGB, false);
//    vc.set(CV_CAP_PROP_FRAME_WIDTH, 128);
//    vc.set(CV_CAP_PROP_FRAME_HEIGHT, 72);
//    cv::Mat test;
//    while(true){
//        vc>>test;
//        if(test.empty())
//            break;
//        writer.write(test);
//        cv::imshow("test", test);
//        cv::waitKey(33);
//    }
    
    
    return 0;
}
