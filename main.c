#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int FPS = 60;
int winWidth = 800;
int winHeight = 800;
int sequenceLen = 5;
int PAUSE = 10000;

float tileWidth = 100.0;
float tileHeight = 10.0f;
float tileRotation = 0;
float tileOffsetY = 20;
int maxTileSize = 45;
Color tileColor = YELLOW;

const char *title = "Double Down";

typedef struct Tile {
  Rectangle rect;
  Color color;
} Tile;

int randInt() {
  float num = (float)rand() / RAND_MAX;
  return (int)(num * 10);
}

int *generateSequence() {
  int *sequence = malloc(sizeof(sequenceLen) * sequenceLen);
  for (int i = 0; i < sequenceLen; i++) {
    sequence[i] = randInt();
  }
  return sequence;
}

void customDrawText(char *text, int x, int y, int fs) {
  DrawText(text, x, y, fs, RAYWHITE);
}

void showSequence(int *seq) {
  for (int i = 0; i < sequenceLen; i++) {
    DrawText(TextFormat("%d ", seq[i]), 170 + (100 * i), 200, 70, RAYWHITE);
  }
}

void pause(int delay) {
  for (int i = 0; i < delay; i++) {
    for (int j = 0; j < delay; j++) {
    }
  }
}

void welcomeInterface() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    customDrawText("Double Down", 270, 50, 40);
    customDrawText(
        "You have 3 seconds to memorize five random numbers when the game", 100,
        200, 18);
    customDrawText(
        "loads. For each number press the 'SPACE' key that number of times to",
        100, 250, 18);
    customDrawText(
        "load tiles matching that number. When done with a number, press the",
        100, 300, 18);
    customDrawText("'ENTER' key to signal completion and move on to the next. "
                   "All the best",
                   100, 350, 18);
    customDrawText("Press C to continue", 300, 700, 18);

    EndDrawing();
    if (IsKeyPressed(KEY_C))
      break;
  }
}

void startInterface(int *seq) {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    showSequence(seq);
    EndDrawing();
    pause(10000);
    break;
  }
}

void gameInterface() {
  while (!WindowShouldClose()) {

    Tile *tiles = malloc(sizeof(Tile) * maxTileSize);
    if (tiles == NULL)
      printf("Memory allocation failed for tiles");

    BeginDrawing();
    ClearBackground(BLACK);

    // used
    int tileIndex = 0;
    int stackIndex = 0;
    int stacks[] = {100, 200, 300, 400, 500};
    int currentStack = stacks[stackIndex];
    int currentTilePosY = 700;

    if (IsKeyPressed(KEY_ENTER)) {
      stackIndex += 1;
      currentStack = stacks[stackIndex];
    }

    if (IsKeyPressed(KEY_SPACE)) {
      tileIndex += 1;
      currentTilePosY = currentTilePosY - tileOffsetY;
      tiles[tileIndex] = (Tile){.rect =
                                    (Rectangle){
                                        .x = currentStack,
                                        .y = currentTilePosY,
                                        .width = tileWidth,
                                        .height = tileHeight,
                                    },
                                .color = tileColor};
      printf("stack => %d \n", currentStack);
      printf("stack index => %d \n", stackIndex);
      printf("tile index => %d \n", tileIndex);
    }

    for (int i = 0; i < tileIndex; i++) {
      DrawRectanglePro(tiles[i].rect, (Vector2){0.0, 0.0}, tileRotation,
                       tiles[i].color);
    }
    EndDrawing();
  }
}

int main() {

  srand(time(NULL));
  InitWindow(winWidth, winHeight, "Double Down");
  SetTargetFPS(FPS);

  int *seq = generateSequence();

  welcomeInterface();
  startInterface(seq);
  gameInterface();

  // free(layerMem);

  CloseWindow();
}
