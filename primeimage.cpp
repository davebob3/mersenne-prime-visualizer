//
//  main.cpp
//  Mersenne Prime Image
//
//  Created by David Robson on 2/23/13.
//  Copyright (c) 2024 David Robson. All rights reserved.
//

#include <iostream>
#include <string>

#include "CImg/CImg.h"

using namespace cimg_library;

static int get_exponent(const char *argument, unsigned long *value)
{
    int result = 0;
    unsigned long exponent_value = 0;
    int arg_size = std::strlen(argument);
    for (int c = 0; c < arg_size; c++)
    {
        if (!std::isdigit(argument[c]))
        {
            result = __LINE__;
            break;
        }
    }
    if (result == 0)
    {
        try 
        {
            exponent_value = std::stoul(argument);
        }
        catch (...)
        {
            result = __LINE__;
        }
    }
    if (result == 0)
    {
        *value = exponent_value;
    }
    return result;
}

int main(int argc, const char *argv[])
{
    unsigned long thePrimeFactor = 136279841;
    unsigned long theImageWidth = 400;
    unsigned long theImageHeight = 300;
    unsigned long theIncrement = 100;

    if (argc == 2)
    {
        unsigned long argument;
        if (get_exponent(argv[1], &argument) != 0)
        {
            std::cout << "Could not parse number from commandline, using exponent "
                << thePrimeFactor << std::endl;
        }
        else
        {
            thePrimeFactor = argument;
        }   
    }
    unsigned long theNumberWhitePix = thePrimeFactor / 24;
    unsigned long theRemainderNum = thePrimeFactor % 24;
    uint32_t theRemainder = 0;
    for (unsigned int bit = 0; bit < theRemainderNum; bit++)
    {
        theRemainder |= 1 << bit;
    }

    for (; theImageWidth <= 4000; theImageWidth += theIncrement)
    {
        theImageHeight = (theImageWidth / 4) * 3;
        if (theImageHeight * theImageWidth > theNumberWhitePix)
            break;
    }

    const unsigned char white[] = {0xff, 0xff, 0xff};
    const unsigned char black[] = {0x00, 0x00, 0x00};
    unsigned char remainder[] = {(unsigned char)(theRemainder & 0xff),
                                 (unsigned char)((theRemainder >> 8) & 0xff),
                                 (unsigned char)((theRemainder >> 16) & 0xff)};
    std::cout << "rendering 2^" << thePrimeFactor << " - 1" << std::endl;
    std::cout << "Width: " << theImageWidth << ", Height: " << theImageHeight << std::endl;
    std::cout << "Size: " << theImageHeight * theImageWidth << ", White pixels: " << theNumberWhitePix << std::endl;
    std::cout << "Remainder: " << std::hex << theRemainder << std::endl;

    CImg<unsigned char> image(theImageWidth, theImageHeight, 1, 3);

    unsigned int currentLocation = 0;
    for (unsigned int h = 0; h < theImageHeight; h++)
    {
        for (unsigned int w = 0; w < theImageWidth; w++)
        {
            if (currentLocation < theNumberWhitePix)
            {
                image.draw_point(w, h, white);
            }
            else if (currentLocation == theNumberWhitePix)
            {
                image.draw_point(w, h, remainder);
            }
            else
            {
                image.draw_point(w, h, black);
            }
            currentLocation++;
        }
    }
    image.save_png("primeimage.png");
    return 0;
}
