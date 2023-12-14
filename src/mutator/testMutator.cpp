#include "flatbuffers/reflection.h"
#include "flatbuffers/reflection_generated.h"
#include "flatbuffers/util.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/flatbuffers.h"
#include "test_generated.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <random>

#ifndef _FIXED_CHAR
#define _FIXED_CHAR 0x41
#endif

#define SCHEMA_FILE_PATH "SCHEMA_FILE_PATH"

std::mt19937 createGenerator(unsigned int seed) {
    return std::mt19937(seed);
}


bool getRandomBool(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(rng) == 0;
}


char getRandomByte(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 255);
    return static_cast<char>(distribution(rng));
}


unsigned char getRandomUByte(std::mt19937& rng) {
    std::uniform_int_distribution<int> distribution(0, 255);
    return static_cast<unsigned char>(distribution(rng));
}


short getRandomShort(std::mt19937& rng) {
    std::uniform_int_distribution<short> distribution(std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
    return distribution(rng);
}


unsigned short getRandomUShort(std::mt19937& rng) {
    std::uniform_int_distribution<unsigned short> distribution(0, std::numeric_limits<unsigned short>::max());
    return distribution(rng);
}


int getRandomInt(std::mt19937& rng) {
    return rng();
}


unsigned int getRandomUInt(std::mt19937& rng) {
    return rng();
}


long getRandomLong(std::mt19937& rng) {
    std::uniform_int_distribution<long> distribution(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
    return distribution(rng);
}


unsigned long getRandomULong(std::mt19937& rng) {
    std::uniform_int_distribution<unsigned long> distribution(0, std::numeric_limits<unsigned long>::max());
    return distribution(rng);
}


float getRandomFloat(std::mt19937& rng) {
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(rng);
}


double getRandomDouble(std::mt19937& rng) {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(rng);
}


std::string getRandomString(std::mt19937& rng, int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::uniform_int_distribution<int> distribution(0, sizeof(alphanum) - 2);

    std::string randomString;
    randomString.reserve(length);

    for (int i = 0; i < length; ++i) {
        randomString += alphanum[distribution(rng)];
    }

    return randomString;
}


std::vector<int> getRandomVector(std::mt19937& rng, int size) {
    std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::vector<int> randomVector;
    randomVector.reserve(size);

    for (int i = 0; i < size; ++i) {
        randomVector.push_back(distribution(rng));
    }

    return randomVector;
}


typedef struct flatbuffer_mutator
{

    std::string flatbuf = "";

    uint8_t *outbuf;

    unsigned int seed;

    std::vector<std::pair<std::string, reflection::BaseType>> attributeVec;

} flatbuffer_mutator_t;

// read flatbuffer scheam file
std::string loadSchema()
{

    std::string bfbsfile;

    flatbuffers::LoadFile("/xerg/src/mutator/buildHarness/test.bfbs", true, &bfbsfile);

    flatbuffers::Verifier verifier(
        reinterpret_cast<const uint8_t *>(bfbsfile.c_str()), bfbsfile.length());

    assert(reflection::VerifySchemaBuffer(verifier));

    return bfbsfile;
}

flatbuffer_mutator_t *init(unsigned int seed)
{
    srand(seed);
    flatbuffer_mutator_t *data = (flatbuffer_mutator_t *)calloc(1, sizeof(flatbuffer_mutator_t));
    if (!data)
    {

        perror("afl_custom_init alloc");
        return NULL;
    }

    data->flatbuf = loadSchema();

    auto &schema = *reflection::GetSchema(data->flatbuf.c_str());

    auto root_table = schema.root_table();

    auto flatobjs = schema.objects();

    for (auto it = flatobjs->begin(); it != flatobjs->end(); ++it)
    {

        for (auto atr = it->fields()->begin(); atr != it->fields()->end(); ++atr)
        {
            data->attributeVec.push_back(std::make_pair(atr->name()->str(), atr->type()->base_type()));
        }
    }

    if (data->flatbuf == "" || data->attributeVec.empty())
    {

        perror("afl_custom_init malloc");
        return NULL;
    }

    data->seed = seed;

    data->outbuf = (u_int8_t *)malloc(1544);

    return data;
}

size_t fuzz(flatbuffer_mutator_t *data, u_int8_t **out_buf)
{
    data->flatbuf = loadSchema();

    std::vector<uint8_t> resizingbuf(data->outbuf, data->outbuf + data->flatbuf.size() * sizeof(u_int8_t) );

    auto &schema = *reflection::GetSchema(data->outbuf);
    auto root_table = schema.root_table();
    auto flatobjs = schema.objects();
    auto fields = root_table->fields();

    auto &root = *flatbuffers::GetAnyRoot(data->outbuf);

    auto rroot = flatbuffers::piv(flatbuffers::GetAnyRoot(resizingbuf.data()),
                                resizingbuf);

    int vecLen = data->attributeVec.size();

    std::vector<bool> bitVector;

    bitVector.reserve(vecLen);

    std::uniform_int_distribution<int> distribution(0, 1);
    auto rng = std::mt19937(data->seed);

    for (int i = 0; i < vecLen; ++i)
    {
        bitVector.push_back(distribution(rng) == 1);
    }

    for (int i = 0; i < vecLen; i++)
    {
        if (bitVector[i])
        {
            // std::pair<std::string, reflection::BaseType>
            auto pair = data->attributeVec[i];
            std::string atrName = pair.first;
            reflection::BaseType type = pair.second;
            auto field_ptr = fields->LookupByKey(atrName.c_str());
            auto &field = *field_ptr;

            std::cout << "Set:" << atrName << "Type:" << type << std::endl;

            switch (type)
            {
            case reflection::BaseType::Bool:
                flatbuffers::SetField<bool>(*rroot, field, getRandomBool(rng));
                break;
            case reflection::BaseType::Byte:
                flatbuffers::SetField<u_int8_t>(*rroot, field, getRandomByte(rng));
                break;
            case reflection::BaseType::Short:
                flatbuffers::SetField<int16_t>(*rroot, field, getRandomShort(rng));
                break;
            case reflection::BaseType::UShort:
                flatbuffers::SetField<u_int16_t>(*rroot, field, getRandomUShort(rng));
                break;
            case reflection::BaseType::Int:
                flatbuffers::SetField<int32_t>(*rroot, field, getRandomInt(rng));
                break;
            case reflection::BaseType::UInt:
                flatbuffers::SetField<u_int32_t>(*rroot, field, getRandomUInt(rng));
                break;
            case reflection::BaseType::Long:
                flatbuffers::SetField<long>(*rroot, field, getRandomLong(rng));
                break;
            case reflection::BaseType::ULong:
                flatbuffers::SetField<u_long>(*rroot, field, getRandomULong(rng));
                break;
            case reflection::BaseType::Double:
                flatbuffers::SetField<double>(*rroot, field, getRandomDouble(rng));
                break;
            case reflection::BaseType::String:
                flatbuffers::SetString(schema, "hello", GetFieldS(**rroot, field),
            &resizingbuf);
                std::cout<< "setting name:" << GetFieldS(**rroot, field)->c_str() << std::endl;
                break;
            default:
                std::cout << "Unknown type!" << type << std::endl;
                break;
            }
        }
    }

    std::ofstream outputFile("outFlatbuf.bfbs", std::ios::trunc);

    if (!outputFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1;
    }

    *out_buf = resizingbuf.data();

    outputFile.write(reinterpret_cast<char *>(*out_buf), resizingbuf.size() * sizeof(u_int8_t));

    outputFile.close();

    return resizingbuf.size() * sizeof(u_int8_t);
}

/**
 * Deinitialize everything
 *
 * @param data The data ptr from afl_custom_init
 */
extern "C" void afl_custom_deinit(flatbuffer_mutator_t *data)
{

    free(data->outbuf);
    free(data);
}

// testing 
int main (int)

{
    u_int8_t** outbuf;
    flatbuffer_mutator_t mut =  *init(1);
    fuzz(&mut,outbuf);

    std::ifstream inputFile("debug.txt");

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        assert(false);
        // std::cerr << "Error: Unable to open the file '" << filePath << "'" << std::endl;
        return 1; // Return an error code
    }

    std::ostringstream fileContentStream;
    fileContentStream << inputFile.rdbuf();
    std::string fileContent = fileContentStream.str();

    auto monster = MyGame::GetMonster(fileContent.data());

    std::cout  << "hp:" << monster->hp() << std::endl;
    std::cout  << "name:" << monster->name()->c_str() << std::endl;
    std::cout  << "mana:" << monster->mana() << std::endl;

    inputFile.close();

}