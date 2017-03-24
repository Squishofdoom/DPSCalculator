//
//

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct wep {

	string name;
	int maxDamage;
	int minDamage;
	int maxRange;
	int minRange;
	int magSize;
	int velocity;
	double headShotMult;
	int RPM;
	string damageType;
};
struct vwep {

	string name;
	int maxDamage;
	int minDamage;
	int maxSplashDamage;
	int minSplashDamage;
	int minRange;
	int maxRange;
	double maxSplashRange;
	double minSplashRange;
	int magSize;
	int velocity;
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

void infantryDPSCalc();
void vehicleDPSCalc(vwep);
wep infantryInput(wep);
wep infantryInput();
vwep vehicleInput(vwep);
vwep importVehicle(vwep);
wep importInfantry(wep);
void saveInfantry(wep);
void saveVehicle(vwep);
string convertLower(string);

int main() {

	int input;
	bool exit = false;

	cout << "Welcome to the Planetside 2 DPS Calculator." << endl;

	while (exit == false) {
		cout << "1. Find DPS against infantry" << endl;
		cout << "2. Find DPS against vehicles" << endl;
		cout << "3. Create an infantry weapon file" << endl;
		cout << "4. Create a vehicle weapon file" << endl;
		cout << "5. Exit" << endl;

		cin >> input;

		cout << endl;

		if (input == 1) {
			cout << "Would you like to use..." << endl;
			cout << "1. Infantry weapons" << endl;
			cout << "2. Vehicle weapons" << endl;
			cin >> input;

			if (input == 2) { wep weapon, infantryDPSCalc(weapon); }
			else { vwep weapon, infantryDPSCalc(weapon); }


		}
		else if (input == 2) {
			vwep weapon;
			vehicleDPSCalc(weapon);
		}

		else if (input == 3) {
			infantryInput();
		}
		else if (input == 4) {
			cout << "Exiting..." << endl;
			exit = true;
		}

	}//end of menu while loop
}

void infantryDPSCalc(wep weapon) {//infantry weapon overload

	int input;
	bool validation = false;

	cout << "Would you like to..." << endl;
	cout << "1. Input data manually" << endl;
	cout << "2. Import weapon file" << endl;

	while (validation == false) {

		cin >> input;

		if (input == 1) {
			validation = true;
			weapon = infantryInput(weapon);
		}
		else if (input == 2) {
			validation = true;
			weapon = importInfantry(weapon);
		}
		else { cout << "That input was somehow invalid. Please try again." << endl; }
	}//end of while loop

	double dps;			//damage per second
	double idealDPS;	//dps assuming 100% accuracy and infinite ammo
	double rps;			//rounds per second
	double damage;		//damage after linear interpolation
	double lostDamage;	//amount of damage lost to missed shots, used to calculate dps
	double distance;	//distance from target in meters
	double BTK;			//bullets to kill, accounting for accuracy
	double basicTTK;	//time to kill, 100% accuracy on the body
	double simpleTTK;	//time to kill, user-provided accuracy on the body
	double accuracy;	//user-input accuracy percentage
	double missedShots;	//amount of shots the player will miss
	double travelTime;	//time it takes for the shot to be fired and hit the target
	double critRate;	//user-input percentage of how many headshots the player will hit
	double critDamage;	//extra damage added by crits
	double totalDamage; //total damage with falloff and crits
	
	
	cout << "What distance in meters are you shooting from?" << endl;

	cin >> distance;

	cout << "What is your accuracy percentage(do not include the % sign, just the number)?" << endl;
	cout << "25% is the average overall accuracy for all players." << endl;

	cin >> input;

	cout << "What is your headshot rate percentage(no % sign)?" << endl;
	cout << "18% is the average headshot rate." << endl;

	cin >> critRate;

	cout << endl;

	accuracy = (double)input / 100.0;
	accuracy = 1.0 - accuracy;

	if (distance <= weapon.minRange) {
		damage = weapon.maxDamage;
	}
	else if (distance >= weapon.maxRange) {
		damage = weapon.minDamage;
	}
	else {
		damage = weapon.maxDamage - (distance - weapon.minRange) / (weapon.maxRange - weapon.minRange) * (weapon.maxDamage - weapon.minDamage);
	}
	critRate = critRate / 100;
	critDamage = ((damage * critRate) * weapon.headShotMult);

	totalDamage = damage + critDamage;

	rps = weapon.RPM / 60.0;
	travelTime = distance / weapon.velocity;

	idealDPS = rps * damage;
	lostDamage = idealDPS * accuracy;
	dps = (rps * damage) - lostDamage;
	dps = dps + (dps * critRate);

	BTK = 1000 / totalDamage;
	BTK = ceil(BTK);

	missedShots = BTK * accuracy;
	missedShots = ceil(missedShots);

	simpleTTK = (((BTK + missedShots) - 1) * 60 / weapon.RPM) + travelTime;
	basicTTK = ((BTK - 1) * 60 / weapon.RPM) + travelTime;


	cout << rps << " rounds per second." << endl;
	cout << travelTime << " second travel time." << endl;
	cout << endl;

	cout << weapon.maxDamage << " base max damage." << endl;
	cout << damage << " damage at " << distance << " meters." << endl;
	cout << endl;

	cout << idealDPS << " ideal DPS(100% accuracy, infinite ammo)" << endl;
	cout << dps << " DPS with " << input << "% accuracy." << endl;
	cout << endl;

	cout << BTK << " hits to kill." << endl;
	cout << (BTK + missedShots) << " shots to kill, accounting for accuracy." << endl;
	cout << endl;

	cout << basicTTK << " seconds to kill, assuming 100% accuracy on the body." << endl;
	cout << simpleTTK << " seconds to kill, assuming " << input << "% accuracy and a " << (critRate * 100) << "% headshot rate." << endl;
	cout << endl;

	


}//end of function InfantryDPSCalc(infantry overload)
//completed

void infantryDPSCalc(vwep weapon) {//vehicle weapon overload

	int input;
	bool validation = false;

	cout << "Would you like to..." << endl;
	cout << "1. Input data manually" << endl;
	cout << "2. Import weapon file" << endl;

	while (validation == false) {

		cin >> input;

		if (input == 1) {
			validation = true;
			weapon = vehicleInput(weapon);
		}
		else if (input == 2) {
			validation = true;
			weapon = importVehicle(weapon);
		}
		else { cout << "That input was somehow invalid. Please try again." << endl; }
	}//end of while loop

	double dps;			//damage per second
	double idealDPS;	//dps assuming 100% accuracy and infinite ammo
	double rps;			//rounds per second
	double damage;		//damage after linear interpolation
	double lostDamage;	//amount of damage lost to missed shots, used to calculate dps
	double distance;	//distance from target in meters
	double BTK;			//bullets to kill, accounting for accuracy
	double basicTTK;	//time to kill, 100% accuracy on the body
	double simpleTTK;	//time to kill, user-provided accuracy on the body
	double accuracy;	//user-input accuracy percentage
	double missedShots;	//amount of shots the player will miss
	double travelTime;	//time it takes for the shot to be fired and hit the target
	double critRate;	//user-input percentage of how many headshots the player will hit
	double critDamage;	//extra damage added by crits
	double totalDamage; //total damage with falloff and crits


	cout << "What distance in meters are you shooting from?" << endl;

	cin >> distance;

	cout << "What is your accuracy percentage(do not include the % sign, just the number)?" << endl;
	cout << "25% is the average overall accuracy for all players." << endl;

	cin >> input;

	cout << "What is your headshot rate percentage(no % sign)?" << endl;
	cout << "18% is the average headshot rate." << endl;

	cin >> critRate;

	cout << endl;

	accuracy = (double)input / 100.0;
	accuracy = 1.0 - accuracy;

	if (weapon.minRange != 0 && weapon.maxRange != 0) {

		if (distance <= weapon.minRange) {
			damage = weapon.maxDamage;
		}
		else if (distance >= weapon.maxRange) {
			damage = weapon.minDamage;
		}
		else {
			damage = weapon.maxDamage - (distance - weapon.minRange) / (weapon.maxRange - weapon.minRange) * (weapon.maxDamage - weapon.minDamage);
		}
	}


	critRate = critRate / 100;
	critDamage = ((damage * critRate) * weapon.headShotMult);

	totalDamage = damage + critDamage;

	rps = weapon.RPM / 60.0;
	travelTime = distance / weapon.velocity;

	idealDPS = rps * damage;
	lostDamage = idealDPS * accuracy;
	dps = (rps * damage) - lostDamage;
	dps = dps + (dps * critRate);

	BTK = 1000 / totalDamage;
	BTK = ceil(BTK);

	missedShots = BTK * accuracy;
	missedShots = ceil(missedShots);

	simpleTTK = (((BTK + missedShots) - 1) * 60 / weapon.RPM) + travelTime;
	basicTTK = ((BTK - 1) * 60 / weapon.RPM) + travelTime;


	cout << rps << " rounds per second." << endl;
	cout << travelTime << " second travel time." << endl;
	cout << endl;

	cout << weapon.maxDamage << " base max damage." << endl;
	cout << damage << " damage at " << distance << " meters." << endl;
	cout << endl;

	cout << idealDPS << " ideal DPS(100% accuracy, infinite ammo)" << endl;
	cout << dps << " DPS with " << input << "% accuracy." << endl;
	cout << endl;

	cout << BTK << " hits to kill." << endl;
	cout << (BTK + missedShots) << " shots to kill, accounting for accuracy." << endl;
	cout << endl;

	cout << basicTTK << " seconds to kill, assuming 100% accuracy on the body." << endl;
	cout << simpleTTK << " seconds to kill, assuming " << input << "% accuracy and a " << (critRate * 100) << "% headshot rate." << endl;
	cout << endl;




}//end of function InfantryDPSCalc(vehicle overload)
//incomplete

void vehicleDPSCalc(vwep weapon) {


	int input;
	bool validation = false;

	cout << "Would you like to..." << endl;
	cout << "1. Input data manually" << endl;
	cout << "2. Import weapon file" << endl;

	while (validation == false) {

		cin >> input;

		if (input == 1) {
			validation = true;
			weapon = vehicleInput(weapon);
		}
		else if (input == 2) {
			validation = true;
			weapon = importVehicle(weapon);
		}
		else { cout << "That input was somehow invalid. Please try again." << endl; }
	}//end of while loop
}
//incomplete

wep infantryInput(wep weapon) {

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

	cout << "Bullet velocity: ";
	cin >> weapon.velocity;
	cout << endl;

	cout << "Headshot multiplier(default is 2.0): ";
	cin >> weapon.headShotMult;
	cout << endl;

	cout << "Damage type(\"infantry\" for infantry weapons): ";
	cin >> weapon.damageType;
	cout << endl;

	cout << "Would you like to save this weapon into file? 1 for yes, 2 for no." << endl;
	cin >> input;
	cin.ignore();

	weapon.damageType = convertLower(weapon.damageType);

	if (input == 1) {

		cout << "Name of weapon: ";
		getline(cin, weapon.name);
		cout << endl;

		weapon.name = convertLower(weapon.name);

		saveInfantry(weapon);
	}
	return weapon;
}

vwep vehicleInput(vwep weapon) {

	int input;

	cout << "Beginning input..." << endl << endl;

	cout << "Max damage: ";
	cin >> weapon.maxDamage;
	cout << endl;

	cout << "Minimum dropoff range(0 if it has none): ";
	cin >> weapon.minRange;
	cout << endl;

	cout << "Minimum damage: ";
	cin >> weapon.minDamage;
	cout << endl;

	cout << "Maximum dropoff range(0 for none): ";
	cin >> weapon.maxRange;
	cout << endl;

	cout << "Maximum splash damage: ";
	cin >> weapon.maxSplashDamage;
	cout << endl;

	cout << "Minimum splash range: ";
	cin >> weapon.minSplashRange;
	cout << endl;

	cout << "Minimum splash damage: ";
	cin >> weapon.minSplashDamage;
	cout << endl;

	cout << "Maximum splash range: ";
	cin >> weapon.maxSplashRange;
	cout << endl;

	cout << "Magazine size: ";
	cin >> weapon.magSize;
	cout << endl;

	cout << "Rounds Per Minute: ";
	cin >> weapon.RPM;
	cout << endl;

	cout << "Round velocity: ";
	cin >> weapon.velocity;
	cout << endl;

	cout << "Headshot multiplier(default is 2.0, explosive weapons have 0.0): ";
	cin >> weapon.headShotMult;
	cout << endl;

	cout << "Damage type: ";
	cin >> weapon.damageType;
	cout << endl;

	cout << "Would you like to save this weapon into file? 1 for yes, 2 for no." << endl;
	cin >> input;
	cin.ignore();

	weapon.damageType = convertLower(weapon.damageType);

	if (input == 1) {

		cout << "Name of weapon: ";
		getline(cin, weapon.name);
		cout << endl;

		weapon.name = convertLower(weapon.name);

		saveVehicle(weapon);
	}

	return weapon;
}

wep infantryInput() {

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

	cout << "Bullet velocity: ";
	cin >> weapon.velocity;
	cout << endl;

	cout << "Headshot multiplier(default is 2.0): ";
	cin >> weapon.headShotMult;
	cout << endl;

	cout << "Damage type(\"infantry\" for infantry weapons): ";
	cin >> weapon.damageType;
	cout << endl;
	cin.ignore();

	cout << "Name of weapon: ";
	getline(cin, weapon.name);
	cout << endl;

	weapon.damageType = convertLower(weapon.damageType);
	weapon.name = convertLower(weapon.name);

	saveInfantry(weapon);
	
	return weapon;
}

wep importInfantry(wep weapon) {

	ifstream weapons;
	weapons.open("Data/Weapons.txt");
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
			weapons >> weapon.velocity;
			weapons >> weapon.headShotMult;
			weapons >> weapon.damageType;

			break;
		}else{
		
			weapons.ignore(INT_MAX, 'S');
		}

		
	}

	weapons.close();

	return weapon;
}

vwep importVehicle(vwep weapon) {

	return weapon;
}

void saveInfantry(wep weapon) {

	ofstream weapons;
	weapons.open("Data/Weapons.txt", ofstream::app);

	weapons << 'S' << endl;
	weapons << weapon.name << endl;
	weapons << weapon.maxDamage << endl;
	weapons << weapon.minDamage << endl;
	weapons << weapon.minRange << endl;
	weapons << weapon.maxRange << endl;
	weapons << weapon.magSize << endl;
	weapons << weapon.RPM << endl;
	weapons << weapon.velocity << endl;
	weapons << weapon.headShotMult << endl;
	weapons << weapon.damageType << endl;
	weapons << "<END>" << endl;

	weapons.close();

	return;
}

void saveVehicle(vwep weapon) {

	ofstream weapons;
	weapons.open("Data/VehicleWeapons.txt", ofstream::app);

	weapons << 'S' << endl;
	weapons << weapon.name << endl;
	weapons << weapon.maxDamage << endl;
	weapons << weapon.minDamage << endl;
	weapons << weapon.maxSplashDamage << endl;
	weapons << weapon.minSplashDamage << endl;
	weapons << weapon.minRange << endl;
	weapons << weapon.maxRange << endl;
	weapons << weapon.maxSplashRange << endl;
	weapons << weapon.minSplashRange << endl;
	weapons << weapon.magSize << endl;
	weapons << weapon.RPM << endl;
	weapons << weapon.velocity << endl;
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