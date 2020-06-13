#ifndef _PICTURE_HEADER_
#define _PICTURE_HEADER_

#include <cstdint>
#include <iostream>

struct PicturePGM
{

    std::uint32_t height;
    std::uint32_t width;
    std::uint32_t size;
    std::uint8_t max_value;
    float** map;

    PicturePGM(const std::uint32_t h, const std::uint32_t w, const std::uint32_t s, const std::uint8_t max_v, float** m)
    : height(h), width(w), size(s), max_value(max_v), map(m) {}

    PicturePGM() : height(0), width(0), size(0), max_value(0), map(nullptr) {}

    PicturePGM(const PicturePGM& p) : height(p.height), width(p.width), size(p.size), max_value(p.max_value)
    {
        map = new float*[p.height];
        for(int i=0; i<p.height; ++i)
            map[i] = new float[p.width];
        
        for(int i=0; i<p.height; ++i)
            for(int j=0;j<p.width;++j)
                map[i][j] = p.map[i][j];
    }

    PicturePGM(PicturePGM&& p) noexcept :height(p.height), width(p.width), size(p.size), max_value(p.max_value)
    {
        map = p.map;
        p.map = nullptr;
    }

    ~PicturePGM()
    {
        for(int i=0; i<height; ++i)
            delete [] map[i];
        delete [] map;
    }

    PicturePGM& operator =(PicturePGM& p) noexcept
    {
        height = p.height;
        width = p.width;
        size = p.size;
        max_value = p.max_value;
        map = p.map;
        p.map = nullptr;
        return *this;
    }

    void printPic() const
    {
        for(int i=0; i<height; ++i)
        {
            for(int j=0; j<width;++j)
            {
                printf("%.2f ", map[i][j]);
            }
            printf("\n");
        }
    }

};

#endif