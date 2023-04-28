#include <utils.hpp>
#include <cell.hpp>

Vector2 operator/(Vector2 v, float f) {
    return Vector2{v.x / f, v.y / f};
}

Vector2 operator*(Vector2 v, float f) {
    return Vector2{v.x / f, v.y / f};
}

std::ostream& operator<<(std::ostream& os, Vector2 v) {
    os << v.x << ", " << v.y;
    return os;
}

std::ostream& operator<<(std::ostream& os, Vec2Int v) {
    os << v.x << ", " << v.y;
    return os;
}