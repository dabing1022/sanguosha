#ifndef __PACKET_FACTORY_H__
#define __PACKET_FACTORY_H__

#include <string>
#include <boost\shared_ptr.hpp>
#include "ServerPlayer.h"
#include "ClientPlayer.h"

using namespace std;
using namespace sgs::server;
using namespace sgs::client;

namespace sgs{
    namespace packet {

        
        static const char* PACKET_PLAYER_MESSAGE = "PlayerMessage";
        static const char* PACKET_GAME_START = "GameStart";
        static const char* PACKET_GAME_READY = "GameReady";

        static const char* PACKET_NAME_ERROR = "Error";
        static const char* PACKET_NAME_HEARTBEAT = "HeartBeat";
        static const char* PACKET_NAME_ROOM = "Room";
        static const char* PACKET_NAME_REQUEST_ROOM = "RequestRoom";
        static const char* PACKET_NAME_ROOM_PLAYER_PATH = "/Room/Player";
        static const char* PACKET_NAME_PLAYER = "Player";
        
        static const char* PACKET_NAME_PLAYER_JOIN = "PlayerJoin";
        static const char* PACKET_NAME_PLAYER_EXIT = "PlayerExit";
        static const char* PACKET_NAME_ROOM_DESTORY = "RoomDestory";
        static const char* PACKET_NAME_JOIN_ROOM_SUCCESS = "JoinSuccess";
        static const char* PACKET_NAME_SEAT_AND_ROLE = "AssignSeatAndRole";
        static const char* PACKET_NAME_SEAT_AND_ROLE_PLAYER_PATH = "/AssignSeatAndRole/Player";
        static const char* PACKET_NAME_CHOOSE_LORD = "ChooseLord";
        static const char* PACKET_NAME_CHOOSE_GENERAL = "ChooseGeneral";
        
        static const char* PACKET_NAME_DRAW_CARD = "DrawCard";
        static const char* PACKET_NAME_DISCARD_CARD = "DiscardCard";
        static const char* PACKET_NAME_FORCE_DISCARD_CARD = "ForceDiscardCard";
        static const char* PACKET_NAME_LEFT_PILES = "LeftPiles";
        static const char* PACKET_NAME_CARD = "Card";

        static const char* PACKET_NAME_PHASE_CHANGE = "PhaseChange";
        
        static const char* PACKET_NAME_SHOW_TIME_BAR = "ShowTimeBar";
        static const char* PACKET_NAME_HIDDEN_TIME_BAR = "HiddenTimeBar";
        
        static const char* PACKET_NAME_GENERAL = "General";
        static const char* PACKET_NAME_LORD = "Lord";

        static const char* PACKET_ATTRIBUTE_ID = "id";
        static const char* PACKET_ATTRIBUTE_NAME = "name";
        static const char* PACKET_ATTRIBUTE_PHASE = "phase";
        static const char* PACKET_ATTRIBUTE_NUM = "num";
        static const char* PACKET_ATTRIBUTE_TIME = "time";
        static const char* PACKET_ATTRIBUTE_CODE = "code";
        static const char* PACKET_ATTRIBUTE_HEAD = "head";
        static const char* PACKET_ATTRIBUTE_MSG = "msg";
        static const char* PACKET_ATTRIBUTE_LORD = "lord";
        static const char* PACKET_ATTRIBUTE_LOYALIST = "loyalist";
        static const char* PACKET_ATTRIBUTE_REBEL = "rebel";
        static const char* PACKET_ATTRIBUTE_RENEGADE = "renegade";
        static const char* PACKET_ATTRIBUTE_VERSION = "version";
        static const char* PACKET_ATTRIBUTE_ROLE = "role";

        /**
        * @brife stream��ʼ����
        **/
        string streamBeginPacket();

        /**
        * @brife stream��������
        **/
        string streamEndPacket();
        /**
        * @brife ��Ϸ��ʼ����
        **/
        string gameStartPacket();

        /**
        * @brife ��������
        **/
        string heartBeatPacket();

        namespace client {
            /**
            * @brife ���뷿�䱨��
            **/
            string joinRoomPacket();

            /**
            * @brife ���󷿼���Ϣ����
            **/
            string requestRoomInfoPacket();

            /**
            * @brife
            **/
            string readyPacket();

            /**
            * @brife ѡ���佫����
            **/
            string selectGeneralPacket(boost::shared_ptr<Player> player, boost::shared_ptr<General> general);
        }

        namespace server {

            string forceDiscardCards(const boost::shared_ptr<ServerPlayer> player, const set<int>& cards);

            string discardCards(const boost::shared_ptr<ServerPlayer> player, const set<int>& cards);

            /**
            * @brife ����ʣ������
            **/
            string leftPilesPacket(const int number);

            /**
            * @brife ��ʾʱ����
            **/
            string showTimeBarPacket(const boost::shared_ptr<ServerPlayer> player, float time);

            /**
            * @brife ����ʱ����
            **/
            string hiddenTimeBarPacket(const boost::shared_ptr<ServerPlayer> player);

            /**
            * @brife �׶θı�
            **/
            string phaseChangePacket(const boost::shared_ptr<ServerPlayer> player, const Player::Phase phase);
            /**
            * @brife ץ��
            **/
            string drawCardPacket(const boost::shared_ptr<ServerPlayer> player, const vector<int>& cardIds, bool cardDetail = true);
            
            /**
            * @brife ����
            **/
            string discardCardPacket(const boost::shared_ptr<ServerPlayer> player, const vector<int>& cardIds, bool cardDetail = true);
            
            /**
            * @brife ����ѡ��
            **/
            string chooseLordGeneral(const boost::shared_ptr<ServerPlayer> player, const vector<string> & generals);
             /**
            * @brife ������ѡ��
            **/
            string chooseGeneral(const boost::shared_ptr<ServerPlayer> player, const string & lord, const vector<string> & generals);
            /**
            * @brife ��λ���ɫ��Ϣ
            **/
            string seatAndRolePacket(const boost::shared_ptr<ServerPlayer> player, int lord, int loyalist, int rebel, int renegade);
            /**
            * @brife �û����뷿��ɹ�
            **/
            string joinSuccessPacket(const boost::shared_ptr<ServerPlayer> player);

            /**
            * @brife ������
            **/
            string errorMsgPacket(int code ,const string& msg);

            /**
            * @brife ����б���
            **/
            string playerListPacket(const vector<boost::shared_ptr<ServerPlayer> > playerList);

            /**
            * @brife ����Ҽ��뱨��
            **/
            string newPlayerPacket(const boost::shared_ptr<ServerPlayer> player);

            /**
            * @brife ����˳�����
            **/
            string deletePlayerPacket(const boost::shared_ptr<ServerPlayer> player);

            /**
            * @brife �����ɢ����
            **/
            string roomDismissPacket();
        }
    }
}


#endif