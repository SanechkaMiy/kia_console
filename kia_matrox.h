#ifndef KIA_MATROX_H
#define KIA_MATROX_H
#include <mil.h>
#include <CppLinuxSerial/SerialPort.hpp>
#include <iostream>
#include "mainStruct.h"
#include <string.h>
#include <memory>
#include <math.h>
#include "Kia_modules/kia_help_functions.h"
#include <queue>
#define DCF_DUAL    "Radient eV-CL Dual-Base.dcf"//Radient eV-CL2.dcf
#define CMD_GRAB    0x04 // 0x20
typedef struct
{
    MIL_ID  m_app_id;
    MIL_ID  m_sys_id;
    MIL_ID  m_dig_id;
    MIL_ID  m_buf_id;
    MIL_INT m_num_com;
    MIL_INT m_board_type;

} MIL_SYS_STRUCT;

typedef struct
{
    MIL_INT m_size_x;
    MIL_INT m_size_y;
    MIL_INT m_buffer_size;

} MIL_DIG_STRUCT;

typedef struct
{
    MIL_INT m_com_num;
} COM_STRUCT;

MIL_INT MFTYPE HookFrameEnd(MIL_INT HookType, MIL_ID EventID, void *UserDataPtr);

class Kia_matrox : public QObject
{
    Q_OBJECT
public:
    uint32_t get_buf_size();
    void* get_frame_buf();
    Kia_matrox();
    ~Kia_matrox();
    void matrox_grab_frame(Kia_frame_parametrs *kia_frame_parametrs);
public slots:
    void do_read_frame(Kia_frame_parametrs *kia_frame_parametrs);
signals:
    void end_read_frame(quint16);
private:
    void wait_for_event();
    std::shared_ptr <mn::CppLinuxSerial::SerialPort> m_serial_port;
    uint16_t matrox_init();
    void matrox_close();
    void frame_build();
    void matrox_get_buffer();
    void calc_frame_param(std::shared_ptr<Kia_data> kia_data);
    void open_com(uint16_t num_port);
    MIL_SYS_STRUCT m_mil = {};
    MIL_DIG_STRUCT m_dig = {};
    COM_STRUCT m_com = {};
    void* m_lpv_buf;
    uint16_t m_is_load;
    std::future<void> m_matrox_thread;
    std::atomic_bool m_matrox_stop{false};
    std::queue<std::pair<std::string, Kia_frame_parametrs*>> m_data;
    std::condition_variable m_cv;
    std::mutex m_mtx;
};

#endif // KIA_MATROX_H
