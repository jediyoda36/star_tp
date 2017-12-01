#include "CThreadPool.h"

CThreadPool::CThreadPool(size_t size) {
    mWork.reset(new boost::asio::io_service::work(mIoService));
    for (size_t i = 0; i < size; i++) {
        mWorkers.create_thread(boost::bind(&boost::asio::io_service::run, &mIoService));
    }
}

CThreadPool::~CThreadPool() {
    mWork.reset();
    //mIoService.stop();
    mWorkers.join_all();
}

void CThreadPool::submit(CTask* task) {
    if (task)
        mIoService.post([task]{(*task)();});
    else {
        printf("submited CTask* is null\n");
    }
}

void CThreadPool::submit(boost::function<void()> func) {
    mIoService.post(func);
}

