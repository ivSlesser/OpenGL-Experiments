// MIT License
//
// Copyright (c) 2020 Ian Vincent Slesser
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#pragma once

#include "Common.h"

class Clock {

 public:
  static double DeltaTime;          // Delta time (Time since last frame) in seconds
  static double ElapsedTime;          // Total elapsed time in seconds, scaled by mScale

 private:
  double mStart{0};                // Starting system time (nanoseconds)
  double mCurrent{0};              // Current system time (nanoseconds)
  double mFrameCount{0};           // Current frame count

  float mScale{1.0f};              // Time scale factor
  double mElapsedTimeUnscaled{0};  // Total elapsed time in seconds, not scaled

  double mAccumulate{0};           // Timestep accumulator for use in timestep fixing
  double mInterval{0};             // Time per frame to achieve mMaxFPS
  uint16_t mMaxFPS{100};           // Target FPS
  uint8_t mMaxSimulations{5};      // Maximum number of simulation steps

  // -------------------------------------------------------------------------------------------------------------------

 public:
  bool Init();
  double Update();

  inline double ElapsedUnscaledTime() const { return mElapsedTimeUnscaled; }

  inline const double GetInterval() const { return mInterval; }
  inline double GetIntervalWhileDecrementingAccumulate() {
    mAccumulate -= mInterval;
    return mInterval;
  }
  inline const bool ShouldProceedWithSimulationStep(uint32_t step) const {
    return step < mMaxSimulations && mAccumulate > mInterval;
  }

  inline static double NanosecondsToMicroseconds(const double &nanoseconds) { return nanoseconds * 1e-3; }
  inline static double NanosecondsToMilliseconds(const double &nanoseconds) { return nanoseconds * 1e-6; }
  inline static double NanosecondsToSeconds(const double &nanoseconds) { return nanoseconds * 1e-9; }
  inline static double SecondsToNanoseconds(const double &seconds) { return seconds * 1e9; }
  inline static double MillisecondsToNanoseconds(const double &milliseconds) { return milliseconds * 1e6; }
  inline static double MicrosecondsToNanoseconds(const double &microseconds) { return microseconds * 1e3; }

  // --------------------------------------------------------------------------------------------------------------------

  static double GetHighPrecisionTime();

  // -------------------------------------------------------------------------------------------------------------------


};
