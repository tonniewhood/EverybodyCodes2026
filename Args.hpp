
#pragma once

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief A class that contains the arguments used for a given iteration
 */
class Args {

public:

    /**
     * @brief Determines the quest that's being run, the part number, and if it's a test or not
     *        via the command line arguments
     * 
     * @param argc - The number of input arguments
     * @param argv - The input arguments
     * 
     * @return The Args object
     * 
     * @throws std::invalid_argument If the requested quest isn't found
     */
    Args(int argc, char *argv[]);
    ~Args() {};

    uint8_t m_questNum;
    uint8_t m_partNum;
    bool m_test;

private:
    void determineQuest(std::string &questArg);
    void determinePart(std::string &partArg);
    std::vector<std::string> determineTest(std::vector<std::string> &argc);
}; 
