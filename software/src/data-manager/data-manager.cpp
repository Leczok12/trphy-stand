#include "data-manager.hpp"

DataManager::DataManager(int &R, int &G, int &B, int &MODE, int &OLD_MODE, int &SPEED, bool &POWER)
    : _R(R),
      _G(G),
      _B(B),
      _MODE(MODE),
      _OLD_MODE(OLD_MODE),
      _SPEED(SPEED),
      _POWER(POWER)
{
}

DataManager::~DataManager() {}

void DataManager::write()
{
    EEPROM.update(0, _R);
    EEPROM.update(1, _G);
    EEPROM.update(2, _B);
    EEPROM.update(3, _MODE);
    EEPROM.update(4, _OLD_MODE);
    EEPROM.update(5, _SPEED);
    EEPROM.update(6, _POWER);
}

void DataManager::read()
{
    _R = EEPROM.read(0);
    _G = EEPROM.read(1);
    _B = EEPROM.read(2);
    _MODE = EEPROM.read(3);
    _OLD_MODE = EEPROM.read(4);
    _SPEED = EEPROM.read(5);
    _POWER = EEPROM.read(6);
}
