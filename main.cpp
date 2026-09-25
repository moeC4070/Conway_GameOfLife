#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include <SDL3/SDL.h>
#include <vector>
const int TILE_SIZE = 16;
const int TILE_ROW = 30;
const int TILE_COL = 60;
struct SDLState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int w, h, logW, logH;
};
struct Cell {
  bool alive;
  int aliveNeigh;
  void count_aliveNeig(Cell cells[TILE_ROW][TILE_COL], int r, int c) {
    this->aliveNeigh = 0;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0)
          continue;

        int neighborRow = r + i;
        int neighborCol = c + j;

        if (neighborRow >= 0 && neighborRow < TILE_ROW && neighborCol >= 0 &&
            neighborCol < TILE_COL) {

          if (cells[neighborRow][neighborCol].alive) {
            this->aliveNeigh += 1;
          }
        }
      }
    }
  }
  void updateCell() {
    if (this->alive) {
      if (this->aliveNeigh < 2 || this->aliveNeigh > 3) {
        this->alive = false; // Overpopulation / Underpopulation
      }
    } else {
      if (this->aliveNeigh == 3) {
        this->alive = true; // Reproduction
      }
    }
  }
};

//=============functions==============
bool init(SDLState *state);
void drawCells(Cell cells[TILE_ROW][TILE_COL], SDLState &state);
void updateCells(Cell cells[TILE_ROW][TILE_COL]);
void quit(SDLState *state);

int main(int argc, char *argv[]) {
  SDLState state;
  state.w = 800;
  state.h = 400;
  state.logW = TILE_COL * TILE_SIZE;
  state.logH = TILE_ROW * TILE_SIZE;
  if (!init(&state)) {
    SDL_Log("initialization failed:%s", SDL_GetError());
  }
  Cell cells[TILE_ROW][TILE_COL]{};

  float p_time = SDL_GetTicks() / 1000.0f;
  float accumulator = 0.0f;
  const float step_rate = 1.0f;

  bool running = true;
  SDL_Event event;
  bool living = false;
  while (running) {
    float c_time = SDL_GetTicks() / 1000.0f;
    float d_time = c_time - p_time;
    p_time = c_time;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        running = false;
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        SDL_ConvertEventToRenderCoordinates(state.renderer, &event);
        if (event.button.button == SDL_BUTTON_LEFT) {

          float mouseX = event.button.x;
          float mouseY = event.button.y;

          int clickedCol = (int)(mouseX / TILE_SIZE);
          int clickedRow = (int)(mouseY / TILE_SIZE);

          if (clickedRow >= 0 && clickedRow < TILE_ROW && clickedCol >= 0 &&
              clickedCol < TILE_COL) {
            cells[clickedRow][clickedCol].alive =
                !cells[clickedRow][clickedCol].alive;
          }
        }
        break;

      case SDL_EVENT_KEY_DOWN:
        if (event.key.scancode == SDL_SCANCODE_SPACE) {
          living = true;
        }
        break;
      }
    }
    if (living) {

      accumulator += d_time;
      while (accumulator >= step_rate) {
        updateCells(cells);
        accumulator -= step_rate;
      }
    }

    SDL_SetRenderDrawColor(state.renderer, 20, 20, 20, 255);
    SDL_RenderClear(state.renderer);

    drawCells(cells, state);

    SDL_RenderPresent(state.renderer);
  }
  quit(&state);
  return 0;
}
void drawCells(Cell cells[TILE_ROW][TILE_COL], SDLState &state) {
  for (int row = 0; row < TILE_ROW; row++) {
    for (int col = 0; col < TILE_COL; col++) {
      SDL_FRect rect = {(float)col * TILE_SIZE, (float)row * TILE_SIZE,
                        TILE_SIZE, TILE_SIZE};

      if (cells[row][col].alive == true) {
        SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(state.renderer, &rect);
      } else {
        SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(state.renderer, &rect);
      }
      SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
      SDL_RenderRect(state.renderer, &rect);
    }
  }
}
void updateCells(Cell cells[TILE_ROW][TILE_COL]) {

  Cell tempCells[TILE_ROW][TILE_COL];
  for (int row = 0; row < TILE_ROW; row++) {
    for (int col = 0; col < TILE_COL; col++) {
      tempCells[row][col] = cells[row][col];
    }
  }
  for (int row = 0; row < TILE_ROW; row++) {
    for (int col = 0; col < TILE_COL; col++) {
      cells[row][col].count_aliveNeig(tempCells, row, col);
      cells[row][col].updateCell();
    }
  }
}

bool init(SDLState *state) {
  bool succes = true;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    succes = false;
  }
  state->window =
      SDL_CreateWindow("Gonway", state->w, state->h, SDL_WINDOW_RESIZABLE);
  if (!state->window) {
    succes = false;
  }
  state->renderer = SDL_CreateRenderer(state->window, nullptr);
  if (!state->renderer) {
    succes = false;
  }
  SDL_SetRenderLogicalPresentation(state->renderer, state->logW, state->logH,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
  return succes;
}

void quit(SDLState *state) {
  SDL_DestroyRenderer(state->renderer);
  SDL_DestroyWindow(state->window);
  SDL_Quit();
}
