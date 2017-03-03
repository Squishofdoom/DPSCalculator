//
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct wep {

	string name;
	int maxDamage;
	int minDamage;
	int maxRange;
	int minRange;
	int magSize;
	double headShotMult;
	int RPM;
	string damageType;
};

void DPSCalc();
wep manualInput(wep);
wep import(wep);
void save(wep);

int main() {

	int input;
	bool exit = false;

	cout << "Welcome to the Planetside 2 DPS Calculator." << endl;

	while (exit == false) {
		cout << "1. Find DPS" << endl;
		cout << "2. Create a weapon file" << endl;
		cout << "3. Exit" << endl;

		cin >> input;

		if (input == 1) {
			DPSCalc();
		}
		else if (input == 2) {
			cout << "This has not been implemented yet. Sorry." << endl;
		}
		else if (input == 3) {
			cout << "Exiting..." << endl;
			exit = true;
		}

	}//end of menu while loop
}

void DPSCalc() {

	wep weapon;
	int input;
	bool validation = false;

	cout << "Would you like to..." << endl;
	cout << "1. Input data manually" << endl;
	cout << "2. Import weapon file" << endl;
	
	while (validation == false) {

		cin >> input;

		if (input == 1) {
			validation = true;
			weapon = manualInput(weapon);
		}
		else if (input == 2) {
			validation = true;
			weapon = import(weapon);
		}
		else { cout << "That input was somehow invalid. Please try again." << endl; }
	}
}

wep manualInput(wep weapon) {

	int input;

	cout << "Beginning input..." << endl << endl;

	cout << "Max damage: ";
	cin >> weapon.maxDamage;
	cout << endl;
	
	cout << "Minimum dropoff range: ";
	cin >> weapon.minRange;
	cout << endl;

	cout << "Minimum damage: ";
	cin >> weapon.minDamage;
	cout << endl;

	cout << "Maximum dropoff range: ";
	cin >> weapon.maxRange;
	cout << endl;

	cout << "Magazine size: ";
	cin >> weapon.magSize;
	cout << endl;

	cout << "Rounds Per Minute: ";
	cin >> weapon.RPM;
	cout << endl;

	cout << "Headshot multiplier(default is 2.0): ";
	cin >> weapon.headShotMult;
	cout << endl;

	cout << "Damage type(\"infantry\" for infantry weapons): ";
	cin >> weapon.damageType;
	cout << endl;

	cout << "Would you like to save this weapon into file? 1 for yes, 2 for no." << endl;
	cin >> input;

	if (input == 1) {

		cout << "Name of weapon: ";
		cin >> weapon.name;
		cout << endl;

		save(weapon);
	}
	return weapon;
}

wep import(wep weapon) {

	return weapon;
}

void save(wep weapon) {

	ofstream weapons;
	weapons.open("Weapons.txt");

	weapons << weapon.name << endl;
	weapons << weapon.maxDamage << endl;
	weapons << weapon.minDamage << endl;
	weapons << weapon.minRange << endl;
	weapons << weapon.maxRange << endl;
	weapons << weapon.magSize << endl;
	weapons << weapon.RPM << endl;
	weapons << weapon.headShotMult << endl;
	weapons << weapon.damageType << endl;
	weapons << "<END>" << endl;

	return;
}