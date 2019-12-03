//
//  Input.hpp
//  ComputerGraphicsProject
//
//  Created by Liunx on 2019. 11. 27..
//  Copyright © 2019년 Liunx. All rights reserved.
//

/*
입력 관리 클래스 정의
*/

#ifndef Input_hpp
#define Input_hpp

#include "VoxelData.h"

//사용할 수 있는 키보드 타입 정의 (몇 개 사용 불가)
enum KeyType {
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u,
    v, w, x, y, z,
    leftArrow, upArrow, rightArrow, downArrow,
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    ctrl, alt, shift, space, esc, ent, size
};

//마우스 버튼 타입 정의
enum MouseType {
    left, middle, right, _size
};

//입력 상태 정의
enum InputState {
    none, down, up, stay
};

class Input {
public:
    static InputState keyState[KeyType::size]; //키보드 입력 상태 저장
    static Position mousePosition; //마우스 좌표 저장
    static Position mouseChangeRate;
    static Position mousePrevPosition;
    static InputState mouseState[_size]; //마우스 입력 상태 저장
public:
    void InputUpdate(); //매 프레임 입력 상태 체크
    //OpenGL 키보드 입력 이벤트 콜백 함수
    static void SetKeyDown(unsigned char key, int x, int y);
    static void SetSpecialKeyDown(int key, int x, int y);
    static void SetKeyUp(unsigned char key, int x, int y);
    static void SetSpecialKeyUp(int key, int x, int y);
public:
    //키보드 입력 상태 반환
    InputState GetKey(KeyType key);
public:
    //OpenGL 마우스 입력 이벤트 콜백 함수
    static void SetMousePress(int button, int state, int x, int y);
    static void SetMouseMove(int x, int y);
public:
    //마우스 입력 상태 반환
    Position GetMousePosition();
    Position GetMouseChangeRate();
    bool GetMouseDown(MouseType button);
    bool GetMouseUp(MouseType button);
    bool GetMouseStay(MouseType button);
};

static Input input;

#endif /* Input_hpp */
