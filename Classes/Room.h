#ifndef __ROOM_H__
#define __ROOM_H__

#include <vector>
#include <boost\smart_ptr.hpp>
#include "Structs.h"
#include "ServerPlayer.h"
#include "Card.h"
#include "IoHandler.h"

namespace sgs {
    namespace package {
        class TrickCard;
    }
}
using namespace sgs::package;

using namespace std;
using namespace sgs::core;
using namespace sgs::net;

namespace sgs {
    namespace server {

        /**
        * @brief ������
        **/
        class Room : public sgs::net::IoHandler
        {
        public:
            Room(void);
            ~Room(void);
            /**
            * @brief ���ر�������û����غ��ڣ�
            **/
            boost::shared_ptr<ServerPlayer> getCurrent() const;
            /**
            * @brief ����ĳ�û�
            **/
            void setCurrent(boost::shared_ptr<ServerPlayer> current);
            /**
            * @brief ������ŵ����
            * @return int
            **/
            int alivePlayerCount() const;
            /**
            * @brief ��ȡ�������
            **/
            vector<boost::shared_ptr<ServerPlayer> > getOtherPlayers(boost::shared_ptr<ServerPlayer> except) const;
            /**
            * @brief ��ȡ�������
            **/
            vector<boost::shared_ptr<ServerPlayer> > getPlayers() const;
            /**
            * @brief �Ե�ǰ���Ϊ����ȡ�������
            **/
            vector<boost::shared_ptr<ServerPlayer> > getAllPlayers() const;
            /**
            * @brief ��ȡ���л��ŵ����
            **/
            vector<boost::shared_ptr<ServerPlayer> > getAlivePlayers() const;
            /**
            * @brief ��������״̬
            **/
            void enterDying(boost::shared_ptr<ServerPlayer> player, boost::shared_ptr<DamageStruct> reason);
            /**
            * @brief ɱ�����
            **/
            void killPlayer(boost::shared_ptr<ServerPlayer> player, boost::shared_ptr<DamageStruct> reason = boost::shared_ptr<DamageStruct>());
            /**
            * @brief �������
            **/
            void revivePlayer(boost::shared_ptr<ServerPlayer> player);
            /**
            * @brief ��ȡ���ŵĽ�ɫ
            **/
            vector<string> aliveRoles(boost::shared_ptr<ServerPlayer> except = boost::shared_ptr<ServerPlayer>()) const;
            /**
            * @brief ��Ϸ����
            **/
            void gameOver(const string &winner);
            /**
            * @brief ɱЧ���������а���SlashEffect\SlashEffected�����¼��Ĵ�����
            *        ����һ�������ɱ��Ч����������ȸ����ʹ������ɱ���ɱ���ݻ𡢴���˫�ɽ�����ֽ�����������
            *        ��һ�����ܵ�ɱ��Ч������������ʹ��ɱ��Ч���ټ�ʹ��ͨɱ��Ч��������ɱ���������ơ���������
            **/
            void slashEffect(const SlashEffectStruct &effect);
            /**
            * @brief ɱ�Ľ���������а���SlashHit��SlashMissed�����¼��Ĵ�����
            *        ǰ����ɱ���У������빭������������������1��ɱ���˺�������ɱ��ɱ�������Ƽ�ǿ�������2���˺�
            *        ������ɱ�����ܣ����ʯ�����������µ����ͽ���
            **/
            void slashResult(const SlashEffectStruct &effect, const boost::shared_ptr<Card> jink);
            /**
            * @brief ����Ҹ��Ӽ��ܣ�һ�����������йػ������ļ��ܣ�����졢�ưԡ�����Ҫ�Ƶ�
            **/
            void attachSkillToPlayer(boost::shared_ptr<ServerPlayer> player, const string &skillName);
            /**
            * @brief �����ж�����ܣ��������
            **/
            void detachSkillFromPlayer(boost::shared_ptr<ServerPlayer> player, const string &skillName);
            /**
            * @brief �������ӻ�ȥ��ĳ���
            **/
            void setPlayerFlag(boost::shared_ptr<ServerPlayer> player, const string &flag);
            /**
            * @brief �޸�ĳ��ҵ�ĳ���ԣ������ھ��Ѽ��޸�Ѫ�����ߣ�sp�佫��ԭ���佫����ʱ�޸Ĺ���
            **/
            void setPlayerProperty(boost::shared_ptr<ServerPlayer> player, const char *property_name, const string &value);
            /**
            * @brief ������ҵı����
            **/
            void setPlayerMark(boost::shared_ptr<ServerPlayer> player, const string &mark, int value);
            /**
            * @brief ʹ��ĳ����
            **/
            void useCard(const CardUseStruct &card_use, bool add_history = true);
            /**
            * @brief �����˺�
            **/
            void damage(DamageStruct &data);
            /**
            * @brief ��ʧ����
            **/
            void loseHp(boost::shared_ptr<ServerPlayer> victim, int lose = 1);
            /**
            * @brief ��ʧ��������
            **/
            void loseMaxHp(boost::shared_ptr<ServerPlayer> victim, int lose = 1);
            /**
            * @brief �ָ�����
            **/
            void recover(boost::shared_ptr<ServerPlayer> player, const RecoverStruct &recover, bool set_emotion = false);
            /**
            * @brief ����ʹ��Ч��
            **/
            bool cardEffect(const boost::shared_ptr<Card> card, boost::shared_ptr<ServerPlayer> from, boost::shared_ptr<ServerPlayer> to);
            bool cardEffect(const CardEffectStruct &effect);
            /**
            * @brief �ж�
            **/
            void judge(JudgeStruct &judge_struct);
            /**
            * @brief ץn����
            **/
            vector<int> getNCards(int n, bool update_pile_number = true);
            /**
            * @brief ��ȡ�������
            **/
            boost::shared_ptr<ServerPlayer> getLord() const;
            /**
            * @brief ѯ���Ƿ����
            **/
            void askForGuanxing(boost::shared_ptr<ServerPlayer> zhuge, const vector<int> &cards, bool up_only);
            void doGongxin(boost::shared_ptr<ServerPlayer> shenlvmeng, boost::shared_ptr<ServerPlayer> *target);
            /**
            * @brief ��һ����
            **/
            int drawCard();
            /**
            * @brief ������к����Ƶ���ȷ��
            **/
            void fillAG(const vector<int> &card_ids, boost::shared_ptr<ServerPlayer> who = boost::shared_ptr<ServerPlayer>());
            /**
            * @brief ����ȷ����ץȡһ����
            **/
            void takeAG(boost::shared_ptr<ServerPlayer> player, int card_id);
            /**
            * @brief ��ϵͳ�ṩĳ�ƣ��������Լ������������к������������ɱ�����ݵ���
            **/
            void provide(const boost::shared_ptr<Card> card);
            /**
            * @brief ��ó������ڷ���ĳ�������µ��佫
            **/
            vector<boost::shared_ptr<ServerPlayer> > getLieges(const string &kingdom, boost::shared_ptr<ServerPlayer> lord) const;
            /**
            * @brief չʾĳ�ƣ����
            **/
            void showCard(boost::shared_ptr<ServerPlayer> player, int card_id, boost::shared_ptr<ServerPlayer> only_viewer = boost::shared_ptr<ServerPlayer>());
            /**
            * @brief չʾ������
            **/
            void showAllCards(boost::shared_ptr<ServerPlayer> player, boost::shared_ptr<ServerPlayer> to = boost::shared_ptr<ServerPlayer>());   
            /**
            * @brief ����
            **/
            void drawCards(boost::shared_ptr<ServerPlayer> player, int n, const string &reason = string());
            /**
            * @brief �����
            **/
            void obtainCard(boost::shared_ptr<ServerPlayer> target, const boost::shared_ptr<Card> card, bool unhide = true);
            /**
            * @brief ����
            **/
            void throwCard(int card_id, boost::shared_ptr<ServerPlayer> who);
            /**
            * @brief �ƶ���
            **/
            void moveCardTo(const boost::shared_ptr<Card> card, boost::shared_ptr<ServerPlayer> dstPlayer, Player::Place dstPlace,
                bool forceMoveVisible = false);

            /**
            * @brief ��褷�����ʾ��ɫ
            **/
            Card::Suit askForSuit(boost::shared_ptr<ServerPlayer> player, const string &reason);
            /**
            * @brief ��ʾ���ܴ�����ѡ���Ƿ񷢶�
            **/
            bool askForSkillInvoke(boost::shared_ptr<ServerPlayer> player, const string &skill_name, const string &data = string());
            /**
            * @brief ��ʾ����
            **/
            bool askForDiscard(boost::shared_ptr<ServerPlayer> target, const string &reason, int discard_num, int min_num,
                bool optional = false, bool include_equip = false, const string &prompt = string());
            /**
            * @brief ��ʾ�Ƿ�����и�ɻ�
            **/
            bool askForNullification(const boost::shared_ptr<TrickCard> trick, boost::shared_ptr<ServerPlayer> from, boost::shared_ptr<ServerPlayer> to, bool positive);
            /**
            * @brief ��ʾҪ����ĳ�ƣ���ɱ�������ʾ����������������ʾɱ
            **/
            //const boost::shared_ptr<Card> askForCard(boost::shared_ptr<ServerPlayer> player, const string &pattern, const string &prompt,
            //                  const QVariant &data = QVariant(), TriggerEvent trigger_event = CardResponsed, ServerPlayer *to = NULL);

            bool isFull() const;
            bool isFinished() const;
        protected:
            //��Ϸģʽ
            string mode_;
            //������ң����ŵ����
            vector<boost::shared_ptr<ServerPlayer> > players_, alivePlayers_;
            //
            boost::shared_ptr<ServerPlayer> owner_;
            //�������
            int playerCount_;
            //��ǰ�������
            boost::shared_ptr<ServerPlayer> current_;
            boost::shared_ptr<ServerPlayer> replyPlayer_;
            vector<int> pile1_, pile2_;
            //���������ϵ�δ�������������ƣ����ж��ƣ��ϻ��������
            vector<int> tableCards_;
            //���ƶѣ����ƶ�
            vector<int> drawPile_, discardPile_;
            //��Ϸ�Ƿ�ʼ
            bool gameStarted_;
            //��Ϸ�Ƿ����
            bool gameFinished_;
            int signupCount_;
            //��¼��ÿ���Ƽ���λ��
            map<int, Player::Place> placeMap_;
            //��¼��ÿ���Ƽ���ӵ����
            map<int, boost::shared_ptr<ServerPlayer> > ownerMap_;
            //����
            //boost::shared_ptr<AsioServer> asioServerPtr_;
        };

    };
};

#endif