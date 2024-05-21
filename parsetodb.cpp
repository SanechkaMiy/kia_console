#include "parsetodb.h"

ParseToDB::ParseToDB(std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
                     std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_db(kia_db)
  , m_kia_settings(kia_settings)

{
    create_parse_list_data();
    create_list_for_mpi_arrays();
}
ParseToDB::~ParseToDB()
{

}

void ParseToDB::set_kia_data(Kia_data kia_data)
{
    m_kia_data = kia_data;
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
                          "\"nint\":%i,"
                          "\"wresult\":%i,"
                          "\"os\":%i,"
                          "\"data\":\"%s\"}",
            m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data.data_bokz->m_date_time.c_str(), m_kia_data.data_bokz->struct_id.first.c_str(),
            m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->subarray_id,
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            m_kia_data.mpi_data->send_time.c_str(), m_kia_data.mpi_data->m_mpi_index,
            m_kia_settings->m_data_for_db->m_exchange_counter, m_kia_data.mpi_data->m_lpi,
            m_kia_data.mpi_data->m_base, m_kia_data.mpi_data->m_address,
            m_kia_data.mpi_data->m_direction, m_kia_data.mpi_data->m_sub_address,
            m_kia_data.mpi_data->m_word_data, m_kia_data.mpi_data->m_format,
            m_kia_data.mpi_data->receive_time.c_str(), m_kia_data.mpi_data->m_nInt, m_kia_data.mpi_data->m_wResult,
            m_kia_data.mpi_data->m_answer_word, m_kia_data.data_bokz->hex_data.toStdString().c_str());
    m_kia_db[TYPE_RAW]->insert_data(m_data_to_mpi, "prepare_insert_into_mpi");
}

void ParseToDB::send_data_to_db(uint16_t key_arr, std::string prepare_query, uint16_t num_bokz, int32_t bshv, DATA data_struct)
{

    std::vector<std::string> temp;
    uint16_t ind = 0;
    uint16_t ind_data_manage = 0;
    std::string data = "{";

    set_default_head_files(num_bokz, data, bshv);
    if (m_data_manage[key_arr].size() != 0)
    {
        while (ind < data_struct.data.size())
        {
            temp.clear();
            for (uint16_t num_el = ind; num_el < ind + std::get<TDM_SIZE>(m_data_manage[key_arr][ind_data_manage]); num_el++)
            {
                temp.push_back(cast_to(std::get<Pio_bokz::DOUBLE_VALUE>(data_struct.data[num_el]),
                                       std::get<TDM_TYPE_CAST>(m_data_manage[key_arr][ind_data_manage])));
            }
            auto str_value = m_prepare_data[std::get<TDM_TYPE_DATA>(m_data_manage[key_arr][ind_data_manage])](temp);
            data = data + "\"" + std::get<TDM_STR>(m_data_manage[key_arr][ind_data_manage]) + "\":" + str_value + ",";

            ind = ind + std::get<TDM_SIZE>(m_data_manage[key_arr][ind_data_manage]);
            ind_data_manage++;
        }
    }
    for (const auto& data_manage_key_array : m_data_manage_key_array[key_arr])
    {
        temp.clear();
        if (data_struct.data_array.find(data_manage_key_array.first) == data_struct.data_array.end())
        {
            continue;
        }
        for (uint16_t num_el = 0; num_el < data_struct.data_array[data_manage_key_array.first].size(); num_el++)
        {
            temp.push_back(cast_to(std::get<Pio_bokz::DOUBLE_VALUE>(data_struct.data_array[data_manage_key_array.first][num_el]),
                           data_manage_key_array.second));
        }
        auto str_value = m_prepare_data[IS_ARR](temp);
        data = data + "\"" + data_manage_key_array.first + "\":" + str_value + ",";
    }
    data.pop_back();
    data = data + "}";
    m_kia_db[TYPE_DATA]->insert_data(data, prepare_query);
}

void ParseToDB::sendDataIntoMSHIOR_MF(uint16_t &num_bokz, int32_t &bshv, MSHIOR_MF &st_mshior)
{
    //    char data_into_mshior[1024];
    //    sprintf(data_into_mshior,"{\"experiment_id\":\"%s\","
    //                             "\"serial_num\":%i,"
    //                             "\"datetime\":\"%s\","
    //                             "\"host_id\":\"%s\","
    //                             "\"unit_id\":\"%s\","
    //                             "\"bshv\":%d,"
    //                             "\"st1\":%i,"
    //                             "\"st2\":%i,"
    //                             "\"t\":%i,"
    //                             "\"tms\":%i,"
    //                             "\"qo\":\"{%f,%f,%f,%f}\","
    //                             "\"wox\":%f,"
    //                             "\"woy\":%f,"
    //                             "\"woz\":%f,"
    //                             "\"tcmv\":%i,"
    //                             "\"numfrag\":%i,"
    //                             "\"numloc_0\":%i,"
    //                             "\"numdet\":%i,"
    //                             "\"lightmv5\":%i,"
    //                             "\"mean\":%i,"
    //                             "\"sigma\":%i,"
    //                             "\"thmax\":%i,"
    //                             "\"m_cur\":%i,"
    //                             "\"p\":%i,"
    //                             "\"dpf_hotpixels\":%i,"
    //                             "\"dpf_updated\":%i,"
    //                             "\"dpf_rejected\":%i,"
    //                             "\"dpf_threshold\":%i,"
    //                             "\"dpf_applied\":%i,"
    //                             "\"sernum\":%i,"
    //                             "\"alpha\":%f,"
    //                             "\"delta\":%f,"
    //                             "\"azimuth\":%f}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
    //            bshv, st_mshior.KC1 , st_mshior.KC2 , st_mshior.T, st_mshior.Tms, st_mshior.Qo0, st_mshior.Qo1, st_mshior.Qo2, st_mshior.Qo3, st_mshior.wox,
    //            st_mshior.woy, st_mshior.woz, st_mshior.Tcmv, st_mshior.NumFrag, st_mshior.NumLoc_0, st_mshior.NumDet,
    //            st_mshior.LightMv5, st_mshior.Mean, st_mshior.Sigma, st_mshior.ThMax, st_mshior.m_cur, st_mshior.P,
    //            st_mshior.dpf_hotpixels, st_mshior.dpf_updated, st_mshior.dpf_rejected, st_mshior.dpf_threshold,
    //            st_mshior.dpf_applied, st_mshior.ser_num,
    //            m_kia_data->m_data_db->m_alpha, m_kia_data->m_data_db->m_delta, m_kia_data->m_data_db->m_azimuth);
    //    m_kia_db[TYPE_DATA]->insert_data(data_into_mshior, "prepare_insert_into_mshior");
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
                             "\"csum\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
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
                             "\"cs\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, st_shtmi2.nAr , st_shtmi2.T , st_shtmi2.Tms, st_shtmi2.KC1,
            st_shtmi2.KC2, st_shtmi2.SerNum, st_shtmi2.POST, st_shtmi2.Texp, st_shtmi2.Nusd,
            st_shtmi2.Nno, st_shtmi2.Nnosl, st_shtmi2.Nto, st_shtmi2.Ntosl, st_shtmi2.Nsl, st_shtmi2.eCount1, st_shtmi2.eCount2, st_shtmi2.eCount3, st_shtmi2.eCount4, st_shtmi2.eCount5,
            st_shtmi2.eCount6, st_shtmi2.eCount7, st_shtmi2.eCount8, st_shtmi2.eCount9, st_shtmi2.eCount10, st_shtmi2.eCount11, st_shtmi2.eCount12, st_shtmi2.eCount13, st_shtmi2.eCount14, st_shtmi2.eCount15,
            st_shtmi2.eCount16, st_shtmi2.eCount17, st_shtmi2.eCount18, st_shtmi2.eCount19, st_shtmi2.cs);
    m_kia_db[TYPE_DATA]->insert_data(data_into_shtmi2, "prepare_insert_into_shtmi2");
}

void ParseToDB::sendDataIntoMLOC_MF(uint16_t &num_bokz, int32_t &bshv, MLoc_MF &mloc_mf)
{
    SimpleTimer st("DTMI INTO LOC");
    std::string test;
    char data_into_dtmiloc[2048];
    sprintf(data_into_dtmiloc,"{\"experiment_id\":\"%s\","
                              "\"serial_num\":%i,"
                              "\"datetime\":\"%s\","
                              "\"host_id\":\"%s\","
                              "\"unit_id\":\"%s\","
                              "\"bshv\":%d,"
                              "\"nar\":\"%s\","
                              "\"cs\":\"%s\","
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
                              "\"locx\":\"%s\","
                              "\"locy\":\"%s\","
                              "\"locb\":\"%s\","
                              "\"locs\":\"%s\","
                              "\"npixns\":%i,"
                              "\"npixgrns\":%i,"
                              "\"th\":%i,"
                              "\"tcmv\":%i}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            convert_array_to_json_string(mloc_mf.nAr).c_str(),
            convert_array_to_json_string(mloc_mf.cs).c_str(),
            mloc_mf.mLoc_1_mf.T, mloc_mf.mLoc_1_mf.Tms, mloc_mf.mLoc_1_mf.KC1,
            mloc_mf.mLoc_1_mf.KC2, mloc_mf.mLoc_1_mf.SerNum, mloc_mf.mLoc_1_mf.Texp, mloc_mf.mLoc_1_mf.NumLoc, mloc_mf.mLoc_1_mf.NumObj,
            mloc_mf.mLoc_1_mf.PixCount,
            mloc_mf.mLoc_1_mf.Mean, mloc_mf.mLoc_1_mf.Sigma,
            convert_array_to_json_string(mloc_mf.loc_x).c_str(),
            convert_array_to_json_string(mloc_mf.loc_y).c_str(),
            convert_array_to_json_string(mloc_mf.loc_b).c_str(),
            convert_array_to_json_string(mloc_mf.loc_c).c_str(),
            mloc_mf.mLoc_9_mf.nPixNs,
            mloc_mf.mLoc_9_mf.nPixGrNs,
            mloc_mf.mLoc_9_mf.Th,
            mloc_mf.mLoc_9_mf.Tcmv);
    m_kia_db[TYPE_DATA]->insert_data(data_into_dtmiloc, "prepare_insert_into_mloc");
}

void ParseToDB::sendDataIntoDTMI_MF(uint16_t &num_bokz, int32_t &bshv, DTMI_MF &dtmi)
{
    char data_into_dtmi[4096];
    sprintf(data_into_dtmi,"{\"experiment_id\":\"%s\","
                           "\"serial_num\":%i,"
                           "\"datetime\":\"%s\","
                           "\"host_id\":\"%s\","
                           "\"unit_id\":\"%s\","
                           "\"bshv\":%d,"
                           "\"nar\":\"%s\","
                           "\"cs\":\"%s\","
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
                           "\"qlst\":\"%s\","
                           "\"histdef\":\"%s\","
                           "\"rsloc0x\":\"%s\","
                           "\"rsloc0y\":\"%s\","
                           "\"rsloc0b\":\"%s\","
                           "\"rsloc0s\":\"%s\","
                           "\"rsloc1x\":\"%s\","
                           "\"rsloc1y\":\"%s\","
                           "\"rsloc1b\":\"%s\","
                           "\"rsloc1s\":\"%s\","
                           "\"xc\":\"%s\","
                           "\"yc\":\"%s\","
                           "\"meanfrag\":\"%s\","
                           "\"sigmafrag\":\"%s\","
                           "\"thfrag\":\"%s\","
                           "\"objfrag\":\"%s\","
                           "\"multxy\":\"%s\","
                           "\"zipx\":\"%s\","
                           "\"zipy\":\"%s\","
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
                           "\"deltat\":%i,"
                           "\"m_cur\":%i,"
                           "\"histpix\":\"%s\"}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz,
            m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->true_host.c_str(),
            m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv,
            convert_array_to_json_string(dtmi.nAr).c_str(),
            convert_array_to_json_string(dtmi.cs).c_str(),
            dtmi.dtmi_1_mf.T, dtmi.dtmi_1_mf.Tms, dtmi.dtmi_1_mf.KC1,
            dtmi.dtmi_1_mf.KC2, dtmi.dtmi_1_mf.SerNum, dtmi.dtmi_1_mf.POST, dtmi.dtmi_1_mf.Tcmv, dtmi.dtmi_1_mf.Mean, dtmi.dtmi_1_mf.Sigma, dtmi.dtmi_1_mf.Texp,
            dtmi.dtmi_1_mf.PixCount_NumLoc, dtmi.dtmi_1_mf.NumStore, dtmi.dtmi_1_mf.NumDet, dtmi.dtmi_1_mf.NumProgFrag,
            dtmi.dtmi_1_mf.NumFrag, dtmi.dtmi_1_mf.Tlast, dtmi.dtmi_1_mf.Tmslast, convert_array_to_json_string(dtmi.qlst).c_str(),
            convert_array_to_json_string(dtmi.HistDef).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_0_x).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_0_y).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_0_b).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_0_s).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_1_x).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_1_y).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_1_b).c_str(),
            convert_array_to_json_string(dtmi.rsLoc_1_s).c_str(),
            convert_array_to_json_string(dtmi.XYc_x).c_str(),
            convert_array_to_json_string(dtmi.XYc_y).c_str(),
            convert_array_to_json_string(dtmi.MeanFrag).c_str(),
            convert_array_to_json_string(dtmi.SigmaFrag).c_str(),
            convert_array_to_json_string(dtmi.ThFrag).c_str(),
            convert_array_to_json_string(dtmi.ObjFrag).c_str(),
            convert_array_to_json_string(dtmi.MultXY).c_str(),
            convert_array_to_json_string(dtmi.ZipXY_X).c_str(),
            convert_array_to_json_string(dtmi.ZipXY_Y).c_str(),
            dtmi.dtmi_12_mf.Vx,
            dtmi.dtmi_12_mf.Vy,
            dtmi.dtmi_12_mf.Vz,
            dtmi.dtmi_12_mf.Wx,
            dtmi.dtmi_12_mf.Wy,
            dtmi.dtmi_12_mf.Wz,
            dtmi.dtmi_12_mf.Epoch,
            dtmi.dtmi_12_mf.NumL_0,
            dtmi.dtmi_12_mf.NumL_1,
            dtmi.dtmi_12_mf.maxH,
            dtmi.dtmi_12_mf.dxmaxH,
            dtmi.dtmi_12_mf.dymaxH,
            dtmi.dtmi_12_mf.NumSec,
            dtmi.dtmi_12_mf.Epsilon,
            dtmi.dtmi_12_mf.deltaT,
            dtmi.dtmi_12_mf.m_cur,
            convert_array_to_json_string(dtmi.HistPix).c_str());
    m_kia_db[TYPE_DATA]->insert_data(data_into_dtmi, "prepare_insert_into_dtmi");
}

void ParseToDB::send_to_bkpik(uint16_t &num_bi)
{

    //    char data_into_raw[512];
    //    sprintf(data_into_raw,"{""\"host_id\":\"%s\","
    //                          "\"experiment_id\":\"%s\","
    //                          "\"datetime\":\"%s\","
    //                          "\"bshv\":%d,"
    //                          "\"serial_num\":%i,"
    //                          "\"data\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
    //            m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, m_kia_data->m_data_db->data.toStdString().c_str());
    //    char data_into_telemetry[512];
    //    sprintf(data_into_telemetry,"{""\"host_id\":\"%s\","
    //                                "\"experiment_id\":\"%s\","
    //                                "\"datetime\":\"%s\","
    //                                "\"bshv\":%d,"
    //                                "\"serial_num\":%i,"
    //                                "\"kc\":\"%s\","
    //                                "\"kp\":\"%s\","
    //                                "\"td\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
    //            m_kia_data.data_bokz->m_date_time.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, parse_kc_kp(0).c_str(), parse_kc_kp(1).c_str(), parse_td().c_str());
    //    m_kia_db[TYPE_RAW]->insert_data(data_into_raw, "prepare_insert_raw");
    //    m_kia_db[TYPE_DATA]->insert_data(data_into_telemetry, "prepare_insert_telemetry");
}

void ParseToDB::send_to_bi(uint16_t &num_bi)
{
    std::string std_kc;
    parse_data_bi(std_kc, m_kia_data.kia_bi_data->m_kc);
    std::string std_kp;
    parse_data_bi(std_kp, m_kia_data.kia_bi_data->m_kp);
    std::string std_td;
    parse_data_bi(std_td, m_kia_data.kia_bi_data->m_td);
    char data_into_raw[512];
    sprintf(data_into_raw,"{""\"host_id\":\"%s\","
                          "\"experiment_id\":\"%s\","
                          "\"datetime\":\"%s\","
                          "\"bshv\":%d,"
                          "\"serial_num\":%i,"
                          "\"data\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            m_kia_data.kia_bi_data->m_date_time.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, m_kia_data.kia_bi_data->hex_data.toStdString().c_str());
    char data_into_telemetry[512];
    sprintf(data_into_telemetry,"{""\"host_id\":\"%s\","
                                "\"experiment_id\":\"%s\","
                                "\"datetime\":\"%s\","
                                "\"bshv\":%d,"
                                "\"serial_num\":%i,"
                                "\"kc\":\"%s\","
                                "\"kp\":\"%s\","
                                "\"td\":\"%s\"}", m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(),
            m_kia_data.kia_bi_data->m_date_time.c_str(), m_kia_settings->m_data_for_db->bshv[num_bi], num_bi, std_kc.c_str(), std_kp.c_str(), std_td.c_str());
    //m_kia_db[TYPE_RAW]->insert_data(data_into_raw, "prepare_insert_raw");
    //m_kia_db[TYPE_DATA]->insert_data(data_into_telemetry, "prepare_insert_telemetry");
}
template<typename arr>
void ParseToDB::parse_data_bi(string &str, arr data)
{
    str = "{";
    for (uint16_t num_ch = 0; num_ch < m_kia_data.kia_bi_data->m_count_channel; ++num_ch)
    {
        str = str + to_string(data[num_ch]) + ",";
    }
    str.pop_back();
    str = str + "}";
}

string ParseToDB::parse_td()
{
    const double tarTD[6][2] = {{4.465309361, 235.5450688},{4.456359845, 235.5186178},{4.447446551, 235.4922949},
                                {4.438569256, 235.466099},{4.429727741, 235.4400294},{4.420921788, 235.4140852}};
    float temperature1 = 46.3;
    float temperature2 = 64.4;
    int16_t acp1 = 89;
    int16_t acp2 = 192;
    string buffer_td = "{";
    //    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]; num_ch++)
    //    {
    //        m_kia_settings->m_data_for_bi->m_td.push_back(tarTD[m_kia_data->m_data_bi->m_term_group[num_ch] - 1][0] * (temperature2  + (temperature2 - temperature1)
    //                                                                                                                              * (m_kia_data->m_data_bi->m_commandR[num_ch + 1] - acp2) / (acp2 - acp1)) - tarTD[m_kia_data->m_data_bi->m_term_group[num_ch] - 1][1]);
    //        buffer_td = buffer_td + to_string(m_kia_data->m_data_bi->m_td[num_ch]) + ",";
    //    }
    //    buffer_td.pop_back();
    //    buffer_td = buffer_td + "}";
    return buffer_td;

}

string ParseToDB::parse_kc_kp(uint16_t n)
{
    //    std::vector<uint16_t> commandBuff;
    //    for (uint16_t i = 0; i < m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi] * 2; i++)
    //    {
    //        commandBuff.push_back(((m_kia_data->m_data_bi->m_commandR[0] >> i) & 0x0001));
    //    }
    string buffer = "{";
    //    for (unsigned int i = 0; i < (commandBuff.size() / m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]) + 1; i++)
    //    {
    //        if (commandBuff[i * 2 + n] != CS_IS_ON)
    //            buffer = buffer + to_string(CS_IS_ON) + ",";
    //        else
    //            buffer = buffer + to_string(CS_IS_OFF) + ",";

    //        if (commandBuff[i * 2] != CS_IS_ON)
    //            m_kia_settings->m_data_for_bi->m_kc.push_back(CS_IS_ON);
    //        else
    //            m_kia_settings->m_data_for_bi->m_kc.push_back(CS_IS_OFF);

    //        if (commandBuff[i * 2 + 1] != CS_IS_ON)
    //            m_kia_settings->m_data_for_bi->m_kp.push_back(CS_IS_ON);
    //        else
    //            m_kia_settings->m_data_for_bi->m_kp.push_back(CS_IS_OFF);
    //    }
    //    buffer.pop_back();
    //    buffer = buffer + "}";
    return buffer;
}



void ParseToDB::send_to_frames(uint16_t &num_bokz, int32_t &bshv)
{
    char data_into_frames[1024];
    //    sprintf(data_into_frames,"{\"experiment_id\":\"%s\","
    //                             "\"serial_num\":%i,"
    //                             "\"datetime\":\"%s\","
    //                             "\"host_id\":\"%s\","
    //                             "\"unit_id\":\"%s\","
    //                             "\"bshv\":%d,"
    //                             "\"frame_name\":\"%s\","
    //                             "\"max_v\":%d,"
    //                             "\"min_v\":%d,"
    //                             "\"average_v\":%f,"
    //                             "\"variance_v\":%f}", m_kia_settings->m_data_for_db->experiment_id.c_str(), num_bokz, m_kia_data.data_bokz->m_date_time.c_str(),
    //            m_kia_settings->m_data_for_db->true_host.c_str(), m_kia_settings->m_data_for_db->experiment_id.c_str(), bshv, m_kia_data->m_data_db->frame_name.c_str(),
    //            m_kia_data->m_data_db->m_max, m_kia_data->m_data_db->m_min, m_kia_data->m_data_db->m_average, m_kia_data->m_data_db->m_variance);
    m_kia_db[TYPE_DATA]->insert_data(data_into_frames, "prepare_insert_into_frames");
}

void ParseToDB::send_data_to_db_for_mpi(quint16 num_bokz, qint32 bshv)
{
    sendDataIntoMPI(num_bokz, bshv);
}

void ParseToDB::send_data_to_db_for_bokz(qint16 type_func, quint16 num_bokz, qint32 bshv, Kia_mko_struct kia_mko_struct)
{
    switch(m_kia_settings->m_type_bokz)
    {
    case TYPE_BOKZ_BOKZM60:
        break;
    case TYPE_BOKZ_BOKZMF:
        m_func_to_send_data_bokzmf[type_func](num_bokz, bshv, kia_mko_struct);
        break;
    }


}

void ParseToDB::send_data_to_db_for_bi(qint16 type_func, quint16 num_bi)
{
    m_func_to_send_bi[type_func](num_bi);
}

void ParseToDB::send_data_to_db_for_frames(quint16 num_bokz, qint32 bshv)
{
    send_to_frames(num_bokz, bshv);
}

void ParseToDB::create_list_func_to_send_bokz()
{

    //-------------- mf
    auto func_shtmi1_MF = [this](uint16_t num_bokz, int32_t bshv, Kia_mko_struct kia_mko_struct)
    {
        sendDataIntoSHTMI1_MF(num_bokz, bshv, kia_mko_struct.st_shtmi1_mf);
    };
    m_func_to_send_data_bokzmf[MF_SHTMI1] = func_shtmi1_MF;

    auto func_shtmi2_MF = [this](uint16_t num_bokz, int32_t bshv, Kia_mko_struct kia_mko_struct)
    {
        sendDataIntoSHTMI2_MF(num_bokz, bshv, kia_mko_struct.st_shtmi2_mf);
    };
    m_func_to_send_data_bokzmf[MF_SHTMI2] = func_shtmi2_MF;

    auto func_mshior_MF = [this](uint16_t num_bokz, int32_t bshv, Kia_mko_struct kia_mko_struct)
    {
        sendDataIntoMSHIOR_MF(num_bokz, bshv, kia_mko_struct.st_mshior_mf);
    };
    m_func_to_send_data_bokzmf[MF_MSHIOR] = func_mshior_MF;

    auto func_dtmi_MF = [this](uint16_t num_bokz, int32_t bshv, Kia_mko_struct kia_mko_struct)
    {
        sendDataIntoDTMI_MF(num_bokz, bshv, kia_mko_struct.st_dtmi_mf);
    };
    m_func_to_send_data_bokzmf[MF_DTMI] = func_dtmi_MF;

    auto func_dtmi_mloc_MF = [this](uint16_t num_bokz, int32_t bshv, Kia_mko_struct kia_mko_struct)
    {
        sendDataIntoMLOC_MF(num_bokz, bshv, kia_mko_struct.st_mloc_mf);
    };
    m_func_to_send_data_bokzmf[MF_MLOC] = func_dtmi_mloc_MF;
}

void ParseToDB::create_list_func_to_send_bi()
{
    auto func_shtmi1_m60 = [this](uint16_t num_bi)
    {
        send_to_bkpik(num_bi);
    };
    m_func_to_send_bi.push_back(func_shtmi1_m60);

    auto func_shtmi2_m60 = [this](uint16_t num_bi)
    {
        send_to_bi(num_bi);
    };
    m_func_to_send_bi.push_back(func_shtmi2_m60);
}

void ParseToDB::send_data_to_db_slot(qint16 type_func, QString prepare_query, quint16 num_bokz, qint32 bshv, DATA data_struct)
{
    send_data_to_db(type_func, prepare_query.toStdString(), num_bokz, bshv, data_struct);
}


void ParseToDB::set_default_head_files(uint16_t num_bokz, string &data, int32_t bshv)
{
    data = data + "\"" + "experiment_id" + "\":\"" + m_kia_settings->m_data_for_db->experiment_id.c_str() + "\",";
    data = data + "\"" + "serial_num" + "\":" + std::to_string(num_bokz) + ",";
    data = data + "\"" + "datetime" + "\":\"" + m_kia_data.data_bokz->m_date_time.c_str() + "\",";
    data = data + "\"" + "host_id" + "\":\"" + m_kia_settings->m_data_for_db->true_host.c_str() + "\",";
    data = data + "\"" + "unit_id" + "\":\"" + m_kia_settings->m_data_for_db->experiment_id.c_str() + "\",";
    data = data + "\"" + "bshv" + "\":" + std::to_string(bshv) + ",";
}

void ParseToDB::create_parse_list_data()
{
    auto func_is_el = [this](std::vector<std::string> data)
    {
        std::string ret;
        ret = data[0];
        return ret;
    };
    m_prepare_data.push_back(func_is_el);
    auto func_is_arr = [this](std::vector<std::string> data)
    {
        std::string ret;
        ret = "\"{";
        for (uint16_t ind = 0; ind < data.size(); ind++)
        {
            ret = ret + data[ind] + ",";
        }
        ret.pop_back();
        ret = ret + "}\"";
        return ret;
    };
    m_prepare_data.push_back(func_is_arr);

}

void ParseToDB::create_list_for_mpi_arrays()
{
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "ss1", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "ss2", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "t", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "st1", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "st2", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "sernum", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "post", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "foc", TC_FLOAT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "xo", TC_FLOAT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "yo", TC_FLOAT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "texp", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "meant", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "sigmat", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "ndef", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "xcf", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "datempi", TC_INT));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(IS_EL, 1, "ver", TC_INT));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "ss1", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "ss2", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "t", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "st1", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "st2", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "sernum", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "post", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "texp", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "nusd", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "nno", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "nnosl", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "nto", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "ntosl", TC_INT));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "nsl", TC_INT));

    for (uint16_t num_counter = 0; num_counter < 16; num_counter++)
    {
        m_data_manage[M60_SHTMI2].push_back(std::make_tuple(IS_EL, 1, "ec" + std::to_string(num_counter + 1), TC_INT));
    }

    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "st1", TC_INT));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "st2", TC_INT));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "t", TC_INT));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "ozx", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "ozy", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "ozz", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_ARR, 4, "qo", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "wox", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "woy", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "woz", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "alpha", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "delta", TC_DOUBLE));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(IS_EL, 1, "azimuth", TC_DOUBLE));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "t", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "st1", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "st2", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "sernum", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "texp", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "numloc", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "numobj", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "numfrag", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "epsilon", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "deltat", TC_DOUBLE));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "wx", TC_DOUBLE));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "wy", TC_DOUBLE));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "wz", TC_DOUBLE));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "tolg", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_ARR, 4, "qolg", TC_DOUBLE));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "epoch", TC_DOUBLE));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "numl0", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "numl1", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "maxh", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "dxmaxh", TC_INT));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(IS_EL, 1, "dymaxh", TC_INT));

    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("cc1", TC_INT));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("cc2", TC_INT));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("locx", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("locy", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("locb", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("locs", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("xc", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("yc", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("thfrag", TC_INT));
    m_data_manage_key_array[M60_DTMI].push_back(std::make_pair("objfrag", TC_INT));


    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "t", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "st1", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "st2", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "sernum", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "texp", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "numloc", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "numobj", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "mean", TC_INT));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(IS_EL, 1, "sigma", TC_INT));

    m_data_manage_key_array[M60_DTMI_LOC].push_back(std::make_pair("cc1", TC_INT));
    m_data_manage_key_array[M60_DTMI_LOC].push_back(std::make_pair("cc2", TC_INT));
    m_data_manage_key_array[M60_DTMI_LOC].push_back(std::make_pair("locx", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI_LOC].push_back(std::make_pair("locy", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI_LOC].push_back(std::make_pair("locb", TC_DOUBLE));
    m_data_manage_key_array[M60_DTMI_LOC].push_back(std::make_pair("locs", TC_DOUBLE));
}




template<typename T>
string ParseToDB::convert_array_to_json_string(T data)
{
    std::string ret;
    ret = "{";
    for (uint16_t ind = 0; ind < data.size(); ind++)
    {
        ret = ret + std::to_string(std::get<0>(data[ind])) + ",";
    }
    ret.pop_back();
    ret.push_back('}');
    return ret;
}

