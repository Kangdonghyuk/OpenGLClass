//
//  Input.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 27..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "VoxelData.h"

enum KeyType {
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u,
    v, w, x, y, z,
    leftArrow, upArrow, rightArrow, downArrow,
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    ctrl, alt, shift, space, esc, ent, size
};

enum MouseType {
    left, middle, right, _size
};

enum InputState {
    none, down, up, stay
};

class Input {
public:
    static InputState keyState[KeyType::size];
    static Position mousePosition;
    static Position mouseChangeRate;
    static Position mousePrevPosition;
    static InputState mouseState[_size];
public:
    void InputUpdate();
    static void SetKeyDown(unsigned char key, int x, int y);
    static void SetSpecialKeyDown(int key, int x, int y);
    static void SetKeyUp(unsigned char key, int x, int y);
    static void SetSpecialKeyUp(int key, int x, int y);
public:
    bool GetKeyDown(KeyType key);
    bool GetKeyUp(KeyType key);
    bool GetKeyStay(KeyType key);
    InputState GetKey(KeyType key);
public:
    static void SetMousePress(int button, int state, int x, int y);
    static void SetMouseMove(int x, int y);
public:
    Position GetMousePosition();
    Position GetMouseChangeRate();
    bool GetMouseDown(MouseType button);
    bool GetMouseUp(MouseType button);
    bool GetMouseStay(MouseType button);
};

static Input input;

#endif /* Input_hpp */
