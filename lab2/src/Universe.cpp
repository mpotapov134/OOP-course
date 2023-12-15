#include <iostream>
#include "Universe.h"

static int mod(int dividend, int divisor) {
    while (dividend < 0) dividend += divisor;
    return dividend % divisor;
}


int Universe::m_width = 100;
int Universe::m_height = 20;

void Universe::FillField(std::set<std::pair<int, int>> coords) {
    for (int i = 0; i < m_width * m_height; i++) {
        m_field[i] = 0;
    }

    for (const auto& x_y : coords) {
        int x = mod(x_y.first, m_width);
        int y = mod(x_y.second, m_height);
        m_field[y * m_width + x] = 1;
    }
}

int Universe::GetNumOfNeighbours(int x, int y) {
    int num_of_neighbours = 0;
    for (int shift_x = -1; shift_x <= 1; shift_x++) {
        for (int shift_y = -1; shift_y <= 1; shift_y++) {
            if (shift_x == 0 && shift_y == 0) continue;
            int neighbour_x = mod(x + shift_x, m_width);
            int neighbour_y = mod(y + shift_y, m_height);
            num_of_neighbours += m_field[neighbour_y * m_width + neighbour_x];
        }
    }
    return num_of_neighbours;
}

Universe::Universe(std::string name, std::set<int> b_rule,
        std::set<int> s_rule, std::set<std::pair<int, int>> coords)
        : m_name(name), m_birth_rule(b_rule), m_survival_rule(s_rule) {
    m_field = new char[m_width * m_height];
    FillField(coords);
}

Universe::~Universe() {
    delete[] m_field;
}

void Universe::Tick() {
    char* new_field = new char[m_width * m_height];
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            int num_of_neighbours = GetNumOfNeighbours(x, y);
            if (m_field[y * m_width + x] == 0) { // Current cell is not alive
                if (m_birth_rule.contains(num_of_neighbours)) {
                    new_field[y * m_width + x] = 1;
                }
                else {
                    new_field[y * m_width + x] = 0;
                }
            }

            else { // Current cell is alive
                if (m_survival_rule.contains(num_of_neighbours)) {
                    new_field[y * m_width + x] = 1;
                }
                else {
                    new_field[y * m_width + x] = 0;
                }
            }
        }
    }

    delete[] m_field;
    m_field = new_field;
}

void Universe::PrintUniverse() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (m_field[y * m_width + x] == 1) {
                std::cout << '*';
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }
}
