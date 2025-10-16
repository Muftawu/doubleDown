#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int FPS = 60;
int winWidth = 800;
int winHeight = 800;
int numLayers = 21;
int currentLayer = 0;
int dropLayerItem = 0;
int sequenceLen = 5;
int showStartInterface = 1;
int showWelcomeInterface = 1;
int PAUSE = 20000;

float tileWidth = 100.0;
float tileHeight = 10.0f;
float tileRotation = 0;
float tileOffsetY = 20;
Color tileColor = YELLOW;

const char *title = "Double Down";

typedef struct Layer {
  Rectangle rect;
  Color color;
} Layer;

typedef struct Destroyer {
  int x;
  int y;
  int radius;
  Color color;
} Destroyer;

void popLayer(Layer *layers, int layerIndex) {
  layers[layerIndex].rect.x = 10.0f;
  layers[layerIndex].color = RED;
}

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
  customDrawText(
      "'ENTER' key to signal completion and move on to the next. All the best",
      100, 350, 18);
  EndDrawing();
}

void startInterface(int *seq) {
  BeginDrawing();
  ClearBackground(BLACK);
  showSequence(seq);
  EndDrawing();
}

void gameInterface(Layer *layerMem, Destroyer *destroyer, int *seq) {
  BeginDrawing();
  ClearBackground(BLACK);

  DrawCircle(destroyer->x, destroyer->y, destroyer->radius, destroyer->color);

  for (int i = 0; i < numLayers; i++) {
    DrawRectanglePro(layerMem[i].rect, (Vector2){0.0, 0.0}, tileRotation,
                     layerMem[i].color);
  }

  EndDrawing();
}

int main() {

  srand(time(NULL));
  InitWindow(winWidth, winHeight, "Double Down");
  SetTargetFPS(FPS);

  int *seq = generateSequence();

  Layer *layerMem = malloc(sizeof(Layer) * numLayers);
  if (layerMem == NULL) {
    printf("Failed to allocate memory");
  }

  Destroyer destroyer = (Destroyer){
      .x = 400,
      .y = 200,
      .radius = 20,
      .color = BLUE,
  };

  for (int i = 1; i < numLayers; i++) {
    layerMem[i] = (Layer){.rect = (Rectangle){.x = 350.0,
                                              .y = 200.0 + (i * tileOffsetY),
                                              .width = tileWidth,
                                              .height = tileHeight},
                          .color = tileColor};
  }

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_SPACE)) {
      dropLayerItem = 1;
    }

    if (dropLayerItem) {
      currentLayer += 1;
      popLayer(layerMem, currentLayer);
      destroyer.y += tileOffsetY;
      dropLayerItem = 0;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    if (showWelcomeInterface) {
      welcomeInterface();
      pause(PAUSE);
    }
    showWelcomeInterface = 0;

    if (showStartInterface) {
      startInterface(seq);
      pause(PAUSE);
    }
    showStartInterface = 0;

    gameInterface(layerMem, &destroyer, seq);

    EndDrawing();
  }

  free(layerMem);

  CloseWindow();
}
