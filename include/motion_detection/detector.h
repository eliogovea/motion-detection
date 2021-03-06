#pragma once

#include <memory>

#include <opencv2/opencv.hpp>

#include <motion_detection/shared_data.h>

namespace motion_detection {

    class detector {
        public:
            explicit detector(std::shared_ptr<shared_data> const &);
            void start();
        private:
            std::shared_ptr<shared_data> shared_data_;
            cv::Mat current_frame_{};
            cv::Mat prev_frame_{};
            cv::Mat delta_frame_{};
            cv::Mat show_frame_{}; // TEST
    };

} // namespace motion_detction
