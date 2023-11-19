#ifndef KIA_MATROX_H
#define KIA_MATROX_H
#include <mil.h>
#include <CppLinuxSerial/SerialPort.hpp>
#include <iostream>
#include "workwithstruct.h"
#include "mainStruct.h"
#include <string.h>
#include <memory>
#define DCF_DUAL    "KAM_DUALBASE.dcf"
#define CMD_GRAB    0x04 // 0x20
typedef struct
{
    MIL_ID  m_app_id;
    MIL_ID  m_sys_id;
    MIL_ID  m_dig_id;
    MIL_ID  m_buf_id;
    MIL_INT m_num_com;

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

class Kia_matrox
{
public:
    uint32_t get_buf_size();
    void* get_frame_buf();
    Kia_matrox(std::shared_ptr<WorkWithStruct> wws, std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_matrox();
    void matrox_grab_frame(std::shared_ptr<Kia_data> kia_data);
private:
    std::shared_ptr <mn::CppLinuxSerial::SerialPort> m_serial_port;
    std::shared_ptr<WorkWithStruct> m_wws;
    std::shared_ptr<Kia_settings> m_kia_settings;
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
};

#endif // KIA_MATROX_H
