#include "Weapon.h"
#include "Beam.h"
#include "Bullet.h"
#include "Ring.h"



tower_defense::Weapon::Weapon(
        const double range, const int fireRate, const WeaponFireList *const weaponFireList) {
    this->fireRate = fireRate;
    this->range = range;
    this->parent = nullptr;
    this->reloading = 0;
    this->fireList = weaponFireList;
}

tower_defense::Weapon::Weapon(const Weapon &base, const Turret *const parent) {
    this->fireRate = base.fireRate;
    this->range = base.range;
    this->parent = parent;
    this->reloading = 0;
    this->fireList = base.fireList;
    this->cur = fireList->begin();
}

double tower_defense::Weapon::getRange() const {
    return this->range;
}

int tower_defense::Weapon::getFireRate() const {
    return this->fireRate;
}

int tower_defense::Weapon::getReloading() const {
    return this->reloading;
}
#include <iostream>

void tower_defense::Weapon::refresh(bool beginSequence, Map* m) {
	if (this->reloading != 0 || beginSequence) {
		while (this->cur->first == this->reloading) {
			WeaponFire* fire = nullptr;
			
			switch(this->cur->second.first->getType()){
			case FireType::bullet: 
				fire = new Bullet(*dynamic_cast<tower_defense::Bullet*>(this->cur->second.first),
					this->parent->getLocation(), this->parent->getAngle(), this->cur->second.second);
				break;
			case FireType::beam:
				fire = new Beam(*dynamic_cast<tower_defense::Beam*>(this->cur->second.first),
					this->parent->getLocation(), this->parent->getAngle(), this->cur->second.second);
				break;
			case FireType::ring:
				fire = new Ring(*dynamic_cast<tower_defense::Ring*>(this->cur->second.first),
					this->parent->getLocation(), this->parent->getAngle(), this->cur->second.second);
				break;
			default: std::cout << "FIRE ERROR " << std::endl;
			}

			if (fire != nullptr) {
				m->addFire(fire);
			}

			if (++cur == this->fireList->cend()) {
				this->cur = this->fireList->cbegin();
				break;
			}

		}

		if (++this->reloading == this->fireRate) this->reloading = 0;
	}
}