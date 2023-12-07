#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/reflection_generated.h"
#include "flatbuffers/util.h"
#include "test_generated.h"
#include <iostream>
#include <fstream>

std::string loadSchema()
{
    std::string bfbsfile;

    flatbuffers::LoadFile("/xerg/src/mutator/buildHarness/test.bfbs", true, &bfbsfile);

    flatbuffers::Verifier verifier(
    reinterpret_cast<const uint8_t *>(bfbsfile.c_str()), bfbsfile.length());

    assert(reflection::VerifySchemaBuffer(verifier));

    return bfbsfile;
}

size_t afl_custom_fuzz(uint8_t **out_buf)
{
    uint8_t* outbuf = (uint8_t *)malloc(1544);
    std::string flatbuf = loadSchema();
    std::vector<uint8_t> bufferCopy(flatbuf.data(), flatbuf.data() + flatbuf.size());

    // Allocate memory on the heap
    std::copy(bufferCopy.begin(), bufferCopy.end(), outbuf);

    auto &schema = *reflection::GetSchema(outbuf);
    auto root_table = schema.root_table();
    auto flatobjs = schema.objects();
    auto fields = root_table->fields();
    auto hp_field_ptr = fields->LookupByKey("hp");
    auto &hp_field = *hp_field_ptr;

    // Copy data to the allocated memory
    auto &root = *flatbuffers::GetAnyRoot(outbuf);

    // Mutation
    flatbuffers::SetField<uint16_t>(&root, hp_field, 100);
    
    std::ofstream outputFile("debug.txt", std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1;
    }
    std::cout << "seg" << std::endl;
    *out_buf = outbuf;
    std::cout << "outbuf:" << reinterpret_cast<char*>(out_buf) <<std::endl;
    return sizeof(bufferCopy.size());
}

int main()
{
    uint8_t** out_buf;
    afl_custom_fuzz(out_buf);

    // std::ofstream outputFile("debug.txt", std::ios::trunc);

    // if (!outputFile.is_open()) {
    //     std::cerr << "Error: Unable to open the file." << std::endl;
    //     return 1;
    // }

    // outputFile.write(reinterpret_cast<char*>(*out_buf), 1544);


    // outputFile.close();
}

// std::string bfbsfile;

//     // std::vector<std::pair<std::string,reflection::BaseType>> attributeVec;

//     flatbuffers::LoadFile("test.bfbs",true, &bfbsfile);

//     auto &schema = *reflection::GetSchema(bfbsfile.c_str());
//     auto root_table = schema.root_table();

//     auto fields = root_table->fields();
//     auto hp_field_ptr = fields->LookupByKey("hp");
//     auto mana_field_ptr = fields->LookupByKey("mana");
//     auto &hp_field = *hp_field_ptr;

//     std::vector<uint8_t> bufferCopy(bfbsfile.data(), bfbsfile.data() + bfbsfile.size());
//     // Allocate memory on the heap
//     uint8_t *byteArray = new uint8_t[bufferCopy.size()];
//     std::copy(bufferCopy.begin(), bufferCopy.end(), byteArray);

//     // short test = 50;
//     // WriteToOffset(byteArray,hp_field_ptr->offset(), test);
//     auto &root = *flatbuffers::GetAnyRoot(byteArray);
//     short hp_testMutation = 50;
//     flatbuffers::SetField<short>(&root, hp_field, hp_testMutation);


//     std::cout << "bfbs size:" << bufferCopy.size() << std::endl;

//     std::cout << "offset:" << (size_t) hp_field_ptr->offset() << std::endl;

//     std::cout << "offset:" << (size_t) mana_field_ptr->offset() << std::endl;

//     auto &schemaAfter = *reflection::GetSchema(byteArray);
//     auto &rootAfter = *flatbuffers::GetAnyRoot(byteArray);
//     auto root_tableAfter = schemaAfter.root_table();
//     auto fieldsAfter = root_tableAfter->fields();
//     auto hp_field_ptrAfter = fieldsAfter->LookupByKey("hp");
//     auto &hp_fieldAfter = *hp_field_ptrAfter;

//     auto hpAfter = flatbuffers::GetFieldI<uint16_t>(rootAfter, hp_fieldAfter);

//     std::cout << "hp:" << hpAfter << std::endl; 