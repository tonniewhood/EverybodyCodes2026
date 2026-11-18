
#include <cmath>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <functional>
#include <iostream>

#include "quest.hpp"


/**
 * @brief determines the distance to the next square of a given digit
 * 
 * @param digit - The digit to compute
 * 
 * @return The distance to the next square
 */
uint32_t distanceToSquare(float digit) {
    float sqrt_val = std::sqrt(digit);
    uint32_t raised = static_cast<uint32_t>(std::ceil(sqrt_val));
    return (raised * raised) - static_cast<uint32_t>(digit);
}

/**
 * @brief Determines the distance to the next hightest multiple of 4. Has the caviat that any number less than 
 *        4 HAS to go to 8 since that's the smallest value a square with an internal can have
 * 
 * @param digit - The digit to compute
 * 
 * @return The distnace to the next highest multiple of 4
 */
uint32_t distanceToNextMul4(float digit) {
    uint32_t intDigit = static_cast<uint32_t>(digit);
    return intDigit > 4 ? (4 - (intDigit % 4)) % 4 : 8 - intDigit;
}

/**
 * @brief Determines the distance to the next odd square of a given digit. Has the caviat that 3 is the smallest
 *        odd square that can be used here.
 * 
 * @param digit - The digit to compute
 * 
 * @return The distance to the next odd square of a givin digit
 */
uint32_t distanceToNextOddSquare(float digit) {
    float sqrt_val = std::sqrt(digit);
    float ceil_val = std::ceil(sqrt_val);

    // If the ceiling is the same (within tolerance), it's already a perfect square, so add 1 since it's own size
    // wont be enough
    if (ceil_val - sqrt_val < q1::EPSILON) {
        ceil_val += 1.0f;
    }

    uint32_t raised = std::max(static_cast<uint32_t>(ceil_val), uint32_t{3});
    raised += (1 - raised % 2); // Make the number odd if not already;
    return (raised * raised) - static_cast<uint32_t>(digit) - 1;
}

/**
 * @brief Takes in a buffer of characters, and splits them on a comma to determine the numbered values
 * 
 * @param currentNum - Any digit characters previously collected but not yet used
 * @param f_buf - The buffer of input characters
 * @param currentSum - A reference to the current sum. Is modified by the function
 * @param accumulationFunc - The function used to determine how much to accumulate
 * 
 * @throws std::length_error - If the digit is found to be larger than the max number of bits, the function
 *                             will throw
 */
void extractValues(char currentNum[q1::MAX_NUM_DIGITS], char f_buf[q1::CHUNK_SIZE], uint32_t &currentSum, std::function<uint32_t(float)> accumulationFunc) {

    size_t currentDigitSize = std::strlen(currentNum);
    for (size_t i = 0; i < q1::CHUNK_SIZE; i++) {
        // If we see a 0, we can just bail out
        switch (f_buf[i])
        {
        case 0: 
            currentSum += accumulationFunc(std::atof(currentNum));
            // std::cout << currentNum << " - " << accumulationFunc(std::atof(currentNum)) << " (" << currentSum << ")\n";
            return;

        case ',': 
            currentSum += accumulationFunc(std::atof(currentNum));
            // std::cout << currentNum << " - " << accumulationFunc(std::atof(currentNum)) << " (" << currentSum << ")\n";
            currentDigitSize = 0;
            std::memset(currentNum, 0, q1::MAX_NUM_DIGITS + 1);
            break;

        default:

            if (currentDigitSize + 1 > q1::MAX_NUM_DIGITS) {
                throw std::length_error("Digits exceed buffer length");
            }
            currentNum[currentDigitSize] = f_buf[i];
            currentDigitSize++;
            
        }
    }

}

/**
 * @brief Runs part1 on of the quest
 */
void runPart(const std::string_view filename, std::function<uint32_t(float)> accumulationFunc) {

    std::fstream inputFile(filename.data());
    if (!inputFile.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    char currentNum[q1::MAX_NUM_DIGITS + 1] = {0};
    uint32_t currentSum = 0;
    do {
        char f_buf[q1::CHUNK_SIZE + 1] = {0};
        inputFile.read(f_buf, q1::CHUNK_SIZE);

        try {
            extractValues(currentNum, f_buf, currentSum, accumulationFunc);
        } catch (std::length_error &e) {
            std::cerr << "Could not parse file '" << filename << "': " << e.what() << std::endl;
            return;
        }

    } while (!inputFile.eof());

    std::cout << "\tFound sum: " << currentSum << "\n" << std::endl;
}


void q1::quest(uint8_t part, bool isTest) {

    std::cout << "Calling quest 1" << std::endl;

    switch (part) {
        case 0:
        case 1:
            std::cout << "Running part 1\n";
            runPart(!isTest ? q1::P1_FILENAME : q1::TEST_FILENAME, distanceToSquare);
            if (part == 1) break;
        case 2:
            std::cout << "Running part 2\n";
            runPart(!isTest ? q1::P2_FILENAME : q1::TEST_FILENAME, distanceToNextMul4);
            if (part == 2) break;
        case 3:
            std::cout << "Running part 3\n";
            runPart(!isTest ? q1::P3_FILENAME : q1::TEST_FILENAME, distanceToNextOddSquare);
            if (part == 3) break;
        default:
            std::cerr << "Invalid part chosen" << std::endl;
    }

}