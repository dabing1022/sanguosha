#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <string>
#include <queue>
#include <map>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "IoHandler.h"
#include "AsioPtr.h"
#include "MyLock.h"

namespace sgs {
    namespace net {

        class ConnectionManager;

        struct WriteJob{
            std::string message;
        };

        class Connection : public boost::enable_shared_from_this<Connection>{
        public :
            Connection(int cid, IoServicePtr ioServicePtr, boost::shared_ptr<IoHandler> ioHandlerPtr, boost::shared_ptr<ConnectionManager> connectionManagerPtr);

            ~Connection();

            //void connect(std::string ip, short port);

            void open();

            /**
            * @brief �ر�һ��Conncetion
            *   �ر���ɺ�����IoHandler::connectionClosed����
            *   ����ȷ���Ƿ�������ConnectionManager��ɾ�������ӣ�Ĭ��Ϊ�Զ�ɾ��
            *
            * @param delFromManager
            */
            void close(bool delFromManager = true);

            /**
            * @brief ��ȡ���ӵ�ΨһId����ͨ����AsioServer������id����ȡ��ƫ������id
            *
            * @return 
            */
            int getId();

            /**
            * @brief ��ȡIoHandler
            *
            * @return 
            */
            boost::shared_ptr<IoHandler> getIoHandler();

            /**
            * @brief ִ���첽��ȡ
            *   ��ȡ�ɹ����ص�IoHandler::messageReceived����
            *   �������ܿ��ǣ��÷��������̰߳�ȫ��
            *   ��ֹ���ֶ��߳�ͬʱ���ø÷�����
            */
            void read();

            /**
            * @brief ִ���첽д
            *   ��ȡ�ɹ����ص�IoHandler::messageSent����
            *   �������ܿ��ǣ��÷��������̰߳�ȫ��
            *   ��ֹ���ֶ��߳�ͬʱ���ø÷�����
            *
            * @param message
            *
            * @return 
            */
            bool write(const std::string& message);

            /**
            * @brief ��ȡ���ӵĿͻ���ip��ַ
            *
            * @return 
            */
            std::string getRemoteAddress();

            /**
            * @brief ���һ�ζ���д�ɹ���ʱ��
            *
            * @return 
            */
            time_t getLastIoTime();

            /**
            * @brief ���һ�ζ��ɹ���ʱ��
            *
            * @return 
            */
            time_t getLastReadTime();

            /**
            * @brief ���һ��д�ɹ���ʱ��
            *
            * @return 
            */
            time_t getLastWriteTime();

            /**
            * @brief �������ԣ����ڱ���Ự��صı���
            *
            * @param key
            * @param value
            */
            void setAttribute(const std::string& key, const std::string& value);

            /**
            * @brief ����ֻ��key������
            *
            * @param key
            */
            void setAttribute(const std::string& key);

            /**
            * @brief �ж��Ƿ����ָ��������
            *
            * @param key
            *
            * @return 
            */
            bool containsAttribute( const std::string& key);

            /**
            * @brief ��ȡָ�����ԣ�������Բ����ڣ����ؿ��ַ���
            *
            * @param key
            *
            * @return 
            */
            std::string getAttribute(const std::string& key);

            /**
            * @brief �Ƴ�ָ������
            *
            * @param key
            *
            * @return 
            */
            std::string removeAttribute(const std::string& key);

            /**
            * @brief ��������ȡ��ʱʱ�䣬��λ��
            *
            * @param time
            */
            void setMaxReadIdleTime(int time);

            /**
            * @brief �������д��ʱʱ�䣬��λ��
            *
            * @param time
            */
            void setMaxWriteIdleTime(int time);

            boost::asio::ip::tcp::socket& getSocket();

            /**
            * @brief ���������Ƿ�������״̬
            *
            * @return 
            */
            bool isConnected();
        private :

            void handleRead(const boost::system::error_code& e,
                size_t bytes_transferred);

            void handleWrite(const boost::system::error_code& e ,  size_t  len , int i);

            bool asyncWrite(const std::string& message);

            void resetTimer();

            void handleTimer(const IdleStatus idleStatus, const boost::system::error_code& e);

            int id_;

            time_t lastReadTime_;
            time_t lastWriteTime_;

            int maxReadIdleTime_;
            int maxWriteIdleTime_;

            /**
            * @brief ��ȡ���ݵĴ���,ʧ�ܵĶ�ȡͬ��������
            */
            long readMessages_;

            /**
            * @brief д���ݵĴ���,ʧ�ܵ�д��ͬ��������
            */
            long writtenMessages_;

            bool isReading_;
            bool isWriting_;

            bool isConnected_;

            bool isTimerStarted_;

            boost::asio::ip::tcp::socket socket_;

            boost::asio::deadline_timer timer_;

            boost::array<char, 8192> buffer_;

            boost::shared_ptr<IoHandler> ioHandlerPtr_;
            
            boost::shared_ptr<ConnectionManager> connectionManagerPtr_;
            /**
            * @brief ����attribute�е���key�ı��棬��Ϊһ���̶���value
            */
            static const std::string ATTRIBUTE_VALUE;

            std::map<std::string, std::string> attributes_;

            std::queue<std::string> writeJobQueue_;

            boost::mutex writeJobQueueMutex_;
            boost::mutex writeMutex_;

            std::string remoteAddress_;
        };

        typedef boost::shared_ptr<Connection> ConnectionPtr;
}
}
#endif