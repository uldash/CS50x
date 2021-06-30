#include <stdio.h>
#include "helpers.h"
#include "math.h"
#include <stdint.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t grscl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grscl = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = grscl;
            image[i][j].rgbtGreen = grscl;
            image[i][j].rgbtRed = grscl;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int r, g, b;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            g = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            b = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtBlue = (b > 255) ? 255 : b;
            image[i][j].rgbtGreen = (g > 255) ? 255 : g;
            image[i][j].rgbtRed = (r > 255) ? 255 : r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t r, g, b;
    RGBTRIPLE(*image_original)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fprintf(stderr, "Not enough memory to store image.\n");
        return;
    }
    // save original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_original[i][j] = image[i][j];
        }
    }

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtBlue = round((image_original[i - 1][j - 1].rgbtBlue + image_original[i - 1][j].rgbtBlue +
                                          image_original[i - 1][j + 1].rgbtBlue + image_original[i][j - 1].rgbtBlue +
                                          image_original[i][j].rgbtBlue + image_original[i][j + 1].rgbtBlue +
                                          image_original[i + 1][j - 1].rgbtBlue + image_original[i + 1][j].rgbtBlue +
                                          image_original[i + 1][j + 1].rgbtBlue) / 9.0);
            image[i][j].rgbtGreen = round((image_original[i - 1][j - 1].rgbtGreen + image_original[i - 1][j].rgbtGreen +
                                           image_original[i - 1][j + 1].rgbtGreen + image_original[i][j - 1].rgbtGreen +
                                           image_original[i][j].rgbtGreen + image_original[i][j + 1].rgbtGreen +
                                           image_original[i + 1][j - 1].rgbtGreen + image_original[i + 1][j].rgbtGreen +
                                           image_original[i + 1][j + 1].rgbtGreen) / 9.0);
            image[i][j].rgbtRed = round((image_original[i - 1][j - 1].rgbtRed + image_original[i - 1][j].rgbtRed +
                                         image_original[i - 1][j + 1].rgbtRed + image_original[i][j - 1].rgbtRed +
                                         image_original[i][j].rgbtRed + image_original[i][j + 1].rgbtRed +
                                         image_original[i + 1][j - 1].rgbtRed + image_original[i + 1][j].rgbtRed +
                                         image_original[i + 1][j + 1].rgbtRed) / 9.0);
        }
    }

    // UP LEFT
    image[0][0].rgbtBlue = round((image_original[0][0].rgbtBlue + image_original[0][1].rgbtBlue +
                                  image_original[1][0].rgbtBlue + image_original[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = round((image_original[0][0].rgbtGreen + image_original[0][1].rgbtGreen +
                                   image_original[1][0].rgbtGreen + image_original[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = round((image_original[0][0].rgbtRed + image_original[0][1].rgbtRed + image_original[1][0].rgbtRed +
                                 image_original[1][1].rgbtRed) / 4.0);
    // UP RIGHT
    image[0][width - 1].rgbtBlue = round((image_original[0][width - 2].rgbtBlue + image_original[0][width - 1].rgbtBlue +
                                          image_original[1][width - 2].rgbtBlue + image_original[1][width - 1].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = round((image_original[0][width - 2].rgbtGreen + image_original[0][width - 1].rgbtGreen +
                                           image_original[1][width - 2].rgbtGreen + image_original[1][width - 1].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = round((image_original[0][width - 2].rgbtRed + image_original[0][width - 1].rgbtRed +
                                         image_original[1][width - 2].rgbtRed + image_original[1][width - 1].rgbtRed) / 4.0);
    // DOWN LEFT
    image[height - 1][0].rgbtBlue = round((image_original[height - 2][0].rgbtBlue + image_original[height - 2][1].rgbtBlue +
                                           image_original[height - 1][0].rgbtBlue + image_original[height - 1][1].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtGreen = round((image_original[height - 2][0].rgbtGreen + image_original[height - 2][1].rgbtGreen +
                                            image_original[height - 1][0].rgbtGreen + image_original[height - 1][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtRed = round((image_original[height - 2][0].rgbtRed + image_original[height - 2][1].rgbtRed +
                                          image_original[height - 1][0].rgbtRed + image_original[height - 1][1].rgbtRed) / 4.0);
    // DOWN RIGHT
    image[height - 1][width - 1].rgbtBlue = round((image_original[height - 2][width - 2].rgbtBlue +
                                            image_original[height - 2][width - 1].rgbtBlue +
                                            image_original[height - 1][width - 2].rgbtBlue +
                                            image_original[height - 1][width - 1].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtGreen = round((image_original[height - 2][width - 2].rgbtGreen +
            image_original[height - 2][width - 1].rgbtGreen + image_original[height - 1][width - 2].rgbtGreen +
            image_original[height - 1][width - 1].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtRed = round((image_original[height - 2][width - 2].rgbtRed +
                                           image_original[height - 2][width - 1].rgbtRed + image_original[height - 1][width - 2].rgbtRed +
                                           image_original[height - 1][width - 1].rgbtRed) / 4.0);

    // LEFT
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtBlue = round((image_original[i - 1][0].rgbtBlue + image_original[i - 1][1].rgbtBlue +
                                      image_original[i][0].rgbtBlue + image_original[i][1].rgbtBlue + image_original[i + 1][0].rgbtBlue +
                                      image_original[i + 1][1].rgbtBlue) / 6.0);
        image[i][0].rgbtGreen = round((image_original[i - 1][0].rgbtGreen + image_original[i - 1][1].rgbtGreen +
                                       image_original[i][0].rgbtGreen + image_original[i][1].rgbtGreen + image_original[i + 1][0].rgbtGreen +
                                       image_original[i + 1][1].rgbtGreen) / 6.0);
        image[i][0].rgbtRed = round((image_original[i - 1][0].rgbtRed + image_original[i - 1][1].rgbtRed + image_original[i][0].rgbtRed +
                                     image_original[i][1].rgbtRed + image_original[i + 1][0].rgbtRed + image_original[i + 1][1].rgbtRed) / 6.0);
        // image[i][0].rgbtBlue = 0;
        // image[i][0].rgbtGreen = 255;
        // image[i][0].rgbtRed = 0;
    }
    // RIGHT
    for (int i = 1; i < height - 1; i++)
    {
        image[i][width - 1].rgbtBlue = round((image_original[i - 1][width - 1].rgbtBlue + image_original[i - 1][width - 2].rgbtBlue +
                                              image_original[i][width - 1].rgbtBlue + image_original[i][width - 2].rgbtBlue +
                                              image_original[i + 1][width - 1].rgbtBlue + image_original[i + 1][width - 2].rgbtBlue) / 6.0);
        image[i][width - 1].rgbtGreen = round((image_original[i - 1][width - 1].rgbtGreen + image_original[i - 1][width - 2].rgbtGreen +
                                               image_original[i][width - 1].rgbtGreen + image_original[i][width - 2].rgbtGreen +
                                               image_original[i + 1][width - 1].rgbtGreen + image_original[i + 1][width - 2].rgbtGreen) / 6.0);
        image[i][width - 1].rgbtRed = round((image_original[i - 1][width - 1].rgbtRed + image_original[i - 1][width - 2].rgbtRed +
                                             image_original[i][width - 1].rgbtRed + image_original[i][width - 2].rgbtRed +
                                             image_original[i + 1][width - 1].rgbtRed + image_original[i + 1][width - 2].rgbtRed) / 6.0);
        // image[i][width - 1].rgbtBlue = 0;
        // image[i][width - 1].rgbtGreen = 255;
        // image[i][width - 1].rgbtRed = 0;
    }
    // UP
    for (int j = 1; j < width - 1; j++)
    {
        image[0][j].rgbtBlue = round((image_original[0][j - 1].rgbtBlue + image_original[0][j].rgbtBlue +
                                      image_original[0][j + 1].rgbtBlue + image_original[1][j - 1].rgbtBlue +
                                      image_original[1][j].rgbtBlue + image_original[1][j + 1].rgbtBlue) / 6.0);
        image[0][j].rgbtGreen = round((image_original[0][j - 1].rgbtGreen + image_original[0][j].rgbtGreen +
                                       image_original[0][j + 1].rgbtGreen + image_original[1][j - 1].rgbtGreen +
                                       image_original[1][j].rgbtGreen + image_original[1][j + 1].rgbtGreen) / 6.0);
        image[0][j].rgbtRed = round((image_original[0][j - 1].rgbtRed + image_original[0][j].rgbtRed + image_original[0][j + 1].rgbtRed +
                                     image_original[1][j - 1].rgbtRed + image_original[1][j].rgbtRed + image_original[1][j + 1].rgbtRed) / 6.0);
        // image[0][j].rgbtBlue = 0;
        // image[0][j].rgbtGreen = 255;
        // image[0][j].rgbtRed = 0;
    }
    // DOWN
    for (int j = 1; j < width - 1; j++)
    {
        image[height - 1][j].rgbtBlue = round((image_original[height - 2][j - 1].rgbtBlue + image_original[height - 2][j].rgbtBlue +
                                               image_original[height - 2][j + 1].rgbtBlue + image_original[height - 1][j - 1].rgbtBlue +
                                               image_original[height - 1][j].rgbtBlue + image_original[height - 1][j + 1].rgbtBlue) / 6.0);
        image[height - 1][j].rgbtGreen = round((image_original[height - 2][j - 1].rgbtGreen + image_original[height - 2][j].rgbtGreen +
                                                image_original[height - 2][j + 1].rgbtGreen + image_original[height - 1][j - 1].rgbtGreen +
                                                image_original[height - 1][j].rgbtGreen + image_original[height - 1][j + 1].rgbtGreen) / 6.0);
        image[height - 1][j].rgbtRed = round((image_original[height - 2][j - 1].rgbtRed + image_original[height - 2][j].rgbtRed +
                                              image_original[height - 2][j + 1].rgbtRed + image_original[height - 1][j - 1].rgbtRed +
                                              image_original[height - 1][j].rgbtRed + image_original[height - 1][j + 1].rgbtRed) / 6.0);
        // image[height - 1][j].rgbtBlue =0;
        // image[height - 1][j].rgbtGreen = 255;
        // image[height - 1][j].rgbtRed = 0;
    }
    free(image_original);
    return;
}