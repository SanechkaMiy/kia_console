#include "kia_load_initial_settings.h"

Kia_load_initial_settings::Kia_load_initial_settings(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
    load_initial_settings();
//    std::ifstream f("data.json", std::ifstream::in);
//    json j;
//    f >> j;
////    for (auto it = j["test2"].begin(); it != j["test2"].end(); ++it)
////    {
////        std::cout << "key: " << it.key() << ", value:" << it.value() << '\n';
////    }
//    std::cout << j["8"]["Наименование параметра"] << std::endl;
}

void Kia_load_initial_settings::load_initial_settings()
{
    std::ifstream f("kia_ini.json", std::ifstream::in);
    json j;
    f >> j;

    m_kia_settings->m_type_bokz = j["kia_settings"]["type_bokz"];
    m_kia_settings->m_type_bi = j["kia_settings"]["type_bi"];
    m_kia_settings->m_freq_bokz = j["kia_settings"]["freq"];

}
