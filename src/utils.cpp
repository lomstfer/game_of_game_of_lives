#include <utils.hpp>

Vector2 operator/(Vector2 v, float f) {
    return Vector2{v.x / f, v.y / f};
}

Vector2 operator*(Vector2 v, float f) {
    return Vector2{v.x / f, v.y / f};
}

std::ostream& operator<<(std::ostream& os, Vector2 v) {
    os << v.x << "; " << v.y;
    return os;
}

int who_won(std::vector<std::vector<cell>> &world) 
{
    int blue_count = 0;
    int red_count = 0;
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {

            switch (world[x][y].type)
            {
            case team_red:
                red_count++;
                break;
            
            case team_blue:
                blue_count++;
                break;
            }

        }   
    }
    if (blue_count > red_count) {
        return team_blue;
    }
    else {
        return team_red;
    }
}