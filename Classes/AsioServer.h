#ifndef __ASIO_SERVER_H__
#define __ASIO_SERVER_H__

#include <string>
#include <map>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include "MyLock.h"
#include "IoServicePool.h"
#include "ConnectionManager.h"

namespace sgs {
    namespace net {

        class Connection;
        typedef boost::shared_ptr<Connection> ConnectionPtr;

        class IoHandler;
        class UdpIoHandler;
        /**
        * @brief �첽������Server.ʹ��ʱ
        * ��Ҫ���ü����˿ںź������¼��Ĵ�����IoHandler
        * ����bind������ʼ�����˿�
        *
        **/
        class AsioServer: public boost::enable_shared_from_this<AsioServer> {
        public:
            AsioServer(void);
            ~AsioServer(void);
            /**
            * @brief ��ʼ��server, ��ʼ��handler��������Լ̳�
            *
            * @param port
            */
            void setPort(const short port);

            /**
            * @brief ���������¼��Ĵ�������
            *
            * @param ioHandlerPtr
            */
            void setIoHandler(boost::shared_ptr<IoHandler> ioHandlerPtr);

            /**
            * @brief ���������˿ڣ���������
            */
            void bind();

            /**
            * @brief ��ָ���˿����������񲢼���
            *
            * @param port
            */
            void bind(const short port);

            void unbind();

            /**
            * @brief ��һ�����ӷ������ӳ���holding
            *
            * @param connectionPtr
            */
            void addConnection(ConnectionPtr connectionPtr);

            /**
            * @brief �����ӳ���ɾ��ָ��id������
            *
            * @param connectionId
            */
            void delConnection(long connectionId);

            /**
            * @brief ��ȡһ��Connection����
            *   ��connectionId������ʱ����һ���յ�����ָ�롣
            *
            * @param connectionId
            *
            * @return 
            */
            ConnectionPtr getConnection(long connectionId);

            /**
            * @brief ��ָ����connection id����message
            *
            * @param connectionId
            * @param msg
            */
            void deliverMsg(const long connectionId, const std::string& msg);

            /**
            * @brief ������б����ŵ�Connection
            */
            void clearAllConnection();


            void startBoardcastLocalIp(const short port);
            void startBoardcastLocalIp();
            void stopBoardcastLocalIp();
            std::string getBrocastMessage() const;

        private :
            short port_;
            //�㲥�˿�
            short boardcastPort_;
            //�Ƿ�ʼ�㲥ip
            bool boardcastStarted_;
            //udpsocket
            boost::shared_ptr<boost::asio::ip::udp::socket> udpSocketPtr_;
            //timer
            sgs::utils::Timer boardcastTimer_;
            const static size_t IOSERVER_POOL_SIZE = 8;

            void handleAccept(const boost::system::error_code& e);

            ConnectionPtr newConnection();

            int generateConnectionId();

            boost::shared_ptr<IoHandler> ioHandlerPtr_;

            IoServicePool ioServicePool_;

            boost::asio::ip::tcp::acceptor acceptor_;

            ConnectionPtr newConnection_;

            int connectionCount_;

            /**
            * @brief holding���ӹ�����
            */
            boost::shared_ptr<ConnectionManager> connectionManagerPtr_;
        };

        /*
        class UdpBroadcaster {
        public:
            
        private:
            
        };
        */
    }
}
#endif
