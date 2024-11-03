#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, z; // 3D 벡터
} vec3;

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 벡터와 행렬의 곱셈
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = a.x * b.m[0][0] + a.y * b.m[1][0] + a.z * b.m[2][0];
    result.y = a.x * b.m[0][1] + a.y * b.m[1][1] + a.z * b.m[2][1];
    result.z = a.x * b.m[0][2] + a.y * b.m[1][2] + a.z * b.m[2][2];
    return result;
}

// 회전 행렬 생성
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    mat.m[2][2] = 1; // Z축은 1로 설정
    return mat;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(int earthAngle, int moonAngle) {
    clearScreen();
    int pX = WIDTH / 2; // 태양 위치
    int pY = HEIGHT / 2;

    // 지구 초기 위치
    vec3 earthPos = { 0.0f, 3.0f, 0.0f }; // 태양으로부터의 거리

    // 달 초기 위치
    vec3 moonPos = { 0.0f, 1.0f, 0.0f }; // 지구로부터의 거리

    // 지구 위치 변환 (태양 주위를 돌기 위해)
    Matrix3x3 rotationEarth = createRotationMatrix(earthAngle);
    earthPos = Mul(earthPos, rotationEarth);

    // 지구 위치에 태양의 위치를 더함
    earthPos.x += pX; // 태양의 위치를 X축에 더함
    earthPos.y = pY - earthPos.y; // Y축 반전

    // 달 위치 변환 (지구 주위를 돌기 위해)
    Matrix3x3 rotationMoon = createRotationMatrix(moonAngle);
    moonPos = Mul(moonPos, rotationMoon);

    // 달 위치에 지구의 위치를 더함
    moonPos.x += earthPos.x;
    moonPos.y = earthPos.y - moonPos.y; // Y축 반전

    // 화면 그리기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("O"); // 태양
            }
            else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // 지구
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("*"); // 달
            }
            else {
                printf(" "); // 빈 공간
            }
        }
        printf("\n");
    }
}

int main() {
    // 지구의 각도 증가량을 20도로 설정
    for (int earthAngle = 0; earthAngle < 360; earthAngle += 20) { // 더 빨라짐
        for (int moonAngle = 0; moonAngle < 360; moonAngle += 15) {
            draw(earthAngle, moonAngle); // 지구와 달의 위치 그리기
            Sleep(100); // 0.1초 대기
        }
    }
    return 0;
}
