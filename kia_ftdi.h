#ifndef KIA_FTDI_H
#define KIA_FTDI_H
#include <ftd2xx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "mainStruct.h"
#include <queue>
#define MAX_DEVICES 5
class Kia_ftdi  : public QObject
{
    Q_OBJECT
public:
    Kia_ftdi(std::shared_ptr<Kia_settings> kia_settings);
    void init();
    void close();
    ~Kia_ftdi();
    void read_frame(Kia_frame_parametrs *kia_frame_parametrs);
    std::vector<uint16_t> get_frame_buf();
    uint32_t get_buf_size();
public slots:
    void do_read_frame(Kia_frame_parametrs *kia_frame_parametrs);
signals:
    void end_read_frame(quint16);
private:
    void wait_for_event();
    std::shared_ptr<Kia_settings> m_kia_settings;
    uint16_t m_num_devs;
    FT_HANDLE	m_ftHandle[MAX_DEVICES];
    std::vector<uint16_t > m_read_buffer;
    std::future<void> m_ftdi_thread;
    std::atomic_bool m_ftdi_stop{false};
    std::queue<std::pair<std::string, Kia_frame_parametrs*>> m_data;
    std::condition_variable m_cv;
    std::mutex m_mtx;
};

#endif // KIA_FTDI_H
