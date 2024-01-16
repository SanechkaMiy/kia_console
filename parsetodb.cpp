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

void ParseToDB::sendDataIntoMSHIOR_M60(uint16_t& num_bokz, int32_t& bshv, MSHIOR &st_mshior)
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

void ParseToDB::sendDataIntoSHTMI1_M60(uint16_t &num_bokz, int32_t& bshv, SHTMI1& st_shtmi1)
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
                             "\"foc\":%f,"
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

void ParseToDB::sendDataIntoSHTMI2_M60(uint16_t &num_bokz, int32_t& bshv, SHTMI2& st_shtmi2)
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
    m_kia_db[TYPE_DATA]->insert_data(data_into_shtmi2, "prepare_insert_into_shtmi2");
}

void ParseToDB::sendDataIntoMPI(uint16_t &num_bokz, int32_t &bshv)
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

void ParseToDB::sendDataIntoDTMILOC_M60(uint16_t &num_bokz, int32_t& bshv, DTMILoc_1& dtmiLoc_1, DTMILoc_2& dtmiLoc_2, DTMILoc_3& dtmiLoc_3,
                                        DTMILoc_4& dtmiLoc_4, DTMILoc_5& dtmiLoc_5, DTMILoc_6& dtmiLoc_6,
                                        DTMILoc_7& dtmiLoc_7, DTMILoc_8& dtmiLoc_8, DTMILoc_9& dtmiLoc_9)
{
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

void ParseToDB::sendDataIntoDTMI_M60(uint16_t &num_bokz, int32_t& bshv, DTMI_1& dtmi_1, DTMI_2& dtmi_2, DTMI_3& dtmi_3, DTMI_4& dtmi_4,
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

void ParseToDB::sendDataIntoMSHIOR_MF(uint16_t &num_bokz, int32_t &bshv, MSHIOR_MF &st_mshior)
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
                             "\"tms\":%i,"
                             "\"qo\":\"{%f,%f,%f,%f}\","
                             "\"wox\":%f,"
                             "\"woy\":%f,"
                             "\"woz\":%f,"
                             "\"tcmv\":%i,"
                             "\"numfrag\":%i,"
                             "\"numloc_0\":%i,"
                             "\"numdet\":%i,"
                             "\"lightmv5\":%i,"
                             "\"mean\":%i,"
                             "\"sigma\":%i,"
                             "\"thmax\":%i,"
                             "\"m_cur\":%i,"
                             "\"p\":%i,"
                             "\"dpf_hotpixels\":%i,"
                             "\"dpf_updated\":%i,"
                             "\"dpf_rejected\":%i,"
                             "\"dpf_threshold\":%i,"
                             "\"dpf_applied\":%i,"
                             "\"sernum\":%i,"
                             "\"alpha\":%f,"
                             "\"delta\":%f,"
                             "\"azimuth\":%f}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            bshv, st_mshior.KC1 , st_mshior.KC2 , st_mshior.T, st_mshior.Tms, st_mshior.Qo0, st_mshior.Qo1, st_mshior.Qo2, st_mshior.Qo3, st_mshior.wox,
            st_mshior.woy, st_mshior.woz, st_mshior.Tcmv, st_mshior.NumFrag, st_mshior.NumLoc_0, st_mshior.NumDet,
            st_mshior.LightMv5, st_mshior.Mean, st_mshior.Sigma, st_mshior.ThMax, st_mshior.m_cur, st_mshior.P,
            st_mshior.dpf_hotpixels, st_mshior.dpf_updated, st_mshior.dpf_rejected, st_mshior.dpf_threshold,
            st_mshior.dpf_applied, st_mshior.ser_num,
            m_kia_data->m_data_db->m_alpha, m_kia_data->m_data_db->m_delta, m_kia_data->m_data_db->m_azimuth);
    m_kia_db[TYPE_DATA]->insert_data(data_into_mshior, "prepare_insert_into_mshior");
}

void ParseToDB::sendDataIntoSHTMI1_MF(uint16_t &num_bokz, int32_t &bshv, SHTMI1_MF &st_shtmi1)
{
    char data_into_shtmi1[1024];
    sprintf(data_into_shtmi1,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"nar\":%i,"
                             "\"t\":%i,"
                             "\"tms\":%i,"
                             "\"st1\":%i,"
                             "\"st2\":%i,"
                             "\"sernum\":%i,"
                             "\"post\":%i,"
                             "\"foc\":%f,"
                             "\"xo\":%f,"
                             "\"yo\":%f,"
                             "\"texp\":%i,"
                             "\"meant\":%i,"
                             "\"sigmat\":%i,"
                             "\"cntupn\":%i,"
                             "\"tcmv\":%i,"
                             "\"confcs\":%i,"
                             "\"desct\":%i,"
                             "\"ogconstcrc\":%i,"
                             "\"reserve\":\"{%i,%i}\","
                             "\"catcs0\":%i,"
                             "\"catcs1\":%i,"
                             "\"constcs0\":%i,"
                             "\"constcs1\":%i,"
                             "\"progcs0\":%i,"
                             "\"progcs1\":%i,"
                             "\"ver\":%i,"
                             "\"csum\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, st_shtmi1.nAr , st_shtmi1.T , st_shtmi1.Tms, st_shtmi1.KC1,
            st_shtmi1.KC2, st_shtmi1.SerNum, st_shtmi1.POST, st_shtmi1.Foc, st_shtmi1.Xo,
            st_shtmi1.Yo, st_shtmi1.Texp, st_shtmi1.Mean, st_shtmi1.Sigma, st_shtmi1.cntUPN, st_shtmi1.Tcmv, st_shtmi1.ConfCS, st_shtmi1.desc, st_shtmi1.ogConstCrc, st_shtmi1.rezerv1, st_shtmi1.rezerv2, st_shtmi1.CatCS0, st_shtmi1.CatCS1,
            st_shtmi1.ConstCS0, st_shtmi1.ConstCS1, st_shtmi1.ProgCS0, st_shtmi1.ProgCS1,
            st_shtmi1.Ver1 + st_shtmi1.Ver2 + st_shtmi1.Ver3,
            st_shtmi1.cs);
    m_kia_db[TYPE_DATA]->insert_data(data_into_shtmi1, "prepare_insert_into_shtmi1");
}

void ParseToDB::sendDataIntoSHTMI2_MF(uint16_t &num_bokz, int32_t &bshv, SHTMI2_MF &st_shtmi2)
{
    char data_into_shtmi2[1024];
    sprintf(data_into_shtmi2,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"nar\":%i,"
                             "\"t\":%i,"
                             "\"t,s\":%i,"
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
                             "\"ec16\":%i,"
                             "\"ec17\":%i,"
                             "\"ec18\":%i,"
                             "\"ec19\":%i,"
                             "\"cs\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, st_shtmi2.nAr , st_shtmi2.T , st_shtmi2.Tms, st_shtmi2.KC1,
            st_shtmi2.KC2, st_shtmi2.SerNum, st_shtmi2.POST, st_shtmi2.Texp, st_shtmi2.Nusd,
            st_shtmi2.Nno, st_shtmi2.Nnosl, st_shtmi2.Nto, st_shtmi2.Ntosl, st_shtmi2.Nsl, st_shtmi2.eCount1, st_shtmi2.eCount2, st_shtmi2.eCount3, st_shtmi2.eCount4, st_shtmi2.eCount5,
            st_shtmi2.eCount6, st_shtmi2.eCount7, st_shtmi2.eCount8, st_shtmi2.eCount9, st_shtmi2.eCount10, st_shtmi2.eCount11, st_shtmi2.eCount12, st_shtmi2.eCount13, st_shtmi2.eCount14, st_shtmi2.eCount15,
            st_shtmi2.eCount16, st_shtmi2.eCount17, st_shtmi2.eCount18, st_shtmi2.eCount19, st_shtmi2.cs);
    m_kia_db[TYPE_DATA]->insert_data(data_into_shtmi2, "prepare_insert_into_shtmi2");
}

void ParseToDB::sendDataIntoMLOC_MF(uint16_t &num_bokz, int32_t &bshv, MLoc_1_MF &dtmiLoc_1, MLoc_2_MF &dtmiLoc_2, MLoc_3_MF &dtmiLoc_3, MLoc_4_MF &dtmiLoc_4, MLoc_5_MF &dtmiLoc_5, MLoc_6_MF &dtmiLoc_6, MLoc_7_MF &dtmiLoc_7, MLoc_8_MF &dtmiLoc_8, MLoc_9_MF &dtmiLoc_9)
{
    SimpleTimer st("DTMI INTO LOC");
    char data_into_dtmiloc[2048];
    sprintf(data_into_dtmiloc,"{\"experiment_id\":\"%s\","
                              "\"serial_num\":%i,"
                              "\"datetime\":\"%s\","
                              "\"host_id\":\"%s\","
                              "\"unit_id\":\"%s\","
                              "\"bshv\":%d,"
                              "\"nar\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                              "\"cs\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                              "\"t\":%i,"
                              "\"tms\":%i,"
                              "\"st1\":%i,"
                              "\"st2\":%i,"
                              "\"sernum\":%i,"
                              "\"texp\":%i,"
                              "\"numloc\":%i,"
                              "\"numobj\":%i,"
                              "\"pixcount\":%i,"
                              "\"mean\":%u,"
                              "\"sigma\":%u,"
                              "\"locx\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"locy\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"locb\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                              "\"locs\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                              "\"npixns\":%i,"
                              "\"npixgrns\":%i,"
                              "\"th\":%i,"
                              "\"tcmv\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            dtmiLoc_1.nAr, dtmiLoc_2.nAr, dtmiLoc_3.nAr, dtmiLoc_4.nAr, dtmiLoc_5.nAr, dtmiLoc_6.nAr, dtmiLoc_7.nAr, dtmiLoc_8.nAr, dtmiLoc_9.nAr,
            dtmiLoc_1.cs, dtmiLoc_2.cs, dtmiLoc_3.cs, dtmiLoc_4.cs, dtmiLoc_5.cs, dtmiLoc_6.cs, dtmiLoc_7.cs, dtmiLoc_8.cs, dtmiLoc_9.cs,
            dtmiLoc_1.T, dtmiLoc_1.Tms, dtmiLoc_1.KC1,
            dtmiLoc_1.KC2, dtmiLoc_1.SerNum, dtmiLoc_1.Texp, dtmiLoc_1.NumLoc, dtmiLoc_1.NumObj,
            dtmiLoc_1.PixCount,
            dtmiLoc_1.Mean, dtmiLoc_1.Sigma,
            dtmiLoc_1.Loc_0_X, dtmiLoc_1.Loc_1_X, dtmiLoc_1.Loc_2_X,
            dtmiLoc_2.Loc_3_X, dtmiLoc_2.Loc_4_X, dtmiLoc_2.Loc_5_X,
            dtmiLoc_2.Loc_6_X, dtmiLoc_3.Loc_7_X, dtmiLoc_3.Loc_8_X, dtmiLoc_3.Loc_9_X,
            dtmiLoc_3.Loc_10_X, dtmiLoc_4.Loc_11_X, dtmiLoc_4.Loc_12_X, dtmiLoc_4.Loc_13_X,
            dtmiLoc_4.Loc_14_X, dtmiLoc_4.Loc_15_X, dtmiLoc_5.Loc_16_X, dtmiLoc_5.Loc_17_X,
            dtmiLoc_5.Loc_18_X, dtmiLoc_5.Loc_19_X, dtmiLoc_6.Loc_20_X,
            dtmiLoc_6.Loc_21_X, dtmiLoc_6.Loc_22_X, dtmiLoc_6.Loc_23_X, dtmiLoc_7.Loc_24_X,
            dtmiLoc_7.Loc_25_X, dtmiLoc_7.Loc_26_X, dtmiLoc_7.Loc_27_X, dtmiLoc_8.Loc_28_X,
            dtmiLoc_8.Loc_29_X, dtmiLoc_8.Loc_30_X, dtmiLoc_8.Loc_31_X, dtmiLoc_8.Loc_32_X,
            dtmiLoc_9.Loc_33_X, dtmiLoc_9.Loc_34_X, dtmiLoc_9.Loc_35_X,

            dtmiLoc_1.Loc_0_Y, dtmiLoc_1.Loc_1_Y, dtmiLoc_1.Loc_2_Y,
            dtmiLoc_2.Loc_3_Y, dtmiLoc_2.Loc_4_Y, dtmiLoc_2.Loc_5_Y,
            dtmiLoc_2.Loc_6_Y, dtmiLoc_3.Loc_7_Y, dtmiLoc_3.Loc_8_Y, dtmiLoc_3.Loc_9_Y,
            dtmiLoc_3.Loc_10_Y, dtmiLoc_4.Loc_11_Y, dtmiLoc_4.Loc_12_Y, dtmiLoc_4.Loc_13_Y,
            dtmiLoc_4.Loc_14_Y, dtmiLoc_5.Loc_15_Y, dtmiLoc_5.Loc_16_Y, dtmiLoc_5.Loc_17_Y,
            dtmiLoc_5.Loc_18_Y, dtmiLoc_5.Loc_19_Y, dtmiLoc_6.Loc_20_Y,
            dtmiLoc_6.Loc_21_Y, dtmiLoc_6.Loc_22_Y, dtmiLoc_6.Loc_23_Y, dtmiLoc_7.Loc_24_Y,
            dtmiLoc_7.Loc_25_Y, dtmiLoc_7.Loc_26_Y, dtmiLoc_7.Loc_27_Y, dtmiLoc_8.Loc_28_Y,
            dtmiLoc_8.Loc_29_Y, dtmiLoc_8.Loc_30_Y, dtmiLoc_8.Loc_31_Y, dtmiLoc_9.Loc_32_Y,
            dtmiLoc_9.Loc_33_Y, dtmiLoc_9.Loc_34_Y, dtmiLoc_9.Loc_35_Y,


            dtmiLoc_1.Loc_0_B, dtmiLoc_1.Loc_1_B, dtmiLoc_2.Loc_2_B,
            dtmiLoc_2.Loc_3_B, dtmiLoc_2.Loc_4_B, dtmiLoc_2.Loc_5_B,
            dtmiLoc_2.Loc_6_B, dtmiLoc_3.Loc_7_B, dtmiLoc_3.Loc_8_B, dtmiLoc_3.Loc_9_B,
            dtmiLoc_3.Loc_10_B, dtmiLoc_4.Loc_11_B, dtmiLoc_4.Loc_12_B, dtmiLoc_4.Loc_13_B,
            dtmiLoc_4.Loc_14_B, dtmiLoc_5.Loc_15_B, dtmiLoc_5.Loc_16_B, dtmiLoc_5.Loc_17_B,
            dtmiLoc_5.Loc_18_B, dtmiLoc_6.Loc_19_B, dtmiLoc_6.Loc_20_B,
            dtmiLoc_6.Loc_21_B, dtmiLoc_6.Loc_22_B, dtmiLoc_6.Loc_23_B, dtmiLoc_7.Loc_24_B,
            dtmiLoc_7.Loc_25_B, dtmiLoc_7.Loc_26_B, dtmiLoc_7.Loc_27_B, dtmiLoc_8.Loc_28_B,
            dtmiLoc_8.Loc_29_B, dtmiLoc_8.Loc_30_B, dtmiLoc_8.Loc_31_B, dtmiLoc_9.Loc_32_B,
            dtmiLoc_9.Loc_33_B, dtmiLoc_9.Loc_34_B, dtmiLoc_9.Loc_35_B,

            dtmiLoc_1.Loc_0_S, dtmiLoc_1.Loc_1_S, dtmiLoc_2.Loc_2_S,
            dtmiLoc_2.Loc_3_S, dtmiLoc_2.Loc_4_S, dtmiLoc_2.Loc_5_S,
            dtmiLoc_3.Loc_6_S, dtmiLoc_3.Loc_7_S, dtmiLoc_3.Loc_8_S, dtmiLoc_3.Loc_9_S,
            dtmiLoc_3.Loc_10_S, dtmiLoc_4.Loc_11_S, dtmiLoc_4.Loc_12_S, dtmiLoc_4.Loc_13_S,
            dtmiLoc_4.Loc_14_S, dtmiLoc_5.Loc_15_S, dtmiLoc_5.Loc_16_S, dtmiLoc_5.Loc_17_S,
            dtmiLoc_5.Loc_18_S, dtmiLoc_6.Loc_19_S, dtmiLoc_6.Loc_20_S,
            dtmiLoc_6.Loc_21_S, dtmiLoc_6.Loc_22_S, dtmiLoc_7.Loc_23_S, dtmiLoc_7.Loc_24_S,
            dtmiLoc_7.Loc_25_S, dtmiLoc_7.Loc_26_S, dtmiLoc_7.Loc_27_S, dtmiLoc_8.Loc_28_S,
            dtmiLoc_8.Loc_29_S, dtmiLoc_8.Loc_30_S, dtmiLoc_8.Loc_31_S, dtmiLoc_9.Loc_32_S,
            dtmiLoc_9.Loc_33_S, dtmiLoc_9.Loc_34_S, dtmiLoc_9.Loc_35_S,
            dtmiLoc_9.nPixNs,
            dtmiLoc_9.nPixGrNs,
            dtmiLoc_9.Th,
            dtmiLoc_9.Tcmv);
    m_kia_db[TYPE_DATA]->insert_data(data_into_dtmiloc, "prepare_insert_into_dtmiloc");
}

void ParseToDB::sendDataIntoDTMI_MF(uint16_t &num_bokz, int32_t &bshv, DTMI_1_MF &dtmi_1, DTMI_2_MF &dtmi_2, DTMI_3_MF &dtmi_3, DTMI_4_MF &dtmi_4, DTMI_5_MF &dtmi_5, DTMI_6_MF &dtmi_6, DTMI_7_MF &dtmi_7, DTMI_8_MF &dtmi_8, DTMI_9_MF &dtmi_9, DTMI_10_MF &dtmi_10, DTMI_11_MF &dtmi_11, DTMI_12_MF &dtmi_12)
{
    char data_into_dtmi[4096];
    auto ObjFrag_0_1_2_3 = helpers::split_data_from_word(dtmi_11.ObjFrag_0_1_2_3);
    auto MultXY_0_1_2_3 = helpers::split_data_from_word(dtmi_11.MultXY_0_1_2_3);
    auto ZipXY_0_1 = helpers::split_data_from_word(dtmi_11.ZipXY_0_0_0_1_1_0_1_1);
    auto ZipXY_2_3 = helpers::split_data_from_word(dtmi_11.ZipXY_2_0_2_1_3_0_3_1);
    auto ObjFrag_4_5_6_7 = helpers::split_data_from_word(dtmi_11.ObjFrag_4_5_6_7);
    auto MultXY_4_5_6_7 = helpers::split_data_from_word(dtmi_11.MultXY_4_5_6_7);
    auto ZipXY_4_5 = helpers::split_data_from_word(dtmi_11.ZipXY_4_0_4_1_5_0_5_1);
    auto ZipXY_6_7 = helpers::split_data_from_word(dtmi_11.ZipXY_6_0_6_0_7_0_7_1);
    auto ObjFrag_8_9_10_11 = helpers::split_data_from_word(dtmi_11.ObjFrag_8_9_10_11);
    auto MultXY_8_9_10_11 = helpers::split_data_from_word(dtmi_11.MultXY_8_9_10_11);
    auto ZipXY_8_9 = helpers::split_data_from_word(dtmi_11.ZipXY_8_0_8_0_9_0_9_1);
    auto ZipXY_10_11 = helpers::split_data_from_word(dtmi_11.ZipXY_10_0_10_0_11_0_11_1);
    auto ObjFrag_12_13_14_Xh = helpers::split_data_from_word(dtmi_11.ObjFrag_12_13_14_Xh);
    auto MultXY_12_13_14_Xh = helpers::split_data_from_word(dtmi_11.MultXY_12_13_14_Xh);
    auto ZipXY_12_13 = helpers::split_data_from_word(dtmi_11.ZipXY_12_0_12_0_13_0_13_1);
    sprintf(data_into_dtmi,"{\"experiment_id\":\"%s\","
                           "\"serial_num\":%i,"
                           "\"datetime\":\"%s\","
                           "\"host_id\":\"%s\","
                           "\"unit_id\":\"%s\","
                           "\"bshv\":%d,"
                           "\"nar\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"cs\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"t\":%i,"
                           "\"tms\":%i,"
                           "\"st1\":%i,"
                           "\"st2\":%i,"
                           "\"sernum\":%i,"
                           "\"post\":%i,"
                           "\"tcmv\":%i,"
                           "\"meant\":%i,"
                           "\"sigmat\":%i,"
                           "\"texp\":%i,"
                           "\"pixcount_numloc\":%i,"
                           "\"numstore\":%i,"
                           "\"numdet\":%i,"
                           "\"numprogfrag\":%i,"
                           "\"numfrag\":%i,"
                           "\"tlast\":%i,"
                           "\"tmslast\":%i,"
                           "\"qlst\":\"{%f,%f,%f,%f}\","
                           "\"reserve\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"histdef\":\"{%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"rsloc0x\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"rsloc0y\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"rsloc0b\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"rsloc0s\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"rsloc1x\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"rsloc1y\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"rsloc1b\":\"{%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\","
                           "\"rsloc1s\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"xc\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"yc\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"meanfrag\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"sigmafrag\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"thfrag\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"objfrag\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"multxy\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"zipx\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i}\","
                           "\"vx\":%i,"
                           "\"vy\":%i,"
                           "\"vz\":%i,"
                           "\"wx\":%i,"
                           "\"wy\":%i,"
                           "\"wz\":%i,"
                           "\"epoch\":%f,"
                           "\"numl0\":%i,"
                           "\"numl1\":%i,"
                           "\"maxh\":%i,"
                           "\"dxmaxh\":%i,"
                           "\"dymaxh\":%i,"
                           "\"numsec\":%i,"
                           "\"epsilon\":%i,"
                           "\"deltat\":%f,"
                           "\"m_cur\":%f,"
                           "\"histpix\":\"{%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i, %i}\"}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data->m_data_db->m_datetime.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            dtmi_1.nAr, dtmi_2.nAr, dtmi_3.nAr, dtmi_4.nAr, dtmi_5.nAr, dtmi_6.nAr, dtmi_7.nAr, dtmi_8.nAr, dtmi_9.nAr, dtmi_10.nAr, dtmi_11.nAr, dtmi_12.nAr,
            dtmi_1.cs, dtmi_2.cs, dtmi_3.cs, dtmi_4.cs, dtmi_5.cs, dtmi_6.cs, dtmi_7.cs, dtmi_8.cs, dtmi_9.cs, dtmi_10.cs, dtmi_11.cs, dtmi_12.cs,
            dtmi_1.T, dtmi_1.Tms, dtmi_1.KC1,
            dtmi_1.KC2, dtmi_1.SerNum, dtmi_1.POST, dtmi_1.Tcmv, dtmi_1.Mean, dtmi_1.Sigma, dtmi_1.Texp,
            dtmi_1.PixCount_NumLoc, dtmi_1.NumStore, dtmi_1.NumDet, dtmi_1.NumProgFrag,
            dtmi_1.NumFrag, dtmi_1.Tlast, dtmi_1.Tmslast,
            dtmi_1.Qlst_0, dtmi_1.Qlst_1, dtmi_1.Qlst_2, dtmi_1.Qlst_3,
            dtmi_1.rezerv, dtmi_12.rezerv_8, dtmi_12.rezerv_9, dtmi_12.rezerv_10, dtmi_12.rezerv_11, dtmi_12.rezerv_12, dtmi_12.rezerv_13, dtmi_12.rezerv_14, dtmi_12.rezerv_15,

            dtmi_2.RsLoc_0_x, dtmi_2.RsLoc_1_x, dtmi_2.RsLoc_2_x,
            dtmi_2.RsLoc_3_x, dtmi_2.RsLoc_4_x, dtmi_3.RsLoc_5_x,
            dtmi_3.RsLoc_6_x, dtmi_3.RsLoc_7_x, dtmi_3.RsLoc_8_x, dtmi_3.RsLoc_9_x,
            dtmi_4.RsLoc_10_x, dtmi_4.RsLoc_11_x, dtmi_4.RsLoc_12_x, dtmi_4.RsLoc_13_x,
            dtmi_4.RsLoc_14_x,

            dtmi_2.RsLoc_0_y, dtmi_2.RsLoc_1_y, dtmi_2.RsLoc_2_y,
            dtmi_2.RsLoc_3_y, dtmi_2.RsLoc_4_y, dtmi_3.RsLoc_5_y,
            dtmi_3.RsLoc_6_y, dtmi_3.RsLoc_7_y, dtmi_3.RsLoc_8_y, dtmi_3.RsLoc_9_y,
            dtmi_4.RsLoc_10_y, dtmi_4.RsLoc_11_y, dtmi_4.RsLoc_12_y, dtmi_4.RsLoc_13_y,
            dtmi_4.RsLoc_14_y,

            dtmi_2.RsLoc_0_b, dtmi_2.RsLoc_1_b, dtmi_2.RsLoc_2_b,
            dtmi_2.RsLoc_3_b, dtmi_2.RsLoc_4_b, dtmi_3.RsLoc_5_b,
            dtmi_3.RsLoc_6_b, dtmi_3.RsLoc_7_b, dtmi_3.RsLoc_8_b, dtmi_3.RsLoc_9_b,
            dtmi_4.RsLoc_10_b, dtmi_4.RsLoc_11_b, dtmi_4.RsLoc_12_b, dtmi_4.RsLoc_13_b,
            dtmi_4.RsLoc_14_b,

            dtmi_8.RsLoc_T0_0_S, dtmi_8.RsLoc_T0_1_S, dtmi_8.RsLoc_T0_2_S,
            dtmi_8.RsLoc_T0_3_S, dtmi_8.RsLoc_T0_4_S, dtmi_8.RsLoc_T0_5_S,
            dtmi_8.RsLoc_T0_6_S, dtmi_8.RsLoc_T0_7_S, dtmi_8.RsLoc_T0_8_S, dtmi_8.RsLoc_T0_9_S,
            dtmi_8.RsLoc_T0_10_S, dtmi_8.RsLoc_T0_11_S, dtmi_8.RsLoc_T0_12_S, dtmi_8.RsLoc_T0_13_S,
            dtmi_8.RsLoc_T0_14_S,

            dtmi_5.RsLoc_0_x, dtmi_5.RsLoc_1_x, dtmi_5.RsLoc_2_x,
            dtmi_5.RsLoc_3_x, dtmi_5.RsLoc_4_x, dtmi_6.RsLoc_5_x,
            dtmi_6.RsLoc_6_x, dtmi_6.RsLoc_7_x, dtmi_6.RsLoc_8_x, dtmi_6.RsLoc_9_x,
            dtmi_7.RsLoc_10_x, dtmi_7.RsLoc_11_x, dtmi_7.RsLoc_12_x, dtmi_7.RsLoc_13_x,
            dtmi_7.RsLoc_14_x,

            dtmi_5.RsLoc_0_y, dtmi_5.RsLoc_1_y, dtmi_5.RsLoc_2_y,
            dtmi_5.RsLoc_3_y, dtmi_5.RsLoc_4_y, dtmi_6.RsLoc_5_y,
            dtmi_6.RsLoc_6_y, dtmi_6.RsLoc_7_y, dtmi_6.RsLoc_8_y, dtmi_6.RsLoc_9_y,
            dtmi_7.RsLoc_10_y, dtmi_7.RsLoc_11_y, dtmi_7.RsLoc_12_y, dtmi_7.RsLoc_13_y,
            dtmi_7.RsLoc_14_y,

            dtmi_5.RsLoc_0_b, dtmi_5.RsLoc_1_b, dtmi_5.RsLoc_2_b,
            dtmi_5.RsLoc_3_b, dtmi_5.RsLoc_4_b, dtmi_6.RsLoc_5_b,
            dtmi_6.RsLoc_6_b, dtmi_6.RsLoc_7_b, dtmi_6.RsLoc_8_b, dtmi_6.RsLoc_9_b,
            dtmi_7.RsLoc_10_b, dtmi_7.RsLoc_11_b, dtmi_7.RsLoc_12_b, dtmi_7.RsLoc_13_b,
            dtmi_7.RsLoc_14_b,

            dtmi_8.RsLoc_T1_0_S, dtmi_8.RsLoc_T1_1_S, dtmi_8.RsLoc_T1_2_S,
            dtmi_8.RsLoc_T1_3_S, dtmi_8.RsLoc_T1_4_S, dtmi_8.RsLoc_T1_5_S,
            dtmi_8.RsLoc_T1_6_S, dtmi_8.RsLoc_T1_7_S, dtmi_8.RsLoc_T1_8_S, dtmi_8.RsLoc_T1_9_S,
            dtmi_8.RsLoc_T1_10_S, dtmi_8.RsLoc_T1_11_S, dtmi_8.RsLoc_T1_12_S, dtmi_8.RsLoc_T1_13_S,
            dtmi_8.RsLoc_T1_14_S,


            dtmi_5.Wo_x, dtmi_5.Wo_y, dtmi_5.Wo_z,

            dtmi_9.XYc_0_0, dtmi_9.XYc_1_0, dtmi_9.XYc_2_0, dtmi_9.XYc_3_0, dtmi_9.XYc_4_0,
            dtmi_9.XYc_5_0, dtmi_9.XYc_6_0, dtmi_9.XYc_7_0, dtmi_9.XYc_8_0,
            dtmi_9.XYc_9_0, dtmi_9.XYc_10_0, dtmi_9.XYc_11_0, dtmi_9.XYc_12_0,
            dtmi_9.XYc_13_0, dtmi_9.XYc_14_0,

            dtmi_9.XYc_0_1, dtmi_9.XYc_1_1, dtmi_9.XYc_2_1, dtmi_9.XYc_3_1, dtmi_9.XYc_4_1,
            dtmi_9.XYc_5_1, dtmi_9.XYc_6_1, dtmi_9.XYc_7_1, dtmi_9.XYc_8_1,
            dtmi_9.XYc_9_1, dtmi_9.XYc_10_1, dtmi_9.XYc_11_1, dtmi_9.XYc_12_1,
            dtmi_9.XYc_13_1, dtmi_9.XYc_14_1,

            dtmi_10.Mean_0_0, dtmi_10.Mean_1_0, dtmi_10.Mean_2_0, dtmi_10.Mean_3_0, dtmi_10.Mean_4_0,
            dtmi_10.Mean_5_0, dtmi_10.Mean_6_0, dtmi_10.Mean_7_0, dtmi_10.Mean_8_0,
            dtmi_10.Mean_9_0, dtmi_10.Mean_10_0, dtmi_10.Mean_11_0, dtmi_10.Mean_12_0,
            dtmi_10.Mean_13_0, dtmi_10.Mean_14_0,

            dtmi_10.Mean_0_1, dtmi_10.Mean_1_1, dtmi_10.Mean_2_1, dtmi_10.Mean_3_1, dtmi_10.Mean_4_1,
            dtmi_10.Mean_5_1, dtmi_10.Mean_6_1, dtmi_10.Mean_7_1, dtmi_10.Mean_8_1,
            dtmi_10.Mean_9_1, dtmi_10.Mean_10_1, dtmi_10.Mean_11_1, dtmi_10.Mean_12_1,
            dtmi_10.Mean_13_1, dtmi_10.Mean_14_1,

            dtmi_11.ThFrag_0, dtmi_11.ThFrag_1, dtmi_11.ThFrag_2, dtmi_11.ThFrag_3, dtmi_11.ThFrag_4,
            dtmi_11.ThFrag_5, dtmi_11.ThFrag_6, dtmi_11.ThFrag_7, dtmi_11.ThFrag_8,
            dtmi_11.ThFrag_9, dtmi_11.ThFrag_10, dtmi_11.ThFrag_11, dtmi_11.ThFrag_12,
            dtmi_11.ThFrag_13, dtmi_11.ThFrag_14,

            dtmi_11.ThFrag_0, dtmi_11.ThFrag_1, dtmi_11.ThFrag_2, dtmi_11.ThFrag_3, dtmi_11.ThFrag_4,
            dtmi_11.ThFrag_5, dtmi_11.ThFrag_6, dtmi_11.ThFrag_7, dtmi_11.ThFrag_8,
            dtmi_11.ThFrag_9, dtmi_11.ThFrag_10, dtmi_11.ThFrag_11, dtmi_11.ThFrag_12,
            dtmi_11.ThFrag_13, dtmi_11.ThFrag_14,

            ObjFrag_0_1_2_3[0], ObjFrag_0_1_2_3[1], ObjFrag_0_1_2_3[2], ObjFrag_0_1_2_3[3],
            ObjFrag_4_5_6_7[0], ObjFrag_4_5_6_7[1], ObjFrag_4_5_6_7[2], ObjFrag_4_5_6_7[3],
            ObjFrag_4_5_6_7[0], ObjFrag_4_5_6_7[1], ObjFrag_4_5_6_7[2], ObjFrag_4_5_6_7[3],
            ObjFrag_8_9_10_11[0], ObjFrag_8_9_10_11[1], ObjFrag_8_9_10_11[2], ObjFrag_8_9_10_11[3],
            ObjFrag_12_13_14_Xh[0], ObjFrag_12_13_14_Xh[1], ObjFrag_12_13_14_Xh[2], ObjFrag_12_13_14_Xh[3],

            MultXY_0_1_2_3[0], MultXY_0_1_2_3[1], MultXY_0_1_2_3[2], MultXY_0_1_2_3[3],
            MultXY_4_5_6_7[0], MultXY_4_5_6_7[1], MultXY_4_5_6_7[2], MultXY_4_5_6_7[3],
            MultXY_8_9_10_11[0], MultXY_8_9_10_11[1], MultXY_8_9_10_11[2], MultXY_8_9_10_11[3],
            MultXY_12_13_14_Xh[0], MultXY_12_13_14_Xh[1], MultXY_12_13_14_Xh[2], MultXY_12_13_14_Xh[3],

            ZipXY_0_1[0]
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



void ParseToDB::send_to_frames(uint16_t &num_bokz, int32_t &bshv)
{
    char data_into_frames[1024];
    sprintf(data_into_frames,"{\"experiment_id\":\"%s\","
                             "\"serial_num\":%i,"
                             "\"datetime\":\"%s\","
                             "\"host_id\":\"%s\","
                             "\"unit_id\":\"%s\","
                             "\"bshv\":%d,"
                             "\"frame_name\":\"%s\","
                             "\"max_v\":%d,"
                             "\"min_v\":%d,"
                             "\"average_v\":%f,"
                             "\"variance_v\":%f}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data->m_data_db->m_datetime.c_str(),
            m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, m_kia_data->m_data_db->frame_name.c_str(),
            m_kia_data->m_data_db->m_max, m_kia_data->m_data_db->m_min, m_kia_data->m_data_db->m_average, m_kia_data->m_data_db->m_variance);
    m_kia_db[TYPE_DATA]->insert_data(data_into_frames, "prepare_insert_into_frames");
}



