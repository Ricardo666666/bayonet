/*=============================================================================
#
#     FileName: record_time.h
#         Desc: 用来减少gettimeofday的频率，在一次循环里面获取一次足够了
#
#       Author: dantezhu
#        Email: zny2008@gmail.com
#     HomePage: http://www.vimer.cn
#
#      Created: 2011-06-17 10:35:04
#      Version: 0.0.1
#      History:
#               0.0.1 | dantezhu | 2011-06-17 10:35:04 | initialization
#
=============================================================================*/

#ifndef __RECORD_TIME_H__
#define __RECORD_TIME_H__
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <sys/time.h>
using namespace std;
class CRecordTime
{
public:
    static CRecordTime * Ins()
    {
        static CRecordTime * _ins = NULL;
        if ( _ins == NULL)
            _ins = new CRecordTime();
        return _ins;
    }

    struct timeval record_time()
    {
        return deal_time(0);
    }

    struct timeval get_time()
    {
        return deal_time(1);
    }

protected:
    //0: set, 1:get
    struct timeval deal_time(int type)
    {
        static struct timeval tv;
        if (type == 0)
        {
            gettimeofday(&tv, NULL);
        }
        return tv;
    }

protected:
    CRecordTime()
    {
        static auto_ptr<CRecordTime> _auto_ptr = auto_ptr<CRecordTime>(this);
        record_time();
    }
    CRecordTime(const CRecordTime&);
    virtual ~CRecordTime(){}
    friend class auto_ptr<CRecordTime>;
};
#endif