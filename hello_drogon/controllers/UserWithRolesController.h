#pragma once
#include <drogon/HttpController.h>

class UserWithRolesController : public drogon::HttpController<UserWithRolesController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserWithRolesController::getUsersWithRoles, "/users_roles", drogon::Get);
    ADD_METHOD_TO(UserWithRolesController::addUserWithORM, "/users_roles/add", drogon::Post);
    METHOD_LIST_END

    void getUsersWithRoles(
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback
    );

    void addUserWithORM(
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback
    );
};

