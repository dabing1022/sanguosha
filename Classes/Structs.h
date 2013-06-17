#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <string>
#include <boost\smart_ptr.hpp>
namespace sgs {
namespace server {
    class Room;
    class ServerPlayer;
}
}
namespace sgs {
namespace core {
    class Card;
}
}
#include "ServerPlayer.h"

using namespace std;

using namespace sgs::core;

using namespace sgs::server;

namespace sgs {
namespace core {

    /**
    * @brief �˺��ṹ��
    **/
    struct DamageStruct{
        DamageStruct();

        enum Nature{
            Normal, // normal slash, duel and most damage caused by skill
            Fire,  // fire slash, fire attack and few damage skill (Yeyan, etc)
            Thunder // lightning, thunder slash, and few damage skill (Leiji, etc)
        };
        //�˺���Դ
        boost::shared_ptr<ServerPlayer> from;
        //�˺�����
        boost::shared_ptr<ServerPlayer> to;
        //����˺��Ŀ���
        const boost::shared_ptr<Card> card;
        //�˺�����
        int damage;
        //�˺�����
        Nature nature;
        //�Ƿ�Ϊ�������������˺�
        bool chain;
        bool transfer;
        bool trigger_chain;
    };
    /**
    * @brief ɱ�Ľṹ��
    **/
    struct SlashEffectStruct{
        SlashEffectStruct();
        //ʹ�õ�ɱ
        const boost::shared_ptr<Card> slash;
        //��������ɱ�õ���
        const boost::shared_ptr<Card> jink;
        //ɱ��ʹ����
        boost::shared_ptr<ServerPlayer> from;
        //ɱ��Ŀ��
        boost::shared_ptr<ServerPlayer> to;
        //�Ƿ�Ⱦ�
        bool drank;
        //ɱ������
        DamageStruct::Nature nature;
    };

    /**
    * @brief �����ṹ��
    **/
    struct DyingStruct{
        DyingStruct();
        //���������
        boost::shared_ptr<ServerPlayer> who; // who is ask for help
        //���Ϊ�գ���Ϊ������ʧ��ɵ�����
        boost::shared_ptr<DamageStruct> damage; // if it is NULL that means the dying is caused by losing hp
    };
    /**
    * @brief �ظ��ṹ��
    **/
    struct RecoverStruct{
        RecoverStruct();
        //�ظ�����
        int recover;
        //�ظ����ö���
        boost::shared_ptr<ServerPlayer> who;
        //�����ظ�Ч���Ŀ���
        const boost::shared_ptr<Card> card;
    };

     /**
    * @brief ƴ��ṹ��
    **/
    struct PindianStruct{
        PindianStruct();
        /**
        * @brief �Ƿ�ɹ�
        **/
        bool isSuccess() const;
        //ƴ�㷢����
        boost::shared_ptr<ServerPlayer> from;
        //ƴ����Ӧ��
        boost::shared_ptr<ServerPlayer> to;
        //ƴ�㷢���߿���
        const boost::shared_ptr<Card> from_card;
        //ƴ����Ӧ�߿���
        const boost::shared_ptr<Card> to_card;
        //ԭ��
        string reason;
    };

    /**
    * @breif ����Ч���ṹ��
    **/
    struct CardEffectStruct{
        CardEffectStruct();
        //����ָ��
        const boost::shared_ptr<Card> card;
        //����ʹ����
        boost::shared_ptr<ServerPlayer> from;
        //����ʹ��Ŀ��
        boost::shared_ptr<ServerPlayer> to;
        //����Ŀ���Ƿ�Ψһ
        bool multiple;
    };

    
    /**
    * @breif ����ʹ�ýṹ��
    **/
    struct CardUseStruct{
        enum CardUseReason
        {
            CARD_USE_REASON_UNKNOWN,
            CARD_USE_REASON_PLAY,
            CARD_USE_REASON_RESPONSE
        };

        CardUseStruct();
        //�жϿ����Ƿ�Ϸ�
        bool isValid(CardUseReason reason, const string &pattern) const;
        //ͨ��string���ݸ�CardUseStruct��ֵ
        void parse(const string &str, Room *room);
        //����ָ��
        const boost::shared_ptr<Card> card;
        //����ʹ����
        boost::shared_ptr<ServerPlayer> from;
        //����Ŀ��
        vector<boost::shared_ptr<ServerPlayer> > to;
    };

    /**
    * @brief �ж��ṹ��ģʽ
    **/
    class JudgeStructPattern{
    private:
        string pattern;
        bool isRegex;

    public:
        JudgeStructPattern();
        //JudgeStructPattern &operator=(const QRegExp &rx);
        //JudgeStructPattern &operator=(const QString &str);
        bool match(const Player *player, const boost::shared_ptr<Card> card) const;
    };

    /**
    * @brief �ж��ṹ��
    **/
    struct JudgeStruct{
        JudgeStruct();
        /**
        * @brief �ж��ṹ��
        **/
        bool isGood() const;
        bool isGood(const boost::shared_ptr<Card> card) const;
        void updateResult();
        bool isEffected();
        bool isBad() const;

        bool negative;
        bool play_animation;
        //�����ж������
        boost::shared_ptr<ServerPlayer> who;
        //�ж���
        const boost::shared_ptr<Card> card;
        JudgeStructPattern pattern;
        //����Ƿ�����
        bool good;
        //�ж�ԭ��
        string reason;
        bool time_consuming;
    private:
        enum TrialResult
        {
            TRIAL_RESULT_UNKNOWN,
            TRIAL_RESULT_GOOD,
            TRIAL_RESULT_BAD
        } _m_result;
    };


};
};
#endif