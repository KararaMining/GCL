﻿//*********************************************************************************************************************************
//
// PROJECT:							General Class Library (GCL)
// FILE:								Resource Utilisations (CPU and Memory)
// SUBSYSTEM:						General Class Library Exception subsystem
// LANGUAGE:						C++
// TARGET OS:						All - Supported through compiler directives.
// NAMESPACE:						GCL
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2015-2022, 2024 Gavin Blakeman.
//                      This file is part of the General Class Library (GCL)
//
//                      GCL is free software: you can redistribute it and/or modify it under the terms of the GNU General
//                      Public License as published by the Free Software Foundation, either version 2 of the License, or
//                      (at your option) any later version.
//
//                      GCL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//                      implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//                      for more details.
//
//                      You should have received a copy of the GNU General Public License along with GCL.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:            A class for determining resource utilisations.
//
// CLASSES INCLUDED:    CResourceUsage
//
// FUNCTIONS INCLUDED:  None
//
// HISTORY:             2015-09-22 GGB - AIRDAS 2015.09 release
//                      2015-01-02/GGB - File created.
//
//*********************************************************************************************************************************

#ifndef GCL_RESOURCE_H
#define GCL_RESOURCE_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace GCL
{
  class CResourceUsage
  {
  public:
    using system_t = unsigned long long; // Done in case windows needs different definition.

  private:
    size_t totalRAM_;           ///< Total RAM in system
    size_t usedRAM_;            ///< Total RAM used.
    size_t totalSwap_;          ///< Total swap available
    size_t usedSwap_;           ///< Total swap used.

    system_t lastTotalUser;       ///<
    system_t lastTotalUserLow;
    system_t lastTotalSys;
    system_t lastTotalIdle;

    double percentCPU_;         ///< Percent usage of the CPU

#if defined(_WIN32)
    PDH_HQUERY cpuQuery;
    static PDH_HCOUNTER cpuTotal;
#endif

  protected:

  public:
    CResourceUsage();

    virtual void determineMemory();
    virtual void determineCPU();

    size_t totalRAM() { return totalRAM_; }
    size_t usedRAM() {return usedRAM_; }
    size_t processRAM() { return 0;}

    size_t totalVirtMemory() { return (totalRAM_  + totalSwap_); }
    size_t usedVirtMemory() { return (usedRAM_ + usedSwap_); }
    size_t processVirtMemory() {return 0;}

    size_t totalSwapMemory() { return totalSwap_; }
    size_t usedSwapMemory() { return usedSwap_; }

    double usageCPU() { return percentCPU_; }
    double processCPU() { return 0; }
  };

  std::string getHostName();
}

#endif // GCL_RESOURCE_H
