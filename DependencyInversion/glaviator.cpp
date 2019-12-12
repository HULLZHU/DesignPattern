//He Zhu's example for DIP
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Glaviator;

struct Equipment
{
    string name;
    double damage;
    double defense;

    Equipment(string name, double damage, double defense):
    damage(damage), defense(defense),name(name){};

    virtual ~Equipment() = default;

    virtual void describe()
    {
        cout<<name<<endl;
        cout<<"Damage\t"<<damage<<endl;
        cout<<"Defense\t"<<defense<<endl;
        cout<<"----------------------"<<endl;
    };
};

struct Armor: public Equipment
{
    string name;

    Armor(string name, double damage, double defense):
    Equipment(name,damage, defense){};

};

struct Weapon: public Equipment
{
    string name;

    Weapon(string name, double damage, double defense):
    Equipment(name, damage, defense){};
};

class Glaviator
{   public:
    string name;
    double damage;
    double defense;

    vector<Equipment> equipments;
    
    Glaviator(string name):name(name)
    {
        damage = 0;
        defense = 0;
    };

    //role methods
    virtual void describe()const{};

    //battle methods
    virtual double attack(){};
    virtual double defend(){};

    //preparation methods
    void mount(const Equipment &e)
    {
        damage += e.damage;
        defense += e.defense;
        equipments.push_back(e);
    }

    void unmount(const Equipment &e)
    {   
        damage -= e.damage;
        damage -= e.defense;
        for( int i = 0 ; i < equipments.size(); i ++ )
        {
            if(equipments[i].name == e.name)
            {
                equipments.erase(equipments.begin() + i);
                break;
            }
        }
    }

};

class Swordsman : public Glaviator
{   
    public:
    Swordsman(string name):Glaviator(name)
    {
        damage = 100;
        defense = 100;
    }

    void describe() const override
    {
        cout<<"Name:\t"<<name<<endl;
        cout<<"Role:\t"<<"Swordsman"<<endl;
        cout<<"Attack: \t"<<damage<<endl;
        cout<<"Defense: \t"<<defense<<endl;   
        cout<<"List of Equipments\t"<<endl;
        cout<<"------------------------\t"<<endl;
        cout<<"Totally "<<equipments.size()<<" Equipments"<<endl;

        for( auto i : equipments)
        {
            // (&i)->describe();
            i.describe();
        }
    }

    double attack() override
    {
        cout<<"Swordsman "<<name<<" attacks +"<<damage<<endl;
        return damage;
    }

    double defend() override
    {   
        cout<<"Swordsman "<<name<<" defend -"<<damage<<endl;
        return defense;
    }
};

// struct Ranger: public Glaviator
// {
// };

// struct Magician: public Glaviator
// {
// };


//place for battle
struct Arena
{
    Glaviator *glaviator1;
    Glaviator *glaviator2;

    Arena(Glaviator &g1, Glaviator &g2):glaviator1(&g1), glaviator2(&g2)
    {
        cout<<"Battle Start"<<endl;
        cout<<g1.name<<" vs "<<g2.name<<endl;
        glaviator1->describe();
        glaviator2->describe();
    };

};

int main()
{
    Swordsman alex("Alex");
    alex.mount(Weapon("BlackSword",100,20));
    alex.mount(Armor("Anti-Armor",12,80));

    Swordsman crisus("Crisus");
    crisus.mount(Weapon("HolySword",200,-40));
    crisus.mount(Armor("Strong-Armor",30,80));
    
    Arena arena(alex,crisus);
    
    return 0;
}