//
//  Input.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 27..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "Input.hpp"

KeyState Input::keyState[KeyType::size];

void Input::KeyUpdate() {
    for(int i=0; i<KeyType::size; i++) {
        if(keyState[i] == none)
            continue;
        else if(keyState[i] == KeyState::down)
            keyState[i] = KeyState::stay;
        else if(keyState[i] == KeyState::up)
            keyState[i] = KeyState::none;
    }
}

void Input::SetKeyDown(unsigned char key, int x, int y) {
    if(key >= 'a' && key <= 'z')
        keyState[key - 'a'] = KeyState::down;
    else if(key >= '0' && key <= '9')
        keyState[key - '0' + KeyType::_0] = KeyState::down;
    else if(key == 32)
        keyState[KeyType::space] = KeyState::down;
    else if(key == 27)
        keyState[KeyType::esc] = KeyState::down;
}
void Input::SetSpecialKeyDown(int key, int x, int y) {
    if(key >= 100 && key <= 103)
        keyState[key - 100 + KeyType::leftArrow] = KeyState::down;
}
void Input::SetKeyUp(unsigned char key, int x, int y) {
    if(key >= 'a' && key <= 'z')
        keyState[key - 'a'] = KeyState::up;
    else if(key >= '0' && key <= '9')
        keyState[key - '0' + KeyType::_0] = KeyState::up;
    else if(key == 32)
        keyState[KeyType::space] = KeyState::up;
    else if(key == 27)
        keyState[KeyType::esc] = KeyState::up;
}
void Input::SetSpecialKeyUp(int key, int x, int y) {
    if(key >= 100 && key <= 103)
        keyState[key - 100 + KeyType::leftArrow] = KeyState::up;
}
KeyState Input::GetKey(KeyType key) {
    return keyState[key];
}
