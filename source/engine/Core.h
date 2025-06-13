#ifndef CORE_H
#define CORE_H

#pragma once

// LOGGING MACROS
#include "Util/Log.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include "Component/Camera/Camera2D.h"

#include "Component/AbstractComponent.h"
#include "Component/Transform.h"
#include "Component/SpriteRenderer.h"

#include "Shader.h"
#include "Texture2D.h"
#include "KeyCode.h"
#include "Input.h"
#include "ResourceManager.h"
#include "GameObject.h"

#include "AbstractGameBase.h"
#include "Engine.h"

// GLOBALS 
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_ASPECT_RATIO ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)
#define WINDOW_TITLE "Arcadia"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

#endif // CORE_H