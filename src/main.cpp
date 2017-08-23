//
//  main.cpp
//  QuauticFlow_Display
//
//  Created by ?‹ç€šç? on 2017/7/17.
//  Copyright Â© 2017å¹??‹ç€šç?. All rights reserved.
//

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "Display.hpp"
int main(int argc, const char * argv[]) {
    
    Display* display = new Display(3,2500);
    display->Start();
	cv::Mat result;
	cv::VideoWriter writer;
	writer.open("result_3_2500.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, cv::Size(1038, 209), true);
    while(true){
		if (display->isComposeUpdate()) {
			result = display->getResult();
			writer.write(result);

			cv::imshow("result", result);
			cv::waitKey(1);

			if (display->isClosed()) {
				delete display;
				break;
			}
		}

		else if (!display->isComposeUpdate() && display->isClosed())
		{
			delete display;
			break;
		}	
    }
	
	writer.release();
	
	display = new Display(3, 3500);
	display->Start();
	cv::VideoWriter writer1;
	writer1.open("result_3_3500.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, cv::Size(1038, 209), true);
	while (true) {
		if (display->isComposeUpdate()) {
			result = display->getResult();
			writer1.write(result);

			cv::imshow("result", result);
			cv::waitKey(1);

			if (display->isClosed()) {
				delete display;
				break;
			}
		}

		else if (!display->isComposeUpdate() && display->isClosed())
		{
			delete display;
			break;
		}
	}
	
	writer1.release();

	/*display = new Display(3, 4000);
	display->Start();
	cv::VideoWriter writer2;
	writer2.open("result_3_4000.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, cv::Size(1038, 209), true);
	while (true) {
		if (display->isComposeUpdate()) {
			result = display->getResult();
			writer2.write(result);

			cv::imshow("result", result);
			cv::waitKey(1);

			if (display->isClosed()) {
				delete display;
				break;
			}
		}

		else if (!display->isComposeUpdate() && display->isClosed())
		{
			delete display;
			break;
		}
	}

	writer2.release();*/

	
	
	return 0;
}

