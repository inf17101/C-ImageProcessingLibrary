#include <iostream>
#include <algorithm>


int main()
{
    //float array[] = {0,0,0,0,5,10,0,5,10}; // 3,3,3,3,6,8,3,6,8
    //float array[] = {1,2,3,4,5,6,7,8,9}; // 1,2,3,4,5,6,7,8,9
    float array[] = {0,0,0,0,5,10,0,5,9}; // 3,3,3,3,6,9,3,6,8
    const size_t len = sizeof(array)/sizeof(array[0]);

    float **parray = new float*[len];
    if(parray == nullptr)
    {
        std::cout << "error while allocating memory." << std::endl;
        return 1;
    }
    for(size_t i=0;i<len; ++i)
        parray[i] = array + i;

    std::sort(parray, parray + len, [](float* left, float* right){ return (*left) < (*right); });
    for(int i=0; i<len; ++i)
        std::cout << (*parray[i]) << " ";
    
    std::cout << std::endl;

    std::cout << "array with positions inserted: " << std::endl;

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

    for(int i=0; i<len; ++i)
        std::cout << array[i] << " ";
    
    std::cout << std::endl;

    delete[] parray;

    return 0;
}