#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum class Cap{mini, small, mid, large, superb};
enum class Industry{finance, telecommunicate, realEstate, energy, healthCare, Tech};
enum class Profit{veryBad, bad, neutral, good, veryGood};
enum class Rating{AAA,AA,A,BBB,BB,B,CCC,CC,C,D};

struct Stock
{
    string name;
    Cap cap;
    Industry industry;
    Profit profit;
    Rating rating;
};

template <typename T> struct AndSpecification;

template <typename T> 
struct Specification
{
    virtual ~Specification() = default;
    virtual bool is_satisfied(T *item) const = 0;
};

template <typename T>
AndSpecification<T> operator&&(const Specification<T> &first, const Specification<T> &second)
{
    return { first, second};
}

template <typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct StockFilter: Filter<Stock>
{
    vector<Stock*> filter(vector<Stock*> items, Specification<Stock> &spec) override
    {
        vector<Stock*> result;
        for(auto &p : items)
        {
            if( spec.is_satisfied(p))
            {
                result.push_back(p);
            }
        }
        return result;
    } 
};

struct CapSpecification:Specification<Stock>
{
    Cap cap;
    explicit CapSpecification(const Cap cap): cap(cap)
    {}

    bool is_satisfied(Stock *item)const override
    {
        return item->cap == cap;
    }
};

struct IndustrySpecification:Specification<Stock>
{   
    Industry industry;
    explicit IndustrySpecification(const Industry industry):industry(industry)
    {}

    bool is_satisfied(Stock *item) const override
    {
        return item->industry == industry;
    }
};

struct ProfitSpecification:Specification<Stock>
{
    Profit profit;
    explicit ProfitSpecification(const Profit profit): profit(profit)
    {}

    bool is_satisfied(Stock *item)const override
    {
        return item->profit == profit;
    } 
};

struct RatingSpecification:Specification<Stock>
{
    Rating rating;
    explicit RatingSpecification(const Rating rating): rating(rating)
    {}

    bool is_satisfied(Stock *item) const override
    {
        return item->rating == rating;
    }
};

template <typename T>
struct AndSpecification:Specification<T>
{
    const Specification<T> &first;
    const Specification<T> &second;

    AndSpecification(const Specification<T> &first, const Specification<T> &second)
    :first(first), second(second){}

    bool is_satisfied(T *item) const override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main()
{
    Stock apple{"Apple",Cap::superb, Industry::telecommunicate, Profit::good, Rating::AA};
    Stock msft{"MSFT",Cap::superb, Industry:: Tech, Profit::veryGood, Rating::AAA};
    Stock jj{"J&J",Cap::large, Industry::healthCare, Profit::good, Rating::A};
    Stock albb{"ALIBABA", Cap::superb, Industry::Tech, Profit::veryGood, Rating::AAA};
    Stock JPMG{"JP-Morgan", Cap::superb,Industry::finance, Profit::good,Rating::AAA};

    StockFilter stockFilter;
    const vector<Stock*> stocks{&apple, &msft, &jj, &albb, &JPMG};

    CapSpecification capSpecification(Cap::superb);
    auto SuperbStocks = stockFilter.filter(stocks, capSpecification);
    for(auto &s : SuperbStocks)
    {
        cout<<"Superb Stock: "<<s->name<<endl;
    }

    RatingSpecification ratingSpecification(Rating::AAA);
    auto AAAStocks = stockFilter.filter(stocks, ratingSpecification);
    for(auto &s : AAAStocks)
    {
        cout<<"AAA Stocks: "<<s->name<<endl;
    }
    return 0;

}