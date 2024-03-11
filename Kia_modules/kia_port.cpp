#include "kia_port.h"
#include <CppLinuxSerial/SerialPort.hpp>
Kia_port::Kia_port(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{

}

void Kia_port::check_used_bi_ports(const uint16_t& type_bi)
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    switch(type_bi)
    {
    case TYPE_BI_BKPIK:
        for (const QSerialPortInfo &portInfo : serialPortInfos)
        {
            check_num_com_port(stoi(portInfo.portName().toStdString().erase(0, 4)));
        }
        break;
    case TYPE_BI_BIU:
        std::cout << "biu" << std::endl;
        check_used_bi_usb_ports();
        break;
    }
    std::cout << "count bi "<< m_kia_settings->m_data_for_bi->m_count_bi << std::endl;

}

void Kia_port::check_num_com_port(const uint16_t &num_port)
{
    std::cout << num_port << std::endl;
    m_serial_port.reset(new mn::CppLinuxSerial::SerialPort("/dev/ttyS" + std::to_string(num_port), mn::CppLinuxSerial::BaudRate::B_9600));
    //serialPort->SetTimeout(100); // Block for up to 100ms to receive data
    std::vector<uint8_t> read_com;
    uint8_t is_com_for_bi = 0xff;
    m_com_is_used = true;

    std::thread th_check_com_port = std::thread([&]()
    {
        std::thread fut_check_com_port = std::thread([this, &read_com, is_com_for_bi]
        {
            m_serial_port->Open();
            std::vector<uint8_t> m_commandToCom = {0x9};
            m_serial_port->WriteBinary(m_commandToCom);
            std::vector<uint8_t> synch_command = {is_com_for_bi};//
            m_serial_port->WriteBinary(synch_command);
            m_serial_port->ReadBinary(read_com);
        });
        fut_check_com_port.detach();
        std::cout <<"start_thread" << std::endl;
        uint16_t counter = 0;
        while(m_com_is_used)
        {
            if (counter == 3 )
            {
                if (read_com.size() > 0 && read_com[0] == is_com_for_bi)
                {
                    std::cout << num_port << std::endl;
                    m_kia_settings->m_data_for_bi->m_count_bi++;
                    m_kia_settings->m_data_for_bi->m_num_bi.push_back(num_port);
                    m_com_is_used = false;
                }
                else
                {
                    m_com_is_used = false;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            counter++;
        }
    });
    th_check_com_port.join();


    std::cout <<"end" << std::endl;
}

void Kia_port::check_used_bi_usb_ports()
{
    int16_t (*setSerialPrefix)(char*);
    int16_t (*init)(void);
    m_handle = dlopen ("/usr/local/lib/BiLib_20231123_1653/BiLibNE.so", RTLD_LAZY);

    if (!m_handle) {
        printf("have problem!");
    }

    setSerialPrefix = (int16_t(*)(char*))dlsym(m_handle, "SetSerialPrefix");

    printf("setSerialPrefix: %d\n", (*setSerialPrefix)("BI_U"));
    init = (int16_t(*)(void))dlsym(m_handle, "Init");
    m_kia_settings->m_data_for_bi->m_count_bi = (*init)();
    if (m_kia_settings->m_data_for_bi->m_count_bi == 0)
        m_kia_settings->m_data_for_bi->m_count_bi  = 1;
    m_kia_settings->m_data_for_bi->m_num_bi.resize(m_kia_settings->m_data_for_bi->m_count_bi);
    int16_t (*close)(void);
    close = (int16_t(*)(void))dlsym(m_handle, "Close");
    auto result = (*close)();
    printf("Close: %d\n", result);
    dlclose(m_handle);
}
