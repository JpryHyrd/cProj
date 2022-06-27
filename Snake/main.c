// The Snake Game
//--------------------------------------------------------------------------------------
//Part of includes
#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <stdbool.h>
// Formation of Parameters
//--------------------------------------------------------------------------------------
//Screen Params
#define screen_width 720
#define screen_height 360
//Cube sizes
#define cube_width 30
#define cube_height 30
//Food sizes
#define food_width 18
#define food_height 18
//Squads sizes
#define squad_width 24
#define squad_height 12
bool is_game_over = false;
const Vector2 NULLS = {0, 0};
RenderTexture2D canvas;
// Foods structure
//--------------------------------------------------------------------------------------
typedef struct Food_ {
    int x;
    int y;
} Food;

typedef struct SnakeNode_ {
    int life_t;
    bool eat_inside;
} SnakeNode;
// Snakes structure
//--------------------------------------------------------------------------------------
typedef struct Snake_ {
    int dirX;
    int dirY;
    int next_dir_x;
    int next_dir_y;
    int length;
    int posX;
    int posY;
    float speed;
    float updatedAt;
    bool eaten;
} Snake;

Food food = {-1, -1};
SnakeNode snake_body[squad_width][squad_height];
Snake snake;
// Initialization of the snake
//--------------------------------------------------------------------------------------
void InitSnake() {
    for (int i = 0; i < snake.length; i++) {
        int x = snake.posX - snake.dirX * i;
        int y = snake.posY - snake.dirY * i;
        snake_body[x][y].life_t = snake.length - i;
    }
}
// Initialization of the food
//--------------------------------------------------------------------------------------
void SpawnFood() {
    int x;
    int y;
    do {
        x = GetRandomValue(0, squad_width - 1);
        y = GetRandomValue(0, squad_height - 1);
    } while (snake_body[x][y].life_t > 0);
    TraceLog(LOG_INFO, "Spawn food at [%d,%d]", x, y);
    food.x = x;
    food.y = y;
}
// Setting the game
//--------------------------------------------------------------------------------------
void Setup() {
    snake.dirX = 1;
    snake.dirY = 0;
    snake.next_dir_x = 1;
    snake.next_dir_y = 0;
    snake.length = 2;
    snake.posX = squad_width / 2;
    snake.posY = squad_height / 2;
    snake.updatedAt = 0;
    snake.eaten = false;
    snake.speed = 0.3;
    is_game_over = false;
    for (int i = 0; i < squad_width; i++) {
        for (int j = 0; j < squad_height; j++) {
            snake_body[i][j].life_t = 0;
            snake_body[i][j].eat_inside = false;
        }
    }

    InitSnake();
    SpawnFood();
}
// Initialization body of the snake
//--------------------------------------------------------------------------------------
void DrawSnakeBody(int i, int j) {
    if (snake_body[i][j].life_t < 1) {
        return;
    }

    DrawRectangle(i * cube_width, j * cube_height, cube_width, cube_height,
                  GREEN);
}
// Initialization head of the snake
//--------------------------------------------------------------------------------------
void DrawSnakeHead() {
    DrawRectangle(snake.posX * cube_width, snake.posY * cube_height, cube_width,
                  cube_height, DARKGREEN);
}
// Compilation body and head of the sneak
//--------------------------------------------------------------------------------------
void DrawSnake(){
    for(int i = 0; i < squad_width; i++){
        for(int j = 0; j < squad_height; j++){
            if (snake_body[i][j].life_t > 0){
                DrawSnakeBody(i, j);
            }
        }
    }
    DrawSnakeHead();
}
// Drawing food
//--------------------------------------------------------------------------------------
void DrawFood() {
    int dw = (cube_width - food_width) / 2;
    int dh = (cube_height - food_height) / 2;
    DrawRectangle(food.x * cube_width + dw, food.y * cube_height + dh, food_height,
                  food_width, YELLOW);
}
