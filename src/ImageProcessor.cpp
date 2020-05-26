#include "ImageProcessor.h"
#include <cstring>
#include <fstream>

std::unique_ptr<PicturePGM> ImageProcessor::readImage(const char* filename, uint8_t padding_size)
{
    std::unique_ptr<PicturePGM> inputPicture = std::make_unique<PicturePGM>();
    FILE *fhandle = fopen(filename, "rb");
    if (!fhandle)
    {
        printf("File not found!\n");
        return inputPicture;
    }
    printf("File opened correctly!\n");

    char line[75];
    if (fgets(line, sizeof(line), fhandle) == NULL) return inputPicture;

    if(strncmp(line, "P5",2) != 0) return std::move(inputPicture);

    if(fgets(line, sizeof(line), fhandle) == NULL) return inputPicture;

    inputPicture->width = strtoul(strtok(line, " "), NULL, 10);
    inputPicture->height = strtoul(strtok(NULL, " "), NULL, 10);
    inputPicture->size = inputPicture->height * inputPicture -> width;

    printf("height: %d\nwidth: %d\nsize: %d\n\n", inputPicture->height, inputPicture->width, inputPicture->size);
    
    if(fgets(line, sizeof(line), fhandle) == NULL) return std::make_unique<PicturePGM>();
    inputPicture->max_value = (uint8_t) strtoul(line, NULL, 10);

    inputPicture->height += padding_size; //because of zero padding
    inputPicture->width += padding_size;

    inputPicture->map = new float*[inputPicture->height];
    if (inputPicture->map == NULL) return std::make_unique<PicturePGM>();


    for(int i=0; i<inputPicture->height; ++i) //init matrix and initialize with zero padding
    {
        inputPicture->map[i] = new float[inputPicture->width];
        if (inputPicture->map[i] == NULL) return std::make_unique<PicturePGM>();
        for(int j=0; j<inputPicture->width; ++j)
            inputPicture->map[i][j] = 0;
    }

    for (int i=1; i<inputPicture->height-1; ++i)
        for(int j=1; j<inputPicture->width-1; ++j)
            inputPicture->map[i][j] = static_cast<float> (fgetc(fhandle));

    fclose(fhandle);

    return inputPicture;

}

std::unique_ptr<PicturePGM> ImageProcessor::processImage(PicturePGM* pic, Config& c)
{
    return algorithm_->processImage(pic,c);
}

int8_t ImageProcessor::writeImageAsPGM(PicturePGM* pic, const char* FILE_PATH)
{
    std::ofstream of(FILE_PATH, std::ios::out
                                | std::ios_base::binary
                                | std::ios_base::trunc);
    if(!of)
        return -1;
    
    of << "P5\n";
    of << pic->width << " " << pic->height << "\n";

    of << static_cast<int>(pic->max_value) << "\n";

    if(of.bad())
        return -1;

    for(int i=0; i<pic->height; ++i)
        for(int j=0; j<pic->width; ++j)
            of.put(pic->map[i][j]);
    
    if(of.bad())
        return -1;
    of.close();

    return 0;

}