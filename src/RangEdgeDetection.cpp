#include "RangEdgeDetection.h"
#include "Sobel.h"
#include <memory>
#include <map>
#include <algorithm>

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

    for(int i=1; i<new_pic->height-1; ++i)
        for(int j=1; j<new_pic->width-1; ++j)
            new_pic->map[i][j] = pic->map[i-1][j-1];

    return new_pic;
}

void RangEdgeDetection::calculate_rang_position(float array[], const size_t len)
{
    float **parray = new float*[len];
    if(parray == nullptr) {std::cout << "ERROR: cannot allocate memory to calculate rang position." << std::endl; exit(1);}
    for(size_t i=0;i<len; ++i)
        parray[i] = array + i;
    std::sort(parray, parray + len, [](float* left, float* right){ return (*left) < (*right); });
    size_t pos = 0;
    int first = -1;
    int last = -1;
    float item = (*parray[0]);
    for(pos=0; pos < len; ++pos)
    {
        if((*parray[pos]) != item)
        {
            item = (*parray[pos]);
            if(first < last)
            {
                int rang = (first+last)/2;
                for(;first<=last; ++first)
                    (*parray[first-1]) = rang;
            }else
            {
                (*parray[pos-1]) = first;
            }

            first = -1;
            last = -1;
        }

        if(first == -1)
                first = pos+1;

        last = pos+1;
    }

        if(first < last)
        {
        int rang = (first+last)/2;
        for(;first<=last; ++first)
            (*parray[first-1]) = rang;
        }else
        {
            (*parray[pos-1]) = first;
        }

        delete[] parray;
}

void RangEdgeDetection::replace_by_threshold(PicturePGM* pic, float threshold)
{
    for(int i = 0; i<pic->height; ++i)
        for(int j = 0; j<pic->width; ++j)
        {
            pic->map[i][j] = (pic->map[i][j] > threshold) ? 255.0 : 0.0;
        }
    pic->max_value = 255.0;
}

std::unique_ptr<PicturePGM> RangEdgeDetection::processImage(PicturePGM* pic, Config& c)
{
    auto sobel = std::make_unique<Sobel>();
    Config c_sobel;
    c_sobel["gradient_only"] = new TypedImageProperty<bool>("gradient_only", true);
    auto GradientPicture = sobel->processImage(pic, c_sobel);
    delete c_sobel["gradient_only"];
    auto GradientPicture_WithPadding = make_padding(GradientPicture.get());

    auto rang_pic = std::make_unique<PicturePGM>();
    rang_pic->height = pic->height;
    rang_pic->width = pic->width;
    rang_pic->size = rang_pic->height * rang_pic->width;
    rang_pic->map = new float*[rang_pic->height];
    if(rang_pic->map == nullptr) return std::make_unique<PicturePGM>();
    for(int i=0; i<rang_pic->height; ++i)
    {
        rang_pic->map[i] = new float[rang_pic->width];
        if(rang_pic->map[i] == nullptr) return std::make_unique<PicturePGM>();
    }

    float pixel_surrounding[9];
    for(int row=0; row<GradientPicture_WithPadding->height-2; row++)
    {
        for(int col=0; col<GradientPicture_WithPadding->width-2; col++)
        {
            for(int i=0; i<3; ++i)
                for(int j=0; j<3; ++j)
                    pixel_surrounding[i*3 + j] = GradientPicture_WithPadding->map[row+i][col+j];
            
            RangEdgeDetection::calculate_rang_position(pixel_surrounding, 9);
            for(int i=0; i<3; ++i)
                for(int j=0; j<3; ++j)
                {
                    rang_pic->map[row+i][col+j] = pixel_surrounding[i*3 + j];
                }
            
        }
    }

    RangEdgeDetection::replace_by_threshold(rang_pic.get(), 7);
    return rang_pic;
}