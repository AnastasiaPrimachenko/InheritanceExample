#include <iostream>
using namespace std;
class GameObj
{
private:
	string title;
	double mass; 
protected:
	GameObj() : mass(0.0) { cout << "dasdsa" << endl; }
	GameObj(const GameObj& obj) : title(obj.title), mass(obj.mass) {}
	GameObj(const string& _title, double _mass) : title(_title), mass(_mass) {}
	virtual ~GameObj() { cout << "object deleted" << endl; }
	virtual void _print() const { cout << "title: " << title << ", mass: " << mass; }
public:
	void print() const
	{
		cout << typeid(*this).name() << ": (";
		_print();
		cout << ")" << endl;
	}
	double get_mass() const
	{
		return mass;
	}
	string get_name() const
	{
		return title;
	}
};
class AnimatedObj : public virtual GameObj
{
public:
	int health;
	int defense;
	int attack;
	AnimatedObj() : GameObj() {}
	AnimatedObj(const AnimatedObj& obj) : GameObj(obj), health(obj.health), defense(obj.defense), attack(obj.attack) {}
	AnimatedObj(int _health, int _defense, int _attack) 
		: health(_health), defense(_defense), attack(_attack) {}
	~AnimatedObj() {}
	void _print() const
	{
		GameObj::_print();
		cout << ", health: " << health << ", defense: " << defense << ", attack: " << attack;
	}
};
class Artifact : public GameObj
{
public:
	int cost;
	int abonus;
	int dbonus;
	int hbonus;
	Artifact() : GameObj() {}
	Artifact(const Artifact& obj) : GameObj(obj), cost(obj.cost), hbonus(obj.hbonus), dbonus(obj.dbonus), abonus(obj.abonus) {}
	Artifact(const string& _title, double _mass, int _cost, int _hbonus, int _dbonus, int _abonus)
		: GameObj(_title, _mass), cost(_cost), hbonus(_hbonus), dbonus(_dbonus), abonus(_abonus) {}
	~Artifact() { cout << "Artifact deleted" << endl; }
	int get_cost() const { return cost; }
	int get_abonus() const { return abonus; }
	int get_dbonus() const { return dbonus; }
	int get_hbonus() const { return hbonus; }
protected:
	void _print() const
	{
		GameObj::_print();
		cout << ", cost: " << cost << ", health bonus: " << hbonus << ", defense bonus: " << dbonus << ", attack bonus: " << abonus;
	}
};
class CanAttack : public virtual GameObj
{
protected:
	CanAttack() {}
public:
	~CanAttack() {}
	virtual void fight(AnimatedObj& obj) = 0;
};
class Human : public virtual AnimatedObj, public CanAttack
{
public: 
	int money;
	Human() : AnimatedObj() {}
	Human(const Human& obj) : AnimatedObj(obj), money(obj.money) {}
	Human(const string& _title, double _mass, int _health, int _defense, int _attack, int _money)
		: GameObj(_title,_mass), AnimatedObj(_health, _defense, _attack), money(_money) {}
	Human(int _money) : money(_money) {}
	~Human() { cout << "Human deleted" << endl; }
	void fight(AnimatedObj& obj)
	{
		if (Human::attack - obj.defense) obj.health -= Human::attack - obj.defense;
	}
	void add(Artifact& obj)
	{
		if (Human::money >= obj.cost) {
			Human::attack += obj.abonus;
			Human::defense += obj.dbonus;
			Human::health += obj.hbonus;
			Human::money -= obj.cost;
		}
		else cout << "Not enough money" << endl;
	}
protected:
	void _print() const
	{
		AnimatedObj::_print();
		cout << ", money: " << money;
	}
};

class MythCreature : public AnimatedObj, public CanAttack
{
public:
	bool hostile;
	MythCreature() : AnimatedObj() {}
	MythCreature(const MythCreature& obj) : AnimatedObj(obj), hostile(obj.hostile) {}
	MythCreature(const string& _title, double _mass, int _health, int _defense, int _attack, bool _hostile)
		//: AnimatedObj(_title, _mass, _health, _defense, _attack), hostile(_hostile) {}
		:GameObj(_title, _mass), AnimatedObj(_health, _defense, _attack), hostile(_hostile) {}
	~MythCreature() { cout << "Creature deleted" << endl; }
	void fight(AnimatedObj& obj)
	{
		if (MythCreature::attack - obj.defense > 0) obj.health -= MythCreature::attack - obj.defense;
	}
protected:
	void _print() const
	{
		AnimatedObj::_print();
		cout << ", hostile: " << hostile;
	}
};
class Mage : public  Human
{
public:
	int mana;
	Mage() : Human() {}
	Mage(const Mage& obj) : Human(obj), mana(obj.mana) {}
	Mage(const string& _title, double _mass, int _health, int _defense, int _attack, int _money, int _mana)
		: GameObj(_title, _mass), AnimatedObj(_health, _defense, _attack), Human(_money), mana(_mana) {}
	~Mage() { cout << "Mage deleted" << endl; }
	void fight(AnimatedObj& obj)
	{
		if (Mage::mana >= 30) {
			if (30 - obj.defense > 0) obj.health -= 30 - obj.defense;
			Mage::mana -= 30;
		}
		if (Mage::mana < 30)
		{
			if (Mage::attack - obj.defense > 0) obj.health -= Mage::attack - obj.defense;
			Mage::mana += 15;
		}
	}
protected:
	void _print() const
	{
		Human::_print();
		cout << ", mana: " << mana;
	}
};


//class AnimatedObj : public virtual GameObj
//{
//public:
//	AnimatedObj() : GameObj() {}	
//	~AnimatedObj() {}
//	virtual void fighth(Human & obj) = 0;
//	virtual void fightc(MythCreature& obj) = 0;
////};
//
////class Human : public virtual GameObj, public AnimatedObj
//{
//public:
//	int health;
//	int defense;
//	int attack;
//	Human() : GameObj() {}
//	Human(const Human& obj) : GameObj(obj), health(obj.health), defense(obj.defense), attack(obj.attack) {}
//	Human(const string& _title, int _mass, int _health, int _defense, int _attack)
//				: GameObj(_title, _mass), health(_health), defense(_defense), attack(_attack) {}
//	~Human() { cout << "Human deleted" << endl; }
//	void fighth(Human& obj)
//	{
//		if (Human::get_mass > obj.get_mass) obj.health -= (Human::attack + 5 - obj.defense);
//		else obj.health -= (Human::attack - obj.defense);
//	}
//	void fightc(MythCreature& obj)
//	{
//		if (Human::get_mass > obj.get_mass) obj.health -= (Human::attack + 5 - obj.defense);
//		else obj.health -= (Human::attack - obj.defense);
//	}
//};
//
//class MythCreature : public virtual GameObj, public AnimatedObj
//{
//public:
//	int health;
//	int defense;
//	int attack;
//	bool hostile;
//	MythCreature() : GameObj() {}
//	MythCreature(const MythCreature& obj) : GameObj(obj), health(obj.health), defense(obj.defense), attack(obj.attack), hostile(obj.hostile) {}
//	MythCreature(const string& _title, int _mass, int _health, int _defense, int _attack, bool _hostile)
//		: GameObj(_title, _mass), health(_health), defense(_defense), attack(_attack), hostile(_hostile) {}
//	~MythCreature() { cout << "MythCreature deleted" << endl; }
//	void fighth(Human& obj)
//	{
//		if (MythCreature::get_mass > obj.get_mass) obj.health -= (MythCreature::attack + 5 - obj.defense);
//		else obj.health -= (MythCreature::attack - obj.defense);
//	}
//	void fightc(MythCreature& obj)
//	{}
//};
//
//class Mage : public Human
//{
//public:
//	int mana;
//	Mage() : Human() {}
//	Mage(const Mage& obj) : Human(obj), mana(obj.mana) {}
//	Mage(const string& _title, int _mass, int _health, int _defense, int _attack, int _mana)
//		: Human(_title, _mass, _health, _defense, _attack), mana(_mana) {}
//	~Mage() { cout << "Mage deleted" << endl; }
//	void fighth(Human& obj)
//	{
//		if (Mage::attack <= 30 && Mage::mana >= 20) obj.health -= (30 - obj.defense);
//		else
//		{
//			if (Mage::get_mass > obj.get_mass) obj.health -= (Mage::attack + 5 - obj.defense);
//			else obj.health -= (Mage::attack - obj.defense);
//		}
//	}
//	void fightc(MythCreature& obj)
//	{
//		if (Mage::attack <= 30 && Mage::mana >= 20) obj.health -= (30 - obj.defense);
//		else
//		{
//			if (Mage::get_mass > obj.get_mass) obj.health -= (Mage::attack + 5 - obj.defense);
//			else obj.health -= (Mage::attack - obj.defense);
//		}
//	}
//};


