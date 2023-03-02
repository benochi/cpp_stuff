#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BALL_SIZE = 10;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 50;

struct Paddle {
    int x, y;
    int w, h;
    int dy;
};

struct Ball {
    int x, y;
    int w, h;
    int dx, dy;
};

bool init();
void close();
void handle_input(Paddle& left_paddle, Paddle& right_paddle);
void move_paddle(Paddle& paddle);
void move_ball(Ball& ball, Paddle& left_paddle, Paddle& right_paddle);
void draw_rect(SDL_Renderer* renderer, SDL_Rect rect);

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize SDL" << std::endl;
        return -1;
    }

    Paddle left_paddle = { 10, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, 0 };
    Paddle right_paddle = { SCREEN_WIDTH - 10 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, 0 };
    Ball ball = { SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE, 5, 5 };

    bool running = true;
    while (running) {
        handle_input(left_paddle, right_paddle);
        move_paddle(left_paddle);
        move_paddle(right_paddle);
        move_ball(ball, left_paddle, right_paddle);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        draw_rect(renderer, { left_paddle.x, left_paddle.y, left_paddle.w, left_paddle.h });
        draw_rect(renderer, { right_paddle.x, right_paddle.y, right_paddle.w, right_paddle.h });
        draw_rect(renderer, { ball.x, ball.y, ball.w, ball.h });

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    close();

    return 0;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_Destroy
