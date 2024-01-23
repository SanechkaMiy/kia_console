#ifndef KIA_FTDI_H
#define KIA_FTDI_H
#include <ftd2xx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "mainStruct.h"
#define MAX_DEVICES 5
class Kia_ftdi
{
public:
    Kia_ftdi(std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_ftdi();
    void read_frame(uint32_t resulution);
    std::vector<uint16_t> get_frame_buf();
    uint32_t get_buf_size();
private:
    std::shared_ptr<Kia_settings> m_kia_settings;
    uint16_t m_num_devs;
    FT_HANDLE	m_ftHandle[MAX_DEVICES];
        std::vector<uint16_t > m_read_buffer;
};

#endif // KIA_FTDI_H
