#include <iostream>
#include <thread>
#include <memory>

#include <motion_detection/motion_detection.h>

int main() {
    motion_detection::Detector detector{};

    // start reader on a different thread
    motion_detection::RtspReader reader{"", &detector};
    std::thread read(&motion_detection::RtspReader::start, &reader);

    read.join();
}
