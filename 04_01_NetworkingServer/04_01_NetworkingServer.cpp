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

bool guessingGameRunning = false;
int guessingGameNumber = 0;

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
        while (enet_host_service(server, &event, TIMEOUT_MS) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                cout << "A new client connected from " << event.peer->address.host << ":" << event.peer->address.port << endl;
                event.peer->data = (void*)("Client information");
                SendPacket(WELCOME_MESSAGE, false);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                cout << "A packet of length " << event.packet->dataLength << " containing " << (char*)event.packet->data << endl;
                
                string packet = (char*)event.packet->data;
                string user = packet.substr(0, packet.find(":"));

                // parse message for commands
                string message = (char*)event.packet->data;
                string delimiter = ": ";
                size_t pos = 0;
                while ((pos = message.find(delimiter)) != string::npos) message.erase(0, pos + delimiter.length());
                
                if (message[0] == '/')
                {
                    if (message.substr(0, 6) == "/guess")
                    {
                        if (!guessingGameRunning) SendPacket("The guessing game is not currently active. Type \"/play\" to start.", false);
                        else
                        {
                            int guess = stoi(message.substr(7, message.length() - 6));
                            cout << user << " is making a guess of " << guess << endl;
                            
                            string broadcastMessage = user + " is making a guess of " + to_string(guess) + ".";
                            SendPacket(broadcastMessage, true);

                            if (guess == guessingGameNumber)
                            {
                                // correct!
                                broadcastMessage = user + " made a correct guess! Congratulations!";
                                SendPacket(broadcastMessage, true);
                                guessingGameRunning = false;
                            }
                            else
                            {
                                // incorrect, determine if too high or too low
                                if (guess > guessingGameNumber) SendPacket("The guessed number was too high!", true);
                                else SendPacket("The guessed number was too low!", true);
                            }
                        }
                    }
                    else if (message == "/play")
                    {
                        if (guessingGameRunning) SendPacket("The guessing game is already active. Make your guess with \"/guess #\"", false);
                        else
                        {
                            guessingGameRunning = true;
                            guessingGameNumber = rand() % 100 + 1;
                            string broadcastMessage = user + " has started a round of the Guessing Game! Type \"/guess #\" to make your guesses!";
                            SendPacket(broadcastMessage, true);
                        }
                    }
                    else if (message == "/quit")
                    {
                        string leftMessage = user + " has left the chatroom.";
                        SendPacket(leftMessage, true);
                    }
                    else
                    {
                        string commandsMsg =
                            "/guess - Guess a number for the guessing game. Ex. \"/guess 13\"\n"
                            "/help - Lists all commands\n"
                            "/play - Initiates the Number Guessing game\n"
                            "/quit - Exits the chatroom\n"
                            ;
                        SendPacket(commandsMsg, false);
                    }
                }
                else
                {
                    SendPacket((char*)event.packet->data, true);

                    // check if we should respond back to the client that sent the message with a random message
                    bool sendRandomMessage = (rand() % 10) + 1 == 5;
                    if (sendRandomMessage)
                    {
                        // TROLLING MESSAGES. Not to be taken seriously.
                        int i = (rand() % 5) + 1;
                        string randomMessage = "Private Message from Anonymous: ";
                        if (i == 1) randomMessage += "Pressing Alt+F4 on your keyboard seems to give you money.";
                        else if (i == 2) randomMessage += "Why is Zelda always trying to save the princess?";
                        else if (i == 3) randomMessage += "Why is the Lich King's mount called Invincible when you can see it?";
                        else if (i == 4) randomMessage += "Why is it called an Xbox 360? Because you turn 360 degrees and walk away.";
                        else randomMessage += "Why didn't Harry Potter save Middle-earth at the end of Star Wars?";
                        SendPacket(randomMessage, false);
                    }
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

void SendPacket(string message, bool broadcast)
{
    const char* msg = message.c_str();
    ENetPacket* packet = enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);

    if (broadcast) enet_host_broadcast(server, 0, packet);
    else enet_peer_send(event.peer, 0, packet);

    enet_host_flush(server);
}