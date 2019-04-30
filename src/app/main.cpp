#include <iostream>
#include <thread>
#include <memory>

#include <motion_detection/motion_detection.h>

int main() {
    std::cout << "starting ...\n";
    // auto reader = std::make_unique<motion_detection::RtspReader>("");
    // reader->start();

    motion_detection::Detector detector{};

    // start reader on a different thread
    motion_detection::RtspReader reader{"", &detector};
    std::thread read(&motion_detection::RtspReader::start, &reader);

//    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
//    while (true) {
//        auto frame = reader.getFrame();
//        if (frame.empty()) {
//            continue;
//        }
//        cv::imshow("original", frame);
//        cv::waitKey(25);
//    }


    read.join();
}
