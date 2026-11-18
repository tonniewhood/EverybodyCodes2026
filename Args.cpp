
#include "Args.hpp"

#include <iostream>
#include <regex>
#include <stdexcept>

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
Args::Args(int argc, char *argv[]) {

    if (argc < 2) {
        throw std::invalid_argument("A quest number must be input as an argument");
    }

    std::vector<std::string> strVec;
    for (size_t i = 1; i < argc; i++) {
        strVec.push_back(std::string(argv[i]));
    }

    strVec = determineTest(strVec);
    determineQuest(strVec[0]);
    determinePart(strVec[1]);

}

/**
 * @brief Goes through the arguments and looks for the test flag. If present, the flag is set in the class and
 *        the element is removed from the vector
 * 
 * @param strVec - The vector containing the arguments
 * 
 * @return The bool determining if the test is there or not
 */
std::vector<std::string> Args::determineTest(std::vector<std::string> &strVec) {

    std::vector<std::string> outVec;
    for (const auto& val: strVec) {
        if (val == "-t" || val == "--test") {
            m_test = true;
        } else {
            outVec.push_back(val);
        }
    }

    return outVec;
}

/**
 * @brief Goes through the quest argument and determines which one it is
 * 
 * @param questStr - The argument related to the quest
 */
void Args::determineQuest(std::string &questStr){

    if (questStr == "-a" || questStr == "--all") {
        m_questNum = 0;
        return; // All quests
    }

    static const std::regex questPattern(R"((?:q|quest)?(\d+))");
    std::cmatch match;
    if (!std::regex_match(questStr.c_str(), match, questPattern)) {
        throw std::invalid_argument("Unrecognized quest: " + questStr);
    }

    m_questNum = std::stoi(match[1].str());
}

/**
 * @brief Goes through the part argument and determines which one it is
 * 
 * @param partStr - The argument related to the part
 */
void Args::determinePart(std::string &partStr) {

    static const std::regex questPattern(R"((?:p|part)?(\d+))");
    std::cmatch match;
    if (!std::regex_match(partStr.c_str(), match, questPattern)) {
        throw std::invalid_argument("Unrecognized part: " + partStr);
    }

    m_partNum = std::stoi(match[1].str());

}
