/*
Copyright (c) 2021 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef RDC_MODULES_RDC_ROCR_MEMORYACCESS_H_
#define RDC_MODULES_RDC_ROCR_MEMORYACCESS_H_


#include "rdc_modules/rdc_rocr/TestBase.h"
#include "hsa/hsa.h"
namespace amd {
namespace rdc {

class MemoryAccessTest : public TestBase {
 public:
  explicit MemoryAccessTest(uint32_t gpu_index);

  // @Brief: Destructor for test case of MemoryTest
  virtual ~MemoryAccessTest();

  // @Brief: Setup the environment for measurement
  virtual hsa_status_t SetUp();

  // @Brief: Core measurement execution
  virtual void Run();

  // @Brief: Clean up and retrive the resource
  virtual void Close();

  // @Brief: Display  results
  virtual void DisplayResults() const;

  // @Brief: Display information about what this test does
  virtual void DisplayTestInfo(void);


  // @Brief: This test verify that CPU is able to Read & write GPU memory
  void CPUAccessToGPUMemoryTest(void);

  // @Brief: This test verify that GPU is able to Read & write CPU memory
  void GPUAccessToCPUMemoryTest(void);


 private:
  void CPUAccessToGPUMemoryTest(hsa_agent_t cpuAgent,
                                                   hsa_agent_t gpuAgent,
                                                   hsa_amd_memory_pool_t pool);
  void GPUAccessToCPUMemoryTest(hsa_agent_t cpuAgent, hsa_agent_t gpuAgent);
};

}  // namespace rdc
}  // namespace amd

#endif  // RDC_MODULES_RDC_ROCR_MEMORYACCESS_H_
