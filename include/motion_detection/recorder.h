#pragma once

#include <chrono>
#include <cstring>
#include <vector>

#include <opencv2/opencv.hpp>

namespace motion_detection {
    class recorder {
        public:
            explicit recorder(std::string);
            void open_record();
            void close_record();
            void save(cv::Mat&, int);
        private:
            std::string path_{};
            cv::VideoWriter writer_{};
            int videos_count_{0};

            std::chrono::time_point<std::chrono::system_clock> last_detection_{};
            int current_frames_count_{0};
    };
}
