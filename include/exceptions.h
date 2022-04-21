#ifndef RTCFG_EXCEPTIONS_H
#define RTCFG_EXCEPTIONS_H

#include <exception>
#include <utility>
#include "defines.h"

namespace rtcfg {
    class NetworkException : public std::exception {
    private:
        int code_;
        String message_;
    public:
        NetworkException(int code, const char *message) : code_(code), message_(message) {};

        NetworkException(int code, String message) : code_(code), message_(std::move(message)) {};

        ~NetworkException() override = default;

        const char *what() const noexcept override { return message_.c_str(); }

        int code() const { return code_; }
    };

    class ReadTimeoutException : public std::exception {
        String message_;
    public:
        explicit ReadTimeoutException(String message) : message_(MOVE(message)) {}
        const char *what() const noexcept override { return message_.c_str(); }
    };

    class RTException : public std::exception {
    private:
        String message_;
    public:
        explicit RTException(String message) : message_(std::move(message)) {
        }

        const char *what() const noexcept override {
            return message_.c_str();
        }
    };
}

#endif //RTCFG_EXCEPTIONS_H
