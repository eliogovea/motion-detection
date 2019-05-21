#include <iostream>
#include <chrono>

#include "motion_detection/recorder.h"

namespace motion_detection {
    recorder::recorder(std::string path = "") : path_(path) {
        // TODO check path
        // TODO create records folder
    }

    void recorder::open_record() {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        static char file_name_buffer[100];
        strftime(file_name_buffer, 100, "records/%Y-%d-%m-%H-%M-%S.mpg", localtime(&now));
        std::string file_name = path_ + std::string(file_name_buffer);
        std::cout << "new file " << file_name << "\n";
        writer_.open(file_name, 
                     CV_FOURCC('D','I','V','X'), 
                     30.0, // TODO
                     cv::Size(640, 480), 
                     true
        );
    }

    void recorder::close_record() {
        if (writer_.isOpened()) {
            writer_.release();
        }
        current_frames_count_ = 0;
    }

    void recorder::save(cv::Mat& image, int contours) {
        // std::cout << contours << std::endl;
        if (contours <= 1) {
            if (!writer_.isOpened()) {
              return;
            }
            // std::cout << "no detection\n";
            std::chrono::duration<double> delta = std::chrono::system_clock::now() - last_detection_;
            if (delta.count() > 1.0) {
              close_record();
            }
            return;
        }

        last_detection_ = std::chrono::system_clock::now();

        if (!writer_.isOpened()) {
            open_record();
        }

        writer_.write(image);
        current_frames_count_++;
    }
}
