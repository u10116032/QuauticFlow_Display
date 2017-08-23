//
//  Display.cpp
//  QuauticFlow_Display
//
//  Created by 王瀚磊 on 2017/7/17.
//  Copyright © 2017年 王瀚磊. All rights reserved.
//

#include "Display.hpp"

Display::Display(int monitor_count, float delay_millisec)
{
    index_ = 0;
    videoCapture_ = cv::VideoCapture("video.mp4");
	//videoCapture_.set(CV_CAP_PROP_FPS, 30);
    monitor_count_ = monitor_count;
    isComposeUpdate_ = false;
	isClosed_ = false;
    for (int i = 0; i < monitor_count; i++){
        monitors_.push_back(Monitor::create(delay_millisec * i, buffer_.size()));
    }
    
    
}

Display::~Display()
{
    update_frame_thread_.interrupt();
    update_frame_thread_.join();
	videoCapture_.release();
}

void Display::Start()
{
    for (auto monitor:monitors_)
        monitor->StartDisplay();
    update_frame_thread_ = boost::thread(boost::bind(&Display::UpdateFrameTask, this));
}

void Display::Close() 
{
	isClosed_ = true;
}

bool Display::isComposeUpdate()
{
    return isComposeUpdate_;
}

bool Display::isClosed() 
{
	return isClosed_;
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
			//boost::this_thread::sleep(boost::posix_time::millisec(100));
            cv::Mat frame;
            videoCapture_ >> frame;
			if (frame.empty()) {
				Close();
				break;
			}
            cv::resize(frame, frame, cv::Size(frame.cols*0.2, frame.rows*0.2));
            buffer_[index_] = frame.clone();
            index_ = (index_ + 1) % buffer_.size();
            
            //compose each window to composeMap for synchronize with videoCapture.
            ComposeBuffer();

			cv::waitKey(33);
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
		cv::Mat gap = cv::Mat::zeros(buffer_[tmp].rows, 10, CV_8UC3);
		images.push_back(gap);
	}
	std::reverse(images.begin(), images.end());
    cv::hconcat(images, composeMap);

    isComposeUpdate_ = true;
}
