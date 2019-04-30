#pragma once

#include <string>
#include <memory>

#include <opencv2/opencv.hpp>

#include <motion_detection/detector.h>

namespace motion_detection {

class Reader {
    public:
        explicit Reader();
        virtual bool start() = 0;
};

class RtspReader : public Reader {
    public:
        RtspReader(const std::string&, Detector*);
        bool start() override;
        const std::string& streamPath() const;
        cv::Mat getFrame() const; 
    private:
        std::string path_;
        cv::VideoCapture video_;
        cv::Mat frame_;
        cv::Mat copyFrame_;
        Detector* detector_ = nullptr;
};

} // namespace motion_detection
