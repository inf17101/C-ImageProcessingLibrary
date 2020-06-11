#ifndef _RANGEDGEDETECTION_HEADER_
#define _RANGEDGEDETECTION_HEADER_

#include "ImageAlgorithmStrategy.h"
#include "Picture.h"
#include <memory>

class RangEdgeDetection : public ImageAlgorithmStrategy
{
    std::unique_ptr<PicturePGM> make_padding(PicturePGM* pic);
    void calculate_rang_position(float array[], const size_t len);
    void replace_by_threshold(PicturePGM* pic, float threshold);
    public:
        RangEdgeDetection() = default;
        ~RangEdgeDetection() = default;
        virtual std::unique_ptr<PicturePGM> processImage(PicturePGM* pic, Config& c) override;
};

#endif