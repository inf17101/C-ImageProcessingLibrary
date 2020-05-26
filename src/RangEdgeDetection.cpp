#include "RangEdgeDetection.h"
#include "Sobel.h"
#include <memory>
#include <map>

std::unique_ptr<PicturePGM> RangEdgeDetection::make_padding(PicturePGM* pic)
{
    auto new_pic = std::make_unique<PicturePGM>();
    new_pic->height = pic->height + 2;
    new_pic->width = pic->width + 2;
    new_pic->size = new_pic->height * new_pic->width;
    new_pic->max_value = pic->max_value;

    new_pic->map = new float*[new_pic->height];
    if(new_pic->map == nullptr) return std::make_unique<PicturePGM>();

    for(int i=0; i<new_pic->height; ++i)
    {
        new_pic->map[i] = new float[new_pic->width];
        if (new_pic->map[i] == nullptr) return std::make_unique<PicturePGM>();
        for(int j=0; j<new_pic->width; ++j)
            new_pic->map[i][j] = 0;
    }
    return new_pic;
}

std::unique_ptr<PicturePGM> RangEdgeDetection::processImage(PicturePGM* pic, Config& c)
{
    auto sobel = std::make_unique<Sobel>();
    Config c_sobel;
    c_sobel["gradient_only"] = new TypedImageProperty<bool>("gradient_only", true);
    auto GradientPicture = sobel->processImage(pic, c_sobel);
    delete c_sobel["gradient_only"];
    auto GradientPicture_WithPadding = make_padding(GradientPicture.get());

    for(int row=0; row<GradientPicture_WithPadding->height-2; row++)
    {
        for(int col=0; col<GradientPicture_WithPadding->width-2; col++)
        {
            
        }
    }
}