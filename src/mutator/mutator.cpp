#include "afl-fuzz.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/reflection_generated.h"
#include "flatbuffers/util.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/flatbuffers.h"
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
    auto hp_field_ptr = fields->LookupByKey("hp");
    auto &hp_field = *hp_field_ptr;

    // Copy data to the allocated memory
    auto &root = *flatbuffers::GetAnyRoot(data->outbuf);

    int16_t num = rand() % 1000;
    flatbuffers::SetField<int16_t>(&root, hp_field, num);
    
    std::ofstream outputFile("debug.txt", std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1;
    }

    *out_buf = data->outbuf;

    // outputFile << hp_testMutation << std::endl;
    outputFile.write(reinterpret_cast<char*>(*out_buf), 1544);

    outputFile.close();

    return sizeof(bufferCopy.size());
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