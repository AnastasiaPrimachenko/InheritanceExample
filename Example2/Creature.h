#include <iostream>
using namespace std;
class creature
{
private:
	string title;
	double mass; //kg
protected:
	creature() : mass(0.0) {}
	creature(const creature& obj) : title(obj.title), mass(obj.mass) {}
	creature(const string& _title, double _mass) : title(_title), mass(_mass) {}
	// деструктор (объявлен как виртуальный)
	virtual ~creature() { cout << "creature deleted" << endl; }
	// виртуальная функция для вывода информации об объекте
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
};

class animal : public creature
{
private:
	double speed; //m/s
public:
	animal() : creature() {}
	animal(const animal& obj) : creature(obj), speed(obj.speed) {}
	animal(const string& _title, double _mass, double _speed)
		: creature(_title, _mass), speed(_speed) {}
	~animal() { cout << "animal deleted" << endl; }
	double get_speed() const
	{
		return speed;
	}
protected:
	void _print() const
	{
		creature::_print();
		cout << ", speed: " << speed;
	}

};

class bird : public virtual animal
{
private:
	double topfly; //km
public:
	bird() : animal() {}
	bird(const bird& obj) : animal(obj), topfly(obj.topfly) {}
	bird(const string& _title, double _mass, double _speed, double _topfly)
		: animal(_title, _mass, _speed), topfly(_topfly) {}
	~bird() { cout << "bird deleted" << endl; }
protected:
	// виртуальная функция _print переопределяется в классе bird
	void _print() const
	{
		animal::_print();
		cout << ", topfly: " << topfly;
	}
};
class fish : public animal
{
private:
	double maxdeep; //km
public:
	fish() : animal() {}
	fish(const fish& obj) : animal(obj), maxdeep(obj.maxdeep) {}
	fish(const string&  _title, double _mass, double _speed, double _maxdeep)
		: animal(_title, _mass, _speed), maxdeep(_maxdeep) {}
	~fish() { cout << "fish deleted" << endl; }

protected:
	// виртуальная функция _print переопределяется в классе fish
	void _print() const
	{
		animal::_print();
		cout << " maxdeep: " << maxdeep;
	}
};

class predator : public virtual animal
{
protected:
	predator() {}
public:
	~predator() {}
	// чисто виртуальная функция hunt будет определять
	// посредством производных классов,
	// удастся ли хищнику поохотиться на жертву (obj)
	virtual bool hunt(const animal& obj) = 0;
	// т.к. hunt чисто виртуальная, класс predator является абстрактным
};

class eagle : public bird, public predator
{
public:
	eagle() : bird() {}
	eagle(const eagle &obj)
		: bird(obj),
		// из-за виртуального наследования, для передачи параметров
		// в конструктор класса animal, его необходимо вызвать явно
		animal(obj) {}
	eagle(double _mass, double _speed, double _topfly)
		: bird("", 0, 0, _topfly),
		// аналогично
		animal("Орел", _mass, _speed) {}
	bool hunt(const animal&  obj)
	{
		// функция get_mass может наследоваться классом eagle из класса animal
		// и через класс bird, и через класс predator
		// нужно указать, что она наследуется через bird
		return obj.get_mass() < bird::get_mass()
			&& obj.get_speed() < bird::get_speed();

	}
};

