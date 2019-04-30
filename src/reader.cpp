#include <motion_detection/reader.h>


namespace motion_detection {

Reader::Reader() {

}

RtspReader::RtspReader( RtspInfo rtspInfo, Detector* detector) 
    : rtspInfo_(rtspInfo), detector_(detector), Reader() 
{
}

bool RtspReader::start() {
    std::string streamPath = "rtsp://";
    streamPath += rtspInfo_.username + ":" + rtspInfo_.password + "@";
    streamPath += rtspInfo_.ip + rtspInfo_.path;

    video_.open(streamPath);

    // TEST
    if (!video_.isOpened()) {
        std::cout << "could not open " << streamPath << "\n";
        std::cout << "trying to open web cam ...\n";
        video_.open(0);
    } // TEST
    
    if (!video_.isOpened()) {
        return false;
    }

    while (video_.read(frame_)) {
        frame_.copyTo(copyFrame_);
        detector_->processNewFrame(copyFrame_);
    }

    std::cout << "stream closed\n";
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
