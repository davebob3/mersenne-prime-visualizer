//
//  main.cpp
//  Mersenne Prime Image
//
//  Created by David Robson on 2/23/13.
//  Copyright (c) 2013 David Robson. All rights reserved.
//

#include <iostream>
#include "CImg/CImg.h"

using namespace cimg_library;

int main(int argc, const char *argv[])
{
    unsigned int thePrimeFactor = 136279841;
    unsigned int theImageWidth = 400;
    unsigned int theImageHeight = 300;
    unsigned int theIncrement = 100;
    unsigned int theNumberWhitePix = thePrimeFactor / 24;
    unsigned int theRemainderNum = thePrimeFactor % 24;
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
    std::cout << "Width: " << theImageWidth << std::endl;
    std::cout << "Height: " << theImageHeight << std::endl;
    std::cout << "Size: " << theImageHeight * theImageWidth << std::endl;
    std::cout << "Whitepix: " << theNumberWhitePix << std::endl;
    std::cout << "Remainder: " << std::hex << theRemainder << std::endl;

    for (int c = 0; c < 3; c++)
    {
        std::cout << (int)remainder[c] << std::endl;
    }

    CImg<unsigned char> image(theImageWidth, theImageHeight, 1, 3);

    cimg::info();
    // int totalSize = theImageWidth * theImageHeight;
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
    //image.save_imagemagick_external("primeimage.im");
    return 0;
}
