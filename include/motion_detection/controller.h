#pragma once

#include <string>

#include <opencv2/opencv.hpp>

#include <motion_detection/shared_data.h>
#include <motion_detection/reader.h>
#include <motion_detection/detector.h>

namespace motion_detection {

struct rtsp_info {
    std::string username;
    std::string password;
    std::string ip;
    std::string path;

    const std::string stream_path() const {
        return "rtsp://" + username + ":" + password + "@" + ip + path;
    }
};

class controller {
    public:
        controller(const rtsp_info);
        void start();
    private:
        // shared_data shared_data_;
        // reader reader_;
        // detector detector_;
};

} // namespace motion_detection
