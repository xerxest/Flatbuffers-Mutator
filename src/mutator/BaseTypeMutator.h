#ifndef BASE_TYPE_MUTATOR_H
#define BASE_TYPE_MUTATOR_H

#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <string>

/*
This class is for demonstration/testing purposes only. Please override the function with an appropriate mutator, such as libfuzzer.
*/

class BaseTypeMutator {
public:
    static std::mt19937 createGenerator(unsigned int seed);

    static bool getRandomBool(std::mt19937& rng); 
    static char getRandomByte(std::mt19937& rng);
    static unsigned char getRandomUByte(std::mt19937& rng);
    static short getRandomShort(std::mt19937& rng);
    static unsigned short getRandomUShort(std::mt19937& rng);
    static int getRandomInt(std::mt19937& rng);
    static unsigned int getRandomUInt(std::mt19937& rng);
    static long getRandomLong(std::mt19937& rng);
    static unsigned long getRandomULong(std::mt19937& rng);
    static float getRandomFloat(std::mt19937& rng);
    static double getRandomDouble(std::mt19937& rng);
    static std::string getRandomString(std::mt19937& rng);
    static std::vector<int> getRandomVector(std::mt19937& rng, int size);
};

#endif // BASE_TYPE_MUTATOR_H