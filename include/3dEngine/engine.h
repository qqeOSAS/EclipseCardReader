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

#define NUM_STARS 600
#define ANALOG_SEED_PIN A0

Vec3D* stars = nullptr;

// Виділення пам'яті
void allocateStars(int numStars) {
    if (stars) delete[] stars; // Якщо вже виділено — звільнити
    stars = new Vec3D[numStars];
}

// Звільнення пам'яті
void freeStars() {
    if (stars) {
        delete[] stars;
        stars = nullptr;
    }
}

// Ініціалізація однієї зірки
void resetStar(int i) {
    stars[i].x = random(-64, 64);
    stars[i].y = random(-32, 32);
    stars[i].z = random(16, 64); // avoid too close to center
}

// Ініціалізація всіх зірок
void initStarfield() {
    for (int i = 0; i < NUM_STARS; i++) {
        resetStar(i);
    }
}

// Проєкція 3D-точки у 2D-координати екрану
void projectStar(const Vec3D star, int& sx, int& sy) {
    sx = (int)(star.x * 64 / star.z) + 64;
    sy = (int)(star.y * 32 / star.z) + 32;
}

// Малювання однієї зірки
void drawStarShape(int x, int y) {
    u8g2.drawPixel(x, y); // центр
  
}

// Оновлення позиції зірки (рух вперед)
void updateStar(int i) {
    stars[i].z -= 0.6;
    if (stars[i].z <= 1) {
        resetStar(i);
    }
}

const unsigned char epd_bitmap_Eclipse_logo_65x15 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xe1, 0x0f, 0x0f, 0x07, 0x1f, 0x78, 
	0xfe, 0x00, 0x06, 0x31, 0x18, 0x0d, 0xc5, 0x30, 0x4e, 0x83, 0x00, 0xfa, 0xd9, 0x37, 0x0d, 0x45, 
	0x67, 0x62, 0xfd, 0x00, 0x1a, 0x6c, 0x6c, 0x0d, 0x65, 0x49, 0x59, 0x0d, 0x00, 0x1a, 0x34, 0x48, 
	0x0d, 0x65, 0x59, 0x19, 0x0d, 0x00, 0xfa, 0x15, 0x78, 0x0d, 0x65, 0x5d, 0x33, 0xfd, 0x00, 0x02, 
	0x15, 0x00, 0x0d, 0x65, 0x65, 0x22, 0x81, 0x00, 0xfa, 0x15, 0x78, 0x0d, 0x65, 0x35, 0x4e, 0xfd, 
	0x00, 0x1a, 0x34, 0x48, 0x0d, 0x65, 0x1d, 0x4c, 0x0d, 0x00, 0x1a, 0x6c, 0x6c, 0x7d, 0x65, 0x81, 
	0x4c, 0x0d, 0x00, 0xfa, 0xd9, 0x37, 0x4d, 0x25, 0x81, 0x23, 0xfd, 0x00, 0x06, 0x31, 0x18, 0x41, 
	0x25, 0x81, 0x38, 0x83, 0x00, 0xfc, 0xe1, 0x0f, 0x7f, 0xe7, 0x81, 0x0f, 0xfe, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char epd_bitmap_cardreaded_logo_60x13 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x60, 0xcf, 0x67, 0x3c, 0xdf, 0x03, 
	0x26, 0x00, 0x60, 0xdb, 0x61, 0x6c, 0xc7, 0x06, 0x26, 0xe7, 0x78, 0xdb, 0xf1, 0x6c, 0xc7, 0x06, 
	0xa6, 0x6d, 0x6d, 0xdb, 0xf1, 0x6c, 0xc7, 0x06, 0x86, 0x6d, 0x6d, 0xcf, 0xb7, 0x6c, 0xdf, 0x03, 
	0x06, 0x6c, 0x6d, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 0x26, 0x6f, 0x6c, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 
	0xa6, 0x6d, 0x6c, 0xdb, 0xf1, 0x6c, 0xc7, 0x06, 0xa6, 0x6d, 0x6c, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 
	0xa6, 0x6d, 0x6c, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 0x3c, 0x6f, 0x78, 0xdb, 0x97, 0x3c, 0xdf, 0x06, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
AcceleratedBitmapData Eclipse_logo1 = {
    .end_x = 5,
    .end_y = 0,
    .start_x = -65,
    .start_y = 5,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 20,
    .max_y_speed = 0,
    .axis = 1,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
    .bitmap_width = 65,
    .bitmap_height = 15,
    .bitmap = epd_bitmap_Eclipse_logo_65x15
};

AcceleratedBitmapData cardreaded_logo = {
    .end_x = 25,
    .end_y = 0,
    .start_x = -65,
    .start_y = 23,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 25,
    .max_y_speed = 0,
    .axis = 1,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
    .bitmap_width = 60,
    .bitmap_height = 13,
    .bitmap = epd_bitmap_cardreaded_logo_60x13
};


AcceleratedTextData version_number = {
    .end_x = 0,
    .end_y = 35,
    .start_x = 90   ,
    .start_y = -30,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 20,
    .max_y_speed = 15,
    .axis = 2,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
};  
// Малювання всього зоряного поля
void drawStarfield() {
    u8g2.clearBuffer();
    
    static unsigned long start_time = millis();
    static unsigned long animation1_start_time = start_time + 2000;
    static long animation2_start_time = animation1_start_time + 700;
    static long animation3_start_time = animation2_start_time + 500;
    static bool animation1_started = false;
    static bool animation2_started = false;
    static bool animation3_started = false;
    static unsigned long contrast_timer = 0; // Uncomment if you have a third animation
    static unsigned long tmr_1 = 0;
    static unsigned long tmr_2 = 0;
    static unsigned long tmr_3 = 0;
    unsigned long current_time = millis();
    static int brightness = 0;


    if(current_time - contrast_timer >= 10 && !animation1_started) {
        contrast_timer = current_time;
        if(brightness < 255)
            brightness += 10;
        else
            brightness = 255; // Збільшуємо яскравість на 5
        Serial.print("Brightness: ");
        Serial.println(brightness);
    }
    u8g2.setContrast(brightness);

    if(current_time > animation1_start_time) {
        animation1_started = true;
    }
    if(current_time > animation2_start_time){
        animation2_started = true;
    }
    if(current_time > animation3_start_time){
       animation3_started = true; //animation3_started = true; // Uncomment if you have a third animation
    }
    draw_accelerated_bitmap(Eclipse_logo1, &current_time, &tmr_1, animation1_started);
    draw_accelerated_bitmap(cardreaded_logo, &current_time, &tmr_2, animation2_started);
    draw_accelerated_text("V.1.1.0",version_number, &current_time, &tmr_3, animation3_started);
    
    
    for (int i = 0; i < NUM_STARS; i++) {
        updateStar(i);
        if (stars[i].z <= 1) continue;

        int sx, sy;
        projectStar(stars[i], sx, sy);

        if (sx >= 0 && sx < 128 && sy >= 0 && sy < 64) {
            drawStarShape(sx, sy);
        }
    }

    u8g2.sendBuffer();
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
