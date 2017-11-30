#ifndef STAR_CTHREADPOOL_H
#define STAR_CTHREADPOOL_H

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../task/Task.h"

class CThreadPool {
private:
    boost::thread_group mWorkers;
    boost::asio::io_service mIoService;
    boost::asio::io_service::work mWork;
public:
    explicit CThreadPool(size_t);
    ~CThreadPool();

    void submit(Task<void>&);

};

CThreadPool::CThreadPool(size_t size) : mWork(mIoService) {
    for (size_t i = 0; i < size; i++) {
        mWorkers.create_thread(boost::bind(&boost::asio:io_service::run, &mIoService));
    }
}

CThreadPool::~CThreadPool() {
    mIoService.stop();
    mWorkers.join_all();
}

void CThreadPool::submit(Task<void>& task) {
    mIoService.post(task);
}


#endif // STAR_CTHREADPOOL_H

