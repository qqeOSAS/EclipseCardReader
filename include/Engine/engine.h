#ifndef SIMPLE_3D_RENDERER_H
#define SIMPLE_3D_RENDERER_H

#include <math.h> // Для математичних функцій (cos, sin)
#include <stdio.h> // Для printf (для тестування на ПК)
#include <DisplayConfig.h>
#define SCREEN_WIDTH 128 // Ширина екрану
#define SCREEN_HEIGHT 64 // Висота екрану
#include <drawAnimation.h>

#define PI 3.14159265359 // Значення числа Пі

struct Vec3D {
    float x, y, z;
};

struct Triangle {
    Vec3D vertices[3];
};
struct Mesh {
    Triangle* triangles;
    int triangleCount;
};
Vec3D shaftPoints[] = {
    {-0.2, -0.2, 0},
    {-0.2,  0.2, 0},
    { 0.2,  0.2, 0},
    { 0.2, -0.2, 0},
};

Triangle shaftMesh[] = {
    {{shaftPoints[0], shaftPoints[1], shaftPoints[2]}},
    {{shaftPoints[0], shaftPoints[2], shaftPoints[3]}}
};
Mesh rotatingShaft = { shaftMesh, 2 };

void projectLine(Vec3D v0, Vec3D v1, float scale, float distance) {
    int x0, y0, x1, y1;

    // Проєктуємо першу точку
    float factor0 = scale / (v0.z + distance);
    x0 = (int)(v0.x * factor0 + SCREEN_WIDTH / 2);
    y0 = (int)(v0.y * factor0 + SCREEN_HEIGHT / 2);

    // Проєктуємо другу точку
    float factor1 = scale / (v1.z + distance);
    x1 = (int)(v1.x * factor1 + SCREEN_WIDTH / 2);
    y1 = (int)(v1.y * factor1 + SCREEN_HEIGHT / 2);

    // Малюємо лінію між проєктованими точками
    u8g2.drawLine(x0, y0, x1, y1);
}

void rotateX(Vec3D &point, float angle) {
    float rad = angle * PI / 180;
    float y = point.y * cos(rad) - point.z * sin(rad);
    float z = point.y * sin(rad) + point.z * cos(rad);
    point.y = y;
    point.z = z;
}
void rotateY(Vec3D &point, float angle) {
    float rad = angle * PI / 180;
    float x = point.x * cos(rad) + point.z * sin(rad);
    float z = -point.x * sin(rad) + point.z * cos(rad);
    point.x = x;
    point.z = z;
}
void rotateZ(Vec3D &point, float angle) {
    float rad = angle * PI / 180;
    float x = point.x * cos(rad) - point.y * sin(rad);
    float y = point.x * sin(rad) + point.y * cos(rad);
    point.x = x;
    point.y = y;
}
void drawTriangle(Vec3D v0, Vec3D v1, Vec3D v2, float scale, float distance) {
    projectLine(v0, v1, scale, distance);
    projectLine(v1, v2, scale, distance);
    projectLine(v2, v0, scale, distance);
}

void generateSphereMesh(Triangle *outTriangles, int &count, int segments) {
    count = 0;
    for (int i = 0; i < segments; i++) {
        float theta1 = PI * i / segments;
        float theta2 = PI * (i + 1) / segments;

        for (int j = 0; j < segments * 2; j++) {
            float phi1 = 2 * PI * j / (segments * 2);
            float phi2 = 2 * PI * (j + 1) / (segments * 2);

            Vec3D p1 = { sin(theta1) * cos(phi1), cos(theta1), sin(theta1) * sin(phi1) };
            Vec3D p2 = { sin(theta2) * cos(phi1), cos(theta2), sin(theta2) * sin(phi1) };
            Vec3D p3 = { sin(theta2) * cos(phi2), cos(theta2), sin(theta2) * sin(phi2) };
            Vec3D p4 = { sin(theta1) * cos(phi2), cos(theta1), sin(theta1) * sin(phi2) };

            outTriangles[count++] = {{p1, p2, p3}};
            outTriangles[count++] = {{p1, p3, p4}};
        }
    }
}
Mesh createSphereMesh(int segments) {
    // Підрахунок кількості трикутників для заданої кількості сегментів
    int maxTriangles = 4 * segments * segments; // для меншої кількості трикутників
    Triangle* Triangles = (Triangle*)malloc(maxTriangles * sizeof(Triangle));  // Використовуємо malloc для динамічної пам'яті
    
    if (Triangles == nullptr) {
        Serial.println("Не вдалося виділити пам'ять для сітки");
        return Mesh{nullptr, 0}; // Якщо пам'ять не виділено, повертаємо порожній Mesh
    }

    Mesh sphereMesh;
    sphereMesh.triangleCount = 0;  // Початкове значення кількості трикутників

    // Генерація сітки сфери
    generateSphereMesh(Triangles, sphereMesh.triangleCount, segments);
    sphereMesh.triangles = Triangles;

    return sphereMesh;
}

void drawMesh(const Mesh& mesh, float angleX, float angleY, float angleZ, float scale = 40, float distance = 1.9) {
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    u8g2.setCursor(0, 10);
    u8g2.print("Triangles"); // Встановлюємо курсор для тексту
    u8g2.print(mesh.triangleCount); // Виводимо кількість трикутників на екран
    for (int i = 0; i < mesh.triangleCount; i++) {
        Triangle t = mesh.triangles[i];

        // Обертаємо вершини
        for (int j = 0; j < 3; j++) {
            rotateX(t.vertices[j], angleX);
            rotateY(t.vertices[j], angleY);
            rotateZ(t.vertices[j], angleZ);
        }

        drawTriangle(t.vertices[0], t.vertices[1], t.vertices[2], scale, distance);
    }
}




#endif // SIMPLE_3D_RENDERER_H
