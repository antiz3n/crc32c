// Copyright (c) 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef CRC32C_CRC32C_PREFETCH_H_
#define CRC32C_CRC32C_PREFETCH_H_

#include <cstddef>
#include <cstdint>

#include "crc32c/crc32c_config.h"

namespace crc32c {

// Ask the hardware to prefetch the data at the given address into the L1 cache.
inline void RequestPrefetch(const uint8_t* address) {
#if defined(HAVE_BUILTIN_PREFETCH)
  // Clang and GCC implement the __builtin_prefetch non-standard extension,
  // which maps to the best instruction on the target architecture.
  __builtin_prefetch(
      address, 0  /* Read only. */, 0  /* No temporal locality. */);
#elif defined(HAVE_MM_PREFETCH)
  // Visual Studio doesn't implement __builtin_prefetch, but exposes the
  // PREFETCHNTA instruction via the _mm_prefetch intrinsic.
  _mm_prefetch(address, _MM_HINT_NTA);
#else
  // No prefetch support. Silence compiler warnings.
  (void)address;
#endif  // defined(HAVE_BUILTIN_PREFETCH)
}

}  // namespace crc32c

#endif  // CRC32C_CRC32C_ROUND_UP_H_
