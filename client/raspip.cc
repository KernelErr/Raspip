#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <RaspipConfig.hpp>
#include "include/HTTPRequest.hpp"

#ifdef BUPT_LOGIN
    #include "include/buptlogin.hpp"
    #define WIFIUSER    000000
    #define WIFIPASSWD  000
    #define WIFITYPE    1
#else
    #include "include/nologin.hpp"
    #define WIFIUSER    0
    #define WIFIPASSWD  0
    #define WIFITYPE    0
#endif

std::string remoteServer = "http://127.0.0.1:3000/";

struct NoLocalIPException : public std::exception
{
  const char * what () const throw ()
  {
    return "Can't fetch local IP";
  }
};

std::string getLocalIP()
{
    std::string localIP = "";
    const char *remote_server = "1.1.1.1";
    int dns_port = 53;
    struct sockaddr_in serv;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cout << "Socket error" << std::endl;
    }
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(remote_server);
    serv.sin_port = htons(dns_port);
    int err = connect(sock, (const struct sockaddr *)&serv, sizeof(serv));
    if (err < 0)
    {
        std::cout << "Error number: " << errno
                  << ". Error message: " << strerror(errno) << std::endl;
    }
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr *)&name, &namelen);
    char buffer[80];
    const char *p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
    if (p != NULL)
    {
        localIP = buffer;
    }
    else
    {
        localIP = "E";
    }
    close(sock);
    return localIP;
}

int main()
{
    bool loggedIn = false;
    int checkInterval = 5;
    int sendInterval = 60*5;
    while (1)
    {
        try
        {
            std::string localIP = getLocalIP();
            if(localIP == "E"){
                throw NoLocalIPException();
            }
            http::Request request(remoteServer);
            const http::Response response = request.send("POST", localIP, {"Content-Type: text/plain"});
            if (std::string(response.body.begin(), response.body.end()) == "Gotcha")
            {
                std::cout<<"Successfully sent. Next operation would be " + std::to_string(sendInterval) + " seconds later." << std::endl;
                sleep(sendInterval);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Request failed, error: " << e.what() << ". Waiting another " + std::to_string(checkInterval) + " seconds.\n";
            if(!loggedIn){
                if(WIFITYPE == 1){
                    std::cout<<"Trying to log into BUPT wifi."<<std::endl;
                    if(login(std::to_string(WIFIUSER), std::to_string(WIFIPASSWD))){
                        loggedIn = true;
                        std::cout<<"Logged into BUPT wifi."<<std::endl;
                    } else {
                        std::cerr << "Failed to log into BUPT wifi.\n";
                    }
                } else if (WIFITYPE == 0) {
                    if(login(std::to_string(WIFIUSER), std::to_string(WIFIPASSWD))){
                        loggedIn = true;
                    }
                }
            }
            sleep(checkInterval);
        }
    }
    return 0;
}