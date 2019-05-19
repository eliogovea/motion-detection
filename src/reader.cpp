#include <iostream>

#include <motion_detection/reader.h>


namespace motion_detection {

    reader::reader(const std::string& stream_path, std::shared_ptr<shared_data> const & shared_data_) : 
        stream_path_(stream_path),  
        shared_data_(shared_data_) {
    }

    const std::string reader::stream_path() const {
        return stream_path_;
    }

  void reader::start() {
        video_.open(stream_path_);

        // TEST
        if (!video_.isOpened()) {
            std::cout << "could not open " << stream_path_ << "\n";
            std::cout << "trying to open web cam ...\n";
            video_.open(0);
        }
        // TEST

        while (video_.read(last_frame_)) {
            shared_data_->push(last_frame_); // deep copy ???
        }
    }

} // namespace motion_detection
