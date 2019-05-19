#pragma once

#include <memory>

#include <opencv2/opencv.hpp>

#include <motion_detection/shared_data.h>
#include <motion_detection/recorder.h>

namespace motion_detection {

    class detector_base { // interface
        public:
            virtual void add_frame(const cv::Mat&) = 0;
            virtual ~detector_base() = default;
    };

    class detector_abs_diff : public detector_base {
        public:
            detector_abs_diff();
            void add_frame(const cv::Mat& frame) override;
            ~detector_abs_diff() = default;
        private:
            cv::Mat curr_frame_{};
            cv::Mat prev_frame_{};
            cv::Mat deta_frame_{};
    };

    class detector {
        public:
            explicit detector(std::shared_ptr<shared_data> const &);
            void start();
        private:
            std::shared_ptr<shared_data> shared_data_;
            cv::Mat current_frame_{};
            cv::Mat prev_frame_{};
            cv::Mat delta_frame_{};

            // TEST
            cv::Mat show_frame_{};
            recorder recorder_{""};
    };

} // namespace motion_detction
