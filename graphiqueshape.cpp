#include <iostream>
#include <stdexcept>

class Shape {
    int x ;
    int y ;
    if (x<0) or (y<0){
        throw std::invalid_argument("push error: negative argument");
    }

protected:
    Shape(int x, int y)  : x(x), y(y) {}

public:
    virtual double area() {return -99; }
    void move(int dx, int dy)
    {
        x = x + dx;       
        y = y + dy;
    }
};
class Circle : public Shape
{
    int radius;

public: //tjr mettre public
    Circle(int x, int y, int r) : Shape(x, y), radius(r) 
    {
    }
    double area () {
        return 3.14159 * radius * radius ;
    }
};

int main()
{
    Circle c1(100, 300, 56);
    c1.move(8, 10);
    std::cout << c1.area() << std::endl;

    Rectangle r1(100, 300, 56, 67);
    r1.move(8, 10);
    std::cout << r1.area() << std::endl;

    std::vector <Shape*> shapes;
    shapes.push_back(&c1);
    shapes.push_back(&r1)

    for(int i = 0; i < shapes.size)


    Shape* ps1 = &c1;
    Shape& rs1 = c1;
    
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }


}