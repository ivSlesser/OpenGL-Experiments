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


#include "Clock.h"

double Clock::DeltaTime = 0.0;
double Clock::ElapsedTime = 0.0;

/**
 * Handles initialization of the Clock
 *
 * @return          True if initialization succeeded.
 */
bool Clock::Init() {
  mStart = Clock::GetHighPrecisionTime();
  mCurrent = Clock::GetHighPrecisionTime();
  mInterval = 1.0 / mMaxFPS;
  return true;
}

/**
 * Updates the Clock, calculating the delta time, elapsed time and accumulator used in physics
 * calculations.
 *
 * @return          Delta time (time since last frame)
 */
double Clock::Update() {

  mFrameCount++;

  DeltaTime = 0.0;
  double now = Clock::GetHighPrecisionTime();

  double d = now - mCurrent;
  double e = now - mStart;

  mCurrent = now;
  DeltaTime = Clock::NanosecondsToSeconds(d) * mScale;
  ElapsedTime += DeltaTime;
  mElapsedTimeUnscaled = Clock::NanosecondsToSeconds(e);

  mAccumulate += DeltaTime;

  return DeltaTime;
}

/**
 * Returns the high precision time in nanoseconds from the system clock.
 *
 * @return          Current time in nanoseconds
 */
double Clock::GetHighPrecisionTime() {
  auto tp = std::chrono::high_resolution_clock::now();
  return std::chrono::time_point_cast<std::chrono::nanoseconds>(tp).time_since_epoch().count();
}
