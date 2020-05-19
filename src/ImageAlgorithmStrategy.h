#ifndef _ImageAlgoithmStrategy_HEADER_
#define _ImageAlgoithmStrategy_HEADER_
#include <memory>
#include "Picture.h"
#include "ImageConfig.h"
#include <vector>

using Config = std::vector<ImageProperty*>;

class ImageAlgorithmStrategy
{
    public:
        virtual ~ImageAlgorithmStrategy() = default;
        virtual std::unique_ptr<PicturePGM> processImage(PicturePGM* pic, Config& c) = 0;
        virtual std::unique_ptr<ImageAlgorithmStrategy> clone() const = 0;
};

#endif