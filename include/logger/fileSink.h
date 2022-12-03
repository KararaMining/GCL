﻿//*********************************************************************************************************************************
//
// PROJECT:             General Class Library
// FILE:                fileSink.h
// SUBSYSTEM:           Logging Library
// LANGUAGE:						C++
// TARGET OS:						None.
// NAMESPACE:						GCL
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2014-2022 Gavin Blakeman.
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
// OVERVIEW:            This file implements a logging class to be used to log messages to file.
//                      The class has been designed as a lightweight easy to use class.
//
// CLASSES INCLUDED:    CLogger
//
// HISTORY:             2015-09-22 GGB - AIRDAS 2015.09 release
//                      2014-12-25 GGB - Development of class for "Observatory Weather System - Service"
//
//*********************************************************************************************************************************

#ifndef GCL_FILESINK_H
#define GCL_FILESINK_H

#ifndef GCL_CONTROL

  // Standard C++ library header files.

#include <cstdint>

  // GCL header files

#include "loggerCore.h"

namespace GCL
{
  namespace logger
  {
    class CFileSink : public CLoggerSink
    {
      enum ERotationMethod
      {
        days,               ///< A new log file is created every rotationDays days
        size,               ///< A new log file is created once the old one is above a specified size.
        daily,              ///< A new log file is created every day. (includes date in filename)
        use                 ///< A new log file is created every use (includes date and time in filename)
      };

    private:
      std::filesystem::path logFilePath;
      std::filesystem::path logFileName;
      std::filesystem::path logFileExt;
      std::filesystem::path openLogFileName;

        // Daily based rotation variables

      int fileCreationDate;

      ERotationMethod rotationMethod = daily;
      std::uint16_t maxAge;
      std::uint16_t maxCopies;                        ///< Number of logfile copies to keep. +ve = number, 0 or -ve = none.
      std::uintmax_t rotationSize = 10 * 1024 * 1024; ///< Maximum allowable log file size
      std::uint16_t rotationDays;                     ///< Number of days between rotations.
      bool useUTC = true;                             ///< Use UTC for determining start of days.

      CFileSink() = delete;
      CFileSink(CFileSink const &) = delete;

      void rollFiles(void);

    protected:
      std::ofstream logFile;

      virtual void rotateLogFile();
      virtual void write(std::string const &);

    public:
      CFileSink(std::filesystem::path const &, std::filesystem::path const &, std::filesystem::path const & =".log");
      virtual ~CFileSink();

      void openLogFile();

      void setLogFileName(std::string const &filePath, std::string const &fileName, std::string const &fileExt = ".log");
      void setRotationPolicySize(std::uint16_t copies, std::uintmax_t maxSize = 10 * 1024 * 1024);
      void setRotationPolicyDaily(std::uint16_t copies);
      void setRotationPolicyDays(std::uint16_t copies, std::uint16_t maxDays);
      CFileSink &setRotationPolicyUse(std::uint16_t copies);

    };

  }   // namespace logger
}   // namespace GCL

#endif // GCL_CONTROL

#endif // GCL_FILESINK_H
