#include <iostream>
#define height 10
#define width 10

int main()
{
    float** arr = new float*[height];
    if(arr == nullptr) { std::cout << "error while allocating memory." << std::endl; return 1;}
    for(unsigned int i=0; i<height; ++i)
    {
        arr[i] = new float[width];
        if(arr[i] == nullptr) { std::cout << "error while allocating memory." << std::endl; return 1;}
        for(unsigned int j=0; j<width; ++j)
            arr[i][j] = 0;
    }

    unsigned int new_height = height +2;
    unsigned int new_width = width + 2;

    float** new_arr = new float*[new_height];
    if(new_arr == nullptr) { std::cout << "error while allocating memory." << std::endl; return 1;}
    for(unsigned int i=0; i<new_height; ++i)
    {
        new_arr[i] = new float[new_width];
        if(new_arr[i] == nullptr) { std::cout << "error while allocating memory." << std::endl; return 1;}
        for(unsigned int j=0; j<new_width; ++j)
            new_arr[i][j] = 0;
    }

    for(unsigned int i=1; i<new_height-1; ++i)
        for(unsigned int j=1; j<new_width-1; ++j)
            new_arr[i][j] = arr[i-1][j-1];

    for(unsigned int i=0; i<height; ++i)
        delete [] arr[i];
    delete [] arr;

    arr = new_arr;

    
    for(unsigned int i=0; i<new_height; ++i)
        delete [] new_arr[i];
    delete [] new_arr;
    


    return 0;
}