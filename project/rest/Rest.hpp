#ifndef REST_HPP
#define REST_HPP

#include <string>
#include <map>
#include "../src/http/AHttpRequest.hpp"

class Rest {
public:
    typedef std::map<std::string, std::string> Headers;

    Rest();
    explicit Rest(const std::string& dir);

    void setStorageDir(const std::string& dir);

    std::string get (AHttpRequest& req, int status);
    std::string post(AHttpRequest& req, int status);
    std::string del (AHttpRequest& req, int status, const std::string& filename);

protected:
    virtual std::string formResponse(AHttpRequest& req,
                                     int status,
                                     const std::string& body,
                                     Headers headers);

private:
    std::string storageDir;

    static const char* reasonPhrase(int code);
    static std::string currentTime();
    static std::string safeHeader(AHttpRequest& req, HeaderKey key);
    static std::string safeHttpVersion(AHttpRequest& req);
    static std::string generateTxtName();
};

#endif