#pragma once

#include <cstring>

#include <opencv2/opencv.hpp>

namespace motion_detection {
    class recorder {
        public:
            explicit recorder(std::string);
            void close_record();
            void save(cv::Mat&);
        private:
            cv::VideoWriter writer_{};
            int current_frames_count_{0};
            std::string path_;
    };
}
