/*=============================================================================
#  Author:          dantezhu - http://www.vimer.cn
#  Email:           zny2008@gmail.com
#  FileName:        socketactor_base.h
#  Description:     socketactor的基础类
#  Version:         1.0
#  LastChange:      2011-01-24 20:23:53
#  History:         
=============================================================================*/
#ifndef _SOCKETACTOR_BASE_H_
#define _SOCKETACTOR_BASE_H_
#include "comm_def.h"
#include "fsm_achieve.h"
#include "epoller.h"
#include "fl_log.h"
#include "net_handler.h"

//=============================================================================
class CEPoller;
class CSocketActorBase:public CActorBase
{
public:
    CSocketActorBase ():m_SocketFd(-1),m_Port(0),m_TimeoutMs(-1),m_ProtoType(0) {}
    virtual ~CSocketActorBase () {}

    virtual int Init(string ip,int port,int timeout_ms,int protoType);

    virtual int Init(int socketFd,int timeout_ms,int protoType);

    int GetSocketFd();

    virtual int SetEvent(unsigned event);

    virtual int OnInit();

    virtual int OnFini();

    virtual int OnRecv();

    virtual int OnRecvOver();

    virtual int OnSend();

    virtual int OnSendOver();

    virtual int OnClose();

    virtual int OnCloseOver();

    virtual int OnTimeout();

    virtual int OnError();

protected:
    virtual CEPoller* GetEpoller();

protected:
    int m_SocketFd;

    string m_IP;
    int m_Port;
    int m_TimeoutMs;
    int m_ProtoType;

    //业务需要继承实现
public:
    virtual int CheckTimeOut(struct timeval& now_time);

protected:
    //清理
    virtual int HandleFini()
    {
        return SOCKET_FSM_ALLOVER;
    }
    // socket close完毕
    virtual int HandleCloseOver()
    {
        return SOCKET_FSM_FINI;
    }

    virtual int HandleTimeout(
            int timeout_ms)
    {
        return SOCKET_FSM_CLOSING;
    }

    virtual int HandleError(
            int err_no)
    {
        return SOCKET_FSM_CLOSING;
    }

    //初始化
    virtual int HandleInit()=0;
    // 发送包接收完毕
    virtual int HandleSendOver()=0;
    // 回应包接受完毕
    virtual int HandleRecvOver(const char *buf, int len)=0;
};

//=============================================================================
class CSocketActorData:public CSocketActorBase
{
public:
    CSocketActorData () {
        m_pNetHandler = NULL;
        m_strSingleRecvBuf.resize(1024);
        m_strRecvBuf.resize(2048);
        Clear();
    }
    virtual ~CSocketActorData () {
        if (m_pNetHandler)
        {
            delete m_pNetHandler;
            m_pNetHandler = NULL;
        }
    }

    virtual int OnRecv();

    virtual int OnSend();

    virtual int Init(string ip,int port,int timeout_ms,int protoType);
    virtual int Init(int socketFd,int timeout_ms,int protoType);

    virtual int OnInit();
    virtual int OnRecvOver();
    virtual int OnClose();

    virtual int Clear();

//业务需要继承实现
protected:
    // 为发送打包
    virtual int HandleEncode(
            string & strSendBuf,
            int &len)=0;

    // 回应包完整性检查
    virtual int HandleInput(
            const char *buf,
            int len)=0;

    //初始化
    virtual int HandleInit()=0;
    // 发送包接收完毕
    virtual int HandleSendOver()=0;
    // 回应包接受完毕
    virtual int HandleRecvOver(const char *buf, int len)=0;

protected:
    CNetHandlerBase* m_pNetHandler;

    int m_sendedLen;
    int m_sendBufLen;
    string m_strSendBuf;

    int m_recvedLen;
    string m_strRecvBuf;

    string m_strSingleRecvBuf;

    int m_sendFlag;
    int m_recvFlag;
};
//=============================================================================

#endif