#include "afl_mutator.h"
#include <random>
#include <algorithm>
#include "flatbuffers/flatbuffers.h"
#include "test_schema_generated.h" // Include the generated Flatbuffer code for the TestSchema

namespace flatbuffer_mutator {
namespace aflplusplus {
namespace {

// Define a function to get random values specific to your needs.
size_t GetRandom(size_t s) {
    static std::default_random_engine generator(s);
    std::uniform_int_distribution<size_t> uniform_dist(1, 10);
    return uniform_dist(generator);
}

// Generate a random integer ID.
int GenerateRandomId() {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000);
    return distribution(generator);
}

// Generate a random string of a given length.
std::string GenerateRandomString(size_t length) {
    static std::default_random_engine generator;
    static const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string random_string;
    random_string.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        random_string += charset[generator() % (sizeof(charset) - 1)];
    }
    return random_string;
}

// Generate a random vector of unsigned bytes (data).
std::vector<uint8_t> GenerateRandomData(size_t size) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<uint8_t> distribution(0, 255);

    std::vector<uint8_t> data;
    data.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        data.push_back(distribution(generator));
    }
    return data;
}

// Merge two strings (e.g., for 'name' field).
std::string MergeStrings(const std::string& str1, const std::string& str2) {
    // Implement your merging logic here.
    // For simplicity, we concatenate the strings.
    return str1 + str2;
}

// Merge two data vectors (e.g., for 'data' field).
std::vector<uint8_t> MergeData(const std::vector<uint8_t>& data1, const std::vector<uint8_t>& data2) {
    // Implement your merging logic here.
    // For simplicity, we concatenate the data vectors.
    std::vector<uint8_t> merged_data = data1;
    merged_data.insert(merged_data.end(), data2.begin(), data2.end());
    return merged_data;
}

} // namespace

size_t A_CustomFlatbufferMutator(MutateHelper* m, bool binary, unsigned char* buf, size_t buf_size,
                                 unsigned char** out_buf, unsigned char* add_buf,
                                 size_t add_buf_size, size_t max_size) {
    const flatbuffers::uint8_t* existing_data = reinterpret_cast<const flatbuffers::uint8_t*>(buf);

    if (binary) {
        flatbuffers::Verifier verifier(existing_data, buf_size);
        if (!TestSchema::VerifyTestObjectBuffer(verifier)) {
            // TODO: Handle invalid 'existing_data'.
            return 0;
        }
    }

    const TestSchema::TestObject* existing_object =
        flatbuffers::GetRoot<TestSchema::TestObject>(existing_data);

    switch (GetRandom(m->GetSeed())) {
        case 1:
        case 2: {
            // TODO: Implement mutation logic for Flatbuffers.
            
            // Mutate the 'id' field with a random integer value.
            int new_id = GenerateRandomId();
            existing_object->mutate_id(new_id);

            // Mutate the 'name' field with a random string.
            std::string new_name = GenerateRandomString(10); // Adjust the length as needed.
            existing_object->mutate_name(new_name.c_str());

            // Mutate the 'data' field with random byte values.
            std::vector<uint8_t> new_data = GenerateRandomData(5); // Adjust the size as needed.
            existing_object->mutate_data(&new_data);

            flatbuffers::FlatBufferBuilder fbb;
            fbb.Finish(existing_object->Pack(fbb));
            const uint8_t* serialized_data = fbb.GetBufferPointer();
            size_t serialized_size = fbb.GetSize();

            if (serialized_size <= max_size) {
                memcpy(m->ReallocBuf(serialized_size), serialized_data, serialized_size);
                return serialized_size;
            } else {
                // TODO: Handle the case where the mutation exceeds 'max_size'.
                return 0;
            }
            
            break;
        }
        default: {
            // TODO: Implement crossover logic for Flatbuffers.

            // Ensure that 'add_buf' is a valid Flatbuffer.
            flatbuffers::Verifier add_buf_verifier(reinterpret_cast<const flatbuffers::uint8_t*>(add_buf), add_buf_size);
            if (binary && !TestSchema::VerifyTestObjectBuffer(add_buf_verifier)) {
                // TODO: Handle invalid 'add_buf' data.
                return 0;
            }

            // Parse 'add_buf' to access its data.
            const TestSchema::TestObject* add_object =
                flatbuffers::GetRoot<TestSchema::TestObject>(reinterpret_cast<const flatbuffers::uint8_t*>(add_buf));

            // Merge fields from 'existing_object' and 'add_object' into a new 'merged_object'.
            TestSchema::TestObjectBuilder builder(fbb);
            int merged_id = existing_object->id() + add_object->id();
            builder.add_id(merged_id);
            
            std::string merged_name = MergeStrings(existing_object->name(), add_object->name());
            builder.add_name(merged_name.c_str());

            // Merge the 'data' fields (vector of unsigned bytes) as needed.
            std::vector<uint8_t> merged_data = MergeData(existing_object->data(), add_object->data());
            builder.add_data(fbb.CreateVector(merged_data));

            fbb.Finish(builder.Finish());
            const uint8_t* serialized_data = fbb.GetBufferPointer();
            size_t serialized_size = fbb.GetSize();

            if (serialized_size <= max_size) {
                memcpy(m->ReallocBuf(serialized_size), serialized_data, serialized_size);
                return serialized_size;
            } else {
                // Mutation exceeds 'max_size', truncate it to fit.
        size_t truncated_size = std::min(serialized_size, max_size);
        memcpy(m->ReallocBuf(truncated_size), serialized_data, truncated_size);
        return truncated_size;
            }
            
            break;
        }
    }

    // TODO: Handle any other unexpected error scenarios here.
    
    *out_buf = m->GetOutBuf();
    return m->GetLen();
}

} // aflplusplus
} // flatbuffer_mutator
