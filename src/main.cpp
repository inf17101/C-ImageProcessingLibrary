
#include <iostream>
#include <memory>
#include <cstring>
#include "Picture.h"
#include "Sobel.h"
#include "ImageAlgorithmStrategy.h"
#include "ImageConfig.h"
#include "ImageProcessor.h"

int main()
{
    const char FILE_PATH[] = "../../SteilkurveGRAY_pgm.pgm";
    auto imProcessor = std::make_unique<ImageProcessor>(new Sobel());
    auto picture = imProcessor->readImage(FILE_PATH);
    std::cout << "Read in image: " << std::endl;
    //picture->printPic();
    Config c = {
        new TypedImageProperty<float>("sobel_threshold", 100.0),
        new TypedImageProperty<bool>("gradient_only", false)};
    auto sobel_pic = imProcessor->processImage(picture.get(), c);

    std::cout << "Sobel Picture: " << std::endl;

    //sobel_pic->printPic();

    imProcessor->writeImageAsPGM(sobel_pic.get(), "SteilkurveGRAY_pgm_out.pgm");

    for(auto& i : c)
        delete i;

    return 0;
}

