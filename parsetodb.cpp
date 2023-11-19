#include "parsetodb.h"

ParseToDB::ParseToDB(std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
                     std::shared_ptr<Kia_data> kia_data,
                     std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_db(kia_db)
  , m_kia_data(kia_data)
  , m_kia_settings(kia_settings)

{

}
ParseToDB::~ParseToDB()
{

}

void ParseToDB::sendDataIntoMSHIOR(uint16_t& num_bokz, uint32_t& bshv, MSHIOR &st_mshior)
{
    char data_into_mshior[1024];
    sprintf(data_into_mshior,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"st1\":%i,"
                             "\"st2\":%i,"
                             "\"t\":%i,"
                             "\"ozx\":%f,"
                             "\"ozy\":%f,"
                             "\"ozz\":%f,"
                             "\"qo\":\"{%f,%f,%f,%f}\","
                             "\"wox\":%f,"
                             "\"woy\":%f,"
                             "\"woz\":%f,"
                             "\"alpha\":%f,"
                             "\"delta\":%f,"
                             "\"azimuth\":%f}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            bshv, st_mshior.KC1 , st_mshior.KC2 , st_mshior.T, st_mshior.OZx,
            st_mshior.OZy, st_mshior.OZz, st_mshior.Qo0, st_mshior.Qo1, st_mshior.Qo2, st_mshior.Qo3, st_mshior.wox,
            st_mshior.woy, st_mshior.woz, m_kia_data->m_data_db->m_alpha, m_kia_data->m_data_db->m_delta, m_kia_data->m_data_db->m_azimuth);
    m_kia_db[TYPE_DATA]->insert_data(data_into_mshior, "prepare_insert_into_mshior");
}

void ParseToDB::sendDataIntoSHTMI1(uint16_t &num_bokz, uint32_t& bshv, SHTMI1& st_shtmi1)
{
    char data_into_shtmi1[1024];
    sprintf(data_into_shtmi1,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"ss1\":%i,"
                             "\"ss2\":%i,"
                             "\"t\":%i,"
                             "\"st1\":%i,"
                             "\"st2\":%i,"
                             "\"sernum\":%i,"
                             "\"post\":%i,"
                             "\"foc\":%i,"
                             "\"xo\":%i,"
                             "\"yo\":%i,"
                             "\"texp\":%i,"
                             "\"meant\":%i,"
                             "\"sigmat\":%i,"
                             "\"ndef\":%i,"
                             "\"reserve\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                             "\"progcs0\":%i,"
                             "\"progcs1\":%i,"
                             "\"ver\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, st_shtmi1.CC1 , st_shtmi1.CC2 , st_shtmi1.T, st_shtmi1.KC1,
            st_shtmi1.KC2, st_shtmi1.SerNum, st_shtmi1.POST, st_shtmi1.Foc, st_shtmi1.Xo,
            st_shtmi1.Yo, st_shtmi1.Texp, st_shtmi1.Mt, st_shtmi1.St, st_shtmi1.Ndef, st_shtmi1.rezerv1, st_shtmi1.rezerv2, st_shtmi1.rezerv3, st_shtmi1.rezerv4, st_shtmi1.rezerv5,
            st_shtmi1.rezerv6, st_shtmi1.rezerv7, st_shtmi1.rezerv8, st_shtmi1.rezerv9, st_shtmi1.rezerv10, st_shtmi1.rezerv11 ,st_shtmi1.XCF, st_shtmi1.Years + st_shtmi1.Month + st_shtmi1.Days,
            st_shtmi1.Ver1 + st_shtmi1.Ver2 + st_shtmi1.Ver3);
    m_kia_db[TYPE_DATA]->insert_data(data_into_shtmi1, "prepare_insert_into_shtmi1");
}

void ParseToDB::sendDataIntoSHTMI2(uint16_t &num_bokz, uint32_t& bshv, SHTMI2& st_shtmi2)
{
    char data_into_shtmi2[1024];
    sprintf(data_into_shtmi2,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"ss1\":%i,"
                             "\"ss2\":%i,"
                             "\"t\":%i,"
                             "\"st1\":%i,"
                             "\"st2\":%i,"
                             "\"sernum\":%i,"
                             "\"post\":%i,"
                             "\"texp\":%i,"
                             "\"nusd\":%i,"
                             "\"nno\":%i,"
                             "\"nnosl\":%i,"
                             "\"nto\":%i,"
                             "\"ntosl\":%i,"
                             "\"nsl\":%i,"
                             "\"ec1\":%i,"
                             "\"ec2\":%i,"
                             "\"ec3\":%i,"
                             "\"ec4\":%i,"
                             "\"ec5\":%i,"
                             "\"ec6\":%i,"
                             "\"ec7\":%i,"
                             "\"ec8\":%i,"
                             "\"ec9\":%i,"
                             "\"ec10\":%i,"
                             "\"ec11\":%i,"
                             "\"ec12\":%i,"
                             "\"ec13\":%i,"
                             "\"ec14\":%i,"
                             "\"ec15\":%i,"
                             "\"ec16\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, st_shtmi2.CC1 , st_shtmi2.CC2 , st_shtmi2.T, st_shtmi2.KC1,
            st_shtmi2.KC2, st_shtmi2.SerNum, st_shtmi2.POST, st_shtmi2.Texp, st_shtmi2.Nusd,
            st_shtmi2.Nno, st_shtmi2.Nnosl, st_shtmi2.Nto, st_shtmi2.Ntosl, st_shtmi2.Nsl, st_shtmi2.eCount[0], st_shtmi2.eCount[1], st_shtmi2.eCount[2], st_shtmi2.eCount[3], st_shtmi2.eCount[4],
            st_shtmi2.eCount[5], st_shtmi2.eCount[6], st_shtmi2.eCount[7], st_shtmi2.eCount[8], st_shtmi2.eCount[9], st_shtmi2.eCount[10], st_shtmi2.eCount[11], st_shtmi2.eCount[12], st_shtmi2.eCount[13], st_shtmi2.eCount[14],
            st_shtmi2.eCount[15]);
    std::cout << st_shtmi2.T << std::endl;
    m_kia_db[TYPE_DATA]->insert_data(data_into_shtmi2, "prepare_insert_into_shtmi2");
}

void ParseToDB::sendDataIntoMPI(uint16_t &num_bokz, uint32_t &bshv)
{
    char m_data_to_mpi[1024];
    sprintf(m_data_to_mpi,"{\"experiment_id\":\"%s\","
                          "\"serial_num\":%i,"
                          "\"datetime\":\"%s\","
                          "\"struct_id\":\"%s\","
                          "\"host_id\":\"%s\","
                          "\"subarray_id\":%i,"
                          "\"unit_id\":\"%s\","
                          "\"bshv\":%d,"
                          "\"error_code\":%i,"
                          "\"send_time\":\"%s\","
                          "\"mpi_index\":%i,"
                          "\"exchange_counter\":%i,"
                          "\"lpi\":%i,"
                          "\"base\":%i,"
                          "\"address\":%i,"
                          "\"direction\":%i,"
                          "\"subaddress\":%i,"
                          "\"data_size\":%i,"
                          "\"ctrlcode\":%i,"
                          "\"receive_time\":\"%s\","
                          "\"mpi_result\":%i,"
                          "\"nint\":%i,"
                          "\"wresult\":%i,"
                          "\"os\":%i,"
                          "\"waw1\":%i,"
                          "\"waw2\":%i,"
                          "\"data\":\"%s\"}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_data->m_data_db->struct_id.c_str(),
            m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->subarray_id, m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            m_kia_data->m_data_db->error_code, m_kia_data->m_data_db->send_time.c_str(), m_kia_data->m_data_mpi->m_mpi_index, m_kia_settings->m_data_for_db->m_exchange_counter,
            m_kia_data->m_data_mpi->m_lpi, m_kia_data->m_data_mpi->m_base, m_kia_data->m_data_mpi->m_address, m_kia_data->m_data_mpi->m_direction, m_kia_data->m_data_mpi->m_sub_address,
            m_kia_data->m_data_mpi->m_word_data, m_kia_data->m_data_mpi->m_format, m_kia_data->m_data_db->receive_time.c_str(), m_kia_data->m_data_mpi->m_mpi_result,
            m_kia_data->m_data_mpi->m_nInt, m_kia_data->m_data_mpi->m_wResult, m_kia_data->m_data_mpi->m_wOs, m_kia_data->m_data_db->waw1, m_kia_data->m_data_db->waw2, m_kia_data->m_data_db->data.toStdString().c_str());
    m_kia_db[TYPE_RAW]->insert_data(m_data_to_mpi, "prepare_insert_into_mpi");
}

void ParseToDB::sendDataIntoDTMILOC(uint16_t &num_bokz, uint32_t& bshv, DTMILoc_1& dtmiLoc_1, DTMILoc_2& dtmiLoc_2, DTMILoc_3& dtmiLoc_3,
                                    DTMILoc_4& dtmiLoc_4, DTMILoc_5& dtmiLoc_5, DTMILoc_6& dtmiLoc_6,
                                    DTMILoc_7& dtmiLoc_7, DTMILoc_8& dtmiLoc_8, DTMILoc_9& dtmiLoc_9)
{
    SimpleTimer st("DTMI INTO LOC");
    char data_into_dtmiloc[2048];
    sprintf(data_into_dtmiloc,"{\"experiment_id\":\"%s\","
                              "\"serial_num\":%i,"
                              "\"datetime\":\"%s\","
                              "\"host_id\":\"%s\","
                              "\"unit_id\":\"%s\","
                              "\"bshv\":%d,"
                              "\"cc1\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                              "\"cc2\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                              "\"t\":%i,"
                              "\"st1\":%i,"
                              "\"st2\":%i,"
                              "\"sernum\":%i,"
                              "\"texp\":%i,"
                              "\"numloc\":%i,"
                              "\"numobj\":%i,"
                              "\"mean\":%u,"
                              "\"sigma\":%u,"
                              "\"locx\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"locy\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"locb\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"locs\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"reserve\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            dtmiLoc_1.CC1, dtmiLoc_2.CC1, dtmiLoc_3.CC1, dtmiLoc_4.CC1, dtmiLoc_5.CC1, dtmiLoc_6.CC1, dtmiLoc_7.CC1, dtmiLoc_8.CC1, dtmiLoc_9.CC1,
            dtmiLoc_1.CC2, dtmiLoc_2.CC2, dtmiLoc_3.CC2, dtmiLoc_4.CC2, dtmiLoc_5.CC2, dtmiLoc_6.CC2, dtmiLoc_7.CC2, dtmiLoc_8.CC2, dtmiLoc_9.CC2,
            dtmiLoc_1.T, dtmiLoc_1.KC1,
            dtmiLoc_1.KC2, dtmiLoc_1.SerNum, dtmiLoc_1.Texp, dtmiLoc_1.NumLoc, dtmiLoc_1.NumObj,
            dtmiLoc_1.Mean, dtmiLoc_1.Sigma,
            dtmiLoc_1.Loc_0_0, dtmiLoc_1.Loc_1_0, dtmiLoc_1.Loc_2_0,
            dtmiLoc_2.Loc_9_10, dtmiLoc_2.Loc_17_18, dtmiLoc_2.Loc_25_26,
            dtmiLoc_3.Loc_3_4, dtmiLoc_3.Loc_11_12, dtmiLoc_3.Loc_19_20, dtmiLoc_3.Loc_27_28,
            dtmiLoc_4.Loc_5_6, dtmiLoc_4.Loc_13_14, dtmiLoc_4.Loc_21_22, dtmiLoc_4.Loc_29_30,
            dtmiLoc_5.Loc_7_8, dtmiLoc_5.Loc_15_16, dtmiLoc_5.Loc_23_24, dtmiLoc_5.Loc_31_32,
            dtmiLoc_6.Loc_9_10, dtmiLoc_6.Loc_17_18, dtmiLoc_6.Loc_25_26,
            dtmiLoc_7.Loc_3_4, dtmiLoc_7.Loc_11_12, dtmiLoc_7.Loc_19_20, dtmiLoc_7.Loc_27_28,
            dtmiLoc_8.Loc_5_6, dtmiLoc_8.Loc_13_14, dtmiLoc_8.Loc_21_22, dtmiLoc_8.Loc_29_30,
            dtmiLoc_9.Loc_7_8, dtmiLoc_9.Loc_15_16, dtmiLoc_9.Loc_23_24,

            dtmiLoc_1.Loc_0_1, dtmiLoc_1.Loc_1_1,
            dtmiLoc_2.Loc_3_4, dtmiLoc_2.Loc_11_12, dtmiLoc_2.Loc_19_20, dtmiLoc_2.Loc_27_28,
            dtmiLoc_3.Loc_5_6, dtmiLoc_3.Loc_13_14, dtmiLoc_3.Loc_21_22, dtmiLoc_3.Loc_29_30,
            dtmiLoc_4.Loc_7_8, dtmiLoc_4.Loc_15_16, dtmiLoc_4.Loc_23_24, dtmiLoc_4.Loc_31_32,
            dtmiLoc_5.Loc_9_10, dtmiLoc_5.Loc_17_18, dtmiLoc_5.Loc_25_26,
            dtmiLoc_6.Loc_3_4, dtmiLoc_6.Loc_11_12, dtmiLoc_6.Loc_19_20, dtmiLoc_6.Loc_27_28,
            dtmiLoc_7.Loc_5_6, dtmiLoc_7.Loc_13_14, dtmiLoc_7.Loc_21_22, dtmiLoc_7.Loc_29_30,
            dtmiLoc_8.Loc_7_8, dtmiLoc_8.Loc_15_16, dtmiLoc_8.Loc_23_24, dtmiLoc_8.Loc_31_32,
            dtmiLoc_9.Loc_9_10, dtmiLoc_9.Loc_17_18, dtmiLoc_9.Loc_25_26,

            dtmiLoc_1.Loc_0_2, dtmiLoc_1.Loc_1_2,
            dtmiLoc_2.Loc_5_6, dtmiLoc_2.Loc_13_14, dtmiLoc_2.Loc_21_22, dtmiLoc_2.Loc_29_30,
            dtmiLoc_3.Loc_7_8, dtmiLoc_3.Loc_15_16, dtmiLoc_3.Loc_23_24, dtmiLoc_3.Loc_31_32,
            dtmiLoc_4.Loc_9_10, dtmiLoc_4.Loc_17_18, dtmiLoc_4.Loc_25_26,
            dtmiLoc_5.Loc_3_4, dtmiLoc_5.Loc_11_12, dtmiLoc_5.Loc_19_20, dtmiLoc_5.Loc_27_28,
            dtmiLoc_6.Loc_5_6, dtmiLoc_6.Loc_13_14, dtmiLoc_6.Loc_21_22, dtmiLoc_6.Loc_29_30,
            dtmiLoc_7.Loc_7_8, dtmiLoc_7.Loc_15_16, dtmiLoc_7.Loc_23_24, dtmiLoc_7.Loc_31_32,
            dtmiLoc_8.Loc_9_10, dtmiLoc_8.Loc_17_18, dtmiLoc_8.Loc_25_26,
            dtmiLoc_9.Loc_3_4, dtmiLoc_9.Loc_11_12, dtmiLoc_9.Loc_19_20, dtmiLoc_9.Loc_27_28,

            dtmiLoc_1.Loc_0_3, dtmiLoc_1.Loc_1_3,
            dtmiLoc_2.Loc_7_8, dtmiLoc_2.Loc_15_16, dtmiLoc_2.Loc_23_24, dtmiLoc_2.Loc_31_32,
            dtmiLoc_3.Loc_9_10, dtmiLoc_3.Loc_17_18, dtmiLoc_3.Loc_25_26,
            dtmiLoc_4.Loc_3_4, dtmiLoc_4.Loc_11_12, dtmiLoc_4.Loc_19_20, dtmiLoc_4.Loc_27_28,
            dtmiLoc_5.Loc_5_6, dtmiLoc_5.Loc_13_14, dtmiLoc_5.Loc_21_22, dtmiLoc_5.Loc_29_30,
            dtmiLoc_6.Loc_7_8, dtmiLoc_6.Loc_15_16, dtmiLoc_6.Loc_23_24, dtmiLoc_6.Loc_31_32,
            dtmiLoc_7.Loc_9_10, dtmiLoc_7.Loc_17_18, dtmiLoc_7.Loc_25_26,
            dtmiLoc_8.Loc_3_4, dtmiLoc_8.Loc_11_12, dtmiLoc_8.Loc_19_20, dtmiLoc_8.Loc_27_28,
            dtmiLoc_9.Loc_5_6, dtmiLoc_9.Loc_13_14, dtmiLoc_9.Loc_21_22, dtmiLoc_9.Loc_29_30,
            dtmiLoc_9.rezerv);
     m_kia_db[TYPE_DATA]->insert_data(data_into_dtmiloc, "prepare_insert_into_dtmiloc");
}

void ParseToDB::sendDataIntoDTMI(uint16_t &num_bokz, uint32_t& bshv, DTMI_1& dtmi_1, DTMI_2& dtmi_2, DTMI_3& dtmi_3, DTMI_4& dtmi_4,
                                 DTMI_5& dtmi_5, DTMI_6& dtmi_6, DTMI_7& dtmi_7, DTMI_8& dtmi_8,
                                 DTMI_9& dtmi_9)
{
    char data_into_dtmi[4096];
    sprintf(data_into_dtmi,"{\"experiment_id\":\"%s\","
                           "\"serial_num\":%i,"
                           "\"datetime\":\"%s\","
                           "\"host_id\":\"%s\","
                           "\"unit_id\":\"%s\","
                           "\"bshv\":%d,"
                           "\"cc1\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"cc2\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"t\":%i,"
                           "\"st1\":%i,"
                           "\"st2\":%i,"
                           "\"sernum\":%i,"
                           "\"texp\":%i,"
                           "\"numloc\":%i,"
                           "\"numobj\":%i,"
                           "\"numfrag\":%i,"
                           "\"epsilon\":%u,"
                           "\"deltat\":%f,"
                           "\"locx\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"locy\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"locb\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"locs\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"wx\":%f,"
                           "\"wy\":%f,"
                           "\"wz\":%f,"
                           "\"xc\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"yc\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"thfrag\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"objfrag\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"tolg\":%i,"
                           "\"qolg\":\"{%f,%f,%f,%f}\","
                           "\"epoch\":%f,"
                           "\"numl0\":%i,"
                           "\"numl1\":%i,"
                           "\"maxh\":%i,"
                           "\"dxmaxh\":%i,"
                           "\"dymaxh\":%i,"
                           "\"reserve\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\"}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            dtmi_1.CC1, dtmi_2.CC1, dtmi_3.CC1, dtmi_4.CC1, dtmi_5.CC1, dtmi_6.CC1, dtmi_7.CC1, dtmi_8.CC1, dtmi_9.CC1,
            dtmi_1.CC2, dtmi_2.CC2, dtmi_3.CC2, dtmi_4.CC2, dtmi_5.CC2, dtmi_6.CC2, dtmi_7.CC2, dtmi_8.CC2, dtmi_9.CC2,
            dtmi_1.T, dtmi_1.KC1,
            dtmi_1.KC2, dtmi_1.SerNum, dtmi_1.Texp, dtmi_1.NumLoc, dtmi_1.NumObj,
            dtmi_1.NumFrag, dtmi_1.Epsilon, dtmi_1.deltaT,
            dtmi_1.Loc_0_0, dtmi_1.Loc_1_0, dtmi_1.Loc_2_0,
            dtmi_2.Loc_9_10, dtmi_2.Loc_17_18, dtmi_2.Loc_25_26,
            dtmi_3.Loc_3_4, dtmi_3.Loc_11_12, dtmi_3.Loc_19_20, dtmi_3.Loc_27_28,
            dtmi_4.Loc_5_6, dtmi_4.Loc_13_14, dtmi_4.Loc_21_22, dtmi_4.Loc_29_30,
            dtmi_5.Loc_7_8, dtmi_5.Loc_15_16,

            dtmi_1.Loc_0_1, dtmi_1.Loc_1_1,
            dtmi_2.Loc_3_4, dtmi_2.Loc_11_12, dtmi_2.Loc_19_20, dtmi_2.Loc_27_28,
            dtmi_3.Loc_5_6, dtmi_3.Loc_13_14, dtmi_3.Loc_21_22, dtmi_3.Loc_29_30,
            dtmi_4.Loc_7_8, dtmi_4.Loc_15_16, dtmi_4.Loc_23_24, dtmi_4.Loc_31_32,
            dtmi_5.Loc_9_10, dtmi_5.Loc_17_18,

            dtmi_1.Loc_0_2, dtmi_1.Loc_1_2,
            dtmi_2.Loc_5_6, dtmi_2.Loc_13_14, dtmi_2.Loc_21_22, dtmi_2.Loc_29_30,
            dtmi_3.Loc_7_8, dtmi_3.Loc_15_16, dtmi_3.Loc_23_24, dtmi_3.Loc_31_32,
            dtmi_4.Loc_9_10, dtmi_4.Loc_17_18, dtmi_4.Loc_25_26,
            dtmi_5.Loc_3_4, dtmi_4.Loc_11_12, dtmi_5.Loc_19_20,


            dtmi_1.Loc_0_3, dtmi_1.Loc_1_3,
            dtmi_2.Loc_7_8, dtmi_2.Loc_15_16, dtmi_2.Loc_23_24, dtmi_2.Loc_31_32,
            dtmi_3.Loc_9_10, dtmi_3.Loc_17_18, dtmi_3.Loc_25_26,
            dtmi_4.Loc_3_4, dtmi_4.Loc_11_12, dtmi_4.Loc_19_20, dtmi_4.Loc_27_28,
            dtmi_5.Loc_5_6, dtmi_5.Loc_13_14, dtmi_5.Loc_21_22,

            dtmi_5.Wo_x, dtmi_5.Wo_y, dtmi_5.Wo_z,

            dtmi_5.XYc_0_0, dtmi_6.XYc_3_4, dtmi_6.XYc_7_8, dtmi_6.XYc_11_12, dtmi_6.XYc_15_16,
            dtmi_6.XYc_19_20, dtmi_6.XYc_23_24, dtmi_6.XYc_27_28, dtmi_6.XYc_31_32,
            dtmi_7.XYc_3_4, dtmi_7.XYc_7_8, dtmi_7.XYc_11_12, dtmi_7.XYc_15_16,
            dtmi_7.XYc_19_20, dtmi_7.XYc_23_24, dtmi_7.XYc_27_28, dtmi_7.XYc_31_32,

            dtmi_5.XYc_0_1, dtmi_6.XYc_5_6, dtmi_6.XYc_9_10, dtmi_6.XYc_13_14, dtmi_6.XYc_17_18,
            dtmi_6.XYc_21_22, dtmi_6.XYc_25_26, dtmi_6.XYc_29_30, dtmi_7.XYc_5_6,
            dtmi_7.XYc_9_10, dtmi_7.XYc_13_14, dtmi_7.XYc_17_18, dtmi_7.XYc_21_22,
            dtmi_7.XYc_25_26, dtmi_7.XYc_29_30,

            dtmi_8.TheFrag_0, dtmi_8.TheFrag_1, dtmi_8.TheFrag_2, dtmi_8.TheFrag_3, dtmi_8.TheFrag_4,
            dtmi_8.TheFrag_5, dtmi_8.TheFrag_6, dtmi_8.TheFrag_7, dtmi_8.TheFrag_8, dtmi_8.TheFrag_9,
            dtmi_8.TheFrag_10, dtmi_8.TheFrag_11, dtmi_8.TheFrag_12, dtmi_8.TheFrag_13, dtmi_8.TheFrag_14,
            dtmi_8.TheFrag_15,

            dtmi_8.ObjFrag_0, dtmi_8.ObjFrag_1, dtmi_8.ObjFrag_2, dtmi_8.ObjFrag_3, dtmi_8.ObjFrag_4,
            dtmi_8.ObjFrag_5, dtmi_8.ObjFrag_6, dtmi_8.ObjFrag_7, dtmi_8.ObjFrag_8, dtmi_8.ObjFrag_9,
            dtmi_8.ObjFrag_10, dtmi_8.ObjFrag_11, dtmi_8.ObjFrag_12, dtmi_8.ObjFrag_13, dtmi_9.ObjFrag_14,
            dtmi_9.ObjFrag_15,

            dtmi_9.TOlg,

            dtmi_9.QOlg_0, dtmi_9.QOlg_1, dtmi_9.QOlg_2, dtmi_9.QOlg_3,

            dtmi_9.Epoch,

            dtmi_9.NumL_0, dtmi_9.NumL_1,

            dtmi_9.maxH,

            dtmi_9.dxmaxH,

            dtmi_9.dymaxH,

            dtmi_9.rezerv_22_32[0], dtmi_9.rezerv_22_32[1], dtmi_9.rezerv_22_32[2], dtmi_9.rezerv_22_32[3],
            dtmi_9.rezerv_22_32[4], dtmi_9.rezerv_22_32[5], dtmi_9.rezerv_22_32[6], dtmi_9.rezerv_22_32[7],
            dtmi_9.rezerv_22_32[8], dtmi_9.rezerv_22_32[9], dtmi_9.rezerv_22_32[10]);

    m_kia_db[TYPE_DATA]->insert_data(data_into_dtmi, "prepare_insert_into_dtmi");
}

void ParseToDB::send_to_bkpik(uint16_t &num_bi)
{

    char data_into_raw[512];
    sprintf(data_into_raw,"{""\"host_id\":\"%s\","
                          "\"experiment_id\":\"%s\","
                          "\"datetime\":\"%s\","
                          "\"bshv\":%d,"
                          "\"serial_num\":%i,"
                          "\"data\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, m_kia_data->m_data_db->data.toStdString().c_str());
    char data_into_telemetry[512];
    sprintf(data_into_telemetry,"{""\"host_id\":\"%s\","
                                "\"experiment_id\":\"%s\","
                                "\"datetime\":\"%s\","
                                "\"bshv\":%d,"
                                "\"serial_num\":%i,"
                                "\"kc\":\"%s\","
                                "\"kp\":\"%s\","
                                "\"td\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, parse_kc_kp(0).c_str(), parse_kc_kp(1).c_str(), parse_td().c_str());
    m_kia_db[TYPE_RAW]->insert_data(data_into_raw, "prepare_insert_raw");
    m_kia_db[TYPE_DATA]->insert_data(data_into_telemetry, "prepare_insert_telemetry");
}

void ParseToDB::send_to_bi(uint16_t &num_bi)
{
    std::string std_kc;
    parse_data_bi(std_kc, m_kia_data->m_data_bi->m_kc);
    std::string std_kp;
    parse_data_bi(std_kp, m_kia_data->m_data_bi->m_kp);
    std::string std_td;
    parse_data_bi(std_td, m_kia_data->m_data_bi->m_td);
    char data_into_raw[512];
    sprintf(data_into_raw,"{""\"host_id\":\"%s\","
                          "\"experiment_id\":\"%s\","
                          "\"datetime\":\"%s\","
                          "\"bshv\":%d,"
                          "\"serial_num\":%i,"
                          "\"data\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, m_kia_data->m_data_db->data.toStdString().c_str());
    char data_into_telemetry[512];
    sprintf(data_into_telemetry,"{""\"host_id\":\"%s\","
                                "\"experiment_id\":\"%s\","
                                "\"datetime\":\"%s\","
                                "\"bshv\":%d,"
                                "\"serial_num\":%i,"
                                "\"kc\":\"%s\","
                                "\"kp\":\"%s\","
                                "\"td\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, std_kc.c_str(), std_kp.c_str(), std_td.c_str());
    m_kia_db[TYPE_RAW]->insert_data(data_into_raw, "prepare_insert_raw");
    m_kia_db[TYPE_DATA]->insert_data(data_into_telemetry, "prepare_insert_telemetry");
}
template<typename arr>
void ParseToDB::parse_data_bi(string &str, arr data)
{
    str = "{";
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]; ++num_ch)
    {
        str = str + to_string(data[num_ch]) + ",";
    }
    str.pop_back();
    str = str + "}";
}

string ParseToDB::parse_td()
{
    float temperature1 = 46.3;
    float temperature2 = 64.4;
    int16_t acp1 = 89;
    int16_t acp2 = 192;
    string buffer_td = "{";
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]; num_ch++)
    {
        m_kia_settings->m_data_for_bi->m_td.push_back(constants::tarTD[m_kia_data->m_data_bi->m_term_group[num_ch] - 1][0] * (temperature2  + (temperature2 - temperature1)
                                                                                                                                      * (m_kia_data->m_data_bi->m_commandR[num_ch + 1] - acp2) / (acp2 - acp1)) - constants::tarTD[m_kia_data->m_data_bi->m_term_group[num_ch] - 1][1]);
        buffer_td = buffer_td + to_string(m_kia_data->m_data_bi->m_td[num_ch]) + ",";
    }
    buffer_td.pop_back();
    buffer_td = buffer_td + "}";
    return buffer_td;

}

string ParseToDB::parse_kc_kp(uint16_t n)
{
    std::vector<uint16_t> commandBuff;
    for (uint16_t i = 0; i < m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi] * 2; i++)
    {
        commandBuff.push_back(((m_kia_data->m_data_bi->m_commandR[0] >> i) & 0x0001));
    }
    string buffer = "{";
    for (unsigned int i = 0; i < (commandBuff.size() / m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]) + 1; i++)
    {
        if (commandBuff[i * 2 + n] != CS_IS_ON)
            buffer = buffer + to_string(CS_IS_ON) + ",";
        else
            buffer = buffer + to_string(CS_IS_OFF) + ",";

        if (commandBuff[i * 2] != CS_IS_ON)
            m_kia_settings->m_data_for_bi->m_kc.push_back(CS_IS_ON);
        else
            m_kia_settings->m_data_for_bi->m_kc.push_back(CS_IS_OFF);

        if (commandBuff[i * 2 + 1] != CS_IS_ON)
            m_kia_settings->m_data_for_bi->m_kp.push_back(CS_IS_ON);
        else
            m_kia_settings->m_data_for_bi->m_kp.push_back(CS_IS_OFF);
    }
    buffer.pop_back();
    buffer = buffer + "}";
    return buffer;
}



void ParseToDB::send_to_frames(uint16_t &num_bokz, uint32_t& bshv)
{
    char data_into_frames[1024];
    sprintf(data_into_frames,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"max_v\":%d,"
                             "\"min_v\":%d,"
                             "\"average_v\":%f,"
                             "\"variance_v\":%f}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(),
            m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            m_kia_data->m_data_db->m_max, m_kia_data->m_data_db->m_min, m_kia_data->m_data_db->m_average, m_kia_data->m_data_db->m_variance);
    m_kia_db[TYPE_DATA]->insert_data(data_into_frames, "prepare_insert_into_frames");
}



