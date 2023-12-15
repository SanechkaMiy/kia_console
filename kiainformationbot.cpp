//#include "kiainformationbot.h"

//KiaInformationBot::KiaInformationBot(std::shared_ptr<Kia_settings> kia_settings) :
//    m_kia_settings(kia_settings)
//{
//    if (m_kia_settings->m_is_con_to_tg == CS_IS_ON)
//    {
//        m_kiaBot = make_shared<TgBot::Bot>("6258170200:AAEII5FTliTKxsAtFZK3T50vNj6QiSDkO-4");
//        startBot();
//        sendMessage();
//    }
//}

//KiaInformationBot::~KiaInformationBot()
//{
//    cout<<"desctructor KiaInformationBot"<<endl;
//}

//void KiaInformationBot::startBot()
//{
//    m_kiaBot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message)
//    {
//        m_kiaBot->getApi().sendMessage(message->chat->id, "Привет, это Киа Информатор!");
//    });
//    m_flagsForThread.m_stopKiaInformationBot = true;
//    m_flagsForThread.m_futStopKiaInformationBot = std::async([this]()
//    {
//        try {
//            printf("Bot username: %s\n", m_kiaBot->getApi().getMe()->username.c_str());
//            TgBot::TgLongPoll longPoll(*m_kiaBot);
//            while (m_flagsForThread.m_stopKiaInformationBot) {
//                //printf("Long poll started\n");
//                longPoll.start();

//            }
//        } catch (TgBot::TgException& e) {
//            printf("error: %s\n", e.what());
//        }
//    });
//}

//void KiaInformationBot::readMessage()
//{
//    m_kiaBot->getEvents().onAnyMessage([](TgBot::Message::Ptr message)
//    {
//        printf("User wrote %s\n", message->text.c_str());
//        if (StringTools::startsWith(message->text, "/start"))
//        {
//            return;
//        }
//    });
//}

//void KiaInformationBot::sendMessage()
//{
//    m_flagsForThread.m_stopSendToBot = true;
//    m_flagsForThread.m_futBotSend = std::async([this]
//    {
//        while(m_flagsForThread.m_stopSendToBot)
//        {
//            if (!m_dataToTG.empty())
//            {
//                uint32_t idBot = 451403625;
//                m_kiaBot->getApi().sendMessage(idBot, m_dataToTG.front());
//                m_dataToTG.pop();
//            }
//        }
//    });

//}

//void KiaInformationBot::insertDataIntoQueue(string dataToTG)
//{
//    if (m_kia_settings->m_is_con_to_tg == CS_IS_ON)
//    {
//        m_dataToTG.push(dataToTG);
//    }
//}

//void KiaInformationBot::deleteThreadKiaInformationBot()
//{
//    if (m_kia_settings->m_is_con_to_tg == CS_IS_ON)
//    {
//        while (!m_dataToTG.empty()){}
//        m_flagsForThread.m_stopSendToBot = false;
//        m_flagsForThread.m_futBotSend.get();
//        m_flagsForThread.m_stopKiaInformationBot = false;
//        m_flagsForThread.m_futStopKiaInformationBot.get();
//    }
//}
