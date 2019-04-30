#include <iostream>
// #include <thread>
// #include <memory>

#include <motion_detection/motion_detection.h>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "argc != 5\n";
        std::cout << "./app username password ip path\n";
        return 1;
    }

    motion_detection::Detector detector{};

    motion_detection::RtspInfo rtspInfo{argv[1], argv[2], argv[3], argv[4]};
    motion_detection::RtspReader reader{rtspInfo, &detector};

    // start reader on a different thread
    // std::thread read(&motion_detection::RtspReader::start, &reader);
    // read.join();

    reader.start();
}
