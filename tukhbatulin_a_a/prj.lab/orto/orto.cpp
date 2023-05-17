#include <iostream>
class Quad{
public:
    int x1, x2, y1, y2;
public:
  Quad(int x1,int x2,int y1,int y2) {
        x1 = x1;
        y1 = y1;
        x2 = x2;
        y2 = y1;
    }
};
class Rect : public Quad {
public:
    Rect(int x1, int y1, int x2, int y2) : Quad(x1, y1, x2, y2) {};
    void scale(int k) {
        int mid_x = (x1 + x2) / 2;
        int mid_y = (y1 + y2) / 2;
        int width = x2 - x1;
        int height = y2 - y1;
        int new_widht = width * k;
        int new_height = height * k;
        x1 = mid_x - new_widht / 2;
        y1 = mid_y - new_height / 2;
        x2 = mid_x + new_widht / 2;
        y2 = mid_y + new_height / 2;
    };
    Rect intersect(Rect r) {
        int nx1 =std::max(x1, r.x1);
        int ny1 = std::max(y1, r.y1);
        int nx2 = std::min(x2, r.x2);
        int ny2 = std::min(y2, r.y2);

    }
};
class Squad : public Quad {
};
int main()
{
    Rect r1(0, 0, 5, 5);
    Rect r2(3, 3, 8, 8);
    Rect r3 = r1.intersect(r2);

}
































