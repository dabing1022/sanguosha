#ifndef __STANDARD_H__
#define __STANDARD_H__

#include <string>
#include <boost\enable_shared_from_this.hpp>

namespace sgs {
namespace server {
    class Room;
}
}
#include "Package.h"
#include "Card.h"
#include "Structs.h"
#include "Skill.h"

using namespace std;
using namespace sgs::core;
using namespace sgs::server;

namespace sgs {
namespace package {

    class StandardPackage : public Package{
    public:
        StandardPackage();
        virtual bool init();
        virtual void addGenerals();
        virtual void addCards();
    protected:
        map<string, const boost::shared_ptr<CardPattern> > patterns;
    };

    //������
    class BasicCard : public Card {
    public:
        BasicCard(Suit suit, int number):Card(suit, number){}
        virtual string getType() const;
        virtual CardType getTypeId() const;
    };

    //ɱ
    class Slash: public BasicCard{
    public:
        Slash(Card::Suit suit, int number);
        DamageStruct::Nature getNature() const;
        void setNature(DamageStruct::Nature nature);

        virtual string getSubtype() const;
        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;
        virtual void onEffect(const CardEffectStruct &effect) const;

        virtual bool targetsFeasible(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> Self) const;
        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;

        static bool IsAvailable(const boost::shared_ptr<Player> player);

    protected:
        DamageStruct::Nature nature;
    };
    /*
    //���ҿ�
    class TrickCard:public Card {
    public:
        TrickCard(Suit suit, int number, bool aggressive);
        bool isAggressive() const;
        void setCancelable(bool cancelable);

        virtual string getType() const;
        virtual CardType getTypeId() const;
        virtual bool isCancelable(const CardEffectStruct &effect) const;

    private:
        //�����Ե�
        bool aggressive;
        //��ȡ����
        bool cancelable;
    };

    //װ��
    class EquipCard : public Card{
    public:
        enum Location {
            WeaponLocation = 0,
            ArmorLocation = 1,
            DefensiveHorseLocation = 2,
            OffensiveHorseLocation = 3
        };

        EquipCard(Suit suit, int number):Card(suit, number, true) {}
        boost::shared_ptr<TriggerSkill> getSkill() const;

        virtual string getType() const;
        virtual CardType getTypeId() const;

        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;

        virtual void onInstall(boost::shared_ptr<ServerPlayer> player) const;
        virtual void onUninstall(boost::shared_ptr<ServerPlayer> player) const;

        virtual Location location() const = 0;
        virtual string label() const = 0;

    protected:
        boost::shared_ptr<TriggerSkill> skill;
    };

    //����
    class Weapon:public EquipCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(EquipCard)
        Weapon(Suit suit, int number, int range);
        int getRange() const;

        virtual string getSubtype() const;

        virtual Location location() const;
        virtual string label() const;
        virtual string getCommonEffectName() const;

    protected:
        int range;
    };

    //����
    class Armor : public EquipCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(EquipCard)
        Armor(Suit suit, int number):EquipCard(suit, number), name_("Armor"){}
        virtual string getSubtype() const;

        virtual Location location() const;
        virtual string label() const;
        virtual string getCommonEffectName() const;
    };
    //��
    class Horse:public EquipCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(EquipCard)
        Horse(Suit suit, int number, int correct);
        int getCorrect() const;

        virtual Location location() const;
        virtual void onInstall(boost::shared_ptr<ServerPlayer> player) const;
        virtual void onUninstall(boost::shared_ptr<ServerPlayer> player) const;

        virtual string label() const;
        virtual string getCommonEffectName() const;

    private:
        int correct;
    };
    //������
    class OffensiveHorse: public Horse{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(Horse)
        OffensiveHorse(Card::Suit suit, int number, int correct = -1);
        virtual string getSubtype() const;
    };
    //������
    class DefensiveHorse: public Horse{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(Horse)
        DefensiveHorse(Card::Suit suit, int number, int correct = +1);
        virtual string getSubtype() const;
    };
    //ȫ��Ч��
    class GlobalEffect:public TrickCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(TrickCard)
        GlobalEffect(Card::Suit suit, int number):TrickCard(suit, number, false), name_("GlobalEffect"){ targetFixed_ = true;}
        virtual string getSubtype() const;
        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
    };
    //��԰����
    class GodSalvation:public GlobalEffect{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(GlobalEffect)
        GodSalvation(Card::Suit suit = Heart, int number = 1);
        virtual bool isCancelable(const CardEffectStruct &effect) const;
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //��ȷ��
    class AmazingGrace:public GlobalEffect{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(GlobalEffect)
        AmazingGrace(Card::Suit suit, int number);
        virtual void doPreAction(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &) const;
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //Ⱥ������
    class AOE:public TrickCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(TrickCard)
        AOE(Suit suit, int number):TrickCard(suit, number, true), name_("AOE"){ targetFixed_ = true;}
        virtual string getSubtype() const;
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;
        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
    };
    //��������
    class SavageAssault:public AOE{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(AOE)
        SavageAssault(Card::Suit suit, int number);
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //����뷢
    class ArcheryAttack:public AOE{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(AOE)
        ArcheryAttack(Card::Suit suit = Heart, int number = 1);
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //���������
    class SingleTargetTrick: public TrickCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(TrickCard)
        SingleTargetTrick(Suit suit, int number, bool aggressive):TrickCard(suit, number, aggressive){}
        virtual string getSubtype() const;

        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;
    };
    //�赶ɱ��
    class Collateral:public SingleTargetTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(SingleTargetTrick)
        Collateral(Card::Suit suit, int number);
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;
        virtual bool targetsFeasible(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> Self) const;
        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
        virtual void onEffect(const CardEffectStruct &effect) const;

    private:
        bool doCollateral(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> killer, boost::shared_ptr<ServerPlayer> victim, const string &prompt) const;
    };
    //��������
    class ExNihilo: public SingleTargetTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(SingleTargetTrick)
        ExNihilo(Card::Suit suit, int number);
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //����
    class Duel:public SingleTargetTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(SingleTargetTrick)
        Duel(Card::Suit suit, int number);
        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //��ʱ�Խ���
    class DelayedTrick:public TrickCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(TrickCard)
        DelayedTrick(Suit suit, int number, bool movable = false);
        virtual void onNullified(boost::shared_ptr<ServerPlayer> target) const;

        virtual void onUse(boost::shared_ptr<Room> room, const CardUseStruct &card_use) const;
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;
        virtual string getSubtype() const;
        virtual void onEffect(const CardEffectStruct &effect) const;
        virtual void takeEffect(boost::shared_ptr<ServerPlayer> target) const = 0;
        virtual bool isNDTrick() const;
    protected:
        JudgeStruct judge;

    private:
        bool movable;
    };
    //�ֲ�˼��
    class Indulgence:public DelayedTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(DelayedTrick)
        Indulgence(Card::Suit suit, int number);

        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual void takeEffect(boost::shared_ptr<ServerPlayer> target) const;
    };
    //����
    class Disaster: public DelayedTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(DelayedTrick)
        Disaster(Card::Suit suit, int number);

        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;
    };
    //����
    class Lightning: public Disaster{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(Disaster)
        Lightning(Card::Suit suit, int number);
        virtual void takeEffect(boost::shared_ptr<ServerPlayer> target) const;
    };
    //��и�ɻ�
    class Nullification:public SingleTargetTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(SingleTargetTrick)
        Nullification(Card::Suit suit, int number);

        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;
    };
    
    // cards of standard package
    
    //��
    class Jink: public BasicCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(BasicCard)
        Jink(Card::Suit suit, int number);
        virtual string getSubtype() const;
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;
    };
    //��
    class Peach: public BasicCard{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(BasicCard)
        Peach(Card::Suit suit, int number);
        virtual string getSubtype() const;
        virtual void use(boost::shared_ptr<Room> room, boost::shared_ptr<ServerPlayer> source, vector<boost::shared_ptr<ServerPlayer> > &targets) const;
        virtual void onEffect(const CardEffectStruct &effect) const;
        virtual bool isAvailable(const boost::shared_ptr<Player> player) const;
    };
    //˳��ǣ��
    class Snatch:public SingleTargetTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(SingleTargetTrick)
        Snatch(Card::Suit suit, int number);

        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    //���Ӳ���
    class Dismantlement: public SingleTargetTrick{
    public:
        IS_KIND_OF_DECLARE_FOR_ONE_PARENT(SingleTargetTrick)
        Dismantlement(Card::Suit suit, int number);

        virtual bool targetFilter(const vector<const boost::shared_ptr<Player> > &targets, const boost::shared_ptr<Player> to_select, const boost::shared_ptr<Player> Self) const;
        virtual void onEffect(const CardEffectStruct &effect) const;
    };
    */
};
};

#endif
