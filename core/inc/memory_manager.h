#pragma once

/*******************************************************************************************************************************
 * @file   memory_manager.h
 *
 * @brief  Header file for a memory manager library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <cstddef>
#include <cstdint>
#include <vector>

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup CoreModules
 * @brief    Core modules to run on the CPU for physics management
 * @{
 */

class MemoryManager {
 public:
  /**
   * @brief   Allocate memory
   */
  void *allocate(size_t size);
  void deallocate(void *ptr);
  void *reallocate(void *ptr, size_t newSize);
  void initializePools();
  void cleanupPools();

 private:
  static constexpr size_t POOL_SIZES[] = {16, 32, 64, 128, 256, 512, 1024};
  static constexpr size_t BLOCKS_PER_POOL = 256;
  static constexpr size_t BITMAP_WORDS = (BLOCKS_PER_POOL + 63) / 64; /* Rounded up to nearest 64 */

  struct Pool {
    void *memory;                  /**< Start of memory pool*/
    uint64_t bitmap[BITMAP_WORDS]; /**< 1 = allocated, 0 = free */
    size_t blockSize;              /**< Size of each block */
  };

  std::vector<Pool> memoryPools;

  static inline int findFirstZeroBit(uint64_t word);
  size_t findFreeBlock(Pool &pool);
  size_t getBlockIndex(const Pool &pool, void *ptr);
  bool isPointerInPool(const Pool &pool, void *ptr);
};

/** @} */
