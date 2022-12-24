#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tmp_image[row][col] = image[row][col];
        }
    }

    // Go through each pixel of an image
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int Gx_red = 0;
            int Gy_red = 0;
            int Gx_green = 0;
            int Gy_green = 0;
            int Gx_blue = 0;
            int Gy_blue = 0;

            // Go through surroundings of pixel (3x3 block)
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (row + i == 0)
                    // Conditions: not to exceed the borders
                    if ((row + i >= 0) && (col + j >= 0) && (row + i < height) && (col + j < width))
                    {
                        // For Gx:
                        if ((i == -1) || (i == 1))
                        {
                            Gx_red += tmp_image[row + i][col + j].rgbtRed * j;
                            Gx_green += tmp_image[row + i][col + j].rgbtGreen * j;
                            Gx_blue += tmp_image[row + i][col + j].rgbtBlue * j;
                        }
                        else if (i == 0)
                        {
                            Gx_red += tmp_image[row + i][col + j].rgbtRed * 2 * j;
                            Gx_green += tmp_image[row + i][col + j].rgbtGreen * 2 * j;
                            Gx_blue += tmp_image[row + i][col + j].rgbtBlue * 2 * j;
                        }

                        // For Gy:
                        if ((j == -1) || (j == 1))
                        {
                            Gy_red += tmp_image[row + i][col + j].rgbtRed * i;
                            Gy_green += tmp_image[row + i][col + j].rgbtGreen * i;
                            Gy_blue += tmp_image[row + i][col + j].rgbtBlue * i;
                        }
                        else if (j == 0)
                        {
                            Gy_red += tmp_image[row + i][col + j].rgbtRed * 2 * i;
                            Gy_green += tmp_image[row + i][col + j].rgbtGreen * 2 * i;
                            Gy_blue += tmp_image[row + i][col + j].rgbtBlue * 2 * i;
                        }
                    }
                }
            }

            image[row][col].rgbtRed = sqrt(Gx_red * Gx_red + Gy_red * Gy_red);
            image[row][col].rgbtGreen = sqrt(Gx_green * Gx_green + Gy_green * Gy_green);
            image[row][col].rgbtBlue = sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue);

            if (image[row][col].rgbtRed > 255)
                image[row][col].rgbtRed = 255;
            if (image[row][col].rgbtGreen > 255)
                image[row][col].rgbtGreen = 255;
            if (image[row][col].rgbtBlue > 255)
                image[row][col].rgbtBlue = 255;
        }
    }

    return;
}
