#ifndef STAR_CTHREADPOOL_H
#define STAR_CTHREADPOOL_H

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "CTask.h"

class CThreadPool {
private:
    boost::thread_group mWorkers;
    boost::asio::io_service mIoService;
    boost::shared_ptr<boost::asio::io_service::work> mWork;
public:
    explicit CThreadPool(size_t);
    ~CThreadPool();

    void submit(CTask*);
    void submit(boost::function<void()>);

};

#endif // STAR_CTHREADPOOL_H

