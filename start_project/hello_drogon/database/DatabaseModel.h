#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include <functional>
#include <string>
#include <drogon/drogon.h>
using std::function;

class DatabaseModel {
public:
    static void executeSelect(
        const std::string& sqlQuery,
        std::function<void(const drogon::orm::Result&)>&& successCallback,
        std::function<void(const std::string&)>&& errorCallback
    );

    static void executeUpdate(
        const std::string& sqlQuery,
        std::function<void(size_t rowsAffected)>&& successCallback,
        std::function<void(const std::string&)>&& errorCallback
    );
};

#endif // DATABASE_MODEL_H
