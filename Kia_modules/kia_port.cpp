#include "kia_port.h"
#include <CppLinuxSerial/SerialPort.hpp>
Kia_port::Kia_port(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{

}

std::vector<shared_ptr<Kia_bi> > Kia_port::check_used_bi_ports(const uint16_t& type_bi)
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
        std::cout << "count bi "<< m_kia_settings->m_count_bi << std::endl;
        for (uint16_t num_bi{0}; num_bi < m_kia_settings->m_count_bi; num_bi++)
        {
            m_kia_bi.push_back(std::make_shared<Kia_biu>());
        }
        break;
    }
    return m_kia_bi;
}

void Kia_port::check_num_com_port(const uint16_t &num_port)
{
    std::cout << num_port << std::endl;
    std::shared_ptr<mn::CppLinuxSerial::SerialPort> serial_port(new mn::CppLinuxSerial::SerialPort("/dev/ttyS" + std::to_string(num_port), mn::CppLinuxSerial::BaudRate::B_9600));
    //serialPort->SetTimeout(100); // Block for up to 100ms to receive data
    std::vector<uint8_t> read_com;
    uint8_t is_com_for_bi = 0xff;
    m_com_is_used = true;
    std::vector<uint16_t> num_ports;

    std::thread th_check_com_port = std::thread([&]()
    {
        std::thread fut_check_com_port = std::thread([&]
        {
            serial_port->Open();
            std::vector<uint8_t> m_commandToCom = {0x9};
            serial_port->WriteBinary(m_commandToCom);
            std::vector<uint8_t> synch_command = {is_com_for_bi};//
            serial_port->WriteBinary(synch_command);
            serial_port->ReadBinary(read_com);
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
                    m_kia_settings->m_num_port.push_back(num_port);
                    m_kia_settings->m_count_bi++;
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
    serial_port->Close();
}

void Kia_port::check_used_bi_usb_ports()
{
    std::thread th_check_bi = std::thread([&]()
    {
        int16_t (*setSerialPrefix)(char*);
        int16_t (*init)(void);
        auto handle = dlopen ("../../lib/BiLib_20231123_1653/BiLibNE.so", RTLD_LAZY);

        if (!handle) {
            printf("have problem!\n");
        }

        setSerialPrefix = (int16_t(*)(char*))dlsym(handle, "SetSerialPrefix");
        printf("setSerialPrefix: %d\n", (*setSerialPrefix)("BI_U"));
        init = (int16_t(*)(void))dlsym(handle, "Init");
        int16_t (*close)(void);
        close = (int16_t(*)(void))dlsym(handle, "Close");

        m_kia_settings->m_count_bi = (*init)();


        m_kia_settings->m_bi_used = CS_IS_ON;

        if (m_kia_settings->m_count_bi <= 0)
        {
            m_kia_settings->m_bi_used = CS_IS_OFF;
            m_kia_settings->m_count_bi  = 1;
        }

        (*close)();
        dlclose(handle);
    });
    th_check_bi.join();


    if (m_kia_settings->m_data_for_bi->m_count_bi <= 0)
    {
        m_kia_settings->m_data_for_bi->m_count_bi  = 1;
    }
    m_kia_settings->m_data_for_bi->m_num_bi.resize(m_kia_settings->m_data_for_bi->m_count_bi);
}
