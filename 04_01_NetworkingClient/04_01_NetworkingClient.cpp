#define NOMINMAX

#include <iostream>
#include <string>
#include <thread>

#include <enet/enet.h>

using namespace std;

ENetAddress address;
ENetEvent event;
ENetHost* client = nullptr;
ENetPeer* peer;

bool doneChatting = false;
string name;
string message = "";
bool sendPacket = false;

bool CreateClient();
void SendPacket(string message);
void GetInput();

int main(int argc, char** argv)
{
    cout << "In order to connect to the server." << endl;
    cout << "Enter your name: ";
    getline(cin, name);

    if (enet_initialize() != 0)
    {
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    if (!CreateClient())
    {
        cout << "An error occurred while trying to create an ENet client host." << endl;
        exit(EXIT_FAILURE);
    }

    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect(client, &address, 2, 0);

    if (peer == NULL)
    {
        cout << "No available peers for initiating an ENet connection." << endl;
        exit(EXIT_FAILURE);
    }

    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        cout << "Connection to 127.0.0.1:1234 succeeded." << endl;
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);
        cout << "Connection to 127.0.0.1:1234 failed." << endl;
    }

    thread InputThread(GetInput);

    while (!doneChatting)
    {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(client, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                string packetString = name + " has connected.";
                SendPacket(packetString);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
                //cout << "A packet of length " << event.packet->dataLength << " containing " << (char*)event.packet->data << endl;
                cout << (char*)event.packet->data << endl;

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
            }
        }
    }

    if (client != nullptr)
    {
        enet_host_destroy(client);
    }

    InputThread.join();

    return EXIT_SUCCESS;
}

bool CreateClient()
{
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    return client != nullptr;
}

void SendPacket(string message)
{
    const char* msg = message.c_str();
    ENetPacket* packet = enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);
}

void GetInput()
{
    while (!doneChatting)
    {
        cin.clear();

        getline(cin, message);

        if (message == "/quit")
        {
            doneChatting = true;
            cout << "Exitting chat..." << endl;
            return;
        }

        message = name + ": " + message;
        SendPacket(message);
        message = "";
    }
}