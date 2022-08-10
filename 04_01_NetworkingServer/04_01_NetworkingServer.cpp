#include <enet/enet.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

ENetAddress address;
ENetHost* server = nullptr;
ENetEvent event;

constexpr int SERVER_PORT = 1234;
constexpr int MAX_CLIENTS = 32;
constexpr int MAX_CHANNELS = 2;
constexpr int BANDWIDTH_INCOMING = 0; // 0 = unlimited
constexpr int BANDWIDTH_OUTGOING = 0; // 0 = unlimited
constexpr int TIMEOUT_MS = 1000;
constexpr auto WELCOME_MESSAGE = "You're now connected to chat!\nType \"/help\" to see commands.\n";

constexpr auto COMMANDS = 
    "/guess - Guess a number for the guessing game. Ex. \"/guess 13\"\n"
    "/help - Lists all commands\n"
    "/play - Initiates the Number Guessing game\n"
    "/quit - Exits the chatroom\n"
    ;

bool guessingGameRunning = false;
int guessingGameNumber = 0;

bool CreateServer();
void SendMessageToClient(string message);
void SendMessageToAll(string message);
bool StartGuessingGame();
void CompleteGuessingGame(string user);
int GetRandomNumber(int min, int max);
bool ShouldSendRandomMessage();
string GetRandomMessage();
string GetMessageFromPacket(string data);
void MakeGuess(string user, int guess);
string GetUserFromPacket(string packet);
string GetCommandFromMessage(string message);

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
        while (enet_host_service(server, &event, TIMEOUT_MS) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                cout << "A new client connected from " << event.peer->address.host << ":" << event.peer->address.port << endl;
                event.peer->data = (void*)("Client information");
                SendMessageToClient(WELCOME_MESSAGE);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                cout << "Received a packet of length " << event.packet->dataLength << " containing: " << (char*)event.packet->data << endl;
                
                string packet = (char*)event.packet->data;
                string user = GetUserFromPacket(packet);
                string message = GetMessageFromPacket((char*)event.packet->data);
                
                if (message[0] == '/')
                {
                    // get full command
                    string command = GetCommandFromMessage(message);

                    if (command == "/guess")
                    {
                        if (!guessingGameRunning) SendMessageToClient("The guessing game is not currently active. Type \"/play\" to start.");
                        else MakeGuess(user, stoi(message.substr(7, message.length() - 6)));
                    }
                    else if (command == "/play")
                    {
                        if (StartGuessingGame()) SendMessageToAll(user + " has started a new round of the Guessing Game! Type \"/guess #\" to make a guess!");
                        else SendMessageToClient("The Guessing Game is already active. Make your guess with \"/guess #\"");
                    }
                    else if (command == "/quit")
                    {
                        SendMessageToAll(user + " has left the chatroom.");
                    }
                    else SendMessageToClient(COMMANDS);
                }
                else
                {
                    // send the received message to everyone
                    SendMessageToAll((char*)event.packet->data);

                    // check if we should respond back to the client that sent the message with a random message
                    if (ShouldSendRandomMessage()) SendMessageToClient(GetRandomMessage());
                }

                // Clean up the packet now that we're done using it.
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
                // Reset the peer's client information
                cout << (char*)event.peer->data << " disconnected." << endl;
                event.peer->data = NULL;
            }
        }
    }

    if (server != nullptr) enet_host_destroy(server); 

    return EXIT_SUCCESS;
}

bool CreateServer()
{
    // Bind the server to the default `localhost` on port `1234`
    // The host address can be set with `enet_address_set_host(&address, "x.x.x.x");`
    address.host = ENET_HOST_ANY;
    address.port = SERVER_PORT;
    server = enet_host_create(&address, MAX_CLIENTS, MAX_CHANNELS, BANDWIDTH_INCOMING, BANDWIDTH_OUTGOING);
    return server != nullptr;
}

void SendMessageToClient(string message)
{
    const char* msg = message.c_str();
    ENetPacket* packet = enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(event.peer, 0, packet);
    enet_host_flush(server);
}

void SendMessageToAll(string message)
{
    const char* msg = message.c_str();
    ENetPacket* packet = enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(server, 0, packet);
    enet_host_flush(server);
}

bool StartGuessingGame()
{
    if (!guessingGameRunning)
    {
        guessingGameRunning = true;
        guessingGameNumber = GetRandomNumber(1, 100);
        return true;
    }

    return false;
}

void CompleteGuessingGame(string user)
{
    guessingGameRunning = false;
    SendMessageToAll(user + " has guessed the number correctly! Congratulations!");
}

int GetRandomNumber(int min, int max)
{
    return rand() % max + min;
}

bool ShouldSendRandomMessage()
{
    return (rand() % 10) + 1 == 5;
}

string GetRandomMessage()
{
    int i = (rand() % 5) + 1;
    string randomMessage = "Private Message from Anonymous: ";

    if (i == 1) randomMessage += "Pressing Alt+F4 on your keyboard seems to give you money.";
    else if (i == 2) randomMessage += "Why is Zelda always trying to save the princess?";
    else if (i == 3) randomMessage += "Why is the Lich King's mount called Invincible when you can see it?";
    else if (i == 4) randomMessage += "Why is it called an Xbox 360? Because you turn 360 degrees and walk away.";
    else randomMessage += "Why didn't Harry Potter save Middle-earth at the end of Star Wars?";

    return randomMessage;
}

string GetMessageFromPacket(string data)
{
    string delimiter = ": ";
    size_t pos = 0;
    while ((pos = data.find(delimiter)) != string::npos) data.erase(0, pos + delimiter.length());
    return data;
}

void MakeGuess(string user, int guess)
{
    SendMessageToAll(user + " is making a guess of " + to_string(guess) + ".");

    if (guess == guessingGameNumber) CompleteGuessingGame(user);
    else
    {
        // incorrect, determine if too high or too low
        if (guess > guessingGameNumber) SendMessageToAll(to_string(guess) + " is too high!");
        else SendMessageToAll(to_string(guess) + " is too lower!");
    }
}

string GetUserFromPacket(string packet)
{
    return packet.substr(0, packet.find(":"));
}

string GetCommandFromMessage(string message)
{
    return message.substr(0, message.find(" "));
}
