#include "kia_ftdi.h"

Kia_ftdi::Kia_ftdi(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
    m_ftdi_thread = std::async([this]()
    {
        init();
        m_ftdi_stop = true;
        while(m_ftdi_stop)
        {
            wait_for_event();
            if (m_data.front().first == "stop_ftdi")
            {
                close();
                break;
            }
            if (m_data.front().first == "read_frame")
            {
                read_frame(m_data.front().second);
            }
            m_data.pop();
        }
    });
}

void Kia_ftdi::init()
{
    FT_STATUS ftStatus;
    char * 	buf_dev_list[MAX_DEVICES + 1];
    char 	dev_list[MAX_DEVICES][64];
    for(int i = 0; i < MAX_DEVICES; i++)
    {
        buf_dev_list[i] = dev_list[i];
    }
    buf_dev_list[MAX_DEVICES] = NULL;
    memset(dev_list, 0, sizeof(dev_list));
    ftStatus = FT_ListDevices(buf_dev_list, &m_num_devs, FT_LIST_ALL | FT_OPEN_BY_SERIAL_NUMBER);

    if (ftStatus != FT_OK)
        printf("FTDI is missing!\n");

    for(int i = 0; (i < m_num_devs); i++)
    {
        printf("Device %d Serial Number - %s\n", i, dev_list[i]);
        FT_OpenEx(dev_list[i], FT_OPEN_BY_SERIAL_NUMBER, &m_ftHandle[i]);
        FT_ResetPort(m_ftHandle[i]);
        FT_ResetDevice(m_ftHandle[i]);
        printf("Opened device %s\n", dev_list[i]);
        FT_SetTimeouts(m_ftHandle[i], 5000, 0);

        //FT_SetBaudRate(m_ftHandle[i], 9600);
    }
}

void Kia_ftdi::close()
{
    for(int i = 0; (i < m_num_devs); i++)
    {
        FT_Close(m_ftHandle[i]);
    }
    std::cout << "destrc ftdi" << std::endl;
}

Kia_ftdi::~Kia_ftdi()
{
    std::lock_guard lock(m_mtx);
    Kia_frame_parametrs kia_data;
    m_data.push(std::make_pair("stop_ftdi", &kia_data));
    m_cv.notify_all();
    m_ftdi_stop = false;
    m_ftdi_thread.get();
}

void Kia_ftdi::read_frame(Kia_frame_parametrs* kia_frame_parametrs)
{
    FT_STATUS ftStatus;
    uint32_t bytes_received;
    //unsigned char read_buffer[1024 * 1024 * 2 + 2];
    //uint16_t read_buffer[512 * 512 + 1];
    uint32_t rx_bytes = kia_frame_parametrs->resulution;
    uint32_t pos = 0;

    bytes_received = 0;
    std::vector<uint8_t> buffer(kia_frame_parametrs->resulution * 4);
    m_read_buffer.resize(kia_frame_parametrs->resulution);
    //uint8_t buffer[512 * 512 * 2];// - changed on vector --
    //memset(m_read_buffer, 0xff, sizeof(m_read_buffer));
    std::cout <<"start" << std::endl;
    while(pos < kia_frame_parametrs->resulution * 2)
    {

        ftStatus = FT_GetQueueStatus(m_ftHandle[0], &rx_bytes);
        if ((ftStatus == FT_OK) && (rx_bytes > 0))
        {
            bytes_received = 0;
            memset(m_read_buffer.data(), 0xff, m_read_buffer.size());
            FT_Read(m_ftHandle[0], &buffer[pos], rx_bytes, &bytes_received);

            pos = pos + bytes_received;

        }

    }
    buffer.resize(kia_frame_parametrs->resulution * 2);
    //std::cout << "size " << sizeof(buffer) << std::endl;
    memcpy(m_read_buffer.data(), buffer.data(), kia_frame_parametrs->resulution * 2);
    kia_frame_parametrs->lvp_buf = m_read_buffer.data();
    kia_frame_parametrs->buf_size = m_read_buffer.size() * 2;
    emit end_read_frame(kia_frame_parametrs->num_bokz);
}

std::vector<uint16_t> Kia_ftdi::get_frame_buf()
{
    return m_read_buffer;
}

uint32_t Kia_ftdi::get_buf_size()
{
    return m_read_buffer.size() * 2;
}

void Kia_ftdi::do_read_frame(Kia_frame_parametrs *kia_frame_parametrs)
{
    std::lock_guard lock(m_mtx);
    m_data.push(std::make_pair("read_frame", kia_frame_parametrs));
    m_cv.notify_all();
}

void Kia_ftdi::wait_for_event()
{
    std::mutex m;
    std::unique_lock lk(m);
    m_cv.wait(lk, [this]
    {
        return  !m_data.empty();
    });
}

