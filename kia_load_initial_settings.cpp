#include "kia_load_initial_settings.h"

Kia_load_initial_settings::Kia_load_initial_settings(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
    load_initial_settings();
}

void Kia_load_initial_settings::load_initial_settings()
{
    std::string path = "../kia_console/Kia_resource/";
    std::ifstream f(path + "kia_ini.json", std::ifstream::in);
    json j;
    f >> j;

    m_kia_settings->m_type_bokz = j["kia_settings"]["type_bokz"];
    m_kia_settings->m_type_bi = j["kia_settings"]["type_bi"];
    m_kia_settings->m_freq_bokz = j["kia_settings"]["freq"];

}
