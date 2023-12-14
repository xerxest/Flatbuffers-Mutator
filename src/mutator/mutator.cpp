#include "afl-fuzz.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/reflection_generated.h"
#include "flatbuffers/util.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/flatbuffers.h"
#include "BaseTypeMutator.h"
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

typedef struct flatbuffer_mutator
{

    afl_state_t *afl;

    std::string flatbuf = "";

    uint8_t *outbuf;

    unsigned int seed;

    std::vector<std::pair<std::string, reflection::BaseType>> attributeVec;

} flatbuffer_mutator_t;


std::string loadSchema()
{

    std::string bfbsfile;

    flatbuffers::LoadFile("test.bfbs", true, &bfbsfile);

    flatbuffers::Verifier verifier(
        reinterpret_cast<const uint8_t *>(bfbsfile.c_str()), bfbsfile.length());

    assert(reflection::VerifySchemaBuffer(verifier));

    return bfbsfile;
}

extern "C" flatbuffer_mutator_t *afl_custom_init(afl_state_t *afl, unsigned int seed)
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

    data->outbuf = (u8 *)malloc(1544);

    data->seed = seed;

    data->afl = afl;

    return data;
}

extern "C" size_t afl_custom_fuzz(flatbuffer_mutator_t *data, uint8_t *buf, size_t buf_size,
                                  u8 **out_buf, uint8_t *add_buf,
                                  size_t add_buf_size, // add_buf can be NULL
                                  size_t max_size)
{
    data->flatbuf = loadSchema();

    std::vector<uint8_t> bufferCopy(data->flatbuf.data(), data->flatbuf.data() + data->flatbuf.size());

    // Allocate memory on the heap
    std::copy(bufferCopy.begin(), bufferCopy.end(), data->outbuf);

    auto &schema = *reflection::GetSchema(data->outbuf);
    auto root_table = schema.root_table();
    auto flatobjs = schema.objects();
    auto fields = root_table->fields();

    std::vector<uint8_t> resizingbuf(data->outbuf, data->outbuf + bufferCopy.size() * sizeof(u_int8_t) );

    auto &root = *flatbuffers::GetAnyRoot(data->outbuf);

    auto rroot = flatbuffers::piv(flatbuffers::GetAnyRoot(resizingbuf.data()),
                                resizingbuf);

    int vecLen = data->attributeVec.size();

    std::vector<bool> bitVector;

    bitVector.reserve(vecLen);

    data->seed = data->seed + 1;

    std::uniform_int_distribution<int> distribution(0, 1);
    auto rng = std::mt19937(data->seed);

    for (int i = 0; i < vecLen; ++i)
    {
        bitVector.push_back(distribution(rng) == 1);
    }

    // TODO prevent re-mutating the same bit vec
    for (int i = 0; i < vecLen; i++)
    {
        if (bitVector[i])
        {
        
            auto pair = data->attributeVec[i];
            std::string atrName = pair.first;
            reflection::BaseType type = pair.second;
            auto field_ptr = fields->LookupByKey(atrName.c_str());
            auto &field = *field_ptr;

            switch (type)
            {
            case reflection::BaseType::Bool:
                flatbuffers::SetField<bool>(*rroot, field, BaseTypeMutator::getRandomBool(rng));
                break;
            case reflection::BaseType::Byte:
                flatbuffers::SetField<u8>(*rroot, field, BaseTypeMutator::getRandomByte(rng));
                break;
            case reflection::BaseType::Short:
                flatbuffers::SetField<int16_t>(*rroot, field, BaseTypeMutator::getRandomShort(rng));
                break;
            case reflection::BaseType::UShort:
                flatbuffers::SetField<u_int16_t>(*rroot, field, BaseTypeMutator::getRandomUShort(rng));
                break;
            case reflection::BaseType::Int:
                flatbuffers::SetField<int32_t>(*rroot, field, BaseTypeMutator::getRandomInt(rng));
                break;
            case reflection::BaseType::UInt:
                flatbuffers::SetField<u_int32_t>(*rroot, field, BaseTypeMutator::getRandomUInt(rng));
                break;
            case reflection::BaseType::Long:
                flatbuffers::SetField<long>(*rroot, field, BaseTypeMutator::getRandomLong(rng));
                break;
            case reflection::BaseType::ULong:
                flatbuffers::SetField<u_long>(*rroot, field, BaseTypeMutator::getRandomULong(rng));
                break;
            case reflection::BaseType::Double:
                flatbuffers::SetField<double>(*rroot, field, BaseTypeMutator::getRandomDouble(rng));
                break;
            case reflection::BaseType::String:
                flatbuffers::SetString(schema, BaseTypeMutator::getRandomString(rng).c_str(), GetFieldS(**rroot, field),
                &resizingbuf);
                break;
            default:
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