//
//  Input.cpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 27..
//  Copyright © 2019년 Liunx. All rights reserved.
//

#include "Input.hpp"

InputState Input::keyState[KeyType::size];
Position Input::mousePosition;
InputState Input::mouseState[MouseType::_size];
Position Input::mouseChangeRate;
Position Input::mousePrevPosition;

void Input::InputUpdate() {
    for(int i=0; i<KeyType::size; i++) {
        if(keyState[i] == InputState::none)
            continue;
        else if(keyState[i] == InputState::down)
            keyState[i] = InputState::stay;
        else if(keyState[i] == InputState::up)
            keyState[i] = InputState::none;
    }
    
    for(int i=0; i<MouseType::_size; i++) {
        if(mouseState[i] == InputState::none)
            continue;
        else if(mouseState[i] == InputState::down)
            mouseState[i] = InputState::stay;
        else if(mouseState[i] == InputState::up)
            mouseState[i] = InputState::none;
    }
    
    mousePrevPosition = mousePosition;
}

void Input::SetKeyDown(unsigned char key, int x, int y) {
    if(key >= 'a' && key <= 'z')
        keyState[key - 'a'] = InputState::down;
    else if(key >= '0' && key <= '9')
        keyState[key - '0' + KeyType::_0] = InputState::down;
    else if(key == 32)
        keyState[KeyType::space] = InputState::down;
    else if(key == 27)
        keyState[KeyType::esc] = InputState::down;
}
void Input::SetSpecialKeyDown(int key, int x, int y) {
    if(key >= 100 && key <= 103)
        keyState[key - 100 + KeyType::leftArrow] = InputState::down;
}
void Input::SetKeyUp(unsigned char key, int x, int y) {
    if(key >= 'a' && key <= 'z')
        keyState[key - 'a'] = InputState::up;
    else if(key >= '0' && key <= '9')
        keyState[key - '0' + KeyType::_0] = InputState::up;
    else if(key == 32)
        keyState[KeyType::space] = InputState::up;
    else if(key == 27)
        keyState[KeyType::esc] = InputState::up;
}
void Input::SetSpecialKeyUp(int key, int x, int y) {
    if(key >= 100 && key <= 103)
        keyState[key - 100 + KeyType::leftArrow] = InputState::up;
}
InputState Input::GetKey(KeyType key) {
    return keyState[key];
}

void Input::SetMousePress(int button, int state, int x, int y) {
    mouseState[button] = InputState(state + 1);
    mousePosition.x = x;
    mousePosition.y = y;
}
void Input::SetMouseMove(int x, int y) {
    mousePosition.x = x;
    mousePosition.y = y;
}
Position Input::GetMousePosition() {
    return mousePosition;
}
Position Input::GetMouseChangeRate() {
    mouseChangeRate.x = mousePosition.x - mousePrevPosition.x;
    mouseChangeRate.y = mousePosition.y - mousePrevPosition.y;
    
    return mouseChangeRate;
}
bool Input::GetMouseDown(MouseType button) {
    return mouseState[button] == InputState::down;
}
bool Input::GetMouseUp(MouseType button) {
    return mouseState[button] == InputState::up;
}
bool Input::GetMouseStay(MouseType button) {
    return mouseState[button] == InputState::stay;
}
