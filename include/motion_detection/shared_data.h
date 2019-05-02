#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

#include <opencv2/opencv.hpp>

namespace motion_detection {
    class shared_data {
        public:
            shared_data();
            void push(cv::Mat);
            void pop(cv::Mat&);
        private:
            std::mutex mutex_;
            std::condition_variable cond_;
            std::queue<cv::Mat> data_;
    };
}
