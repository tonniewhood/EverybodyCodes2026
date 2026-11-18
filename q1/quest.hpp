
#pragma once

namespace q1 {

    inline constexpr std::string_view P1_FILENAME = "q1/pinecones1.txt";
    inline constexpr std::string_view P2_FILENAME = "q1/pinecones2.txt";
    inline constexpr std::string_view P3_FILENAME = "q1/pinecones3.txt";
    inline constexpr std::string_view TEST_FILENAME = "q1/test.txt";
    inline constexpr size_t CHUNK_SIZE = 512;
    inline constexpr size_t MAX_NUM_DIGITS = 10;
    inline constexpr float EPSILON = 1e-6;

    /**
     * @brief Runs the first quest found at https://everybody.codes/event/2026/quests/1
     * 
     * @param part - The part being run (0 for all)
     * @param isTest - Whether or not the test file should be used
     */
    void quest(uint8_t part, bool isTest);
}