#pragma once

#include <opencv2/opencv.hpp>

namespace motion_detection {

class Detector {
    public:
        explicit Detector();
        void processNewFrame(cv::Mat frame);
        void preprocessFrame(cv::Mat& frame);
    private:
        bool started_ = false;
        cv::Mat prevFrame_;
        cv::Mat deltaFrame_;
        cv::Mat showFrame_;
};

} // namespace motion_detection
