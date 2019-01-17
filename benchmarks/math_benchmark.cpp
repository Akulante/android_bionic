/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fenv.h>
#include <math.h>

#include <benchmark/benchmark.h>

static const double values[] = { 1234.0, nan(""), HUGE_VAL, 0.0 };
static const char* names[] = { "1234.0", "nan", "HUGE_VAL", "0.0" };

#define BENCHMARK_COMMON_VALS(name) BENCHMARK(name)->Arg(0)->Arg(1)->Arg(2)->Arg(3)

static void SetLabel(benchmark::State& state) {
  state.SetLabel(names[state.range(0)]);
}

// Avoid optimization.
volatile double d;
volatile double v;

static void BM_math_sqrt(benchmark::State& state) {
  d = 0.0;
  v = 2.0;
  while (state.KeepRunning()) {
    d += sqrt(v);
  }
}
BENCHMARK(BM_math_sqrt);

static void BM_math_log10(benchmark::State& state) {
  d = 0.0;
  v = 1234.0;
  while (state.KeepRunning()) {
    d += log10(v);
  }
}
BENCHMARK(BM_math_log10);

static void BM_math_logb(benchmark::State& state) {
  d = 0.0;
  v = 1234.0;
  while (state.KeepRunning()) {
    d += logb(v);
  }
}
BENCHMARK(BM_math_logb);

static void BM_math_isfinite_macro(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += isfinite(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isfinite_macro);

#if defined(__BIONIC__)
#define test_isfinite __isfinite
#else
#define test_isfinite __finite
#endif
static void BM_math_isfinite(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += test_isfinite(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isfinite);

<<<<<<< HEAD
BENCHMARK_WITH_ARG(BM_math_isfinite_macro, double)->AT_COMMON_VALS;
void BM_math_isfinite_macro::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += isfinite(v);
  }

  StopBenchmarkTiming();
}

#if defined(__BIONIC__)
#define test_isfinite __isfinite
#else
#define test_isfinite __finite
#endif
BENCHMARK_WITH_ARG(BM_math_isfinite, double)->AT_COMMON_VALS;
void BM_math_isfinite::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += test_isfinite(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_isinf_macro, double)->AT_COMMON_VALS;
void BM_math_isinf_macro::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += isinf(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_isinf, double)->AT_COMMON_VALS;
void BM_math_isinf::Run(int iters, double value) {
  StartBenchmarkTiming();
=======
static void BM_math_isinf_macro(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += isinf(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isinf_macro);
>>>>>>> android_bionic/lineage-15.1

static void BM_math_isinf(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += (isinf)(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isinf);

static void BM_math_isnan_macro(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += isnan(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isnan_macro);

<<<<<<< HEAD
BENCHMARK_WITH_ARG(BM_math_isnan_macro, double)->AT_COMMON_VALS;
void BM_math_isnan_macro::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += isnan(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_isnan, double)->AT_COMMON_VALS;
void BM_math_isnan::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += (isnan)(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_isnormal_macro, double)->AT_COMMON_VALS;
void BM_math_isnormal_macro::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += isnormal(v);
  }

  StopBenchmarkTiming();
}

#if defined(__BIONIC__)
BENCHMARK_WITH_ARG(BM_math_isnormal, double)->AT_COMMON_VALS;
void BM_math_isnormal::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += (__isnormal)(v);
  }

  StopBenchmarkTiming();
}
#endif

BENCHMARK_NO_ARG(BM_math_sin_fast);
void BM_math_sin_fast::Run(int iters) {
  StartBenchmarkTiming();
=======
static void BM_math_isnan(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += (isnan)(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isnan);
>>>>>>> android_bionic/lineage-15.1

static void BM_math_isnormal_macro(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += isnormal(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isnormal_macro);

#if defined(__BIONIC__)
static void BM_math_isnormal(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += (__isnormal)(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_isnormal);
#endif

static void BM_math_sin_fast(benchmark::State& state) {
  d = 1.0;
  while (state.KeepRunning()) {
    d += sin(d);
  }
}
BENCHMARK(BM_math_sin_fast);

static void BM_math_sin_feupdateenv(benchmark::State& state) {
  d = 1.0;
  while (state.KeepRunning()) {
    fenv_t __libc_save_rm;
    feholdexcept(&__libc_save_rm);
    fesetround(FE_TONEAREST);
    d += sin(d);
    feupdateenv(&__libc_save_rm);
  }
}
BENCHMARK(BM_math_sin_feupdateenv);

static void BM_math_sin_fesetenv(benchmark::State& state) {
  d = 1.0;
  while (state.KeepRunning()) {
    fenv_t __libc_save_rm;
    feholdexcept(&__libc_save_rm);
    fesetround(FE_TONEAREST);
    d += sin(d);
    fesetenv(&__libc_save_rm);
  }
}
BENCHMARK(BM_math_sin_fesetenv);

static void BM_math_fpclassify(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += fpclassify(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_fpclassify);

static void BM_math_signbit_macro(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += signbit(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_signbit_macro);

static void BM_math_signbit(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += (__signbit)(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_signbit);

static void BM_math_fabs_macro(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += fabs(v);
  }
  SetLabel(state);
}
BENCHMARK_COMMON_VALS(BM_math_fabs_macro);

static void BM_math_fabs(benchmark::State& state) {
  d = 0.0;
  v = values[state.range(0)];
  while (state.KeepRunning()) {
    d += (fabs)(v);
  }
  SetLabel(state);
}
<<<<<<< HEAD

BENCHMARK_WITH_ARG(BM_math_signbit_macro, double)->AT_COMMON_VALS;
void BM_math_signbit_macro::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += signbit(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_signbit, double)->AT_COMMON_VALS;
void BM_math_signbit::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += (__signbit)(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_fabs_macro, double)->AT_COMMON_VALS;
void BM_math_fabs_macro::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += fabs(v);
  }

  StopBenchmarkTiming();
}

BENCHMARK_WITH_ARG(BM_math_fabs, double)->AT_COMMON_VALS;
void BM_math_fabs::Run(int iters, double value) {
  StartBenchmarkTiming();

  d = 0.0;
  v = value;
  for (int i = 0; i < iters; ++i) {
    d += (fabs)(v);
  }

  StopBenchmarkTiming();
}
=======
BENCHMARK_COMMON_VALS(BM_math_fabs);
>>>>>>> android_bionic/lineage-15.1
