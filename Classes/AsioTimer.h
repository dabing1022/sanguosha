#ifndef  __TIMER_H__
#define  __TIMER_H__
#include  <boost/asio.hpp>
#include  <boost/shared_ptr.hpp>
#include  <boost/date_time/posix_time/posix_time.hpp>
#include  <boost/bind.hpp>
#include  <boost/function.hpp>
#include  <map>
#include  <vector>
#include <iostream>
#include <stdio.h>
#include  <boost/thread.hpp>

namespace sgs {
    namespace utils {

        typedef int taskHandle; 
        typedef boost::shared_ptr<boost::asio::deadline_timer>  TimerPtr;


        struct TaskContext{
            taskHandle index_;    /*����ID*/
            boost::function<void()>func_; /*��ʱ��������������*/
            TimerPtr timerPtr_;    /*deadline_timerָ��*/
            int deadline_time ;    /*�ӳ�ʱ��*/
            boost::asio::strand strand_;    /*��֤ͬһ����ֻ��һ��handler������*/
            int mode ;//1��ʾ�ظ���0��ʾһ��
            TaskContext(boost::asio::io_service& ios):strand_(ios){}
        };

        typedef boost::shared_ptr<TaskContext> TaskContextPtr;



        class Timer {

        public:
            /*
            * ��ʱ�����캯������¼�߳�������ʼ������ID��ֵ����ʼ��strand����
            */
            Timer(int threadCount):taskIndex_(0),threadCount_(threadCount){}

            /*
            addTask ��ʱ�����һ��һ���Ե����񣬴���ʱ��Ϊdeadline_time���;
            return  ����������
            */
            taskHandle  addTask(boost::function<void ()> func, int deadline_time);

            /*
            addTask ��ʱ�����һ���ظ��Ե����񣬴���ʱ��Ϊÿdeadline_time���;
            */
            taskHandle  addScheduleRepeatedTask(boost::function<void ()> func, int deadline_time);

            /*
            delTask ȡ����ʱ����;
            */
            bool delTask(taskHandle);

             /*
            delTask ȡ����ʱ����;
            */
            bool cleanAllTask();

            /*
            * start ������Ϊ�� startThreads ����д
            * ����threadCount_���̣߳���io_service��run�����������С�
            * ע��˵��ý����������̣߳���Ҫ���������߳̽��е���
            * */

            void start();

        private:

            /*������ӽӿ������õ��ڲ������������������������������ӳ�ʱ���Լ��Ƿ���Ҫ�ظ�����*/

            taskHandle  interAdd(boost::function<void ()> func, int deadline_time, int mode);

            /*deadline_timer���첽����async_wait�Ĳ����б��в���bind�Ĳ����б�����Ϊ�����Ļص�������������Իص����ɹ�����ķ�֧�����߼�*/

            void  run(TaskContextPtr taskContextPtr, const boost::system::error_code& e);

            /* �������ж�ʱ�����map���� */
            std::map<taskHandle, TaskContextPtr>  taskContextPtrMap;

            /*io_service �� strand ������˳�������ios���ϡ�strand���£���Ϊstrand��ʼ����Ҫ����ios*/

            boost::asio::io_service ios_; /*deadline_timer��������io_service*/


            /*�ڲ��Զ�ʱ������б�ʶ�ļ�����*/

            int taskIndex_;     

            /*��interadd�ڲ�����ʹ�õ�ȷ���Խ��̷���һ���ԵĻ�����*/

            boost::mutex scoped_mutex_;

            /*����io_service��run�������̸߳���*/

            int threadCount_;

        };

    }
}
#endif 




















