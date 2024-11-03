#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, z; // 3D ����
} vec3;

typedef struct {
    float m[3][3]; // 3x3 ���
} Matrix3x3;

// ���Ϳ� ����� ����
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = a.x * b.m[0][0] + a.y * b.m[1][0] + a.z * b.m[2][0];
    result.y = a.x * b.m[0][1] + a.y * b.m[1][1] + a.z * b.m[2][1];
    result.z = a.x * b.m[0][2] + a.y * b.m[1][2] + a.z * b.m[2][2];
    return result;
}

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    mat.m[2][2] = 1; // Z���� 1�� ����
    return mat;
}

// �ܼ� ȭ�� �����
void clearScreen() {
    system("cls");
}

// ȭ�� �׸���
void draw(int earthAngle, int moonAngle) {
    clearScreen();
    int pX = WIDTH / 2; // �¾� ��ġ
    int pY = HEIGHT / 2;

    // ���� �ʱ� ��ġ
    vec3 earthPos = { 0.0f, 3.0f, 0.0f }; // �¾����κ����� �Ÿ�

    // �� �ʱ� ��ġ
    vec3 moonPos = { 0.0f, 1.0f, 0.0f }; // �����κ����� �Ÿ�

    // ���� ��ġ ��ȯ (�¾� ������ ���� ����)
    Matrix3x3 rotationEarth = createRotationMatrix(earthAngle);
    earthPos = Mul(earthPos, rotationEarth);

    // ���� ��ġ�� �¾��� ��ġ�� ����
    earthPos.x += pX; // �¾��� ��ġ�� X�࿡ ����
    earthPos.y = pY - earthPos.y; // Y�� ����

    // �� ��ġ ��ȯ (���� ������ ���� ����)
    Matrix3x3 rotationMoon = createRotationMatrix(moonAngle);
    moonPos = Mul(moonPos, rotationMoon);

    // �� ��ġ�� ������ ��ġ�� ����
    moonPos.x += earthPos.x;
    moonPos.y = earthPos.y - moonPos.y; // Y�� ����

    // ȭ�� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("O"); // �¾�
            }
            else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // ����
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("*"); // ��
            }
            else {
                printf(" "); // �� ����
            }
        }
        printf("\n");
    }
}

int main() {
    // ������ ���� �������� 20���� ����
    for (int earthAngle = 0; earthAngle < 360; earthAngle += 20) { // �� ������
        for (int moonAngle = 0; moonAngle < 360; moonAngle += 15) {
            draw(earthAngle, moonAngle); // ������ ���� ��ġ �׸���
            Sleep(100); // 0.1�� ���
        }
    }
    return 0;
}
