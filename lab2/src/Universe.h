#ifndef UNIVERSE_H_INCLUDED
#define UNIVERSE_H_INCLUDED

#include <string>
#include <set>
#include <utility>

/// @brief Class repesenting the world of Game of Life.
class Universe {
    std::string m_name;
    std::set<int> m_birth_rule;
    std::set<int> m_survival_rule;
    static int m_width;
    static int m_height;
    char* m_field;

    void FillField(std::set<std::pair<int, int>> coords);

    int GetNumOfNeighbours(int x, int y);

    public:

    /**
     * @brief Constructs the universe.
     * @param name name of the universe.
     * @param b_rule birth rule - number of alive nearby cells required for the
     * birth of a new cell; {3} by default.
     * @param s_rule survival rule - number of alive nearby cells required for
     * the survival of the current alive cell; {2, 3} by default.
     * @param coords set of coordinates of alive cells.
    */
    Universe(std::string name="Universe", std::set<int> b_rule={3},
        std::set<int> s_rule={2, 3}, std::set<std::pair<int, int>> coords={});

    ~Universe();

    /// @brief Calculates the next state of the universe.
    void Tick();

    /// @brief Prints the field of the universe to the console.
    void PrintUniverse();
};

#endif
