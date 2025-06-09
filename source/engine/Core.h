#ifndef CORE_H
#define CORE_H

#pragma once

// LOGGING MACROS
#include "utilities/Log.h"

#include "camera/Camera2D.h"

#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"

#include "Shader.h"
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "KeyCode.h"
#include "Input.h"
#include "ResourceManager.h"

#include "IGame.h"
#include "Engine.h"

// GLOBALS 
#define PROJECT_PATH "/Users/pratik/Projects/Misc/arcadia/"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_ASPECT_RATIO ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)
#define WINDOW_TITLE "Arcadia"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

#endif // CORE_H