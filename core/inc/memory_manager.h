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
  static void *allocate(size_t size);
  static void deallocate(void *ptr);
  static void *reallocate(void *ptr, size_t newSize);

  // Memory pool operations
  static void initializePools();
  static void cleanupPools();

 private:
  static constexpr size_t POOL_SIZES[] = {16, 32, 64, 128, 256, 512, 1024};
  static std::vector<void *> pools;
};

/** @} */
