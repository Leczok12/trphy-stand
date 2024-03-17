#ifndef DATA_MANAGER
#define DATA_MANAGER

#include <EEPROM.h>
#include <Arduino.h>
class DataManager
{
public:
    DataManager(int &R, int &G, int &B, int &MODE, int &OLD_MODE, int &SPEED, bool &POWER);
    ~DataManager();

    void write();
    void read();

private:
    int &_R;
    int &_G;
    int &_B;
    int &_MODE;
    int &_OLD_MODE;
    int &_SPEED;
    bool &_POWER;
};

#endif