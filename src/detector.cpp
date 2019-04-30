#include <motion_detection/detector.h>

namespace motion_detection {

Detector::Detector() {
    cv::namedWindow("original", cv::WINDOW_AUTOSIZE); // TEST
}

void Detector::preprocessFrame(cv::Mat& frame) {
    cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(frame, frame, cv::Size(21, 21), 0);
}

void Detector::processNewFrame(cv::Mat frame) {
    frame.copyTo(showFrame_);

    preprocessFrame(frame);

    if (started_) {
        cv::absdiff(frame, prevFrame_, deltaFrame_);
        // cv::threshold(deltaFrame_, deltaFrame_, 25, 255, cv::THRESH_BINARY);
        cv::adaptiveThreshold(deltaFrame_, deltaFrame_, 255, cv::THRESH_BINARY_INV, cv::ADAPTIVE_THRESH_MEAN_C, 71, 15);
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(deltaFrame_, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        deltaFrame_ = cv::Scalar::all(0);
        cv::drawContours(showFrame_, contours, -1, cv::Scalar::all(255));
    }

    cv::imshow("original", showFrame_); // TEST
    cv::waitKey(25); // TEST

    started_ = true;
    frame.copyTo(prevFrame_);
}

} // namespace motion_detection
