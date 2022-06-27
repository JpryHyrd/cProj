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
// Checking eaten food and increase of the snakes speed
//--------------------------------------------------------------------------------------
void CheckFood() {
    if (snake.posX == food.x && snake.posY == food.y) {
        snake.length++;
        snake.eaten = true;
        SpawnFood();
        snake.speed -= 0.003;
    }
}
// Checking location of the snake
//--------------------------------------------------------------------------------------
void CheckCollision() {
    if (snake_body[snake.posX][snake.posY].life_t > 0) {
        is_game_over = true;
    }
}
// Moving snake
//--------------------------------------------------------------------------------------
void MoveSnake() {
    snake.updatedAt += GetFrameTime();
    if (snake.updatedAt >= snake.speed) {
        snake.updatedAt = 0;
    } else {
        return;
    }

    if (snake.eaten) {
        snake.eaten = false;
    } else {
        for (int i = 0; i < squad_width; i++) {
            for (int j = 0; j < squad_height; j++) {
                if (snake_body[i][j].life_t > 0) {
                    snake_body[i][j].life_t--;
                }
            }
        }
    }
    snake.dirX = snake.next_dir_x;
    snake.dirY = snake.next_dir_y;
    snake.posX += snake.dirX;
    snake.posY += snake.dirY;
    if (snake.posX >= squad_width) {
        snake.posX = 0;
    }
    if (snake.posX < 0) {
        snake.posX = squad_width - 1;
    }
    if (snake.posY >= squad_height) {
        snake.posY = 0;
    }
    if (snake.posY < 0) {
        snake.posY = squad_height - 1;
    }
    CheckCollision();
    snake_body[snake.posX][snake.posY].life_t = snake.length;
}
// Drawing the game (snake and food)
//--------------------------------------------------------------------------------------
void Draw() {
    DrawFood();
    DrawSnake();
    if (is_game_over) {
        DrawText("You Dead!", 200, screen_height / 2, 25, RED);
        DrawText("Press SPACE to restart the Game", 200, screen_height / 2 + 20, 20, RED);
    }
}
// Administration of the snake
//--------------------------------------------------------------------------------------
void ControlSnake() {
    if ((snake.dirY == 0) && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) {
        snake.next_dir_y = -1;
        snake.next_dir_x = 0;
        return;
    }
    if ((snake.dirY == 0) && (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))) {
        snake.next_dir_y = 1;
        snake.next_dir_x = 0;
        return;
    }
    if ((snake.dirX == 0) && (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))) {
        snake.next_dir_y = 0;
        snake.next_dir_x = -1;
        return;
    }
    if ((snake.dirX == 0) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))) {
        snake.next_dir_y = 0;
        snake.next_dir_x = 1;
        return;
    }
}
// Update
//------------------------------------------------------------------------------------
void Update(){
    if (is_game_over){
        if (IsKeyPressed(KEY_SPACE)) {
            Setup();
        }
        return;
    }
    MoveSnake();
    CheckFood();
    ControlSnake();
}
// Setting screen parameters
//--------------------------------------------------------------------------------------
Rectangle GetCanvasTarget() {
    float sh = (float)GetScreenHeight();
    float sw = (float)GetScreenWidth();
    float scale = fminf(sh / screen_height, sw / screen_width);
    Rectangle rec = {0, 0, screen_width * scale, screen_height * scale};
    return rec;
}
// The main func
//--------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width * 2, screen_height * 2, "Snake");
    SetTargetFPS(30);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);
    canvas = LoadRenderTexture(screen_width, screen_height);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
    Setup();
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) {
        //------------------------------------------------------------------------------------
        // Draw
        //------------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GREEN);
        BeginTextureMode(canvas);
        ClearBackground(BLACK);
        Draw();
        EndTextureMode();
        Rectangle canvas_field = {0, 0, (float)canvas.texture.width,
                                  -(float)canvas.texture.height};
        DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget(), NULLS,
                       0.0f, WHITE);
        EndDrawing();
        //------------------------------------------------------------------------------------
        Update();
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
//------------------------------------------------------------------------------------
// THE END!
//------------------------------------------------------------------------------------
