#include <iostream>
using namespace std;
class Rectangle
{

protected:
        int width;
        int height;
public:
        Rectangle(const int width, const int height):
        width(width), height(height){};

        int get_width() const
        {
            return width;
        }

        int get_height() const
        {
            return height;
        }

        virtual void set_height(const int height)
        {
            this->height = height;
        }

        virtual void set_width(const int width)
        {
            this->width = width;
        }

        int area() const
        {
            return width * height;
        }
};

class Square:public Rectangle
{
    public:
        
        Square(int d):Rectangle(d,d){};
        
        void set_width(const int width) override
        {
                this->width = this->height = width;
        }

        void set_height(const int height) override
        {
                this->height = this->width = height;
        }
};

struct RectangleFactory
{
    static Rectangle create_rectangle(int w , int h)
    {
        return Rectangle(w, h);
    }

    static Rectangle create_square(int s)
    {
        return Rectangle(s,s);
    }
};

void transform(Rectangle &rec, int width )
{
    rec.set_width(width);
};

void printRectangle(Rectangle &rec)
{
    static int count = 0;
    count ++;
    cout<<"Rectangle "<<count<<endl;
    cout<<"Width "<<rec.get_width()<<endl;
    cout<<"Height"<< rec.get_height()<<endl;
}


int main()
{
    Rectangle rec1(10,20);
    transform(rec1,25);
    printRectangle(rec1);

    Square rec2(10);
    transform(rec2,15);
    printRectangle(rec2);

    Rectangle square = RectangleFactory::create_square(10);
    transform(square,15);
    printRectangle(square);
    
    return 0;
}