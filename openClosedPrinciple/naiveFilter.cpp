#include <vector>
#include <iostream>
#include <string>
using namespace std;

//define 2 enumerate class
enum class Color{red, green, blue};
enum class Size {small, medium,large};

//define a product structure
struct Product
{
    string name;
    Color color;
    Size size;
};

//naive methods
struct ProductFilter
{   

    vector<Product*> by_color(vector<Product*> items, const Color color)
    {
        vector<Product*> result;

        for(auto & i : items)
        {
            if( i -> color == color)
                result.push_back(i);
        }
        return result;
    }

    vector<Product*> by_size(vector<Product*> items, const Size size)
    {
        vector<Product*> result;

        for( auto & i : items)
        {
            if( i -> size == size )
                result.push_back(i);
        }
        return result;
    }

    vector<Product*> by_size_and_color(vector<Product*> items, const Size size, const Color color)
    {
        vector<Product *> result;
        for(auto &i : items)
        {
            if( i->size == size && i->color == color)
            {
                result.push_back(i);
            }
        return result;
        }
    }
};

int main()
{   
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    vector<Product*> items{&apple, &tree, &house};

    ProductFilter pf;
    auto green_things = pf.by_color(items, Color::green);

    for(auto &item: green_things)
    {
        cout<<item->name<<" is green \n";
    }
}