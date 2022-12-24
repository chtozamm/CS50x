#include "helpers.h"
#include "math.h"
#include "stdio.h" // used for "printf" function, can be removed after testing

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of RGB
            int grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaBlue = round(image[i][j].rgbtBlue * .131 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtRed * .272);
            int sepiaGreen = round(image[i][j].rgbtBlue * .168 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtRed * .349);
            int sepiaRed = round(image[i][j].rgbtBlue * .189 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtRed * .393);

            if (sepiaBlue > 255) sepiaBlue = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaRed > 255) sepiaRed = 255;

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
 for (int i = 0; i < height; i++)
    {
            for (int j = 0; j < width; j++)
            {
                for (int k = j + 1; k < width; k++)
                {
                    RGBTRIPLE tmp = image[i][j];
                    image[i][j] = image[i][k];
                    image[i][k] = tmp;
                }
            }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare and populate copy of image
    RGBTRIPLE tmp_image[height][width];
    for (int row = 0; row < height; row++)
    {
            for (int col = 0; col < width; col++)
            {
                tmp_image[row][col] = image[row][col];
            }
    }

    // Go through each pixel
    for (int row = 0; row < height; row++)
    {
            for (int col = 0; col < width; col++)
            {
                int red = 0;
                int green = 0;
                int blue = 0;

                int pixel_count = 0;

                // Go through pixel's surroundings (3x3 block)
                for (int k = -1; k < 2; k++)
                {
                        for (int l = -1; l < 2; l++)
                        {
                            if ((row+k >= 0) && (col+l >=0) && (row+k < height) && (col+l < width))
                            {
                                red += tmp_image[row+k][col+l].rgbtRed;
                                green += tmp_image[row+k][col+l].rgbtGreen;
                                blue += tmp_image[row+k][col+l].rgbtBlue;
                                pixel_count++;
                            }
                        }
                }
                image[row][col].rgbtBlue = round(blue / (float) pixel_count);
                image[row][col].rgbtGreen = round(green / (float) pixel_count);
                image[row][col].rgbtRed = round(red / (float) pixel_count);

                if (image[row][col].rgbtBlue > 255) image[row][col].rgbtBlue = 255;
                if (image[row][col].rgbtGreen > 255) image[row][col].rgbtGreen = 255;
                if (image[row][col].rgbtRed > 255) image[row][col].rgbtRed = 255;
            }
    }
    return;
}