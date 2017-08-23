//
//  Display.hpp
//  QuauticFlow_Display
//
//  Created by 王瀚磊 on 2017/7/17.
//  Copyright © 2017年 王瀚磊. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/thread/mutex.hpp>
#include "Monitor.hpp"

class Display
{
public:
    
    Display(int monitorNumber, float delay_millisec);
    ~Display();
    
    void Start();

	void Close();
    
    bool isComposeUpdate();
    
	bool isClosed();

    cv::Mat getResult();

private:
    
    int index_;
    int monitor_count_;
    bool isComposeUpdate_;
	bool isClosed_;
    
    cv::VideoCapture videoCapture_;
    cv::Mat composeMap;
    boost::array<cv::Mat, 1000> buffer_;
    
    std::vector<boost::shared_ptr<Monitor>> monitors_;
    
    boost::thread update_frame_thread_;
    boost::mutex compose_mutex_;
    
    void UpdateFrameTask();
    
    void ComposeBuffer();
    
};

#endif /* Display_hpp */
