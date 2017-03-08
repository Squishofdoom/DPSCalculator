//h
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

struct vehicle {

	int frontResist;
	int sideResist;
	int backResist;
	string name;
};

void DPSCalc();
wep manualInput(wep);
wep manualInput();
wep import(wep);
void save(wep);
string convertLower(string);

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
			manualInput();
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
	}//end of while loop

	short dps;//damage per second
	short rps;//rounds per second
	short headDPS;
	short legDPS;
	short damage;
	short distance = 30;

	damage = (weapon.maxDamage - ((distance - weapon.minRange) / (weapon.maxRange - weapon.minRange) * (weapon.maxDamage - weapon.minDamage)));

	cout << damage << " damage at this range." << endl;

	rps = weapon.RPM / 60;

	dps = rps * weapon.maxDamage;
	headDPS = dps * 2;
	legDPS = dps * .90;


}//end of function DPSCalc

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

	weapon.damageType = convertLower(weapon.damageType);

	if (input == 1) {

		cout << "Name of weapon: ";
		cin >> weapon.name;
		cout << endl;

		weapon.name = convertLower(weapon.name);

		save(weapon);
	}
	return weapon;
}

wep manualInput() {

	int input;
	wep weapon;
	int count = 0;

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

	cout << "Name of weapon: ";
	cin >> weapon.name;
	cout << endl;

	weapon.damageType = convertLower(weapon.damageType);
	weapon.name = convertLower(weapon.name);

	save(weapon);
	
	return weapon;
}

wep import(wep weapon) {

	ifstream weapons;
	weapons.open("Weapons.txt");
	bool exit = false;
	string name;
	string trash;

	cout << "Please input the name of the weapon you wish to import." << endl;

	cin.ignore();
	getline(cin, name);

	weapons >> trash;

	while (weapons) {

		weapons.ignore();
		getline(weapons, weapon.name);

		if (weapon.name == name) {
			weapons >> weapon.maxDamage;
			weapons >> weapon.minDamage;
			weapons >> weapon.minRange;
			weapons >> weapon.maxRange;
			weapons >> weapon.magSize;
			weapons >> weapon.RPM;
			weapons >> weapon.headShotMult;
			weapons >> weapon.damageType;

			break;
		}else{
		
			weapons.ignore(INT_MAX, 'S');
		}

		
	}

	weapons.close();

	cout << weapon.name << endl;
	cout << weapon.maxDamage << endl;

	return weapon;
}

void save(wep weapon) {

	ofstream weapons;
	weapons.open("Weapons.txt", ofstream::app);

	weapons << 'S' << endl;
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

	weapons.close();

	return;
}

string convertLower(string upper) {

	int size;

	size = upper.size();
	
	for (int x = 0; x < size; x++) {
		upper[x] = tolower(upper[x]);
	}

	return upper;
}