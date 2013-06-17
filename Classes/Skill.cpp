#include "Skill.h"

namespace sgs {
    namespace core {

        CCDictionary* Skill::SKILL_STRINGS = NULL;//CCDictionary::createWithContentsOfFileThreadSafe("strings/skills.xml");;
        
        string Skill::getSkillString(const string& key) const {
            if(!SKILL_STRINGS) {
                SKILL_STRINGS = CCDictionary::createWithContentsOfFileThreadSafe("strings/skills.xml");
            }
            CCString* description = ((CCString*)(SKILL_STRINGS->objectForKey(key)));
            return description->m_sString;
        }

        Skill::Skill(const string &name, Frequency frequent): name_(name), frequency_(frequent)
        {
        }


        Skill::~Skill(void)
        {
        }
        //TODO
        /**
        * @brief ��ȡ��������
        **/
        string Skill::getDescription() const {
            const string key = getName()+ "_description";
            return getSkillString(key);
        }
        /**
        * @brief �޶����������������Ѽ�ǰ����С�xx������������������������õ�
        **/
        string Skill::getText() const {
            return "";//((CCString*)(skillStrings->objectForKey(getName()+ "_text")))->m_sString;
        }

        
        string Skill::getChineseName() const {
            string key = getName()+ "_chinese";
            return getSkillString(key);
        }
        /**
        * @brief ��ȡĬ��ѡ�����Ӧ�������г���ʱ�޵�����£�����һЩ��Ҫѡ�񷢶��ļ��ܣ�������û��ѡ��ϵͳ�Զ����ǻ�Ĭ��ѡ�
        *   �維׿�ı���(����>=Ѫ��+2�͵����ߣ������Ѫ��
        **/
        string Skill::getDefaultChoice(boost::shared_ptr<ServerPlayer> player) const {
            return "";
        }
        /**
        * @brief ���ӱ��
        **/
        void Skill::setFlag(boost::shared_ptr<ServerPlayer> player) const {

        }
        /**
        * @brief ���ٱ��
        **/
        void Skill::unsetFlag(boost::shared_ptr<ServerPlayer> player) const {
        }

        ViewAsSkill::ViewAsSkill(const string &name):Skill(name) {

        }
       
        /**
        * @brief �����жϼ����Ƿ����ʹ�ã��������false, ���ܰ�ť������
        * @return bool
        **/
        bool ViewAsSkill::isAvailable(CardUseStruct::CardUseReason reason, const string &pattern) const {
            return false;
        }
        /**
        * @brief �жϼ����Ƿ�����ڳ��ƽ׶��������¼��������������Ƿ���Է���
        *        ����û���ж���ʱ��˾��Ĺ���Ǳ����õ�
        **/
         bool ViewAsSkill::isEnabledAtPlay(const boost::shared_ptr<Player> player) const {
            return false;
         }
        /**
        * @brief һЩ����ֻ�����ض������²��ܱ�����
        *        ���类ɱʱ�������������ʹ�ý���ʱ�Ŀ��ơ�
        *        ��Щ�����ɲ���pattern����������������ʱ����Щ���ܻᱻ����
        **/
         bool ViewAsSkill::isEnabledAtResponse(const boost::shared_ptr<Player> player, const string &pattern) const {
            return false;
         }
        //virtual bool isEnabledAtNullification(const boost::shared_ptr<ServerPlayer> player) const;

        const ViewAsSkill* ViewAsSkill::parseViewAsSkill(const Skill* skill) {
            return NULL;
        }

        /**
        * @brief ���ڷ�������ʱ���˵�����ʹ�õĿ���
        *        ���������˵�װ���ƺͺ�ɫ���ơ����һ���˵���ɫװ������
        **/
        bool ZeroCardViewAsSkill::viewFilter(const vector<const boost::shared_ptr<Card> > &selected, const boost::shared_ptr<Card> to_select) const {
            return false;
        }
        /**
        * @brief �����ڷ�������ʱ��������ת����Ŀ���
        *        ���������Ϊ��
        **/
        const boost::shared_ptr<Card> ZeroCardViewAsSkill::viewAs(const vector<const boost::shared_ptr<Card> > &cards) const {
            return boost::shared_ptr<Card>();
        }

        /**
        * @brief ���ڷ�������ʱ���˵�����ʹ�õĿ���
        *        ���������˵�װ���ƺͺ�ɫ���ơ����һ���˵���ɫװ������
        **/
        bool OneCardViewAsSkill::viewFilter(const vector<const boost::shared_ptr<Card> > &selected, const boost::shared_ptr<Card> to_select) const {
            return false;
        }
        /**
        * @brief �����ڷ�������ʱ��������ת����Ŀ���
        *        ���������Ϊ��
        **/
        const boost::shared_ptr<Card> OneCardViewAsSkill::viewAs(const vector<const Card *> &cards) const {
            return boost::shared_ptr<Card>();
        }

        TriggerSkill::TriggerSkill(const string &name):Skill(name) {
        }
        const boost::shared_ptr<ViewAsSkill> TriggerSkill::getViewAsSkill() const {
            return boost::shared_ptr<ViewAsSkill>();
        }
        
        /**
        * @brief ��ȡʱ�����ȼ�
        **/
        int TriggerSkill::getPriority() const {
            return 0;
        }
        bool TriggerSkill::triggerable(const boost::shared_ptr<ServerPlayer> target) const {
            return false;
        }

       

        int MasochismSkill::getPriority() const {
            return 0;
        }

        ProhibitSkill::ProhibitSkill(const string &name):Skill(name) {
        }

        DistanceSkill::DistanceSkill(const string &name):Skill(name) {
        }


        bool WeaponSkill::triggerable(const boost::shared_ptr<ServerPlayer> target) const {
            return false;
        }

        bool ArmorSkill::triggerable(const boost::shared_ptr<ServerPlayer>target) const {
            return false;
        }

        void MarkAssignSkill::onGameStart(ServerPlayer *player) const {
        }
    };
};