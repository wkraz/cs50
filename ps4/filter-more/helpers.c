#include "helpers.h"
#include <math.h>

// Convert image to grayscale
// take average of all 3 colors, and then make that average the value of every color
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red_pixel_value = round(image[i][j].rgbtRed);
            float green_pixel_value = round(image[i][j].rgbtGreen);
            float blue_pixel_value = round(image[i][j].rgbtBlue);
            float average_float = (red_pixel_value + green_pixel_value + blue_pixel_value) / 3;
            int average = round(average_float);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
// swap x coordinates up to the mid point
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
// First include if statement to only look at pixels next to it (edges)
// Then take average of neighbors and make that the RGB value
// have to make a copy so that the original isn't messed up
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red, sum_green, sum_blue;
            sum_red = sum_green = sum_blue = 0;
            int count = 0;
            // look at neighbors and find sum
            for (int i1 = i - 1; i1 <= i + 1; i1++)
            {
                for (int j1 = j - 1; j1 <= j + 1; j1++)
                {
                    if (i1 >= 0 && i1 <= height - 1 && j1 >= 0 && j1 <= width - 1)
                    {
                        sum_red = sum_red + copy[i1][j1].rgbtRed;
                        sum_green = sum_green + copy[i1][j1].rgbtGreen;
                        sum_blue = sum_blue + copy[i1][j1].rgbtBlue;
                        count++;
                    }
                }
            }
            int average_red = round((double) sum_red / (double) count);
            int average_green = round((double) sum_green / (double) count);
            int average_blue = round((double) sum_blue / (double) count);
            image[i][j].rgbtRed = average_red;
            image[i][j].rgbtGreen = average_green;
            image[i][j].rgbtBlue = average_blue;
        }
    }
    return;
}

// Detect edges
// Multiply 3 pixels on the right (3x3 box) and subtract it from the product of 3 pixels on the left
// This is for Gx
// Do the same for Gy
// Take sqrt(Gx ^ 2 + Gy ^ 2)
// Round this to the nearest int (0 - 255)
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_red, Gx_green, Gx_blue, Gy_red, Gy_green, Gy_blue;
            Gx_red = Gx_green = Gx_blue = Gy_red = Gy_green = Gy_blue = 0;
            for (int i1 = -1; i1 <= 1; i1++)
            {
                for (int j1 = -1; j1 <= 1; j1++)
                {
                    int i2 = i1 + i;
                    int j2 = j1 + j;
                    if (i2 >= 0 && i2 < height && j2 >= 0 && j2 < width)
                    {
                        // Gx & Gy calculations
                        Gx_red += copy[i2][j2].rgbtRed * Gx[i1 + 1][j1 + 1];
                        Gx_green += copy[i2][j2].rgbtGreen * Gx[i1 + 1][j1 + 1];
                        Gx_blue += copy[i2][j2].rgbtBlue * Gx[i1 + 1][j1 + 1];
                        Gy_red += copy[i2][j2].rgbtRed * Gy[i1 + 1][j1 + 1];
                        Gy_green += copy[i2][j2].rgbtGreen * Gy[i1 + 1][j1 + 1];
                        Gy_blue += copy[i2][j2].rgbtBlue * Gy[i1 + 1][j1 + 1];
                    }
                }
            }
            // G
            int G_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int G_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int G_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // cap at 255
            if (G_red > 255)
                G_red = 255;
            if (G_green > 255)
                G_green = 255;
            if (G_blue > 255)
                G_blue = 255;

            // update pixel w/ G value
            image[i][j].rgbtRed = G_red;
            image[i][j].rgbtGreen = G_green;
            image[i][j].rgbtBlue = G_blue;
        }
    }
    return;
}
