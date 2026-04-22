#include <iostream>

class Figure {
    private:
    float area;
    void calculate_area() {
        this->area = 0;
    }


    public:
    int x, y;

    Figure (int _x, int _y)
    {
        printf("Figure:Constructor with parameters called\n");
        this->x = _x;
        this->y = _y;
    }
    Figure (const Figure &f)
    {
        printf("Figure:Copy constructor called\n");
        this->x = f.x;
        this->y = f.y;
    }
    Figure ()
    {
        printf("Figure:Default constructor called\n");
        this->x = 0;
        this->y = 0;
    }

    void print()
    {
        printf("x: %d, y: %d\n", this->x, this->y);
    }

    void print_calculate_area()
    {   
        printf("Area for point?\n");
        calculate_area();
        printf("Figure:Area: %f\n", this->area);
    }

    void set_x(int _x)
    {
        this->x = _x;
    }

    void set_y(int _y)
    {
        this->y = _y;
    }

    ~Figure ()
    {
        printf("Figure:Destructor called\n");
    }
};

class Rectangle:public Figure
{
    private:
    float area;
    void calculate_area() {
        this->area = this->width * this->height;
    }
    public:
    int width, height;
    Rectangle (int _x, int _y, int _width, int _height):Figure(_x, _y)
    {
        printf("Rectangle:Constructor with parameters called\n");
        this->width = _width;
        this->height = _height;
    }
    Rectangle (const Rectangle &r):Figure(r)
    {
        printf("Rectangle:Copy constructor called\n");
        this->width = r.width;
        this->height = r.height;
    }
    Rectangle ():Figure()
    {
        printf("Rectangle:Default constructor called\n");
        this->width = 0;
        this->height = 0;
    }

     void print()
    {
        Figure::print();
        printf("width: %d, height: %d\n", this->width, this->height);
    }

     void print_calculate_area()
    {   
        this->area = this->width * this->height;
        printf("Area: %f\n", this->area);
    }

     ~Rectangle ()
    {
        printf("Rectangle:Destructor called\n");
    }
};





void use_figure()
{
    Figure f1(1, 2);
    Figure f2 = f1;
    Figure f3;
    f1.print();
    f2.print();
    f3.print();
    f1.print_calculate_area();
    f2.print_calculate_area();
    f3.print_calculate_area();
}

void use_rectangle()
{
    Rectangle r1(1, 2, 3, 4);
    Rectangle r2 = r1;
    Rectangle r3;
    r1.print();
    r2.print();
    r3.print();
    r1.print_calculate_area();
    r2.print_calculate_area();
    r3.print_calculate_area();
}

int main() {
    use_figure();
    printf("\n");
    use_rectangle();
    return 0;
}
