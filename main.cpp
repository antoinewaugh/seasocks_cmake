#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>

using namespace seasocks;
using namespace std;

class MyHandler: public WebSocket::Handler {
public:
    explicit MyHandler(Server* server) : _server(server) {
    }

    virtual void onConnect(WebSocket* connection) {
        _connections.insert(connection);
        cout << "Connected: " << connection->getRequestUri()
             << " : " << formatAddress(connection->getRemoteAddress())
             << endl;
        cout << "Credentials: " << *(connection->credentials()) << endl;

    }

    virtual void onDisconnect(WebSocket* connection) {
        _connections.erase(connection);
        cout << "Disconnected: " << connection->getRequestUri()
             << " : " << formatAddress(connection->getRemoteAddress())
             << endl;
    }

    void send(string msg) {
        for (auto *con : _connections) con->send(msg);
    }

    void send(std::string key, std::string value) {
        _server->execute([&] {
            send(key + " : " + value);
        });
    }

private:
    set<WebSocket*> _connections;
    Server* _server;
};

int main(int /*argc*/, const char* /*argv*/[]) {

    auto logger = std::make_shared<PrintfLogger>(Logger::Level::DEBUG);
    Server server(logger);
    auto handler = std::make_shared<MyHandler>(&server);

    for(int i = 0 ; i<10; i++) {
        std::thread t([&] {
            for (;;) {
                sleep(1);
                auto v1 = rand() % 100;
                handler->send("mykey "+ std::to_string(v1), "value");
            }
        });

        t.detach();
    }

    server.addWebSocketHandler("/stream", handler);
    server.serve("web", 9090);

    return 0;
}
