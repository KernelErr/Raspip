#include <iostream>
#include "HTTPRequest.hpp"

std::string getSession()
{
    std::string sessionID = "E";
    try
    {
        http::Request firstRequest("http://inf.link/?cmd=redirect&arubalp=12345");
        const http::Response firstResponse = firstRequest.send("GET");
        int keywordLoc = 0;
        for (; keywordLoc < firstResponse.headers.size(); keywordLoc++)
        {
            if (firstResponse.headers[keywordLoc].find("Location") != std::string::npos)
            {
                break;
            }
        }
        std::string redirectURL = firstResponse.headers[keywordLoc].substr(10);

        http::Request secondRequest(redirectURL);
        const http::Response secondResponse = secondRequest.send("GET");
        for (keywordLoc = 0; keywordLoc < secondResponse.headers.size(); keywordLoc++)
        {
            if (secondResponse.headers[keywordLoc].find("Set-Cookie") != std::string::npos)
            {
                break;
            }
        }
        sessionID = secondResponse.headers[keywordLoc].substr(12, 27);
        return sessionID;
    }
    catch (const std::exception &e)
    {
        return "E";
    }
    return sessionID;
}

bool login(std::string username, std::string password)
{
    try
    {
        http::Request request("http://10.3.8.216/login");
        std::map<std::string, std::string> parameters = {{"user", username}, {"pass", password}};
        std::string sessionID = getSession();
        if (sessionID == "E")
        {
            return false;
        }
        const http::Response response = request.send("POST", parameters, {"User-Agent: curl/7.58.0", "Accept: */*", "Content-Type: application/x-www-form-urlencoded", "Coookie: " + sessionID});
        if (std::string(response.body.begin(), response.body.end()).find("0x0") != std::string::npos)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    catch (const std::exception &e)
    {
        return false;
    }
    return false;
}