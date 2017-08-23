//
//  Monitor.cpp
//  QuauticFlow_Display
//
//  Created by 王瀚磊 on 2017/7/17.
//  Copyright © 2017年 王瀚磊. All rights reserved.
//

#include "Monitor.hpp"

boost::shared_ptr<Monitor> Monitor::create(float delay_sec, int buffer_size)
{
    return boost::shared_ptr<Monitor>(new Monitor(delay_sec, buffer_size));
}

Monitor::Monitor(float delay_sec, int buffer_size)
{
    index_ = 0;
    delay_sec_ = delay_sec;
    wakeup_ = false;
    buffer_size_ = buffer_size;
}

Monitor::~Monitor()
{
    delay_thread_.interrupt();
    delay_thread_.join();
}

int Monitor::get_index()
{
    if(wakeup_)
        return (index_++) % buffer_size_;
    else
        return 0;
}

void Monitor::StartDisplay()
{
    delay_thread_ = boost::thread(boost::bind(&Monitor::DelayTask,shared_from_this(), delay_sec_));
    delay_thread_.detach();
}

void Monitor::DelayTask(float delay_sec)
{
    if(delay_sec > 0){
        boost::this_thread::sleep(boost::posix_time::seconds(delay_sec));
        wakeup_ = true;
    }
    else
        wakeup_ = true;
}
