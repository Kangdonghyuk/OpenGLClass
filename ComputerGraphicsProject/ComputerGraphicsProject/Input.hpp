//
//  Input.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 27..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

enum KeyType {
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u,
    v, w, x, y, z,
    leftArrow, upArrow, rightArrow, downArrow,
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    ctrl, alt, shift, space, esc, ent, size
};

enum KeyState {
    none, down, up, stay
};

class Input {
public:
    static KeyState keyState[KeyType::size];
public:
    void KeyUpdate();
    static void SetKeyDown(unsigned char key, int x, int y);
    static void SetSpecialKeyDown(int key, int x, int y);
    static void SetKeyUp(unsigned char key, int x, int y);
    static void SetSpecialKeyUp(int key, int x, int y);
public:
    bool GetKeyDown(KeyType key);
    bool GetKeyUp(KeyType key);
    bool GetKeyStay(KeyType key);
    KeyState GetKey(KeyType key);
};

static Input input;

#endif /* Input_hpp */
