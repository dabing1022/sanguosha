#ifndef __SERVER_PLAYER_H__
#define __SERVER_PLAYER_H__

#include <boost\enable_shared_from_this.hpp>
#include <boost\shared_ptr.hpp>

#include "Player.h"
#include "Tag.h"

using namespace boost;

using namespace sgs::tagParser;
using namespace sgs::core;

namespace sgs {
namespace server {

    class SgsServer;
    /**
    * @brief 
    **/
    class ServerPlayer : public Player, public boost::enable_shared_from_this<ServerPlayer>
    {
    public:
        CC_SYNTHESIZE(long, connectionId_, ConnectionId);
        ServerPlayer(void);
        ~ServerPlayer(void);
        //ִ��
        virtual void execute(xmlDocumentPtr& doc);
        
        //�Ƿ���Ҫ����
        bool need2Discard();
        //ǿ������
        void forceDiscard();

        //����λ�úͽ�ɫ
        virtual void assignSeatAndRole(int lord, int loyalist, int rebel, int renegade);

        virtual void askChooseLordGeneral(const vector<string> & generals);

        virtual void askChooseGeneral(const string & lord, const vector<string> & generals);

        virtual void showTimeBar(const float& time);

        virtual void hiddenTimeBar();

        void setSgsServer(boost::shared_ptr<SgsServer> server);

        //override
        //ץ��
        virtual void drawCards(vector<int> cardIds);
        virtual void discardCards(const set<int>& discardCards);
            
        virtual void setGeneral(boost::shared_ptr<General> general);

        //���ý׶�
        virtual void setPhase(Player::Phase phase);

    private:
        
        //���ͱ������ͻ���
        void sendPacket(const string& packet);
        //���ͱ������ͻ���
        void send2OtherPacket(const string& packet);
        void send2AllPacket(const string& packet);
        boost::shared_ptr<SgsServer> server_;
    };

    class AiServerPlayer : public ServerPlayer {
       
    };

};
};

#endif