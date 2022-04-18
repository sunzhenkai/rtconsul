#ifndef RTCFG_CONTAINER_H
#define RTCFG_CONTAINER_H

#include "mutex"
#include "condition_variable"
#include "deque"

namespace ctd {
    template<typename T>
    class BlockingQueue {
        int count;
        std::mutex mutex;
        std::condition_variable cv;
        std::deque<T> data;
    public:
        void Push(T const &value) {
            {
                std::unique_lock lock(mutex);
                data.push_front(value);
            }
            cv.notify_one();
        }

        T Pop() {
            std::unique_lock lock(mutex);
            cv.wait(lock, [=] { return !this->data.empty(); });
            T r(std::move(this->data.back()));
            this->data.pop_back();
            return r;
        }
    };
}

#endif //RTCFG_CONTAINER_H
