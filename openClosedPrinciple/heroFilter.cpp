#include <vector>
#include <string>
#include <iostream>
using namespace std;

//define the members which will be used for a hero
enum class Sex{male, female, unknown};
enum class Nature{strength, agility, intelligence};
enum class AttackType{melee, ranged};
enum class Role{carry, disabler, laneSupport,initiator,
jungler,support,durable,nuker, pusher, escape};

//define Hero class
struct Hero
{
    string name;
    Sex sex;
    Nature nature;
    AttackType attackType;
    Role role;
};

//define Specification
template<typename T>
struct Specification
{
    virtual ~Specification() = default;
    virtual bool is_satisfied(T *item) const= 0;
};

template <typename T>
struct Filter
{
    virtual vector<T*> filter(Specification<T> &spec, vector<T*> &heroes)=0;
};

struct HeroFilter:Filter<Hero>
{
    vector<Hero*> filter(Specification<Hero> &spec, vector<Hero*> &heroes) override
    {
        vector<Hero *> results;
        for(auto h : heroes)
        {
            if( spec.is_satisfied(h))
                results.push_back(h);
        }
        return results;
    }
};

//define AndSpecification
template <typename T>
struct AndSpecification:Specification<T>
{
    const Specification<T> &first;
    const Specification<T> &second;

    AndSpecification(const Specification<T>& _first, const Specification<T>& _second)
    :first(_first),second(_second){};

    
    bool is_satisfied(T *item)const override
    {
       return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

struct SexSpecification:Specification<Hero>
{
    Sex sex;
    explicit SexSpecification(const Sex &sex):sex(sex){};

    bool is_satisfied(Hero *hero) const
    {
        return hero->sex == sex;
    }
};

struct NatureSpecification:Specification<Hero>
{
    Nature nature;
    explicit NatureSpecification(const Nature &nature):nature(nature){};
    
    bool is_satisfied(Hero *hero) const
    {
        return hero->nature == nature;
    }
};

struct AttackTypeSpecification:Specification<Hero>
{
    AttackType attackType;
    explicit AttackTypeSpecification(const AttackType &attackType):attackType(attackType){};

    bool is_satisfied(Hero *hero)const
    {
        return hero->attackType == attackType;        
    }
};

struct RoleSpecification:Specification<Hero>
{
    Role role;

    explicit RoleSpecification(const Role& role):role(role)
    {};

    bool is_satisfied(Hero *hero)const
    {
        return hero->role == role;
    }
};

int main()
{
    Hero anti_mage{"Anti Mage",Sex::male, Nature::agility, AttackType::melee, Role::carry};
    Hero tiny{"Tiny", Sex::male, Nature::strength, AttackType::melee,Role::disabler};
    Hero zeus{"Zeus", Sex::male, Nature::intelligence, AttackType::ranged, Role::nuker};
    Hero lina{"Lina", Sex::female, Nature::intelligence, AttackType::ranged, Role::nuker};
    Hero chan{"Chan", Sex::male, Nature::intelligence, AttackType::melee, Role::support};
    Hero silencer{"Silencer",Sex::male, Nature::intelligence, AttackType::ranged, Role::support};
    Hero gerocopter{"Gerocopter", Sex::male, Nature::agility, AttackType::ranged,Role::nuker};
    Hero windRanger{"Wind Ranger", Sex::female, Nature::intelligence, AttackType::ranged, Role::nuker};

    HeroFilter filter;

    SexSpecification maleFilter(Sex::male);
    SexSpecification femaleFilter(Sex::female);
    RoleSpecification nukerFilter(Role::nuker);
    RoleSpecification supportFilter(Role::support);

    vector<Hero*> all{&anti_mage, &tiny, &zeus, &lina, &chan, &silencer, &gerocopter, &windRanger};
    
    vector<Hero*> males = filter.filter(maleFilter,all);
    vector<Hero*> nukers = filter.filter(nukerFilter, all);

    for(auto h : males)
    {
        cout<<"Male: "<<h->name<<endl;
    }

    for(auto h : nukers)
    {
        cout<<"Nuker: "<<h->name<<endl;
    }

    AndSpecification<Hero> maleNukerFilter(maleFilter, nukerFilter);

    vector<Hero*> maleNuker = filter.filter(maleNukerFilter, all);

    for(auto h: maleNuker)
    {
        cout<<"Male nuker: "<<h->name<<endl;
    }
}



