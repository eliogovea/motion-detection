#include <memory>

#include <motion_detection/shared_data.h>

namespace motion_detection {
    shared_data::shared_data() : mutex_(), data_() {}

    void shared_data::push(cv::Mat frame) {
        std::unique_lock<std::mutex> lock(mutex_);
        data_.push(frame);
        cond_.notify_one();
    }

    void shared_data::pop(cv::Mat& frame) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] {
            return !data_.empty();
        });
        frame = data_.front();
        data_.pop();
    }
}
