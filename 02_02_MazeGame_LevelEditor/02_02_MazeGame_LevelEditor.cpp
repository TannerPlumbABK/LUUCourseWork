#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

constexpr char cursor = '_';

constexpr char topRightBorder = 187;
constexpr char topLeftBorder = 201;
constexpr char bottomRightBorder = 188;
constexpr char bottomLeftBorder = 200;
constexpr char horizontalBorder = 205;
constexpr char verticalBorder = 186;

constexpr int arrowInput = 224;
constexpr int leftArrow = 75;
constexpr int rightArrow = 77;
constexpr int upArrow = 72;
constexpr int downArrow = 80;
constexpr int escape = 27;
constexpr int backspace = 8;
constexpr int lowerP = 112;
constexpr int upperP = 80;
constexpr int space = 32;
constexpr int playerSymbol = 64;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromCoords(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height, int& portalEntranceIndex, int& portalExitIndex, int& playerIndex);
void SaveLevel(char* pLevel, int width, int height);
void DisplayLegend();
void RunEditor(char* pLevel, int width, int height, int& portalEntranceIndex, int& portalExitIndex, int& playerIndex);

int main()
{
    char* pLevel = nullptr;
    int levelWidth;
    int levelHeight;

    int portalEntranceIndex = -1;
    int portalExitIndex = -1;
    int playerIndex = -1;

    bool done = false;

    while (!done)
    {
        system("cls");
        cout << "Please select one of the following options: " << endl;
        cout << "1. Load Level" << endl;
        cout << "2. New Level" << endl;
        cout << "3. Quit" << endl;

        int input;
        cin >> input;

        if (input == 1)
        {
            // Load Level
            cout << "Enter Level name: ";
            string levelName;
            cin >> levelName;

            levelName.insert(0, "../02_02_MazeGame_Levels/");
            ifstream levelFile;
            levelFile.open(levelName);

            if (!levelFile)
            {
                cout << "Opening file failed." << endl;
            }
            else
            {
                constexpr int tempSize = 25;
                char temp[tempSize];
                levelFile.getline(temp, tempSize, '\n');
                levelWidth = atoi(temp);

                levelFile.getline(temp, tempSize, '\n');
                levelHeight = atoi(temp);

                pLevel = new char[levelWidth * levelHeight];
                levelFile.read(pLevel, (long long)levelWidth * (long long)levelHeight);
                levelFile.close();

                RunEditor(pLevel, levelWidth, levelHeight, portalEntranceIndex, portalExitIndex, playerIndex);

                delete[] pLevel;
                pLevel = nullptr;
            }
        }
        else if (input == 2)
        {
            // New Level
            GetLevelDimensions(levelWidth, levelHeight);

            char* pLevel = new char[levelWidth * levelHeight];

            for (int i = 0; i < levelWidth * levelHeight; i++)
            {
                pLevel[i] = ' ';
            }

            RunEditor(pLevel, levelWidth, levelHeight, portalEntranceIndex, portalExitIndex, playerIndex);

            delete[] pLevel;
            pLevel = nullptr;
        }
        else if (input == 3)
        {
            done = true;
        }
    }
}

void RunEditor(char* pLevel, int width, int height, int& portalEntranceIndex, int& portalExitIndex, int& playerIndex)
{
    int cursorX = 0;
    int cursorY = 0;
    bool doneEditing = false;

    while (!doneEditing)
    {
        system("cls");
        DisplayLevel(pLevel, width, height, cursorX, cursorY);
        DisplayLegend();
        doneEditing = EditLevel(pLevel, cursorX, cursorY, width, height, portalEntranceIndex, portalExitIndex, playerIndex);
    }

    system("cls");
    DisplayLevel(pLevel, width, height, -1, -1);

    SaveLevel(pLevel, width, height);
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height, int& portalEntranceIndex, int& portalExitIndex, int& playerIndex)
{
    int newCursorX = cursorX;
    int newCursorY = cursorY;

    int intInput = _getch();

    if (intInput == arrowInput)
    {
        int arrowInput = _getch();

        switch (arrowInput)
        {
        case leftArrow:
            newCursorX--;
            break;
        case rightArrow:
            newCursorX++;
            break;
        case upArrow:
            newCursorY--;
            break;
        case downArrow:
            newCursorY++;
            break;
        }

        if (newCursorX < 0)
        {
            newCursorX = 0;
        }
        else if (newCursorX >= width)
        {
            newCursorX = width - 1;
        }

        if (newCursorY < 0)
        {
            newCursorY = 0;
        }
        else if (newCursorY >= height)
        {
            newCursorY = height - 1;
        }

        cursorX = newCursorX;
        cursorY = newCursorY;
    }
    else
    {
        if (intInput == escape)
        {
            return true;
        }
        else if (intInput == backspace)
        {
            // ignore
        }
        else if (intInput == playerSymbol)
        {
            int index = GetIndexFromCoords(newCursorX, newCursorY, width);

            if (playerIndex != -1) pLevel[playerIndex] = ' ';
            playerIndex = index;

            pLevel[index] = (char)intInput;
        }
        else
        {
            int index = GetIndexFromCoords(newCursorX, newCursorY, width);

            // replace any existing p or P with a ' ' before adding the new one
            if (intInput == upperP)
            {
                if (portalEntranceIndex != -1) pLevel[portalEntranceIndex] = ' ';
                portalEntranceIndex = index;
            }
            else if (intInput == lowerP)
            {
                if (portalExitIndex != -1) pLevel[portalExitIndex] = ' ';
                portalExitIndex = index;
            }
            else
            {
                if (pLevel[index] == 'p') portalExitIndex = -1;
                else if (pLevel[index] == 'P') portalEntranceIndex = -1;
            }
            
            pLevel[index] = (char)intInput;
        }
    }

    return false;
}

void SaveLevel(char* pLevel, int width, int height)
{
    cout << "Pick a name for your level file (eg: Level1.txt): ";
    string levelName;
    cin >> levelName;

    levelName.insert(0, "../02_02_MazeGame_Levels/");

    ofstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Opening file failed.";
    }
    else
    {
        levelFile << width << endl;
        levelFile << height << endl;
        levelFile.write(pLevel, (long long)width * (long long)height);
        if (!levelFile)
        {
            cout << "Write failed." << endl;
        }
        levelFile.close();
    }
}

void GetLevelDimensions(int& width, int& height)
{
    cout << "Enter the width of your level: ";
    cin >> width;

    cout << "Enter the height of your level: ";
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
    DisplayTopBorder(width);
    
    for (int y = 0; y < height; y++)
    {
        DisplayLeftBorder();

        for (int x = 0; x < width; x++)
        {
            if (cursorX == x && cursorY == y)
            {
                cout << cursor;
            }
            else
            {
                int index = GetIndexFromCoords(x, y, width);
                cout << pLevel[index];
            }
        }

        DisplayRightBorder();
    }

    DisplayBottomBorder(width);
}

void DisplayLegend()
{
    cout << "Arrows to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "r g b for key" << endl;
    cout << "R G B for door" << endl;
    cout << "$ for money" << endl;
    cout << "v for vertical moving enemy" << endl;
    cout << "h for horizontal moving enemy" << endl;
    cout << "e for non-moving enemy" << endl;
    cout << "P for a portal entry (only 1 per level)" << endl;
    cout << "p for a portal exit (only 1 per level)" << endl;
    cout << "L for a life" << endl;
    cout << "X for end" << endl;
}

void DisplayTopBorder(int width)
{
    cout << topLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << horizontalBorder;
    }
    cout << topRightBorder << endl;
}

void DisplayBottomBorder(int width)
{
    cout << bottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << horizontalBorder;
    }
    cout << bottomRightBorder << endl;
}

void DisplayLeftBorder()
{
    cout << verticalBorder;
}

void DisplayRightBorder()
{
    cout << verticalBorder << endl;
}


int GetIndexFromCoords(int x, int y, int width)
{
    return x + y * width;
}