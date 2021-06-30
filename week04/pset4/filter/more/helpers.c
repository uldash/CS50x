#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    float tmpx, tmpy, tmpxy;

    RGBTRIPLE(*oimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // RGBTRIPLE(*oimage)[width] = calloc(height, (width) * sizeof(RGBTRIPLE));
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
            oimage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //###########################################################################################################################
            if (i > 0 && j > 0 && i < height - 1 && j < width - 1)
            {
                tmpx = oimage[i - 1][j - 1].rgbtBlue * gx[0][0] + oimage[i - 1][j].rgbtBlue * gx[0][1] + oimage[i - 1][j + 1].rgbtBlue * gx[0][2] +
                       oimage[i][j - 1].rgbtBlue * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + oimage[i][j + 1].rgbtBlue * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gx[2][0] + oimage[i + 1][j].rgbtBlue * gx[2][1] + oimage[i + 1][j + 1].rgbtBlue * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtBlue * gy[0][0] + oimage[i - 1][j].rgbtBlue * gy[0][1] + oimage[i - 1][j + 1].rgbtBlue * gy[0][2] +
                       oimage[i][j - 1].rgbtBlue * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + oimage[i][j + 1].rgbtBlue * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gy[2][0] + oimage[i + 1][j].rgbtBlue * gy[2][1] + oimage[i + 1][j + 1].rgbtBlue * gy[2][2];

                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtGreen * gx[0][0] + oimage[i - 1][j].rgbtGreen * gx[0][1] +
                       oimage[i - 1][j + 1].rgbtGreen * gx[0][2] +
                       oimage[i][j - 1].rgbtGreen * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + oimage[i][j + 1].rgbtGreen * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gx[2][0] + oimage[i + 1][j].rgbtGreen * gx[2][1] + oimage[i + 1][j + 1].rgbtGreen * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtGreen * gy[0][0] + oimage[i - 1][j].rgbtGreen * gy[0][1] +
                       oimage[i - 1][j + 1].rgbtGreen * gy[0][2] +
                       oimage[i][j - 1].rgbtGreen * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + oimage[i][j + 1].rgbtGreen * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gy[2][0] + oimage[i + 1][j].rgbtGreen * gy[2][1] + oimage[i + 1][j + 1].rgbtGreen * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtRed * gx[0][0] + oimage[i - 1][j].rgbtRed * gx[0][1] + oimage[i - 1][j + 1].rgbtRed * gx[0][2] +
                       oimage[i][j - 1].rgbtRed * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + oimage[i][j + 1].rgbtRed * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gx[2][0] + oimage[i + 1][j].rgbtRed * gx[2][1] + oimage[i + 1][j + 1].rgbtRed * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtRed * gy[0][0] + oimage[i - 1][j].rgbtRed * gy[0][1] + oimage[i - 1][j + 1].rgbtRed * gy[0][2] +
                       oimage[i][j - 1].rgbtRed * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + oimage[i][j + 1].rgbtRed * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gy[2][0] + oimage[i + 1][j].rgbtRed * gy[2][1] + oimage[i + 1][j + 1].rgbtRed * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i == 0 && j == 0)
            {
                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + oimage[i][j + 1].rgbtBlue * gx[1][2] +
                       0 * gx[2][0] + oimage[i + 1][j].rgbtBlue * gx[2][1] + oimage[i + 1][j + 1].rgbtBlue * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + oimage[i][j + 1].rgbtBlue * gy[1][2] +
                       0 * gy[2][0] + oimage[i + 1][j].rgbtBlue * gy[2][1] + oimage[i + 1][j + 1].rgbtBlue * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + oimage[i][j + 1].rgbtGreen * gx[1][2] +
                       0 * gx[2][0] + oimage[i + 1][j].rgbtGreen * gx[2][1] + oimage[i + 1][j + 1].rgbtGreen * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + oimage[i][j + 1].rgbtGreen * gy[1][2] +
                       0 * gy[2][0] + oimage[i + 1][j].rgbtGreen * gy[2][1] + oimage[i + 1][j + 1].rgbtGreen * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + oimage[i][j + 1].rgbtRed * gx[1][2] +
                       0 * gx[2][0] + oimage[i + 1][j].rgbtRed * gx[2][1] + oimage[i + 1][j + 1].rgbtRed * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + oimage[i][j + 1].rgbtRed * gy[1][2] +
                       0 * gy[2][0] + oimage[i + 1][j].rgbtRed * gy[2][1] + oimage[i + 1][j + 1].rgbtRed * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i == 0 && j == width - 1)
            {
                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtBlue * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + 0 * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gx[2][0] + oimage[i + 1][j].rgbtBlue * gx[2][1] + 0 * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtBlue * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + 0 * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gy[2][0] + oimage[i + 1][j].rgbtBlue * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtGreen * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + 0 * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gx[2][0] + oimage[i + 1][j].rgbtGreen * gx[2][1] + 0 * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtGreen * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + 0 * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gy[2][0] + oimage[i + 1][j].rgbtGreen * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtRed * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + 0 * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gx[2][0] + oimage[i + 1][j].rgbtRed * gx[2][1] + 0 * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtRed * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + 0 * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gy[2][0] + oimage[i + 1][j].rgbtRed * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i == height - 1 && j == 0)
            {
                tmpx = 0 * gx[0][0] + oimage[i - 1][j].rgbtBlue * gx[0][1] + oimage[i - 1][j + 1].rgbtBlue * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + oimage[i][j + 1].rgbtBlue * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = 0 * gy[0][0] + oimage[i - 1][j].rgbtBlue * gy[0][1] + oimage[i - 1][j + 1].rgbtBlue * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + oimage[i][j + 1].rgbtBlue * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + oimage[i - 1][j].rgbtGreen * gx[0][1] + oimage[i - 1][j + 1].rgbtGreen * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + oimage[i][j + 1].rgbtGreen * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = 0 * gy[0][0] + oimage[i - 1][j].rgbtGreen * gy[0][1] + oimage[i - 1][j + 1].rgbtGreen * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + oimage[i][j + 1].rgbtGreen * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + oimage[i - 1][j].rgbtRed * gx[0][1] + oimage[i - 1][j + 1].rgbtRed * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + oimage[i][j + 1].rgbtRed * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = 0 * gy[0][0] + oimage[i - 1][j].rgbtRed * gy[0][1] + oimage[i - 1][j + 1].rgbtRed * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + oimage[i][j + 1].rgbtRed * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i == height - 1 && j == width - 1)
            {
                tmpx = oimage[i - 1][j - 1].rgbtBlue * gx[0][0] + oimage[i - 1][j].rgbtBlue * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtBlue * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + 0 * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtBlue * gy[0][0] + oimage[i - 1][j].rgbtBlue * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtBlue * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + 0 * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtGreen * gx[0][0] + oimage[i - 1][j].rgbtGreen * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtGreen * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + 0 * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtGreen * gy[0][0] + oimage[i - 1][j].rgbtGreen * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtGreen * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + 0 * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtRed * gx[0][0] + oimage[i - 1][j].rgbtRed * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtRed * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + 0 * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtRed * gy[0][0] + oimage[i - 1][j].rgbtRed * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtRed * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + 0 * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i == 0 && j > 0 && j < width - 1)
            {
                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtBlue * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + oimage[i][j + 1].rgbtBlue * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gx[2][0] + oimage[i + 1][j].rgbtBlue * gx[2][1] + oimage[i + 1][j + 1].rgbtBlue * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtBlue * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + oimage[i][j + 1].rgbtBlue * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gy[2][0] + oimage[i + 1][j].rgbtBlue * gy[2][1] + oimage[i + 1][j + 1].rgbtBlue * gy[2][2];

                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtGreen * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + oimage[i][j + 1].rgbtGreen * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gx[2][0] + oimage[i + 1][j].rgbtGreen * gx[2][1] + oimage[i + 1][j + 1].rgbtGreen * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtGreen * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + oimage[i][j + 1].rgbtGreen * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gy[2][0] + oimage[i + 1][j].rgbtGreen * gy[2][1] + oimage[i + 1][j + 1].rgbtGreen * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + 0 * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtRed * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + oimage[i][j + 1].rgbtRed * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gx[2][0] + oimage[i + 1][j].rgbtRed * gx[2][1] + oimage[i + 1][j + 1].rgbtRed * gx[2][2];

                tmpy = 0 * gy[0][0] + 0 * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtRed * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + oimage[i][j + 1].rgbtRed * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gy[2][0] + oimage[i + 1][j].rgbtRed * gy[2][1] + oimage[i + 1][j + 1].rgbtRed * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i == height - 1 && j > 0 && j < width - 1)
            {
                tmpx = oimage[i - 1][j - 1].rgbtBlue * gx[0][0] + oimage[i - 1][j].rgbtBlue * gx[0][1] +
                       oimage[i - 1][j + 1].rgbtBlue * gx[0][2] +
                       oimage[i][j - 1].rgbtBlue * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + oimage[i][j + 1].rgbtBlue * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtBlue * gy[0][0] + oimage[i - 1][j].rgbtBlue * gy[0][1] +
                       oimage[i - 1][j + 1].rgbtBlue * gy[0][2] +
                       oimage[i][j - 1].rgbtBlue * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + oimage[i][j + 1].rgbtBlue * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];

                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtGreen * gx[0][0] + oimage[i - 1][j].rgbtGreen * gx[0][1] +
                       oimage[i - 1][j + 1].rgbtGreen * gx[0][2] +
                       oimage[i][j - 1].rgbtGreen * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + oimage[i][j + 1].rgbtGreen * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtGreen * gy[0][0] + oimage[i - 1][j].rgbtGreen * gy[0][1] +
                       oimage[i - 1][j + 1].rgbtGreen * gy[0][2] +
                       oimage[i][j - 1].rgbtGreen * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + oimage[i][j + 1].rgbtGreen * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtRed * gx[0][0] + oimage[i - 1][j].rgbtRed * gx[0][1] + oimage[i - 1][j + 1].rgbtRed * gx[0][2] +
                       oimage[i][j - 1].rgbtRed * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + oimage[i][j + 1].rgbtRed * gx[1][2] +
                       0 * gx[2][0] + 0 * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtRed * gy[0][0] + oimage[i - 1][j].rgbtRed * gy[0][1] + oimage[i - 1][j + 1].rgbtRed * gy[0][2] +
                       oimage[i][j - 1].rgbtRed * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + oimage[i][j + 1].rgbtRed * gy[1][2] +
                       0 * gy[2][0] + 0 * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i > 0 && i < height - 1 && j == 0)
            {
                tmpx = 0 * gx[0][0] + oimage[i - 1][j].rgbtBlue * gx[0][1] + oimage[i - 1][j + 1].rgbtBlue * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + oimage[i][j + 1].rgbtBlue * gx[1][2] +
                       0 * gx[2][0] + oimage[i + 1][j].rgbtBlue * gx[2][1] + oimage[i + 1][j + 1].rgbtBlue * gx[2][2];

                tmpy = 0 * gy[0][0] + oimage[i - 1][j].rgbtBlue * gy[0][1] + oimage[i - 1][j + 1].rgbtBlue * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + oimage[i][j + 1].rgbtBlue * gy[1][2] +
                       0 * gy[2][0] + oimage[i + 1][j].rgbtBlue * gy[2][1] + oimage[i + 1][j + 1].rgbtBlue * gy[2][2];

                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + oimage[i - 1][j].rgbtGreen * gx[0][1] + oimage[i - 1][j + 1].rgbtGreen * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + oimage[i][j + 1].rgbtGreen * gx[1][2] +
                       0 * gx[2][0] + oimage[i + 1][j].rgbtGreen * gx[2][1] + oimage[i + 1][j + 1].rgbtGreen * gx[2][2];

                tmpy = 0 * gy[0][0] + oimage[i - 1][j].rgbtGreen * gy[0][1] + oimage[i - 1][j + 1].rgbtGreen * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + oimage[i][j + 1].rgbtGreen * gy[1][2] +
                       0 * gy[2][0] + oimage[i + 1][j].rgbtGreen * gy[2][1] + oimage[i + 1][j + 1].rgbtGreen * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = 0 * gx[0][0] + oimage[i - 1][j].rgbtRed * gx[0][1] + oimage[i - 1][j + 1].rgbtRed * gx[0][2] +
                       0 * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + oimage[i][j + 1].rgbtRed * gx[1][2] +
                       0 * gx[2][0] + oimage[i + 1][j].rgbtRed * gx[2][1] + oimage[i + 1][j + 1].rgbtRed * gx[2][2];

                tmpy = 0 * gy[0][0] + oimage[i - 1][j].rgbtRed * gy[0][1] + oimage[i - 1][j + 1].rgbtRed * gy[0][2] +
                       0 * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + oimage[i][j + 1].rgbtRed * gy[1][2] +
                       0 * gy[2][0] + oimage[i + 1][j].rgbtRed * gy[2][1] + oimage[i + 1][j + 1].rgbtRed * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
            //###########################################################################################################################
            if (i > 0 && i < height - 1 && j == width - 1)
            {
                tmpx = oimage[i - 1][j - 1].rgbtBlue * gx[0][0] + oimage[i - 1][j].rgbtBlue * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtBlue * gx[1][0] + oimage[i][j].rgbtBlue * gx[1][1] + 0 * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gx[2][0] + oimage[i + 1][j].rgbtBlue * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtBlue * gy[0][0] + oimage[i - 1][j].rgbtBlue * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtBlue * gy[1][0] + oimage[i][j].rgbtBlue * gy[1][1] + 0 * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtBlue * gy[2][0] + oimage[i + 1][j].rgbtBlue * gy[2][1] + 0 * gy[2][2];

                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtBlue = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtGreen * gx[0][0] + oimage[i - 1][j].rgbtGreen * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtGreen * gx[1][0] + oimage[i][j].rgbtGreen * gx[1][1] + 0 * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gx[2][0] + oimage[i + 1][j].rgbtGreen * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtGreen * gy[0][0] + oimage[i - 1][j].rgbtGreen * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtGreen * gy[1][0] + oimage[i][j].rgbtGreen * gy[1][1] + 0 * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtGreen * gy[2][0] + oimage[i + 1][j].rgbtGreen * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtGreen = (tmpxy > 255) ? 255 : tmpxy;

                tmpx = oimage[i - 1][j - 1].rgbtRed * gx[0][0] + oimage[i - 1][j].rgbtRed * gx[0][1] + 0 * gx[0][2] +
                       oimage[i][j - 1].rgbtRed * gx[1][0] + oimage[i][j].rgbtRed * gx[1][1] + 0 * gx[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gx[2][0] + oimage[i + 1][j].rgbtRed * gx[2][1] + 0 * gx[2][2];

                tmpy = oimage[i - 1][j - 1].rgbtRed * gy[0][0] + oimage[i - 1][j].rgbtRed * gy[0][1] + 0 * gy[0][2] +
                       oimage[i][j - 1].rgbtRed * gy[1][0] + oimage[i][j].rgbtRed * gy[1][1] + 0 * gy[1][2] +
                       oimage[i + 1][j - 1].rgbtRed * gy[2][0] + oimage[i + 1][j].rgbtRed * gy[2][1] + 0 * gy[2][2];
                tmpxy = round(sqrt(pow(tmpx, 2) + pow(tmpy, 2)));
                image[i][j].rgbtRed = (tmpxy > 255) ? 255 : tmpxy;
            }
        }
    }
    free(oimage);
    return;
}
