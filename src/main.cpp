#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

Color green = {173, 204, 96, 255};
Color darkgreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkgreen);
        }
    }

    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }
};

class Food
{
public:
    Vector2 posotion;
    Texture2D texture;

    Food()
    {
        Image image = LoadImage("Graphic/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        posotion = randomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, posotion.x * cellSize, posotion.y * cellSize, WHITE);
    }

    Vector2 randomPos()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food();

    void Draw()
    {
        snake.Draw();
        food.Draw();
    }
    void Update()
    {
        snake.Update();
    }
};

int main()
{
    InitWindow(cellSize * cellCount, cellSize * cellCount, "puta madre");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {

        BeginDrawing();
        if (eventTriggered(0.2))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_W) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_S) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_D) && game.snake.direction.x != -1)
        {
            game.snake.direction = {1, 0};
        }
        if (IsKeyPressed(KEY_A) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1, 0};
        }

        ClearBackground(green);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}