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

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromCoords(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);
void SaveLevel(char* pLevel, int width, int height);

int main()
{
    int levelWidth;
    int levelHeight;

    GetLevelDimensions(levelWidth, levelHeight);

    char* pLevel = new char[levelWidth * levelHeight];

    for (int i = 0; i < levelWidth * levelHeight; i++)
    {
        pLevel[i] = ' ';
    }

    int cursorX = 0;
    int cursorY = 0;
    bool doneEditing = false;

    while (!doneEditing)
    {
        system("cls");
        DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
        doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);
    }

    system("cls");
    DisplayLevel(pLevel, levelWidth, levelHeight, -1, -1);

    SaveLevel(pLevel, levelWidth, levelHeight);

    // cleanup
    delete[] pLevel;
    pLevel = nullptr;
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height)
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
        else
        {
            int index = GetIndexFromCoords(newCursorX, newCursorY, width);
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
        levelFile.write(pLevel, width * height);
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