# Visualize a Mersenne Prime

This program creates a digital representation of 2<sup>136279841</sup> - 1 as a PNG image.

This was written as a rebuke to an article I read in 2013 (link lost) where an artist took 
the largest known Mersenne prime at the time and converted the decimal string to RGB values. 
I thought that was ridiculous, because a Mersenne prime's specialness is best visualized in 
base-2.

This program converts the **binary** representation of 2<sup>136279841</sup> - 1 into RGB 
values and outputs them as a PNG image.

It uses the [CImg library](https://github.com/GreycLab/CImg) to create the image.

Current largest prime was found on [Great Internet Mersenne Prime Search](https://www.mersenne.org/).

## to build

1. clone and cd into this repo.
2. `git submodule update --init`
3. run make

## to run 
`./primeimage`

The program will create a file named "primeimage.png" in the current working directory.
