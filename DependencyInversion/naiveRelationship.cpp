//g++ naiveRelationship.cpp -o naiveRelationship -std=gnu++1z

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

struct Relationships
{
    //a vector to save relations
    vector<tuple<Person, Relationship, Person>> relations;
    void add_parent_and_child(const Person &parent, const Person &child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }
};

struct Research
{
    Research(const Relationships& relationships)
    {
        auto & relations = relationships.relations;

        for(auto && [first, rel, second] : relations)
        {
            if( first.name == "John" && rel == Relationship::parent)
            {
                cout<<"John has a child called "<< second.name<<endl;
            }
        }
    }
};


int main()
{
    //Person is a struct type
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);
}

