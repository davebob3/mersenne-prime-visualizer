#  Created by David Robson on 2/23/13.
#  Copyright (c) 2013 David Robson. All rights reserved.

CC           = g++

ANSI_CFLAGS = -std=c++11
NODISPLAY_CFLAGS = -Dcimg_display=0
OPT_CFLAGS = -O3
PNG_DEFINE = -Dcimg_use_png 
PNG_CFLAGS = $(PNG_DEFINE) $(shell pkg-config --cflags libpng)
PNG_LIBS =  $(shell pkg-config --libs libpng) -lz
CIMG_DEBUG_CFLAGS = -Dcimg_verbosity=3 -Dcimg_strict_warnings -g
VT100_CFLAGS = -Dcimg_use_vt100

CIMG_FLAGS = $(ANSI_CFLAGS) $(CIMG_DEBUG_CFLAGS) $(VT100_CFLAGS) $(NODISPLAY_CFLAGS) $(PNG_CFLAGS) $(PNG_LIBS)
INCLUDE_FLAGS = -ICImg
LINK_FLAGS = -lm -lpthread

primeimage: primeimage.cpp
	$(CC) -o primeimage primeimage.cpp $(INCLUDE_FLAGS) -Wall -W -ansi -pedantic $(CIMG_FLAGS) $(LINK_FLAGS)

clean:
	$(RM) primeimage