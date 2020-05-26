#include "MinionManager.h"

#include "../threading/AppModel.h"
#include "../threading/ResourceManager.h"

#include "../graphics/TextureManager.h"
#include "../graphics/TextureManager.h"

#include "../include/pugixml/pugixml.hpp"

#include "../exceptions.h"

using namespace std;
using namespace data;
using namespace tower_defense;
using namespace sf;
using namespace pugi;

void MinionManager::clear() {
    for (map<int, Minion *>::iterator it = this->minions.begin();
         it != this->minions.end(); it++) {
        delete it->second;
    }
    this->minions.clear();
    this->minionClasses.clear();
    this->nextClass = 0;
}

Minion *MinionManager::addMinion(const string &directory, const string &name, graphics::TextureManager* tm) {
    map<string, int>::iterator it = this->minionClasses.find(name);
    if (it != this->minionClasses.end())
        return this->minions[it->second];

    Minion *minion = this->load(directory + MinionManager::MINION_LOCATION, name, tm);

    if (minion == nullptr)
        return nullptr;

    this->minionClasses[name] = minion->getObjClass();
    this->minions[minion->getObjClass()] = minion;

    return minion;
}


const Minion &MinionManager::getMinion(int minionClass) const {
    map<int, Minion *>::const_iterator it = this->minions.find(minionClass);

    if (it == this->minions.cend())
        NO_MINION_EXCEPTION

    return *it->second;
}

Minion *MinionManager::load(const string &mDirectory, const string &name, graphics::TextureManager* tm) {
    xml_document doc;

    if (!doc.load_file((mDirectory + name + ".xml").c_str(),
                       pugi::parse_default | pugi::parse_trim_pcdata, pugi::encoding_utf8))
        return nullptr;

    xml_node root = doc.child("minion");

    double size = atof(root.child_value("size"));
    double velocity = atof(root.child_value("velocity"));
    int reward = atoi(root.child_value("reward"));
    int damage = atoi(root.child_value("damage"));
    int attackSpeed = atoi(root.child_value("attackSpeed"));
    int health = atoi(root.child_value("health"));

    Minion::TargetPriority priority;

    switch (root.child_value("priority")[0]) {
        case 'C': //Closer
            priority = Minion::Closer;
            break;
        case 'T': //Turret
            priority = Minion::Turret;
            break;
        case 'I': //Item
            priority = Minion::Item;
            break;
    }

    tm->add(graphics::TextureManager::MINION, nextClass, mDirectory + root.child_value("img"));

    return new Minion(velocity, size, nextClass++, reward, health, damage, priority, attackSpeed);
}

MinionManager::~MinionManager() {
	this->clear();
}