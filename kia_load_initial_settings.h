#ifndef KIA_LOAD_INITIAL_SETTINGS_H
#define KIA_LOAD_INITIAL_SETTINGS_H
#include "mainStruct.h"
#include <fstream>
class Kia_load_initial_settings
{
public:
    Kia_load_initial_settings(std::shared_ptr<Kia_settings> kia_settings);
private:
    void load_initial_settings();
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // KIA_LOAD_INITIAL_SETTINGS_H
