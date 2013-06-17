#include "Player.h"
#include <boost\foreach.hpp>
#include "MyLock.h"

using namespace sgs::utils;

namespace sgs {
    namespace core {

        Player::Player(void): phase_(PhaseNone)
        {
        }


        Player::~Player(void)
        {
        }

        void Player::setGeneral(boost::shared_ptr<General> general) {
            general_ = general;
            int hp = general->getMaxHp();
            if(getRole() == Lord) {
                hp ++;//����Ѫ+1
            }
            setHp(hp);
            setMaxHp(hp);
        }

        boost::shared_ptr<General> Player::getGeneral() {
            return general_;
        }

        int Player::getHandCardNum() {
            return handCards_.size();
        }

        //todo
        int Player::getAttackRange() {
            int range = 1;
            return range;
        }
        
        void Player::drawCards(vector<int> cardIds) {
            WriteLock lock(cardMutex_);
            BOOST_FOREACH(int id, cardIds) {
                handCards_.push_back(id);
            }
        }

        void Player::discardCards(const set<int>& discardCards) {
            WriteLock lock(cardMutex_);
            vector<int>::iterator it;
            for(it = handCards_.begin(); it != handCards_.end(); ) {
                if(discardCards.find(*it) != discardCards.end()) {
                    it = handCards_.erase(it);
                }else {
                    it++;
                }
            }
        }
        //bool Player::hasFlag(const string &flag) const {
        //    return flags_.find(flag) != flags_.end();
        //}

        /**
        * @brief ������Ϸ�����л�ȡ���ܣ����Ѽ�����������õ�
        *        ��־�̻�ù��ǣ����˻��Ӣ��Ӣ��
        **/
        void Player::acquireSkill(const string &skill_name) {
        }
        /**
        * @brief ������Ϸ������ʧȥ����
        **/
        void Player::loseSkill(const string &skill_name) {
        }
        bool Player::hasSkill(const string &skill_name) const {
            return false;
        }
        bool Player::hasInnateSkill(const string &skill_name) const {
            return false;
        }
        /**
        * @brief �ж��Ƿ���ĳ��������
        **/
        bool Player::hasLordSkill(const string &skill_name, bool include_lose) const {
            return false;
        }

        /**
        * @brief ��װ��
        **/
        void Player::setEquip(boost::shared_ptr<Card> equip) {
        
        }
        /**
        * @brief жװ��
        **/
        void Player::removeEquip(boost::shared_ptr<Card> equip) {
        }
        /**
        * @brief �Ƿ���ĳ����
        **/
        bool Player::hasEquip(const boost::shared_ptr<Card> card) const {
            return false;
        }
        /**
        * @brief �Ƿ���װ��
        **/
        bool Player::hasEquip() const {
            return false;
        }
        /**
        * @brief �Ƿ���ָ������
        **/
        bool Player::hasWeapon(const string &weapon_name) const {
            return false;
        }
        /**
        * @brief �Ƿ���Է������߼���
        **/
        bool Player::hasArmorEffect(const string &armor_name) const {
            return false;
        }

        //�ж�������
        /**
        * @brief ��ȡ�ж�����������
        **/
        vector<boost::shared_ptr<Card> > Player::getJudgingArea() const {
            return vector<boost::shared_ptr<Card> >();
        }
        /**
        * @brief �����ӳٽ���
        **/
        void Player::addDelayedTrick(const boost::shared_ptr<Card> trick) {
        }
        /**
        * @brief ȥ���ӳٽ���
        **/
        void Player::removeDelayedTrick(const boost::shared_ptr<Card> trick) {
        }
        /**
        * @brief �鿴�ж����Ƿ���ָ���ӳٽ���
        **/
        bool Player::containsTrick(const string &trick_name) const {
            return false;
        }

        //����﷽��
        /**
        * @brief ��ӱ��
        **/
        void Player::addMark(const string &mark) {
            marks_[mark]++;
        }
        /**
        * @brief ȥ�����
        **/
        void Player::removeMark(const string &mark) {
            if(marks_.find(mark) != marks_.end()) {
                marks_[mark]--;
            }
        }
        /**
        * @brief ���ñ��
        **/
        void Player::setMark(const string &mark, int value) {
            marks_[mark] = value;
        }
        /**
        * @brief ��ȡĳ���
        **/
        int Player::getMark(const string &mark) const {
            map<string, int>::const_iterator it = marks_.find(mark);
            if(it != marks_.end()) {
                return it->second;
            }
            return 0;
        }
        /**
        * @brief ��ȡ�����ƶѵ��ƣ������ǡ��������
        **/
        vector<int> Player::getPile(const string &pile_name) const {
            return vector<int>();
        }
        //����ʹ�÷���
        /**
        * @brief �Ƿ��ù�ĳ�ƣ���Ҫ����ÿ�غ�ֻ�ܷ���һ�εļ��ܣ��жϼ����Ƿ񷢶���
        **/
        bool Player::hasUsed(const string &card_class) const {
            return false;
        }
        /**
        * @brief ���ڻغ��ڿɶ��ʹ�õ��Ǵ������Ƶļ���
        **/
        int Player::usedTimes(const string &card_class) const {
            return 0;
        }
        //����ʹ�÷���
        /**
        * @brief ��ֹ������ͨ����ʵ�ֵ�
        **/
        bool Player::isProhibited(const boost::shared_ptr<Player> to, const boost::shared_ptr<Card> card) const {
            return false;
        }

        /**
        * @brief �Ƿ����������ɱ
        **/
        bool Player::canSlashWithoutCrossbow() const {
            return false;
        }

        bool Player::isLastHandCard(const boost::shared_ptr<Card> card) const {
            return false;
        }


        bool Player::hasCanAttackTarget() {
            int attackRange = 1;
            
            map<const boost::shared_ptr<Player> , int>::const_iterator it;
            for(it = fixedDistance_.begin(); it!= fixedDistance_.end(); it++) {
                if(attackRange >= it->second) {
                    return true;
                }
            }

            return false;
        }

    };
};