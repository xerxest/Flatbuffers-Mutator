#include "BaseTypeMutator.h"
#include "flatbuffers/reflection_generated.h"
#include <iostream>
#include <vector>
#include <random>

std::mt19937 BaseTypeMutator::createGenerator(unsigned int seed) {
    return std::mt19937(seed);
}


bool BaseTypeMutator::getRandomBool(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(rng) == 0;
}


char BaseTypeMutator::getRandomByte(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 255);
    return static_cast<char>(distribution(rng));
}


unsigned char BaseTypeMutator::getRandomUByte(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 255);
    return static_cast<unsigned char>(distribution(rng));
}


short BaseTypeMutator::getRandomShort(std::mt19937& rng) {
    std::uniform_int_distribution<short> distribution(std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
    return distribution(rng);
}


unsigned short BaseTypeMutator::getRandomUShort(std::mt19937& rng) {
    std::uniform_int_distribution<unsigned short> distribution(0, std::numeric_limits<unsigned short>::max());
    return distribution(rng);
}


int BaseTypeMutator::getRandomInt(std::mt19937& rng) {
    return rng();
}


unsigned int BaseTypeMutator::getRandomUInt(std::mt19937& rng) {
    return rng();
}


long BaseTypeMutator::getRandomLong(std::mt19937& rng) {
    std::uniform_int_distribution<long> distribution(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
    return distribution(rng);
}


unsigned long BaseTypeMutator::getRandomULong(std::mt19937& rng) {
    std::uniform_int_distribution<unsigned long> distribution(0, std::numeric_limits<unsigned long>::max());
    return distribution(rng);
}


float BaseTypeMutator::getRandomFloat(std::mt19937& rng) {
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(rng);
}


double BaseTypeMutator::getRandomDouble(std::mt19937& rng) {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(rng);
}

std::string BaseTypeMutator::getRandomString(std::mt19937& rng) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::uniform_int_distribution<int> distribution(0, sizeof(alphanum) - 2);
    std::uniform_int_distribution<unsigned int> distLen(0, 1000);

    unsigned int length = distLen(rng);

    std::string randomString;
    randomString.reserve(length);

    for (int i = 0; i < length; ++i) {
        randomString += alphanum[distribution(rng)];
    }

    return randomString;
}

std::vector<int> BaseTypeMutator::getRandomVector(std::mt19937& rng, int size) {
    std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::vector<int> randomVector;
    randomVector.reserve(size);

    for (int i = 0; i < size; ++i) {
        randomVector.push_back(distribution(rng));
    }

    return randomVector;
}
