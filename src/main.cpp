
#include <iostream>
#include <memory>
#include <cstring>
#include <algorithm>
#include "Picture.h"
#include "Sobel.h"
#include "ImageAlgorithmStrategy.h"
#include "ImageConfig.h"
#include "ImageProcessor.h"

int main()
{
    const char FILE_PATH[] = "images/SteilkurveGRAY_pgm.pgm";
    auto imProcessor = std::make_unique<ImageProcessor>(std::make_unique<Sobel>());
    auto picture = imProcessor->readImage(FILE_PATH);

    Config c;
    c["sobel_threshold"] =  new TypedImageProperty<float>("sobel_threshold", 100.0);
    c["gradient_only"] = new TypedImageProperty<bool>("gradient_only", false);
    auto sobel_pic = imProcessor->processImage(picture.get(), c);

    imProcessor->writeImageAsPGM(sobel_pic.get(), "out/SteilkurveGRAY_pgm_out.pgm");

    for(auto it = c.begin(); it != c.end(); ++it)
        delete (it->second);

    return 0;
}

