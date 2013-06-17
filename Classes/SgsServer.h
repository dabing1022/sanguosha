#ifndef __SGS_SERVER_H__
#define __SGS_SERVER_H__

#include <boost\smart_ptr.hpp>
#include <boost\enable_shared_from_this.hpp>
#include <vector>
#include "AsioServer.h"
#include "XmlIoHandler.h"
#include "ServerPlayer.h"

using namespace std;
using namespace sgs::net;

namespace sgs {
    namespace server {

        enum ServerStatus{Waiting, Gaming};

        //1���ȴ����׼�����
        //3������ѡ��
        //4��������ѡ��
        //5��
        enum GamingStatus { Ready, LordChoose , OtherChoose , MainLoop };
        /**
        * @brief �߼���������
        **/
        class SgsServer :public XmlIoHandler
        {
        public:
            SgsServer(void);
            ~SgsServer(void);
            void init();
            /**
            * @brief ����������
            **/
            void start();
            /**
            * @brief �رշ�����
            **/
            void stop();
            
            void connectionOpened(const boost::shared_ptr<Connection> connectionPtr);
            void messaged(const boost::shared_ptr<Connection> connectionPtr, xmlDocumentPtr& doc);
            void connectionClosed(const boost::shared_ptr<Connection> connectionPtr);
            
            virtual void messageSent(const boost::shared_ptr<Connection> connectionPtr, const std::string& msg);
            

            bool validate(const boost::shared_ptr<Connection> connectionPtr, xmlDocumentPtr& doc);
            boost::shared_ptr<ServerPlayer> getPlayerByConnectionId(long connectionId);
            void sendPacket(boost::shared_ptr<ServerPlayer> player, const string& packet);
            void broadcastPacket(const string& packet);
            void broadcastPacketExclude(boost::shared_ptr<ServerPlayer> player, const string& packet);

            //�߼����
            //������λ���ɫ
            void assignSeatAndRole();
            //���������佫
            void assignLordGeneral();
            //�����������佫
            void assignOtherGeneral(const string & lordName);
            //����Ƿ�ȫ��ѡ�����
            void checkChooseGeneral();
            //��ʼϴ��
            int initCards();
            //ץ��
            vector<int> drawCards(int num);
            void discardCards(const set<int>& discardCards);
            
            //��ѭ��
            void mainLoop(bool timerCall = false);

            
        private:
            static const int MAX_PLAYER = 8;
            //�������
            boost::shared_ptr<ServerPlayer> lordPlayer_;
            boost::shared_ptr<ServerPlayer> currentPlayer_;
            //�û��б�
            vector<int > playerList_;
            map<int ,boost::shared_ptr<ServerPlayer> > playerMap_;
            //�ѷ����佫
            set<string> alreadyAssignGeneral_;
            //Asio������
            boost::shared_ptr<AsioServer> server_;
            //�����̶�ʱ��
            Timer mainLoopTimer_;
            //��������ǰ״̬
            ServerStatus status_;
            //�ƶ�
            vector<int> cardIdList_;
            //���ƶ�
            vector<int> discardCardIdList_;
            //��
            boost::shared_mutex mutex_;
            boost::shared_mutex cardMutex_;
            //int playerCount_;
            int readyCount_;
        };

    }
}

#endif