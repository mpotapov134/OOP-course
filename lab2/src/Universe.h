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
    int m_iteration_number;
    static int m_width;
    static int m_height;
    char* m_field;

    void FillField(std::set<std::pair<int, int>> coords);

    int GetNumOfNeighbours(int x, int y);

    public:

    static std::string default_name;
    static std::set<int> default_b_rule;
    static std::set<int> default_s_rule;

    /**
     * @brief Constructs the universe.
     * @param name name of the universe.
     * @param b_rule birth rule - number of alive nearby cells required for the
     * birth of a new cell; {3} by default.
     * @param s_rule survival rule - number of alive nearby cells required for
     * the survival of the current alive cell; {2, 3} by default.
     * @param coords set of coordinates of alive cells.
    */
    Universe(std::string name, std::set<int> b_rule, std::set<int> s_rule,
        std::set<std::pair<int, int>> coords);

    ~Universe();

    /// @brief Calculates the next state of the universe.
    void Tick();

    /// @brief Prints the field of the universe to the console.
    void PrintUniverse();

    /// @return The name of the universe.
    std::string name();

    /// @return The set of birth rules of the universe.
    std::set<int> birth_rule();

    /// @return The set of survival rules of the universe.
    std::set<int> survival_rule();

    /// @return Set of coordinates of alive cells.
    std::set<std::pair<int, int>> coords();
};

#endif
