#ifndef __CARD_H__
#define __CARD_H__

namespace sgs {
namespace server {
    class Room;
    class ServerPlayer;
}
}
using namespace sgs::server;

#include <cocos2d.h>
#include <string>
#include <vector>
#include <boost\smart_ptr.hpp>
#include "Macros.h"
#include "Structs.h"

using namespace cocos2d;
using namespace std;



namespace sgs {
namespace core {
    
    class Player;
    /**
    * @brief ��Ƭ��
    **/
    class Card
    {
    private:
        static int GLOBAL_ID;
    public:
        IS_KIND_OF_DECLARE_FOR_ROOT
        //��ɫ�࣬NosuitΪ��ɫ�ƣ������ĺ�Ԩ������
        enum Suit {Spade, Club, Heart, Diamond, NoSuit};
        //��ɫ
        enum Color{Red, Black, Colorless};
        //��Ƭ���ͣ����ܣ����������ң�װ����
        //�����ƾ����佫����������������ƣ���������������������
        enum CardType{Skill, Basic, Trick, Equip };
        
        CC_SYNTHESIZE(Suit , suit_ , Suit);
        //CC_SYNTHESIZE(Color , color_ ,Color);
        CC_SYNTHESIZE(CardType , cardType_ ,CardType);
        //��Ƭid
        CC_SYNTHESIZE(int , id_ ,Id);
        //��Ƭ����
        CC_SYNTHESIZE_PASS_BY_REF(string, name_, Name);
        //number
        CC_SYNTHESIZE(int , number_, Number);
        
        //�Ƿ�Ϊ��ɫ
        //CC_SYNTHESIZE_READONLY_FOR_BOOL(red_, Red);
        //�Ƿ�Ϊ��ɫ
        //CC_SYNTHESIZE_READONLY_FOR_BOOL(black_, Black);
        //����ʱ�Ƿ���Ҫ�ֶ�ѡ��Ŀ��
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(targetFixed_, TargetFixed);
        //���ѡ������
        CC_SYNTHESIZE_PASS_BY_REF(int, minTarget_, MinTarget);
        //���ѡ������
        CC_SYNTHESIZE_PASS_BY_REF(int, maxTarget_, MaxTarget);
        //Ŀ���ܷ�Ϊ�Լ�
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(targetCanBeSelf_, TargetCanBeSelf);
        //�Ƿ�����������������������з��컭꪿�������ɱ1->3��
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(allowMaxTargetWhenFixed_, AllowMaxTargetWhenFixed);
        //�Ƿ��о�������
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(rangeLimit_, RangeLimit);

        
        //�Ƿ��д�������
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(limitUseTimes_, LimitUseTimes);
        //ʹ�ô�������
        CC_SYNTHESIZE_PASS_BY_REF(int, useTimesLimit_, UseTimesLimit);


        //�Ƿ��̨��
        CC_SYNTHESIZE_READONLY_FOR_BOOL(mute_, Mute);
        //ʹ�ú��Ƿ������������ƶ�
        CC_SYNTHESIZE_READONLY_FOR_BOOL(willThrow_, WillThrow);
        //equipped
        CC_SYNTHESIZE_READONLY_FOR_BOOL(equipped_, Equipped);
        //skill_name,��ת��ϵ�ļ��ܷ���ʱ���ü��ܵ����־ͻ��Ǵ�������Ƶļ�����
        CC_SYNTHESIZE_PASS_BY_REF(string, skillName_, SkillName);

        /**
        * @brief ���캯��
        * @param Suit ��ɫ
        * @param number ��С
        * @param targetFixed ����ʱ�Ƿ���Ҫ�ֶ�ѡ��Ŀ�꣬������һ������
        **/
        Card(Suit suit, int number, bool targetFixed = false);
        ~Card(void);
        /**
        * @brief ��ȡ��ɫ�ı�
        **/
        string getSuitString();
        Color getColor();
        /**
        * @brief �Ƿ�Ϊ���⿨Ƭ
        * @return bool 
        **/
        bool isVirtualCard() const;

        int getEffectiveId() const;
        /**
        * @brief ����ӿ�,��ν�ӿ�Ƭ������ӵ�п�Ƭת�����ܵ��佫ʹ�øü���ʱ��
        *       ���ƣ������缧ʹ����һ�ź���A�����統��������ô��������һ������
        *       ��ɫ�Ǻ���A�����ӿ���Ҫ�������ź���A��id
        *       ��Ҫ�õ�addSubcard���佫�����У���š��������������Ϯ����䡢���ҵȵ�
        * @param int cardId 
        * @return void 
        **/
        virtual void addSubcard(int cardId);
        /**
        * @brief ����ӿ�
        * @param boost::shared_ptr<Card>
        * @return void 
        **/
        virtual void addSubcard(const boost::shared_ptr<Card> card);
        
        /**
        * @brief ��ȡ�����ӿ�
        * @return vector<int> 
        **/
        virtual vector<int> getSubcards() const;
        
        /**
        * @brief ����ӿ�
        * @return void
        **/
        virtual void clearSubcards();
        
        /**
        * @brief ��ȡ�ӿ�����
        * @return int 
        **/
        virtual int getSubcardsCount() const;
         /**
        * @brief ��ȡ��Ƭ���� basic trick equip
        * @return string 
        **/
        virtual string getType() const = 0;
        /**
        * @brief ��ȡ�ӿ�Ƭ���ͣ���Ϊ��
        *        �����ƣ�attack_card: �׻���ͨɱ��
        *        �����ƣ�defense_card������
        *        �ظ��ƣ�revover_card���ң�
        *        ȫ��Ч����global_effect����ȷ�ǣ���԰���壩
        *        AOE��aoe���������֣�����뷢��
        *        ������ң�single_target_trick�����С���и��˳���𡢻𹥡��������赶��
        *        ��ʱ���ң�delayed_trick���֡��������֣�
        *        �����ƣ�weapon�� �����ƣ�armor��
        *        ������offensive_horse��������offensive_horse��
        *        �����ƣ�buff_card���ƣ�
        *        ������Χ��չ�ƣ�demage_spread��������
        *        �����ƣ�disgusting_card��ʺ��
        * @return string 
        **/
        virtual string getSubtype() const = 0;
        
        /**
        * @brief �Ƿ�Ϊ���ӳٽ���
        * @return vector<int> 
        **/
        virtual bool isNDTrick() const;

        /**
        * @brief ѡ��Ķ����Ƿ����
        * @return vector<int> 
        **/
        //virtual bool targetsFeasible(const vector<const boost::shared_ptr<Player> > &targets, const  boost::shared_ptr<Player> self) const;
        /**
        * @brief ���ڰ����������Ŀ�꣬����ʹ��ɱʱ�ᰵ��������Χ�ڵ����
        * @return vector<int> 
        **/
        //virtual bool Card::targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const  boost::shared_ptr<Player> to_select, const  boost::shared_ptr<Player> self) const;
        
        /**
        * @brief ���ڰ������ƽ׶β���ʹ�õĿ��ƣ�����û��ɱʱ����
        **/
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;

        //virtual void doPreAction(Room *room, const CardUseStruct &card_use) const;
        /**
        * @brief ʹ��ǰ��Ԥ���������������Ҫ����������缫�ԣ���Ϯ����������
        **/
        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
        /**
        * @brief ֮����Ŀ�꣬ȷ����ʼʹ�ã�ָ��Ŀ����room�����playCardEffect
        **/
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;
        /**
        * @brief ����ʹ�ú���ɵ�Ч��
        **/
        virtual void onEffect(const CardEffectStruct &effect) const;
        /**
        * ���������������ӣ���������������ʹ�ã������������ʱ��������Ӧ��onUser����, ��onUse�����������ж���������ָ���˼���Ŀ�꣬���û��Ŀ�����Ϊ����������������������һ�ţ����ָ����1~2��Ŀ�꣬����use����
        * ��use�����У�����Ҫ��������������Ȼ����room����ִ��ʹ��������Ч���������ڴ��������playCardEffect������������ָ��onEffect��������ѡ����Ŀ�����û����
        **/
        //========================================

    protected:
        //�ӿ�
        vector<int> subcards_;
    };

    /**
    * @brief ������, ���磺�ƺ⡢�ʵ¡�������ͻϮ�����䡢�����
    **/
    class SkillCard: public Card {
    public:
        void setUserString(const string &user_string);

        virtual string getType() const;
        virtual string getSubtype() const;
    };

    /**
    * @brief �������ƺͽ�����ʱʹ�ã������ƽ׶Ρ���ɱ�ҡ����䡢���ˡ�
    *   ���⣬��˫����������š������Ƿŵ�һ��DummyCard����ΪsubCard,�ٰ����DummyCard��ֵΪJink�ġ����й�ʯ���õ�Ҳ�����
    **/
    class DummyCard: public SkillCard {
    public:
        virtual string getType() const;
        virtual string getSubtype() const;
    };

};
};

#endif