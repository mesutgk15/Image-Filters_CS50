#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through each row
    for (int i = 0; i < height; i++)
    {
        //iterate through in a row to calculate the average for each color
        for (int j = 0; j < width; j++)
        {
            int sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            int avg = round(sum / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //swap every pixel with the symetric symmetric one until halfway of width
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the input image
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initialize variables for every step of iteration
            int sum_nine_blue = 0;
            int sum_nine_green = 0;
            int sum_nine_red = 0;
            float participant_counter = 1.0;
            int average_blue = 0;
            int average_green = 0;
            int average_red = 0;
            //populate the sum for every color if the pixel is not out of edges
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sum_nine_red += image_copy[i - 1][j - 1].rgbtRed;
                sum_nine_green += image_copy[i - 1][j - 1].rgbtGreen;
                sum_nine_blue += image_copy[i - 1][j - 1].rgbtBlue;
                participant_counter++;
            }
            if (i - 1 >= 0)
            {
                sum_nine_red += image_copy[i - 1][j].rgbtRed;
                sum_nine_green += image_copy[i - 1][j].rgbtGreen;
                sum_nine_blue += image_copy[i - 1][j].rgbtBlue;
                participant_counter++;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                sum_nine_red += image_copy[i - 1][j + 1].rgbtRed;
                sum_nine_green += image_copy[i - 1][j + 1].rgbtGreen;
                sum_nine_blue += image_copy[i - 1][j + 1].rgbtBlue;
                participant_counter++;
            }
            if (j + 1 < width)
            {
                sum_nine_red += image_copy[i][j + 1].rgbtRed;
                sum_nine_green += image_copy[i][j + 1].rgbtGreen;
                sum_nine_blue += image_copy[i][j + 1].rgbtBlue;
                participant_counter++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                sum_nine_red += image_copy[i + 1][j + 1].rgbtRed;
                sum_nine_green += image_copy[i + 1][j + 1].rgbtGreen;
                sum_nine_blue += image_copy[i + 1][j + 1].rgbtBlue;
                participant_counter++;
            }
            if (i + 1 < height)
            {
                sum_nine_red += image_copy[i + 1][j].rgbtRed;
                sum_nine_green += image_copy[i + 1][j].rgbtGreen;
                sum_nine_blue += image_copy[i + 1][j].rgbtBlue;
                participant_counter++;
            }
            if (i + 1 < height &&  j - 1 >= 0)
            {
                sum_nine_red += image_copy[i + 1][j - 1].rgbtRed;
                sum_nine_green += image_copy[i + 1][j - 1].rgbtGreen;
                sum_nine_blue += image_copy[i + 1][j - 1].rgbtBlue;
                participant_counter++;
            }
            if (j - 1 >= 0)
            {
                sum_nine_red += image_copy[i][j - 1].rgbtRed;
                sum_nine_green += image_copy[i][j - 1].rgbtGreen;
                sum_nine_blue += image_copy[i][j - 1].rgbtBlue;
                participant_counter++;
            }

            sum_nine_red += image_copy[i][j].rgbtRed;
            sum_nine_green += image_copy[i][j].rgbtGreen;
            sum_nine_blue += image_copy[i][j].rgbtBlue;


            //calculate new average for each color
            average_red = round(sum_nine_red / participant_counter);
            image[i][j].rgbtRed = average_red;

            average_green = round(sum_nine_green / participant_counter);
            image[i][j].rgbtGreen = average_green;

            average_blue = round(sum_nine_blue / participant_counter);
            image[i][j].rgbtBlue = average_blue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //create a copy of the input image
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initialize the variables for every step of iteration
            int sum_gx_red = 0;
            int sum_gy_red = 0;
            int sum_gx_green = 0;
            int sum_gy_green = 0;
            int sum_gx_blue = 0;
            int sum_gy_blue = 0;
            int final_red = 0;
            int final_green = 0;
            int final_blue = 0;

            //populate gx and gy for using the Sobel Operator if the pixel is not out of edges
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sum_gx_red += image_copy[i - 1][j - 1].rgbtRed * -1;
                sum_gy_red += image_copy[i - 1][j - 1].rgbtRed * -1;

                sum_gx_green += image_copy[i - 1][j - 1].rgbtGreen * -1;
                sum_gy_green += image_copy[i - 1][j - 1].rgbtGreen * -1;

                sum_gx_blue += image_copy[i - 1][j - 1].rgbtBlue * -1;
                sum_gy_blue += image_copy[i - 1][j - 1].rgbtBlue * -1;
            }
            if (i - 1 >= 0)
            {
                sum_gy_red += image_copy[i - 1][j].rgbtRed * -2;
                sum_gy_green += image_copy[i - 1][j].rgbtGreen * -2;
                sum_gy_blue += image_copy[i - 1][j].rgbtBlue * -2;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                sum_gx_red += image_copy[i - 1][j + 1].rgbtRed * 1;
                sum_gy_red += image_copy[i - 1][j + 1].rgbtRed * -1;

                sum_gx_green += image_copy[i - 1][j + 1].rgbtGreen * 1;
                sum_gy_green += image_copy[i - 1][j + 1].rgbtGreen * -1;

                sum_gx_blue += image_copy[i - 1][j + 1].rgbtBlue * 1;
                sum_gy_blue += image_copy[i - 1][j + 1].rgbtBlue * -1;
            }
            if (j + 1 < width)
            {
                sum_gx_red += image_copy[i][j + 1].rgbtRed * 2;
                sum_gx_green += image_copy[i][j + 1].rgbtGreen * 2;
                sum_gx_blue += image_copy[i][j + 1].rgbtBlue * 2;
            }
            if (i + 1 < height && j + 1 < width)
            {
                sum_gx_red += image_copy[i + 1][j + 1].rgbtRed * 1;
                sum_gy_red += image_copy[i + 1][j + 1].rgbtRed * 1;
                sum_gx_green += image_copy[i + 1][j + 1].rgbtGreen * 1;
                sum_gy_green += image_copy[i + 1][j + 1].rgbtGreen * 1;
                sum_gx_blue += image_copy[i + 1][j + 1].rgbtBlue * 1;
                sum_gy_blue += image_copy[i + 1][j + 1].rgbtBlue * 1;
            }
            if (i + 1 < height)
            {
                sum_gy_red += image_copy[i + 1][j].rgbtRed * 2;
                sum_gy_green += image_copy[i + 1][j].rgbtGreen * 2;
                sum_gy_blue += image_copy[i + 1][j].rgbtBlue * 2;
            }
            if (j - 1 >= 0 && i + 1 < height)
            {
                sum_gx_red += image_copy[i + 1][j - 1].rgbtRed * -1;
                sum_gy_red += image_copy[i + 1][j - 1].rgbtRed * 1;
                sum_gx_green += image_copy[i + 1][j - 1].rgbtGreen * -1;
                sum_gy_green += image_copy[i + 1][j - 1].rgbtGreen * 1;
                sum_gx_blue += image_copy[i + 1][j - 1].rgbtBlue * -1;
                sum_gy_blue += image_copy[i + 1][j - 1].rgbtBlue * 1;
            }
            if (j - 1 >= 0)
            {
                sum_gx_red += image_copy[i][j - 1].rgbtRed * -2;
                sum_gx_green += image_copy[i][j - 1].rgbtGreen * -2;
                sum_gx_blue += image_copy[i][j - 1].rgbtBlue * -2;
            }

            //calculate the final int for each color using the gx and gy sums. Use a cap of 255
            final_red = round(sqrt((sum_gx_red * sum_gx_red) + (sum_gy_red * sum_gy_red)));
            if (final_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = final_red;
            }

            final_green = round(sqrt((sum_gx_green * sum_gx_green) + (sum_gy_green * sum_gy_green)));
            if (final_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = final_green;
            }

            final_blue = round(sqrt((sum_gx_blue * sum_gx_blue) + (sum_gy_blue * sum_gy_blue)));
            if (final_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = final_blue;
            }

        }
    }
    return;
}
