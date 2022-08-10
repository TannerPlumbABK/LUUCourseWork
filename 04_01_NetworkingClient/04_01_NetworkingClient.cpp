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

constexpr auto SERVER_HOST = "127.0.0.1";
constexpr int SERVER_PORT = 1234;

constexpr int OUTGOING_CONNECTIONS = 1;
constexpr int MAX_CHANNELS = 2;
constexpr int BANDWIDTH_INCOMING = 0; // 0 = unlimited
constexpr int BANDWIDTH_OUTGOING = 0; // 0 = unlimited

constexpr int CONNECT_TIMEOUT_MS = 5000;
constexpr int LOOP_TIMEOUT_MS = 1000;

bool doneChatting = false;
string name;
string message = "";
bool sendPacket = false;

enum Colors
{
    REGULAR = 7,
    BLUE = 9,
    GREEN = 10,
    PURPLE = 13,
};

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

    // connect to the server
    enet_address_set_host(&address, SERVER_HOST);
    address.port = SERVER_PORT;
    peer = enet_host_connect(client, &address, MAX_CHANNELS, 0);

    if (peer == NULL)
    {
        cout << "No available peers for initiating an ENet connection." << endl;
        exit(EXIT_FAILURE);
    }

    // Wait up to CONNECT_TIME_MS for the connection attempt to succeed
    if (enet_host_service(client, &event, CONNECT_TIMEOUT_MS) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        cout << "Connection to " << SERVER_HOST << ":" << SERVER_PORT << " succeeded." << endl;
    else
    {
        // Either CONNECT_TIMEOUT_MS was reached or the client disconnected
        enet_peer_reset(peer);
        cout << "Connection to " << SERVER_HOST << ":" << SERVER_PORT << " failed." << endl;
    }

    thread InputThread(GetInput);

    while (!doneChatting)
    {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(client, &event, LOOP_TIMEOUT_MS) > 0)
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
                HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

                string receivedMessage = (char*)event.packet->data;
                string user = receivedMessage.substr(0, receivedMessage.find(":"));

                if (user == name) SetConsoleTextAttribute(console, Colors::BLUE);
                else if (user == "Private Message from Anonymous") SetConsoleTextAttribute(console, Colors::PURPLE);
                else if (receivedMessage.find(":") == string::npos) SetConsoleTextAttribute(console, Colors::GREEN);
                
                cout << receivedMessage << endl;
                SetConsoleTextAttribute(console, Colors::REGULAR);

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
            }
        }
    }

    if (client != nullptr) enet_host_destroy(client); 

    InputThread.join();

    return EXIT_SUCCESS;
}

bool CreateClient()
{
    client = enet_host_create(NULL, OUTGOING_CONNECTIONS, MAX_CHANNELS, BANDWIDTH_INCOMING, BANDWIDTH_OUTGOING);
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
        }

        // let's back up so new incoming input will overwrite what the user typed
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        short x = 0;
        short y = 0;

        if (GetConsoleScreenBufferInfo(output, &cbsi))
        {
            x = cbsi.dwCursorPosition.X;
            y = cbsi.dwCursorPosition.Y - 1;
        }
        COORD pos = { x, y };
        SetConsoleCursorPosition(output, pos);

        // create and send the message
        message = name + ": " + message;
        SendPacket(message);
        message = "";
    }
}