#include <motion_detection/reader.h>


namespace motion_detection {

Reader::Reader() {

}

RtspReader::RtspReader(
    const std::string& path, 
    Detector* detector
) : path_(path),
    detector_(detector),
    Reader() {

}

const std::string& RtspReader::streamPath() const {
    return path_;
}

bool RtspReader::start() {
    video_.open(path_);

    // TEST
    if (path_ == "") {
        video_.open(0);
    } // TEST
    
    if (!video_.isOpened()) {
        return false;
    }

    // cv::namedWindow("original", cv::WINDOW_AUTOSIZE); // TEST
    while (video_.read(frame_)) {
        // cv::imshow("original", frame_); // TEST
        // cv::waitKey(25); // TEST
        frame_.copyTo(copyFrame_);
        detector_->processNewFrame(copyFrame_);
    }

    return true;
}

cv::Mat RtspReader::getFrame() const {
    if (frame_.empty()) {
        return {};
    }
    frame_.copyTo(copyFrame_);
    return copyFrame_;
}

} // namespace motion_detection
