// Updated afl_mutate.h

// ... (Previous header comments and includes)

#ifndef AFLPLUSPLUS_FLATBUFFER_MUTATOR_SRC_AFL_MUTATE_H_
#define AFLPLUSPLUS_FLATBUFFER_MUTATOR_SRC_AFL_MUTATE_H_

#include <stddef.h>
#include <iostream>
#include <cstdint>
#include <type_traits>
#include <functional>

#include "Fuzzer/FuzzerDefs.h"
#include "Fuzzer/FuzzerRandom.h"
#include "Fuzzer/FuzzerMutate.h"
#include "Fuzzer/FuzzerInternal.h"
#include "Fuzzer/FuzzerCorpus.h"
#include "Fuzzer/FuzzerExtFunctions.h"


// Defines custom mutator, crossover, and test functions using default
// serialization format. Default is text.
#define DEFINE_AFL_FLATBUFFER_FUZZER(args...) DEFINE_AFL_TEXT_FLATBUFFER_FUZZER(args)
// Defines custom mutator, crossover, and test functions using text
// serialization. This format is more convenient to read.
#define DEFINE_AFL_TEXT_FLATBUFFER_FUZZER(args...) DEFINE_AFL_FLATBUFFER_FUZZER_IMPL(false, args)
// Defines custom mutator, crossover, and test functions using binary
// serialization. This makes mutations faster. However, often the test function is
// significantly slower than the mutator, so fuzzing rate may stay unchanged.
#define DEFINE_AFL_BINARY_FLATBUFFER_FUZZER(args...) DEFINE_AFL_FLATBUFFER_FUZZER_IMPL(true, args)

// Initialize this custom mutator.
#define DEFINE_AFL_CUSTOM_INIT                                  \
  extern "C" MutateHelper *afl_custom_init(void *afl, unsigned int s) { \
      using namespace fuzzer;                                      \
      MutateHelper *mutate_helper = new MutateHelper(s);           \
      auto seed = Random(s);                                       \
      FuzzingOptions Options;                                      \
      std::unique_ptr<ExternalFunctions> t(new ExternalFunctions()); \
      EF = t.get();                                                \
      auto *MD = new MutationDispatcher(seed, Options);            \
      static auto *Corpus = new InputCorpus("");                   \
      auto *F = new Fuzzer((UserCallback)nullptr, *Corpus, *MD, Options); \
      return mutate_helper;                                        \
  } 

// Deinitialize everything.
#define DEFINE_AFL_CUSTOM_DEINIT                          \
  extern "C" void afl_custom_deinit(MutateHelper *m) {    \
      delete m;                                           \
  }

// Implementation of macros above.
#define DEFINE_AFL_CUSTOM_FLATBUFFER_MUTATOR_IMPL(use_binary, FlatbufferType)       \
  extern "C" size_t afl_custom_fuzz(                                                  \
      MutateHelper *m, unsigned char *buf, size_t buf_size, unsigned char **out_buf,  \
      unsigned char *add_buf, size_t add_buf_size, size_t max_size) {                 \
      FlatbufferType input1;                                                          \
      FlatbufferType input2;                                                          \
      return A_CustomFlatbufferMutator(m, use_binary, buf, buf_size, out_buf,         \
                                       add_buf, add_buf_size, max_size,               \
                                       &input1, &input2);                             \
  }

// A post-processing function to use right before AFL++ writes the test case to
// disk in order to execute the target.
#define DEFINE_AFL_CUSTOM_FLATBUFFER_POST_PROCESS_IMPL(use_binary, FlatbufferType)          \
  extern "C" size_t afl_custom_post_process(                                                  \
      MutateHelper *m, unsigned char *buf, size_t buf_size, unsigned char **out_buf) {        \
      using flatbuffer_mutator::libfuzzer::LoadFlatbufferInput;                                \
      FlatbufferType input;                                                                  \
      if (LoadFlatbufferInput(use_binary, buf, buf_size, &input))                             \
        return FlatbufferToDataHelper(input, out_buf);                                       \
      return 0;                                                                               \
  }

#define DEFINE_AFL_FLATBUFFER_FUZZER_IMPL(use_binary, args...)                               \
  static size_t FlatbufferToDataHelper(args);                                                \
  using flatbuffer_mutator::aflplusplus::MutateHelper;                                        \
  using FuzzerFlatbufferType = std::remove_const<std::remove_reference<                        \
      std::function<decltype(FlatbufferToDataHelper)>::first_argument_type>::type>::type;    \
  DEFINE_AFL_CUSTOM_FLATBUFFER_MUTATOR_IMPL(use_binary, FuzzerFlatbufferType)                \
  DEFINE_AFL_CUSTOM_FLATBUFFER_POST_PROCESS_IMPL(use_binary, FuzzerFlatbufferType)           \
  DEFINE_AFL_CUSTOM_INIT                                                                      \
  DEFINE_AFL_CUSTOM_DEINIT                                                                    \
  static size_t FlatbufferToDataHelper(args)

namespace flatbuffer_mutator {
namespace aflplusplus {

  // Embedding buf_ in class MutateHelper here to prevent memory 
  // fragmentation caused by frequent memory allocation.
  class MutateHelper {
  public:
    size_t GetSeed() const { return seed_; }
    size_t GetLen() const { return len_; }
    void SetLen(size_t len) { len_ = len; }
    uint8_t* GetOutBuf() { return buf_; }
    uint8_t* ReallocBuf(size_t len);
    MutateHelper(size_t s);
    ~MutateHelper() = default;

  private:
    size_t seed_;
    uint8_t* buf_;
    size_t len_;
  };

} // namespace aflplusplus
} // namespace flatbuffer_mutator

#endif // AFLPLUSPLUS_FLATBUFFER_MUTATOR_SRC_AFL_MUTATE_H_

