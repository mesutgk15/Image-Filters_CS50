# Image-Filters_CS50
Project creates four different image filter for one of CS50 projects. These filters are grayscale, reflection (x axis), blur and edges (edge detection).
File includes its own prototype header file for these functions. And the RGBTRIPLE data structure is defined in another header file so it goes as in following;
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
