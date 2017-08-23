//
//  Monitor.hpp
//  QuauticFlow_Display
//
//  Created by 王瀚磊 on 2017/7/17.
//  Copyright © 2017年 王瀚磊. All rights reserved.
//

#ifndef Monitor_hpp
#define Monitor_hpp

#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class Monitor : public boost::enable_shared_from_this<Monitor> {
    
public:
  
    static boost::shared_ptr<Monitor> create(float delay_sec, int buffer_size);
    
    Monitor(float delay_sec, int buffer_size);
    ~Monitor();
    
    int get_index();
    
    void StartDisplay();
        
private:
    
    int index_;
    int buffer_size_;
    float delay_millisec_;
    bool wakeup_;
    boost::thread delay_thread_;
    
    void DelayTask(float delay_sec);
    
};

#endif /* Monitor_hpp */
