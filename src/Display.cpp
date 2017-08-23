//
//  Display.cpp
//  QuauticFlow_Display
//
//  Created by 王瀚磊 on 2017/7/17.
//  Copyright © 2017年 王瀚磊. All rights reserved.
//

#include "Display.hpp"

Display::Display(int monitor_count, float delay_second)
{
    index_ = 0;
    videoCapture_ = cv::VideoCapture(0);
    //videoCapture_.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    //videoCapture_.set(CV_CAP_PROP_FPS, 60);
    //videoCapture_.set(CV_CAP_PROP_CONVERT_RGB, false);
    //videoCapture_.set(CV_CAP_PROP_FRAME_WIDTH, 128);
    //videoCapture_.set(CV_CAP_PROP_FRAME_HEIGHT, 72);
    monitor_count_ = monitor_count;
    delay_second_ = delay_second;
    isComposeUpdate_ = false;
    for (int i = 0; i < monitor_count; i++){
        monitors_.push_back(Monitor::create(delay_second * i, buffer_.size()));
    }
    
    
}

Display::~Display()
{
    videoCapture_.release();
    update_frame_thread_.interrupt();
    update_frame_thread_.join();

}

void Display::Start()
{
    for (auto monitor:monitors_)
        monitor->StartDisplay();
    update_frame_thread_ = boost::thread(boost::bind(&Display::UpdateFrameTask, this));
}

bool Display::isComposeUpdate()
{
    return isComposeUpdate_;
}

cv::Mat Display::getResult()
{
    isComposeUpdate_ = false;
    return composeMap;
}

void Display::UpdateFrameTask()
{
    while(true){
        try{
            boost::mutex::scoped_lock(compose_mutex_);
            cv::Mat frame;
            videoCapture_ >> frame;
            //cv::resize(frame, frame, cv::Size(frame.cols*0.1,frame.rows*0.1));
            buffer_[index_] = frame.clone();
            index_ = (index_ + 1) % buffer_.size();
            
            //compose each window to composeMap for synchronize with videoCapture.
            ComposeBuffer();
        }
        catch(boost::thread_interrupted&){
            std::cout << "stop videocapture thread" << std::endl;
            return;
        }
    }
}

void Display::ComposeBuffer()
{
    std::cout << "buffer idx: " << index_ << std::endl;
    std::vector<cv::Mat> images;
    for (int i=0; i<monitors_.size(); i++){
        int tmp = monitors_[i]->get_index();
        std::cout << tmp << std::endl;
        images.push_back(buffer_[tmp]);
    }
    cv::hconcat(images, composeMap);
    isComposeUpdate_ = true;
}
