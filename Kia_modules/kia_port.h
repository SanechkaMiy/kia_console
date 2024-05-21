#ifndef KIA_PORT_H
#define KIA_PORT_H
#include <iostream>
#include <QSerialPortInfo>

#include "mainStruct.h"
#include "BiLibNE.h"
#include <dlfcn.h>
#include <thread>
#include <vector>
#include <string.h>
#include "kia_bi.h"
#include "kia_biu.h"
namespace mn::CppLinuxSerial
{
    class SerialPort;
}

class Kia_port
{
public:
    Kia_port(std::shared_ptr<Kia_settings> kia_settings);
    std::vector<shared_ptr<Kia_bi>> check_used_bi_ports(const uint16_t& type_bi);
    void check_num_com_port(const uint16_t &num_port);
    void check_used_bi_usb_ports();
private:
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::atomic_bool m_com_is_used = true;
    std::vector<shared_ptr<Kia_bi>> m_kia_bi;
};

#endif // KIA_PORT_H


