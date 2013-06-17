#ifndef __MY_LOCK_H__
#define __MY_LOCK_H__
#include <boost/thread.hpp>

namespace sgs {
    namespace utils{
        /**
        * ��д��
        */
        typedef boost::shared_lock< boost::shared_mutex > ReadLock;
        typedef boost::unique_lock< boost::shared_mutex > WriteLock;

        /**
        * ������
        */
        typedef boost::mutex::scoped_lock ScopedLock;
    };
};
#endif //TALK_UTILS_MY_LOCK_H_