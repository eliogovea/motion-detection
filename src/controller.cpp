#include <thread>

#include <motion_detection/controller.h>

namespace motion_detection {
    controller::controller(const rtsp_info stream_info) {
        auto data = std::make_shared<shared_data>();

        reader reader_{stream_info.stream_path(), data};
        std::thread read(&reader::start, &reader_);

        detector detector_{data};
        std::thread detect(&detector::start, &detector_);

        read.join();
        detect.join();
    }

    void controller::start() {
        // TODO
    }
}
