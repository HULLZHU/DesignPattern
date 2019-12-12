#include<string>
#include<iostream>
using namespace std;

struct Monster
{
    Monster(string name):name(name){};
    string name;
    virtual void printInfo() = 0;
};

struct Attacker
{
    Attacker(double damage):damage(damage){};
    double damage;
    virtual void attack() = 0;
};

struct Defender
{
    Defender(double defense):defense(defense){};
    double defense;
    virtual void defend() = 0;
};

struct Walker
{
    double walkspeed;
    Walker(double walkspeed):walkspeed(walkspeed){};
    virtual void walk() = 0;
};

struct Flyer
{
    double flyspeed;
    Flyer(double flyspeed):flyspeed(flyspeed){};
    virtual void fly() = 0;
};

struct Swimmer
{
    double swimSpeed;
    Swimmer(double swimSpeed):swimSpeed(swimSpeed){};
    virtual void swim() = 0;
};

struct Invoker
{
    double magicDamage;
    Invoker(double magicDamage):magicDamage(magicDamage){};
    virtual void invoke() =0;
};

struct FireDragon: public Monster, public Attacker, public Defender, public Walker, public Flyer, public Swimmer, public Invoker
{
    FireDragon(string name, double damage, double defense, double walkspeed, double flyspeed, double swimspeed, double magicDamage):
    Monster(name),Attacker(damage),Defender(defense),Walker(walkspeed),Flyer(flyspeed), Swimmer(swimspeed),Invoker(magicDamage)
    {}

    virtual void printInfo() override
    {
        cout<<"Name:\t"<<"Fire Dragon "<<name<<endl;
        cout<<"Attack:\t"<< damage<<endl;
        cout<<"Defense:\t"<<defense<<endl;
        cout<<"Walk Speed:\t"<<walkspeed<<endl;
        cout<<"Fly Speed:\t"<<flyspeed<<endl;
        cout<<"Swim Speed:\t"<<swimSpeed<<endl;
        cout<<"Magical Damage:\t"<<magicDamage<<endl;
    }

    virtual void attack() override
    {
        cout<<"Fire Dragon Attacks "<<damage<<endl;
    }

    virtual void defend() override
    {
        cout<<"Fire Dragon Defends "<<defense<<endl;
    }

    virtual void walk() override
    {
        cout<<"Fire Dragon walks"<<endl;
    }

    virtual void fly() override
    {
        cout<<"Fire Dragon Flys"<<endl;
    }

    virtual void swim() override
    {
        cout<<"Fire Dragon Swims"<<endl;
    }

    virtual void invoke() override
    {
        cout<<"Fire Dragon unleashes the ultimate power"<<endl;
    }
};

int main()
{
    FireDragon dragon("Alexander",138,87,300,560,130,300);
    dragon.printInfo();
    dragon.attack();
    dragon.defend();
    dragon.fly();
    dragon.swim();
    dragon.invoke();

    return 1;
}