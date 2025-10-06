// server.cpp

#include <uwebsockets/App.h>
#include <iostream>
#include <unordered_set>

int main() {
    std::cout << "🚀 Starting WebSocket server on ws://localhost:9001\n";

    std::unordered_set<struct us_socket_context_t *> clients;

    uWS::App().ws<false>("/*", {
        .open = [&clients](auto *ws) {
            std::cout << "🟢 Client connected\n";
            clients.insert((us_socket_context_t *) ws);
        },

        .message = [&clients](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "📨 Message received: " << message << std::endl;

            // Broadcast to all clients
            for (auto *client : clients) {
                if (client != (us_socket_context_t *) ws) {
                    uWS::WebSocket<false, true> *c = (uWS::WebSocket<false, true> *) client;
                    c->send(message, opCode);
                }
            }
        },

        .close = [&clients](auto *ws, int /*code*/, std::string_view /*message*/) {
            std::cout << "🔴 Client disconnected\n";
            clients.erase((us_socket_context_t *) ws);
        }
    }).listen(9001, [](auto *token) {
        if (token) {
            std::cout << "✅ Listening on port 9001\n";
        } else {
            std::cerr << "❌ Failed to listen on port 9001\n";
        }
    }).run();

    return 0;
}
