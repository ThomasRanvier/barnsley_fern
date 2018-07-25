#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>

const int SCALE(75);

const float X_MIN(-2.182), X_MAX(2.6558), Y_MIN(0), Y_MAX(9.9983);

const float FRAME_WIDTH((abs(X_MIN) + X_MAX) * SCALE);
const float FRAME_HEIGHT((abs(Y_MIN) + Y_MAX) * SCALE);

const float INIT_X(abs(X_MIN) * SCALE);
const float INIT_Y(Y_MAX * SCALE);

const int NB_ITERATIONS(50000);

const float COEFFICIENTS[4][7] = {
        {0, 0, 0, 0.25, 0, -0.4, 0.02},
        {0.95, 0.005, -0.005, 0.93, -0.002, 0.5, 0.84},
        {0.035, -0.2, 0.16, 0.04, -0.09, 0.02, 0.07},
        {-0.04, 0.2, 0.16, 0.04, 0.083, 0.12, 0.07}
};

/**
const float COEFFICIENTS[4][7] = {
        {0, 0, 0, 0.16, 0, 0, 0.01},
        {0.85, 0.04, -0.04, 0.85, 0, 1.60, 0.85},
        {0.20, -0.26, 0.23, 0.22, 0, 1.60, 0.07},
        {-0.15, 0.28, 0.26, 0.24, 0, 0.44, 0.07}
};
**/

void updatePosition(float *, float *);

int main() {
    sf::RenderWindow window(sf::VideoMode(FRAME_WIDTH, FRAME_HEIGHT), "sfml_barnsley_fern");

    srand(time(NULL));

    float x(INIT_X), y(INIT_Y);

    for (int i(0); i < NB_ITERATIONS; i++) {
        updatePosition(&x, &y);

        sf::RectangleShape cell(sf::Vector2f(1, 1));
        cell.setFillColor(sf::Color::White);
        cell.setPosition(INIT_X + x * SCALE, INIT_Y - y * SCALE);
        std::cout << x << " " << y << std::endl;
        window.draw(cell);
    }
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

void updatePosition(float * x, float * y) {
    int proba(1 + (rand() % 100));

    float old_x = *x;
    float old_y = *y;

    int total_proba(0);
    bool updated(false);

    for (int i(0); i < 4; i++) {
        if (!updated && proba <= (total_proba += COEFFICIENTS[i][6] * 100)) {
            *x = COEFFICIENTS[i][0] * old_x + COEFFICIENTS[i][1] * old_y + COEFFICIENTS[i][4];
            *y = COEFFICIENTS[i][2] * old_x + COEFFICIENTS[i][3] * old_y + COEFFICIENTS[i][5];
            updated = true;
        }
    }
}