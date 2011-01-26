#ifndef _EPOLLER_H_
#define _EPOLLER_H_
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <map>
#include "socketactor_base.h"
using namespace std;

#define NET_ERRMSG_SIZE     1024
#define EPOLL_FD_MAX        10240

class CSocketActorBase;
class CEPoller
{
public:
    CEPoller();
    ~CEPoller();

    int Create(int size);
    int AttachFrame(IFrame* pFrame);
    int AddEpollIO(int fd,unsigned flag);
    int ModEpollIO(int fd,unsigned flag);
    int SetEpollIO(int fd,unsigned flag);
    int DelEpollIO(int fd);
    void AttachSocket(CSocketActorBase* sock);
    void DetachSocket(CSocketActorBase* sock);
    int  LoopForEvent(int timeout);
    char * GetErrMsg();
protected:
    char            m_szErrMsg[NET_ERRMSG_SIZE];
    int             m_epollFd;              //epoll�ľ��
    epoll_event     m_events[EPOLL_FD_MAX];  //epoll_wait�ķ��ص��¼�

    IFrame* m_pFrame;

    map<int,CSocketActorBase*> m_mapSocketActor;
};

#endif
