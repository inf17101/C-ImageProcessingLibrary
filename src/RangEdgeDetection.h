#ifndef _RANGEDGEDETECTION_HEADER_
#define _RANGEDGEDETECTION_HEADER_

#include "ImageAlgorithmStrategy.h"
#include "Picture.h"
#include <memory>

class RangEdgeDetection : public ImageAlgorithmStrategy
{
    public:
        RangEdgeDetection() = default;
        ~RangEdgeDetection() = default;
        virtual std::unique_ptr<PicturePGM> processImage(PicturePGM* pic, Config& c) override;
        virtual std::unique_ptr<ImageAlgorithmStrategy> clone() const override;
};

#endif