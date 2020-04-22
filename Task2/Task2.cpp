#include <iostream>
#include "Gameobj.h"

int main()
{
	Human w("Warrior", 80, 50, 30, 20, 200);
	MythCreature g("Goblin", 40, 20, 10, 30, 1);
	MythCreature u("Unicron", 100, 60, 20, 30, 0);
	Mage m("Mage", 50, 40, 10, 20, 100, 80);
	Artifact s("Sword", 15, 150, 0, 0, 10);
	Artifact r("Ring of Health", 0.02, 300, 20, 0, 0);
	w.print();
	g.print();
	while (w.health > 0 && g.health > 0) {
		w.fight(g);
		if (g.health > 0) g.fight(w);
		if (w.health <= 0) cout << w.get_name() << " lost" << endl;
		if (g.health <= 0) {
			w.add(s);
			cout << w.get_name() << " won" << endl;
			cout << w.get_name() << " got " << s.get_name() << endl;
		}
	}
	m.print();
	u.print();
	while (m.health > 0 && u.health > 0) {
		m.fight(u);
		if (u.health > 0) u.fight(m);
		if (m.health <= 0) cout << m.get_name() << " lost" << endl;
		if (u.health <= 0) {
			m.add(r);
			cout << m.get_name() << " won" << endl;
			cout << m.get_name() << " got " << r.get_name() << endl;
		}
	}
}

