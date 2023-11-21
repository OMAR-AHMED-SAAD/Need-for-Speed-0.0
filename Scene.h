#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "GLTexture.h"  // Include necessary headers, such as GLTexture.h

// Declare the function to render the ground
void renderGround();

// Declare the function to render the skybox
void renderSkyBox();

// Declare the function to load the textures
void loadSceneTextures();

// Declare the function to render the scene
void drawScene();

#endif // SCENE_H
