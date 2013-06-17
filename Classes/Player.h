#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <cocos2d.h>
#include <boost\smart_ptr.hpp>
#include <boost\thread.hpp>
#include <string>
#include "Macros.h"
#include "General.h"

using namespace std;
using namespace boost;
using namespace cocos2d;

namespace sgs {
    namespace core {
        class Card;
        /**
        * @brief �����
        **/
        class Player
        {
        public:
            //��Ϸ�׶Σ��غϿ�ʼ����ʼ�׶Ρ��ж��׶Ρ����ƽ׶Ρ����ƽ׶Ρ����ƽ׶Ρ������׶Ρ��غ��⡢
            enum Phase {RoundStart, Start, Judge, Draw, Play, Discard, Finish, NotActive, PhaseNone};
            //����λ�ã���������װ������
            enum Place { PlaceHand, PlaceEquip, PlaceDelayedTrick, PlaceJudge,
                PlaceSpecial, DiscardPile, DrawPile, PlaceTable, PlaceUnknown,
                PlaceWuGu};
            //��Ϸ��ɫ�����ҷ���
            enum Role {Lord, Loyalist, Rebel, Renegade, Unknow};

            Player(void);
            ~Player(void);
            //id
            CC_SYNTHESIZE(int, id_, Id);
            //�������
            CC_SYNTHESIZE_PASS_BY_REF(string, name_, Name);
            
            CC_SYNTHESIZE_PASS_BY_REF(string, head_, Head);
            //���ָ�룬��һ��ѭ���б�
            CC_SYNTHESIZE_PASS_BY_REF(boost::shared_ptr<Player>, nextPlayer_, NextPlayer);
            CC_SYNTHESIZE_PASS_BY_REF(boost::shared_ptr<Player>, nextLivePlayer_, NextLivePlayer);
            CC_SYNTHESIZE_PASS_BY_REF(boost::shared_ptr<Player>, prePlayer_, PrePlayer);
            CC_SYNTHESIZE_PASS_BY_REF(boost::shared_ptr<Player>, preLivePlayer_, PreLivePlayer);
            //Ѫ��
            CC_SYNTHESIZE(int, hp_, Hp);
            //Ѫ������
            CC_SYNTHESIZE(int, maxHp_, MaxHp);
            //����
            CC_SYNTHESIZE_PASS_BY_REF(string, kingdom_, Kingdom);
            //������
            //CC_SYNTHESIZE_READONLY(int, handcardNum_, HandCardNum);
            //��λ��
            CC_SYNTHESIZE(int, seat_, Seat);
            //�Ƿ񱻷���
            CC_SYNTHESIZE_READONLY_FOR_BOOL(faceup_, Faceup);
            //�Ƿ����
            CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(alive_, Alive);
            //�Ƿ񱻺���
            CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(chained_, Chained);
            //������Χ
            CC_PROPERTY_READONLY(int, attackRange_, AttackRange);
            //owner
            CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(owner_, Owner);
            //ready
            CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(ready_, Ready);

            //�佫
            CC_PROPERTY(boost::shared_ptr<General>, general_, General);
            //��ɫ
            CC_SYNTHESIZE(Role, role_, Role);
            //Place
            CC_SYNTHESIZE(Place, place_, Place);
            //�׶�
            CC_SYNTHESIZE(Phase, phase_, Phase);
            //����
            CC_SYNTHESIZE(boost::shared_ptr<Card>, weapon_, Weapon);
            //����
            CC_SYNTHESIZE(boost::shared_ptr<Card>, armor_, Armor);
            //������
            CC_SYNTHESIZE(boost::shared_ptr<Card>, defensiveHorse_, DefensiveHorse);
            //������
            CC_SYNTHESIZE(boost::shared_ptr<Card>, offensiveHorse_, OffensiveHorse);

            //bool hasFlag(const string &flag) const;
            //void clearFlags();

            /**
            * @brief ��ȡ��������
            **/
            virtual int getHandCardNum();

            //ץ��
            virtual void drawCards(vector<int> cardIds);

            //����
            virtual void discardCards(const set<int>& discardCards);

            /**
            * @brief ������Ϸ�����л�ȡ���ܣ����Ѽ�����������õ�
            *        ��־�̻�ù��ǣ����˻��Ӣ��Ӣ��
            **/
            void acquireSkill(const string &skill_name);
            /**
            * @brief ������Ϸ������ʧȥ����
            **/
            virtual void loseSkill(const string &skill_name);
            bool hasSkill(const string &skill_name) const;
            bool hasInnateSkill(const string &skill_name) const;
            /**
            * @brief �ж��Ƿ���ĳ��������
            **/
            bool hasLordSkill(const string &skill_name, bool include_lose = false) const;

            /**
            * @brief ��װ��
            **/
            void setEquip(boost::shared_ptr<Card> equip);
            /**
            * @brief жװ��
            **/
            void removeEquip(boost::shared_ptr<Card> equip);
            /**
            * @brief �Ƿ���ĳ����
            **/
            bool hasEquip(const boost::shared_ptr<Card> card) const;
            /**
            * @brief �Ƿ���װ��
            **/
            bool hasEquip() const;
            /**
            * @brief �Ƿ���ָ������
            **/
            bool hasWeapon(const string &weapon_name) const;
            /**
            * @brief �Ƿ���Է������߼���
            **/
            bool hasArmorEffect(const string &armor_name) const;

            //�ж�������
            /**
            * @brief ��ȡ�ж�����������
            **/
            vector<boost::shared_ptr<Card> > getJudgingArea() const;
            /**
            * @brief �����ӳٽ���
            **/
            void addDelayedTrick(const boost::shared_ptr<Card> trick);
            /**
            * @brief ȥ���ӳٽ���
            **/
            void removeDelayedTrick(const boost::shared_ptr<Card> trick);
            /**
            * @brief �鿴�ж����Ƿ���ָ���ӳٽ���
            **/
            bool containsTrick(const string &trick_name) const;

            //����﷽��
            /**
            * @brief ��ӱ��
            **/
            void addMark(const string &mark);
            /**
            * @brief ȥ�����
            **/
            void removeMark(const string &mark);
            /**
            * @brief ���ñ��
            **/
            virtual void setMark(const string &mark, int value);
            /**
            * @brief ��ȡĳ���
            **/
            int getMark(const string &mark) const;
            /**
            * @brief ��ȡ�����ƶѵ��ƣ������ǡ��������
            **/
            vector<int> getPile(const string &pile_name) const;
            //����ʹ�÷���
            /**
            * @brief �Ƿ��ù�ĳ�ƣ���Ҫ����ÿ�غ�ֻ�ܷ���һ�εļ��ܣ��жϼ����Ƿ񷢶���
            **/
            bool hasUsed(const string &card_class) const;
            /**
            * @brief ���ڻغ��ڿɶ��ʹ�õ��Ǵ������Ƶļ���
            **/
            int usedTimes(const string &card_class) const;
            //����ʹ�÷���
            /**
            * @brief ��ֹ������ͨ����ʵ�ֵ�
            **/
            virtual bool isProhibited(const boost::shared_ptr<Player> to, const boost::shared_ptr<Card> card) const;
            /**
            * @brief �Ƿ������һ�����ƣ����ڷ��컭���ɱ�ķ���
            **/
            virtual bool isLastHandCard(const boost::shared_ptr<Card> card) const;// = 0;
            /**
            * @brief �Ƿ����������ɱ
            **/
            bool canSlashWithoutCrossbow() const;

            /**
            * @brief �Ƿ��пɹ����Ķ���
            **/
            bool hasCanAttackTarget();
        protected:
            //�����
            map<string, int> marks_;
            //�����ƶ�
            map<string, vector<int> > piles_;
            //��Ϸ�л�ü���
            set<string> acquiredSkills_;
            vector<string> skills_;
            //��־flag
            set<string> flags_;
            //map<string, int> history_;
            vector<int> handCards_;
            
            boost::shared_mutex cardMutex_;
        private:
            //�ж���
            vector<int> judgingArea_;
            //������ҵľ���
            map<const boost::shared_ptr<Player> , int> fixedDistance_;

        };

    };
};

#endif
