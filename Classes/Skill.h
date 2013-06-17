#ifndef __SKILL_H__
#define __SKILL_H__

#include <cocos2d.h>
#include <string>
#include <boost\smart_ptr.hpp>
#include "Macros.h"
#include "Structs.h"
namespace sgs{
namespace server {
    class Room;
    class ServerPlayer;
}
}
using namespace sgs::server;
namespace sgs{
namespace core {
    class Card;
    class Player;
}
}
using namespace sgs::core;

using namespace std;
using namespace cocos2d;


namespace sgs {
namespace core {

    class General;
    /**
    * @brief ������
    **/
    class Skill
    {
    private:
        static CCDictionary * SKILL_STRINGS;
    public:
       
        enum Frequency{
            Frequent,//Ƶ��ʹ�ü�
            NotFrequent,//��Ƶ��ʹ�ü�
            Compulsory,//������
            Limited,//�޶���
            Wake//���Ѽ���
        };
        //Ĭ�ϼ���Ϊ��Ƶ��ʹ�ü��ܣ�����Ӣ�ˡ����ǡ���Ӫ�ȵȡ�
        //��Ƶ��ʹ�õļ��ܾ���ʣ�µģ�һЩ����ʹ�ã��ʵ£�һЩ����ѯ���Ƿ񷢶�


        enum Location{
            Left,
            Right
        };
        //Ƶ��
        CC_SYNTHESIZE_PASS_BY_REF(Frequency, frequency_, Frequency);
        //����
        CC_SYNTHESIZE_PASS_BY_REF(string, name_, Name);
        //������
        CC_SYNTHESIZE_PASS_BY_REF(boost::shared_ptr<General>, parent_, Parent);
        //�Ƿ�ɼ�
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(visible_, Visible);
        //�Ƿ�Ϊ��������
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(lordSkill_, LordSkill);
        
        Skill(const string &name, Frequency frequent = NotFrequent);
        ~Skill(void);

        string getSkillString(const string& key) const;
        /**
        * @brief ��ȡ��������
        **/
        string getDescription() const;
        /**
        * @brief �޶����������������Ѽ�ǰ����С�xx������������������������õ�
        **/
        string getText() const;

        string getChineseName() const;
        /**
        * @brief ��ȡĬ��ѡ�����Ӧ�������г���ʱ�޵�����£�����һЩ��Ҫѡ�񷢶��ļ��ܣ�������û��ѡ��ϵͳ�Զ����ǻ�Ĭ��ѡ�
        *   �維׿�ı���(����>=Ѫ��+2�͵����ߣ������Ѫ��
        **/
        virtual string getDefaultChoice(boost::shared_ptr<ServerPlayer> player) const;
        /**
        * @brief ���ӱ��
        **/
        void setFlag(boost::shared_ptr<ServerPlayer> player) const;
        /**
        * @brief ���ٱ��
        **/
        void unsetFlag(boost::shared_ptr<ServerPlayer> player) const;
    protected:
        string defaultChoice_;

    };
    /**
    * @brief �������������һ���˫�ۡ���������㡢���񣬿��Խ�ĳЩ�Ƶ���������ʹ��
    *   ��������ƿ����ǻ����ơ������ơ�Ҳ����ʹ�����ƣ�����䣩
    **/
    class ViewAsSkill:public Skill{
    public:
        ViewAsSkill(const string &name);

        /**
        * @brief ���ڷ�������ʱ���˵�����ʹ�õĿ���
        *        ���������˵�װ���ƺͺ�ɫ���ơ����һ���˵���ɫװ������
        **/
        virtual bool viewFilter(const vector<const boost::shared_ptr<Card> > &selected, const Card *to_select) const = 0;
        /**
        * @brief �����ڷ�������ʱ��������ת����Ŀ���
        *        ���������Ϊ��
        **/
        virtual const boost::shared_ptr<Card> viewAs(const vector<const boost::shared_ptr<Card> > &cards) const = 0;
        /**
        * @brief �����жϼ����Ƿ����ʹ�ã��������false, ���ܰ�ť������
        * @return bool
        **/
        bool isAvailable(CardUseStruct::CardUseReason reason, const string &pattern) const;
        /**
        * @brief �жϼ����Ƿ�����ڳ��ƽ׶��������¼��������������Ƿ���Է���
        *        ����û���ж���ʱ��˾��Ĺ���Ǳ����õ�
        **/
        virtual bool isEnabledAtPlay(const boost::shared_ptr<Player> player) const;
        /**
        * @brief һЩ����ֻ�����ض������²��ܱ�����
        *        ���类ɱʱ�������������ʹ�ý���ʱ�Ŀ��ơ�
        *        ��Щ�����ɲ���pattern����������������ʱ����Щ���ܻᱻ����
        **/
        virtual bool isEnabledAtResponse(const boost::shared_ptr<Player> player, const string &pattern) const;
        //virtual bool isEnabledAtNullification(const boost::shared_ptr<ServerPlayer> player) const;
        
        static const ViewAsSkill* parseViewAsSkill(const Skill* skill);
    };

    /**
    * @brief ����Ҫ�ƿ��Է����ļ��ܡ�
    *        ͻϮ�����������䡢���⡢�׻�������Ӣ�ꡣ����
    **/
    class ZeroCardViewAsSkill: public ViewAsSkill{
    public:
        ZeroCardViewAsSkill(const string &name);
        /**
        * @brief ���ڷ�������ʱ���˵�����ʹ�õĿ���
        *        ���������˵�װ���ƺͺ�ɫ���ơ����һ���˵���ɫװ������
        **/
        virtual bool viewFilter(const vector<const boost::shared_ptr<Card> > &selected, const boost::shared_ptr<Card> to_select) const;
        /**
        * @brief �����ڷ�������ʱ��������ת����Ŀ���
        *        ���������Ϊ��
        **/
        virtual const boost::shared_ptr<Card> viewAs(const vector<const boost::shared_ptr<Card> > &cards) const;

        virtual const boost::shared_ptr<Card> viewAs() const = 0;
    };

    /**
    * @brief ʹ��һ���ƿ��Է����ļ���
    *        �����š��������ʥ��������
    **/
    class OneCardViewAsSkill: public ViewAsSkill{
    public:
        OneCardViewAsSkill(const string &name);
        /**
        * @brief ���ڷ�������ʱ���˵�����ʹ�õĿ���
        *        ���������˵�װ���ƺͺ�ɫ���ơ����һ���˵���ɫװ������
        **/
        virtual bool viewFilter(const vector<const boost::shared_ptr<Card> > &selected, const boost::shared_ptr<Card> to_select) const;
        /**
        * @brief �����ڷ�������ʱ��������ת����Ŀ���
        *        ���������Ϊ��
        **/
        virtual const boost::shared_ptr<Card> viewAs(const vector<const Card *> &cards) const;

        virtual bool viewFilter(const boost::shared_ptr<Card> to_select) const = 0;
        virtual const boost::shared_ptr<Card> viewAs(const boost::shared_ptr<Card> originalCard) const = 0;
    };

    /**
    * @brief ���ڡ���Ϊ��������
    *        ���ա���ơ�����
    **/
    class FilterSkill: public OneCardViewAsSkill{
    public:
        FilterSkill(const string &name);
    };

    /**
    * @brief ��������ͨ��ĳһ�¼�����ʹ�õļ���
    *        �磺���ҡ������������
    **/
    class TriggerSkill:public Skill{
    public:
        /**
        * @brief ���캯��
        **/
        TriggerSkill(const string &name);
        const boost::shared_ptr<ViewAsSkill> getViewAsSkill() const;
        
        /**
        * @brief ��ȡʱ�����ȼ�
        **/
        virtual int getPriority() const;
        virtual bool triggerable(const boost::shared_ptr<ServerPlayer> target) const;
    protected:
        const boost::shared_ptr<ViewAsSkill> view_as_skill;
    };

    /**
    * @brief ��Ѫ��
    *        �磺���ۡ��ż������ҡ����������𡢽���������������
    **/
    class MasochismSkill: public TriggerSkill{
    public:
        /**
        * @brief ���캯��
        **/
        MasochismSkill(const string &name);

        virtual int getPriority() const;
        /**
        * @brief �������
        **/
        virtual void onDamaged(boost::shared_ptr<ServerPlayer> target, const DamageStruct &damage) const = 0;
    };

    /**
    * @brief �׶�ת��ʱ�����ļ���
    *        �磺�ʵ¡�ͻϮ�����ǡ��˼������ơ�����
    **/
    class PhaseChangeSkill: public TriggerSkill{
    public:
        PhaseChangeSkill(const string &name);

        virtual bool onPhaseChange(boost::shared_ptr<ServerPlayer> target) const =0;
    };
    /**
    * @brief �иı����ƽ׶����������ļ���
    *        �磺���¡�Ӣ�ˡ���ʩ��
    **/
    class DrawCardsSkill: public TriggerSkill{
    public:
        DrawCardsSkill(const string &name);

        virtual int getDrawNum(boost::shared_ptr<ServerPlayer>  player, int n) const = 0;
    };

    /**
    * @brief ɱ�ĸ�������
    *        �磺������ҹ�
    **/
    class SlashBuffSkill: public TriggerSkill{
    public:
        SlashBuffSkill(const string &name);

        virtual bool buff(const SlashEffectStruct &effect) const = 0;
    };

    /**
    * @brief ��Ϸ��ʼ�Ϳ�ʹ�õļ���
    *        �磺�Ž�����Ⱥ��ɫ��û��켼��
    **/
    class GameStartSkill: public TriggerSkill{
    public:
        GameStartSkill(const string &name);

        virtual void onGameStart(boost::shared_ptr<ServerPlayer> player) const = 0;
    };

    /**
    * @brief ���ü��ܣ���ʾӵ�и��༼�ܵ��佫���ɳ�ΪĳЩ�Ƶ�Ŀ��
    *        �磺�ճǡ�ǫѷ���Ļ��ע�ⲻ�ܳ�ΪĿ��Ϳ�Ƭ������Ч���������
    **/
    class ProhibitSkill: public Skill{
    public:
        ProhibitSkill(const string &name);

        /**
        * @brief ���˵������õ���
        **/
        virtual bool isProhibited(const boost::shared_ptr<Player> from, const boost::shared_ptr<Player>  to, const boost::shared_ptr<Card> card) const = 0;
    };

    /**
    * @brief ���뼼�ܣ�ӵ�д��༼�ܵ��佫�ڼ�������ʱ����Ҫ��������
    *        �磺�������������
    **/
    class DistanceSkill: public Skill{
    public:
        DistanceSkill(const string &name);
        /**
        * @brief ��������
        **/
        virtual int getCorrect(const boost::shared_ptr<Player> from, const boost::shared_ptr<Player> to) const = 0;
    };

    /**
    * @brief �����ļ���
    **/
    class WeaponSkill: public TriggerSkill{
    public:
        WeaponSkill(const string &name);

        virtual bool triggerable(const boost::shared_ptr<ServerPlayer> target) const;
    };

    /**
    * @brief ���ߵļ���
    **/
    class ArmorSkill: public TriggerSkill{
    public:
        ArmorSkill(const string &name);

        virtual bool triggerable(const boost::shared_ptr<ServerPlayer>target) const;
    };

    /**
    * @brief �̳���GameStartSkill ����������Ϸ��ʼ���⽮��ǣ��������裬��������޶������Ƿ�ʹ�ù�
    **/
    class MarkAssignSkill: public GameStartSkill{
    public:
        MarkAssignSkill(const string &mark, int n);

        virtual void onGameStart(ServerPlayer *player) const;

    private:
        string markName_;
        int n;
    };

};
};


#endif