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

namespace mn::CppLinuxSerial
{
    class SerialPort;
}

class Kia_port
{
public:
    Kia_port(std::shared_ptr<Kia_settings> kia_settings);
    void check_used_bi_ports(const uint16_t& type_bi);
    void check_num_com_port(const uint16_t &num_port);
    void check_used_bi_usb_ports();
private:
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr <mn::CppLinuxSerial::SerialPort> m_serial_port;
    std::atomic_bool m_com_is_used = true;
};

#endif // KIA_PORT_H


