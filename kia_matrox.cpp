#include "kia_matrox.h"




Kia_matrox::Kia_matrox(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
    //    auto check_result = matrox_init();
    //    if (check_result != 0)
    //    {
    //        std::cout << "Matrox load" << std::endl;
    //        m_kia_settings->m_matrox_is_define = CS_IS_ON;
    //    }
}

Kia_matrox::~Kia_matrox()
{
    //    if (m_kia_settings->m_matrox_is_define == CS_IS_ON)
    //        matrox_close();
}

void Kia_matrox::matrox_grab_frame(std::shared_ptr<Kia_data> kia_data)
{
    kia_data->m_data_db->m_datetime = helpers::currentDateTime();
    MdigGrab(m_mil.m_dig_id, m_mil.m_buf_id);
    std::vector<uint8_t> m_commandToCom = {CMD_GRAB};
    m_serial_port->WriteBinary(m_commandToCom);
    MdigGrabWait(m_mil.m_dig_id, M_GRAB_FRAME_END);
    std::cout << "GrabWait  finished" << "\n";
    matrox_get_buffer();
    calc_frame_param(kia_data);
}

void Kia_matrox::matrox_get_buffer()
{
    if(!m_lpv_buf) m_lpv_buf = m_lpv_buf = ::operator new (m_dig.m_buffer_size);
    memset(m_lpv_buf, 0, m_dig.m_buffer_size);
    MbufGet(m_mil.m_buf_id, m_lpv_buf);
    frame_build();
}

void Kia_matrox::calc_frame_param(std::shared_ptr<Kia_data> kia_data)
{
    uint16_t* frame_buffer = static_cast<uint16_t*>(m_lpv_buf);
    kia_data->m_data_db->m_max = frame_buffer[0];
    kia_data->m_data_db->m_min = frame_buffer[0];
    uint32_t frame_size = m_dig.m_buffer_size / 2 - 1;
    std::cout << sizeof(frame_buffer) / sizeof(frame_buffer[0]) << std::endl;
    std::cout << frame_buffer[0] << std::endl;
    for (MIL_INT el = 0; el < frame_size; el++)
    {
        if (frame_buffer[el] > kia_data->m_data_db->m_max)
        {
            kia_data->m_data_db->m_max = frame_buffer[el];
        }
        if (frame_buffer[el] < kia_data->m_data_db->m_min)
            kia_data->m_data_db->m_min = frame_buffer[el];
        kia_data->m_data_db->m_average = kia_data->m_data_db->m_average + frame_buffer[el];

    }
    kia_data->m_data_db->m_average = kia_data->m_data_db->m_average / frame_size;
    for (uint32_t el = 2; el < frame_size; el++)
        kia_data->m_data_db->m_variance = kia_data->m_data_db->m_variance
                + pow(abs(frame_buffer[el] - (int32_t)kia_data->m_data_db->m_average), 2);
    kia_data->m_data_db->m_variance = sqrt(kia_data->m_data_db->m_variance / (frame_size));

}

uint32_t Kia_matrox::get_buf_size()
{
    return m_dig.m_buffer_size;
}

void *Kia_matrox::get_frame_buf()
{
    return m_lpv_buf;
}

uint16_t Kia_matrox::matrox_init()
{
    uint32_t num_dev = 0;
    uint32_t result_matrox_init = 0;
    result_matrox_init = MappAlloc(M_DEFAULT, &m_mil.m_app_id);
    std::cout << "MappAlloc result = " << result_matrox_init << "\n";
    if(!result_matrox_init)
        return 0;

    result_matrox_init = MsysAlloc(M_SYSTEM_SOLIOS, num_dev, M_DEFAULT, &m_mil.m_sys_id);
    std::cout << "MsysAlloc result = " << result_matrox_init << "\n";
    if(!result_matrox_init)
        return 0;

    result_matrox_init = MdigAlloc(m_mil.m_sys_id, 0, DCF_DUAL, M_DEFAULT, &m_mil.m_dig_id);
    std::cout << "MdigAlloc result = " << result_matrox_init << "\n";
    if(!result_matrox_init)
        return 0;
    try
    {
        MdigInquire(m_mil.m_dig_id, M_SIZE_X, &m_dig.m_size_x);// узнаем настройки дигитайзера размер по х
        MdigInquire(m_mil.m_dig_id, M_SIZE_Y, &m_dig.m_size_y);// узнаем настройки дигитайзера размер по y

        std::cout << "size x = " << m_dig.m_size_x << "\n";
        std::cout << "size y = " << m_dig.m_size_x << "\n";

        m_dig.m_buffer_size = m_dig.m_size_x * m_dig.m_size_y * 2;

        std::cout << "size buffer = " << m_dig.m_buffer_size << "\n";

        MsysInquire(m_mil.m_sys_id, M_COM_PORT_NUMBER + M_UART_NB(0), &m_com.m_com_num);
        MsysControl(m_mil.m_sys_id, M_UART_FREE + M_UART_NB(0), M_DEFAULT);
        std::cout << "COM num = " << m_com.m_com_num << "\n";
        open_com(m_com.m_com_num);


        MdigControl(m_mil.m_dig_id, M_GRAB_MODE, M_ASYNCHRONOUS);
        //        MdigControl(_mil.digID, M_GRAB_FIELD_NUM, 1);
        MdigControl(m_mil.m_dig_id, M_GRAB_TIMEOUT, 5000);
        MdigControl(m_mil.m_dig_id, M_GRAB_LINE_COUNTER, M_ENABLE);


        result_matrox_init = MbufAlloc2d(m_mil.m_sys_id,
                                         m_dig.m_size_x,
                                         m_dig.m_size_y,
                                         16L + M_UNSIGNED,
                                         M_IMAGE +
                                         M_GRAB +
                                         M_ON_BOARD,
                                         //                    M_HOST_MEMORY,
                                         &m_mil.m_buf_id);
        MbufClear(m_mil.m_buf_id, 0x07d0);

        std::cout << "MbufAlloc2d result = " << result_matrox_init << "\n";

        m_lpv_buf = ::operator new (m_dig.m_buffer_size);
        MdigHookFunction(m_mil.m_dig_id, M_GRAB_FRAME_END, HookFrameEnd, m_lpv_buf);
    }
    catch(uint32_t uiErr)
    {
        result_matrox_init = 0;
        ::operator delete(m_lpv_buf);
        std::cout << "catch err = " << uiErr << "\n";
    }
    std::cout << "Init result = " << result_matrox_init << "\n";
    return result_matrox_init;
}

void Kia_matrox::matrox_close()
{
    std::cout << "Matrox Close" << std::endl;
    if(m_mil.m_buf_id) MbufFree(m_mil.m_buf_id);
    if(m_mil.m_dig_id) MdigFree(m_mil.m_dig_id);
    if(m_mil.m_sys_id) MsysFree(m_mil.m_sys_id);
    if(m_mil.m_app_id) MappFree(m_mil.m_app_id);
    ::operator delete(m_lpv_buf);
}

void Kia_matrox::frame_build()
{
    uint16_t* lpwTempBuf; // указатель на строки собранного кадра
    void* lpvTempBuf = malloc(m_dig.m_buffer_size);
    uint16_t* lpwFrame; // указатель на строки полученного буфера

    memset(lpvTempBuf, 0, m_dig.m_buffer_size);
    int width_limit = m_dig.m_size_x /4; // ширина одного tap`а
    int I_4 = 0; // I*4;
    int I_2 = 0; // I*2;

    //  int flip_x_offset = IsFlipX()? 0 : 508;


    for(int	J = 0; J < m_dig.m_size_y; J++) // идем по строкам
    {
        lpwTempBuf = (uint16_t*)lpvTempBuf + J*m_dig.m_size_x;
        lpwFrame = (uint16_t*)m_lpv_buf + J*m_dig.m_size_x;

        for(int I = 0; I < width_limit; I++) // идем по столбцам
        {
            I_4 = I*4; // I<<2; // I*4;
            lpwTempBuf[I       ] = lpwFrame[I_4    ];
            lpwTempBuf[I +  512] = lpwFrame[I_4 + 1];
            lpwTempBuf[I + 1024] = lpwFrame[I_4 + 2];
            lpwTempBuf[I + 1536] = lpwFrame[I_4 + 3];

            //            lpwTempBuf[I       ] = lpwFrame[I_4    ];
            //            lpwTempBuf[I +  1] = lpwFrame[I_4 + 1];
            //            lpwTempBuf[I + 1024] = lpwFrame[I_4 + 2];
            //            lpwTempBuf[I + 1025] = lpwFrame[I_4 + 3];
        }
    }
    memcpy(m_lpv_buf, lpvTempBuf, m_dig.m_buffer_size); // f_width*f_height*2); // копируем собранный кадр во временный буфер

    if(lpvTempBuf) free(lpvTempBuf);
}

void Kia_matrox::open_com(uint16_t num_port)
{
    try
    {
        m_serial_port.reset(new mn::CppLinuxSerial::SerialPort("/dev/ttyS" + to_string(num_port), mn::CppLinuxSerial::BaudRate::B_57600));
        //serialPort->SetTimeout(100); // Block for up to 100ms to receive data
        m_serial_port->Open();
        //flag что вошли в циклический режим
    }
    catch (std::exception const &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
}

MIL_INT MFTYPE HookFrameEnd(MIL_INT HookType, MIL_ID EventID, void *UserDataPtr)
{
    MIL_INT line_total = 0;
    MdigGetHookInfo( EventID, M_GRAB_LINE_COUNT, &line_total);
    std::cout << "Hook grab end, line total = " << line_total << "\n";
    return 0;
}
