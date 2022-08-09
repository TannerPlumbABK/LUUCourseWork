#include <enet/enet.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

ENetAddress address;
ENetHost* server = nullptr;
ENetEvent event;

constexpr auto WELCOME_MESSAGE = "You're now connected to chat!\nType \"/quit\" to exit.\n";

bool CreateServer();
void SendPacket(string message, bool broadcast);

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    if (!CreateServer())
    {
        cout << "An error occurred while trying to create an ENet server host." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Server running..." << endl;

    while (1)
    {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                cout << "A new client connected from " << event.peer->address.host << ":" << event.peer->address.port << endl;
                /* Store any relevant client information here. */
                event.peer->data = (void*)("Client information");

                SendPacket(WELCOME_MESSAGE, true);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                cout << "A packet of length " << event.packet->dataLength << " containing " << (char*)event.packet->data << endl;
                SendPacket((char*)event.packet->data, false);

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);

                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << " disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
            }
        }
    }

    if (server != nullptr)
    {
        enet_host_destroy(server);
    }

    return EXIT_SUCCESS;
}

bool CreateServer()
{
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = 1234;
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return server != nullptr;
}

void SendPacket(string message, bool broadcast)
{
    const char* msg = message.c_str();
    ENetPacket* packet = enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);

    if (broadcast)
        enet_peer_send(event.peer, 0, packet);
    else
        enet_host_broadcast(server, 0, packet);

    enet_host_flush(server);
}