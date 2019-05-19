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

    motion_detection::rtsp_info stream_info{argv[1], argv[2], argv[3], argv[4]};

    motion_detection::controller{stream_info};
}
