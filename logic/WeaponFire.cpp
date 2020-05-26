#include "WeaponFire.h"
#include "Grid.h"

#include <iostream>
tower_defense::WeaponFire::WeaponFire(const int damage, const double size,
                                      const int lifeTime, const tower_defense::FireType type, const int fireClass)
        : Entity(Point(), 0, size, fireClass) {

    this->damage = damage;
    this->lifeTime = lifeTime;
    this->type = type;
}

tower_defense::WeaponFire::WeaponFire(const WeaponFire &base, const Point &location, const double angle, const double angleModifier)
	: Entity(base) {
	this->damage = base.damage;
	this->lifeTime = base.lifeTime;
	this->type = base.type;
	this->location = location;
	this->angle = angle + angleModifier;
}

std::string tower_defense::WeaponFire::toString() const{
	std::string info = std::string("WeaponFire: Damage: ") + (char)this->damage + " Angle: " + (char)this->angle + " Size: " + (char)this->size + " LifeTime: " + (char) this->lifeTime;

	return info;
}

void tower_defense::WeaponFire::print() const{
	std::cout << this->toString() << std::endl;
}

bool tower_defense::WeaponFire::shouldBeRemoved() const{
	return this->toRemove;
}

void tower_defense::WeaponFire::setToRemove(const bool b){
	this->toRemove = b;
}

double tower_defense::WeaponFire::getDamage() const {
    return this->damage;
}

double tower_defense::WeaponFire::getLifeTime() const {
    return this->lifeTime;
}

tower_defense::FireType tower_defense::WeaponFire::getType() const {
    return this->type;
}
