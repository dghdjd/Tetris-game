#include "colors.h"

    const Color darkGrey    = {26, 31, 40, 255}; 
    const Color red         = RED;
    const Color orange      = ORANGE;
    const Color yellow      = YELLOW;
    const Color green       = GREEN;    
    const Color raylibWhite = RAYWHITE; 
    const Color blue        = BLUE;
    const Color purple      = PURPLE;
    const Color lightBlue   = {59, 85, 162, 255};
    

    std::vector<Color> GetCellColors()
    {
        return {darkGrey, red, orange, yellow, green, raylibWhite, blue, purple};

    }