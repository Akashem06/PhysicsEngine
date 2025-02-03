/*******************************************************************************************************************************
 * @file   memory_manager.cc
 *
 * @brief  Source file for a memory manager library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <algorithm>
#include <cstdlib>
#include <cstring>

/* Inter-component Headers */

/* Intra-component Headers */
#include "memory_manager.h"

int MemoryManager::findFirstZeroBit(uint64_t word) {
/* Returns position of first zero bit, or -1 if none found */
/* Using compiler intrinsic for efficiency */
#if defined(__GNUC__) || defined(__clang__)
  if (word == ~0ULL)
    return -1;
  return __builtin_ffsll(~word) - 1;
#else
  /* Fallback for other compilers */
  for (int i = 0; i < 64; i++) {
    if ((word & (1ULL << i)) == 0)
      return i;
  }
  return -1;
#endif
}

size_t MemoryManager::findFreeBlock(Pool &pool) {
  /* Search through bitmap words */
  for (size_t i = 0; i < BITMAP_WORDS; i++) {
    int bit = findFirstZeroBit(pool.bitmap[i]);
    if (bit != -1) {
      /* Mark the bit as allocated */
      pool.bitmap[i] |= (1ULL << bit);
      return i * 64 + bit;
    }
  }
  return BLOCKS_PER_POOL; /* No free blocks found */
}

size_t MemoryManager::getBlockIndex(const Pool &pool, void *ptr) {
  size_t offset = static_cast<char *>(ptr) - static_cast<char *>(pool.memory);
  return offset / pool.blockSize;
}

bool MemoryManager::isPointerInPool(const Pool &pool, void *ptr) {
  char *charPtr = static_cast<char *>(ptr);
  char *poolStart = static_cast<char *>(pool.memory);
  char *poolEnd = poolStart + (pool.blockSize * BLOCKS_PER_POOL);
  return charPtr >= poolStart && charPtr < poolEnd;
}

void *MemoryManager::allocate(size_t size) {
  /* Find the correct memory pool */
  auto p_poolsizeIndex = std::lower_bound(POOL_SIZES, POOL_SIZES + sizeof(POOL_SIZES) / sizeof(POOL_SIZES[0]), size);

  /* Fallback for allocations bigger than the supported pool sizes */
  if (p_poolsizeIndex == POOL_SIZES + sizeof(POOL_SIZES) / sizeof(POOL_SIZES[0])) {
    return std::malloc(size);
  }

  size_t poolIndex = p_poolsizeIndex - POOL_SIZES;
  Pool &pool = memoryPools[poolIndex];

  /* Find a free block */
  size_t blockIndex = findFreeBlock(pool);

  /* If the pool is full, fallback to malloc */
  if (blockIndex >= BLOCKS_PER_POOL) {
    return std::malloc(size);
  }

  return static_cast<char *>(pool.memory) + (blockIndex * pool.blockSize);
}

void MemoryManager::deallocate(void *ptr) {
  if (!ptr)
    return;

  for (Pool &pool : memoryPools) {
    if (isPointerInPool(pool, ptr)) {
      int blockIndex = getBlockIndex(pool, ptr);
      int wordIndex = blockIndex / 64;
      int bitIndex = blockIndex % 64;

      /* Mark as unused */
      pool.bitmap[wordIndex] &= ~(1ULL << bitIndex);
    }
  }
}

void *MemoryManager::reallocate(void *ptr, size_t newSize) {
  if (!ptr)
    return allocate(newSize);

  for (Pool &pool : memoryPools) {
    if (isPointerInPool(pool, ptr)) {
      /* If the pointer fits in the current pool return the same pointer */
      if (newSize <= pool.blockSize)
        return ptr;

      /* Allocate new block and copy the data */
      void *newPtr = allocate(newSize);
      if (newPtr) {
        std::memcpy(newPtr, ptr, pool.blockSize);
        deallocate(ptr);
      }

      return newPtr;
    }
  }

  /* If the size is not supported, use built in realloc */
  return std::realloc(ptr, newSize);
}

void MemoryManager::initializePools() {
  /* One pool for each memory pool size */
  memoryPools.resize(sizeof(POOL_SIZES) / sizeof(POOL_SIZES[0]));

  for (size_t i = 0; i < memoryPools.size(); i++) {
    Pool &pool = memoryPools[i];
    pool.blockSize = POOL_SIZES[i];

    /* Allocate pool memory */
    pool.memory = std::malloc(pool.blockSize * BLOCKS_PER_POOL);

    /* Initialize the bitmap to 0 */
    std::memset(pool.bitmap, 0, sizeof(pool.bitmap));
  }
}

void MemoryManager::cleanupPools() {
  for (Pool &pool : memoryPools) {
    std::free(pool.memory);
  }
  memoryPools.clear();
}

/** @} */
