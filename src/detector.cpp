#include <iostream>

#include <motion_detection/detector.h>

namespace motion_detection {

    ///////////////////////////////////////////////////////////////////////
    detector_abs_diff::detector_abs_diff() {

    }

    void detector_abs_diff::add_frame(const cv::Mat& frame) {
        curr_frame_.copyTo(prev_frame_);
        frame.copyTo(curr_frame_);

        // 
        cvtColor(curr_frame_, curr_frame_, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(curr_frame_, curr_frame_, cv::Size(5, 5), 0);
        
        // TODO
    }
    
    ////////////////////////////////////////////////////////////////////////
    detector::detector(std::shared_ptr<shared_data> const & _shared_data) :
        shared_data_(_shared_data) {
        // TEST
        cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
        // cv::namedWindow("processed", cv::WINDOW_AUTOSIZE);
        // cv::namedWindow("delta", cv::WINDOW_AUTOSIZE);
        // TEST
    }

    void detector::start() {
        while (true) {
            shared_data_->pop(current_frame_);

            // TEST
            current_frame_.copyTo(show_frame_);
            // TEST
            
            cvtColor(current_frame_, current_frame_, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(current_frame_, current_frame_, cv::Size(5, 5), 0);

            if (!prev_frame_.empty()) {
                cv::absdiff(current_frame_, prev_frame_, delta_frame_);
                cv::adaptiveThreshold(delta_frame_, delta_frame_, 255, cv::THRESH_BINARY_INV, cv::ADAPTIVE_THRESH_MEAN_C, 71, 15);
                // cv::dilate(deltaFrame_, deltaFrame_, cv::Mat(), cv::Point{-1, -1}, 5);
                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(delta_frame_, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

                // TODO remove small contours

                // TEST
                cv::drawContours(show_frame_, contours, -1, cv::Scalar::all(255));
                // std::cout << contours.size() << "\n";
                // TEST
                
                recorder_.save(show_frame_, static_cast<int>(contours.size()));
            }

            // TEST
            cv::imshow("original", show_frame_);
            // cv::imshow("processed", current_frame_);
            cv::waitKey(1);
            // TEST

            current_frame_.copyTo(prev_frame_);
        }
    }
} // namespace motion_detection
