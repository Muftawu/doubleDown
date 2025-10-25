#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int FPS = 60;
int winWidth = 800;
int winHeight = 800;
int sequenceLen = 5;
int PAUSE = 10000;

int tileWidth = 100;
int tileHeight = 10;
int tileOffsetY = 20;
int tileOffsetX = 50;
int maxTileSize = 45;
float tileRotation = 0;
Color tileColor = YELLOW;

int stackIndex = 0;
int tileCounter = 0;

int currentStackHeight = 700;
int stacks[] = {120, 240, 360, 480, 600};

const char *title = "Double Down";

typedef struct Tile {
  Rectangle rect;
  Color color;
} Tile;

typedef struct Renderer {
  int stackIndex;
  int tileCount;
  Rectangle rect[45];
} Renderer;

int randInt() {
  float num = (float)rand() / RAND_MAX;
  return (int)(num * 10);
}

int *generateSequence() {
  int *sequence = malloc(sizeof(sequenceLen) * sequenceLen);
  for (int i = 0; i < sequenceLen; i++) {
    int num = randInt();
    if (num != 0)
      sequence[i] = num;
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
    customDrawText("loads. For each number press the 'SPACE' key that number "
                   "of times to",
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

void gameInterface(Renderer *renderer) {

  for (int i = 0; i < sequenceLen; i++) {
    renderer[i].tileCount = 0;
  }

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(BLACK);

    customDrawText("Press the Space key to start.", 100, 750, 20);
    if (IsKeyPressed(KEY_ENTER)) {

      stackIndex++;
      tileCounter = 0;
      currentStackHeight = 700;
    }

    if (IsKeyPressed(KEY_SPACE)) {
      tileCounter++;
      currentStackHeight = currentStackHeight - tileOffsetY;
      renderer[stackIndex].stackIndex = stackIndex;
      renderer[stackIndex].tileCount = tileCounter + 1;
      renderer[stackIndex].rect[tileCounter] = (Rectangle){
          stacks[stackIndex], currentStackHeight, tileWidth, tileHeight};

      // for (int i = 0; i < sequenceLen; i++) {
      //   printf("%d \t", renderer[i].tileCount);
      // }
      // printf("\n");
    }

    for (int x = 0; x < sequenceLen; x++) {
      int tileCount = renderer[x].tileCount;
      for (int y = 0; y < tileCount; y++) {
        DrawRectanglePro(renderer[x].rect[y], (Vector2){0.0, 0.0}, tileRotation,
                         tileColor);
      }
    }
    EndDrawing();
    if (stackIndex == 5)
      break;
  }
}

void scoreInterface(int *seq, Renderer *renderer) {

  char scores[5] = {};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    customDrawText("Done. Your Score", 270, 50, 40);
    for (int i = 0; i < sequenceLen; i++) {
      if (seq[i] == renderer[i].tileCount)
        scores[i] = 'w';
      else
        scores[i] = 'x';
    }
    customDrawText(scores, 270, 100, 40);
    EndDrawing();
  }
}

int main() {

  srand(time(NULL));
  InitWindow(winWidth, winHeight, "Double Down");
  SetTargetFPS(FPS);

  int *seq = generateSequence();
  Renderer *renderer = malloc(sizeof(Renderer) * sequenceLen);
  if (renderer == NULL)
    printf("Failed to allocate memory to rendere\n");

  welcomeInterface();
  startInterface(seq);
  gameInterface(renderer);
  scoreInterface(seq, renderer);

  for (int i = 0; i < sequenceLen; i++) {
    printf("seq[i]: %d, renderer[i].tileCount: %d \n", seq[i],
           renderer[i].tileCount);
  }

  // free(layerMem);

  free(renderer);
  CloseWindow();
}
