
#include <iostream>
#include <stdexcept>

#include "Args.hpp"
#include "q1/quest.hpp"

enum QuestType {
    ALL,
    Q1,
};

int main(int argc, char **argv) {

    try {

        Args args(argc, argv);
        switch (args.m_questNum)
        {
        case QuestType::ALL:
        case QuestType::Q1:
    
            q1::quest(args.m_partNum, args.m_test);
            if (args.m_questNum != QuestType::ALL) break;
        }

    } catch (std::invalid_argument &e) {
        std::cerr << "Could not find quest (" << e.what() << ")" << std::endl;
        return 1;
    }


    return 0;

}