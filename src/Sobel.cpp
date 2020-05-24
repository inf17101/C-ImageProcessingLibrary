#include "Sobel.h"
#include <cmath>
#include <memory>
#include <algorithm>


bool Sobel::isConfigValid(Config& c, float& threshold_value, bool& gradient_only)
{
    bool validConfig = true;
    std::for_each(c.begin(), c.end(), [&](ImageProperty* c_){
        if(c_->getPropertyName() == "sobel_threshold")
        {
            auto p = dynamic_cast<TypedImageProperty<float>*>(c_);
            if (!p)
                validConfig=false;
            else
                threshold_value = p->getProperty();
            
        }else if(c_->getPropertyName() == "gradient_only")
        {
            auto p = dynamic_cast<TypedImageProperty<bool>*>(c_);
            if(!p)
                validConfig = false;
            else
                gradient_only = p->getProperty();
            
        }else
        {
            validConfig = false;
        }
    });
    return validConfig;
}

std::unique_ptr<PicturePGM> Sobel::processImage(PicturePGM* pic, Config& c)
{
    float threshold_value;
    bool gradient_only;
    if (!isConfigValid(c, threshold_value, gradient_only))
    {
        std::cout << "error in config." << std::endl;
        return std::make_unique<PicturePGM>();
    }

    static float sobel_Dx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    static float sobel_Dy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
    std::uint8_t max_value = gradient_only ? pic->max_value : 255;
    std::uint32_t new_size = pic->height-2 * pic->width-2;
    std::unique_ptr<PicturePGM> sobelPicture = std::make_unique<PicturePGM>(pic->height-2, pic->width-2, new_size, max_value, nullptr);

    sobelPicture->map = new float*[sobelPicture->height];
    for(int i=0; i<sobelPicture->height; ++i)
        sobelPicture->map[i] = new float[sobelPicture->width];

    for(int i=0; i<pic->height-2; i++)
    {
        for(int j=0; j<pic->width-2; j++)
        {
            float Sx_i = 0, Sy_i = 0;
            for(int n=0; n<3; ++n)
                for(int m=0; m<3; ++m)
                {
                    Sx_i += sobel_Dx[n][m] * pic->map[i+n][j+m];
                    Sy_i += sobel_Dy[n][m] * pic->map[i+n][j+m];
                }
            if (gradient_only)
                sobelPicture->map[i][j] = static_cast<float>(sqrt(Sx_i*Sx_i + Sy_i*Sy_i));
            else
                sobelPicture->map[i][j] = static_cast<float>(sqrt(Sx_i*Sx_i + Sy_i*Sy_i)) > threshold_value ? 255.0 : 0;
        }        
    }
    return sobelPicture;
}
