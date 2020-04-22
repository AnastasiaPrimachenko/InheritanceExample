#include <iostream>
#include "Creature.h"

int main()
{
	setlocale(0, "Rus");;
	// создание объектов и вывод информации о них
	bird raven("Ворона", 0.3, 10, 0.1);
	fish hammerhead("Рыба-молот", 150, 5, 0.5);
	raven.print();
	hammerhead.print();
	predator &eagle1 = *new eagle(1, 100, 1);
	cout << "Eagle vs raven: " << eagle1.hunt(raven) << endl;
	cout << "Eagle vs hammerhead " << eagle1.hunt(hammerhead) << endl;
	cout << endl;
	delete& eagle1;
	return 0;
}
