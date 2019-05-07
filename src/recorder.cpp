#include <iostream>
#include <chrono>

#include "motion_detection/recorder.h"

namespace motion_detection {
    recorder::recorder(std::string path = "") : path_(path) {
        // TODO check path
    }

    void recorder::close_record() {
        current_frames_count_ = 0;
        // writer.release();
    }

    void recorder::save(cv::Mat& image) {
        if (current_frames_count_ == 0) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            static char file_name_buffer[100];
            strftime(file_name_buffer, 100, "records/%Y-%d-%m-%H-%M-%S.mpg", localtime(&now)); // TODO create the folder 
            std::string file_name = path_ + std::string(file_name_buffer);
            std::cout << "new file " << file_name << "\n";
            writer_.open(file_name, 
                        CV_FOURCC('D','I','V','X'), 
                        30.0, // TODO
                        cv::Size(640, 480), 
                        true
            );
        }
        current_frames_count_++;
        writer_.write(image);
    }
}
