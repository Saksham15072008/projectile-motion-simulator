#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main()
{
    float u, theta, g = 9.8;
    int rows = 15, cols = 70;   /* size of the "screen" */
    int r, c;

    printf("Enter initial velocity u (m/s): ");
    scanf("%f", &u);
    printf("Enter angle theta (degrees, 1 to 89): ");
    scanf("%f", &theta);

    if (u <= 0 || theta <= 0 || theta >= 90)
    {
        printf("Please enter u > 0 and 0 < theta < 90\n");
        return 0;
    }

    float th = theta * PI / 180;          /* degrees -> radians */

    float T = 2 * u * sin(th) / g;                      /* time of flight */
    float H = (u * sin(th)) * (u * sin(th)) / (2 * g);  /* max height     */
    float R = u * u * sin(2 * th) / g;                  /* range          */

    printf("\nTime of flight = %.2f seconds\n", T);
    printf("Max height     = %.2f meters\n", H);
    printf("Range          = %.2f meters\n\n", R);

    /* Draw row by row, from the top (max height) down to the ground */
    for (r = rows; r >= 0; r--)
    {
        for (c = 0; c <= cols; c++)
        {
            /* horizontal distance this column represents */
            float x = R * c / cols;

            /* height of the ball at that x: y = x tan(th) - g x^2 / (2 u^2 cos^2(th)) */
            float y = x * tan(th) - g * x * x / (2 * u * u * cos(th) * cos(th));

            /* which screen row does that height fall in? */
            int yrow = (int)(y / H * rows + 0.5);

            if (c == cols / 2 && r == rows / 2)
            {
                printf("|");
                /* printf returns how many characters it printed,
                   so we skip that many columns */
                c += printf(" Max height = %.2f m", H);
            }
            else if (yrow == r)
                printf("*");            /* ball path */
            else if (c == cols / 2)
                printf("|");            /* line marking max height */
            else if (r == 0)
                printf("_");            /* ground */
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("<%*s R = %.2f m %*s>\n", cols / 2 - 12, "", R, cols / 2 - 12, "");

    return 0;
}
