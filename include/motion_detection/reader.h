#pragma once

#include <condition_variable>
#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <motion_detection/shared_data.h>

namespace motion_detection {

class reader {
    public:
        reader(const std::string& stream_path, std::shared_ptr<shared_data> const &);
        void start();
        const std::string stream_path() const;
    private:
        std::shared_ptr<shared_data> shared_data_;
        std::string stream_path_;
        cv::VideoCapture video_;
        cv::Mat last_frame_;
};

} // namespace motion_detection
