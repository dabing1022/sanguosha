#ifndef __IO_HANDLER_H__
#define __IO_HANDLER_H__

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>

namespace sgs{
    namespace net{
        class Connection;

        /**
        * @brief �������״̬����
        */
        enum IdleStatus{
            /**
            * @brief ��ͨ������
            */
            READER_IDLE = 1,
            /**
            * @brief дͨ������
            */
            WRITER_IDLE = 2,
            /**
            * @brief ��дͨ��������
            */
            BOTH_IDLE = 3
        };

        /**
        * @brief AsioServer�첽�����ܵ������¼�������
        *    ʹ������Ҫ�̳и���ʵ�ָ���I/O�¼��Ĵ���
        */
        class IoHandler{
        public :
            IoHandler();

            virtual ~IoHandler();

            /**
            * @brief ���Ӵ򿪣������û�����AsioServer���ܺ�ᴥ���÷���
            *
            * @param connectionPtr
            */
            //virtual void connectionConnectTimeout(const boost::shared_ptr<Connection> connectionPtr) = 0;
            /**
            * @brief ���Ӵ򿪣������û�����AsioServer���ܺ�ᴥ���÷���
            *
            * @param connectionPtr
            */
            virtual void connectionOpened(const boost::shared_ptr<Connection> connectionPtr) = 0;

            /**
            * @brief ���ӹرգ���ִ��Connection::close()����ʱ�ᴥ���÷���
            *
            * @param connectionPtr
            */
            virtual void connectionClosed(const boost::shared_ptr<Connection> connectionPtr) = 0;

            /**
            * @brief ���ӿ��У������ӵ�I/O����ʱ�䳬����ָ����������ʱ��ᴥ���÷�����
            *    �ɹ��Ķ���д������������ӵĶ�дʱ�䡣ͨ��Connection::setMaxReadIdleTime��Connection::setMaxWriteIdleTime��������������������I/O����ʱ��
            *
            * @param connectionPtr
            * @param status ���ӵĿ���״̬��
            */
            virtual void connectionIdle(const boost::shared_ptr<Connection> connectionPtr, const IdleStatus status) = 0;

            /**
            * @brief �����ӵ��첽I/O���������쳣ʱ�ᴥ���÷��������ط������쳣�������
            *
            * @param connectionPtr
            * @param e
            */
            virtual void exceptionCaught(const boost::shared_ptr<Connection> connectionPtr, const boost::system::error_code& e) = 0;

            /**
            * @brief �����Ӵ�I/O��ȡ������ʱ�ᴥ���÷�������������Connection���յ�������
            *
            * @param connectionPtr
            * @param message ���յ�������
            */
            virtual void messageReceived(const boost::shared_ptr<Connection> connectionPtr, const std::string& message) = 0;

            /**
            * @brief �����ӵ��첽д�ɹ���ᴥ���÷�����
            *   ͨ������Connection::write�������Կ�ʼ�첽д����
            *
            * @param connectionPtr
            * @param message д�ɹ�����Ϣ����
            */
            virtual void messageSent(const boost::shared_ptr<Connection> connectionPtr, const std::string& message) = 0;

        };

    };
};

#endif 
