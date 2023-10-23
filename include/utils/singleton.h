#ifndef RTCFG_SINGLETON_H
#define RTCFG_SINGLETON_H

namespace rtcfg {
    namespace utils {
        template<typename T>
        class Singleton {
        protected:
            Singleton() noexcept = default;
            Singleton(const Singleton &) = delete;
            Singleton &operator=(const Singleton &) = delete;
            virtual ~Singleton() = default;

        public:
            static T &Instance() {
                static T instance{};
                return instance;
            }
        };
    }
}

#endif //RTCFG_SINGLETON_H
