#include <cs50.h>
#include <stdio.h>

int GetHeight(void);
void DisplayPyramid(int height);

int main(void)
{
    int height = GetHeight();
    DisplayPyramid(height);
}

int GetHeight(void)
{
    int height = 0;
    
    // Prompt user for height
    do
    {
        printf("Height:");
        height = GetInt();
    }
    // Verify height is between 0 and 23 inclusive
    while ((height < 0) || (height > 23));
    
    return height;
}

void DisplayPyramid(int height)
{
    int width = height + 1;
    
    // The top row has two bricks, each subsequent row has an additional brick
    for (int row = 0, bricks = 2; row < height; ++row, ++bricks)
    {
        int spaces = width - bricks;
        // Print empty spaces first
        for (int col = 0; col < spaces; ++col)
        {
            printf(" ");
        }
        
        // Now print bricks
        for (int col = spaces; col < width; ++col)
        {
            printf("#");
        }
        
        // End of row
        printf("\n");
    }
}
