#
# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

# TODO(dimitry): replace with define once https://android-review.googlesource.com/247466 is reverted
# https://github.com/google/kati/issues/83 is currently blocking it.

# Move prebuilt test elf-files to $(TARGET_OUT_NATIVE_TESTS)
bionic_tests_module := libtest_invalid-rw_load_segment.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

bionic_tests_module := libtest_invalid-unaligned_shdr_offset.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

bionic_tests_module := libtest_invalid-zero_shentsize.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

bionic_tests_module := libtest_invalid-zero_shstrndx.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

bionic_tests_module := libtest_invalid-empty_shdr_table.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

bionic_tests_module := libtest_invalid-zero_shdr_table_offset.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

bionic_tests_module := libtest_invalid-zero_shdr_table_content.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

<<<<<<< HEAD
libBionicStandardTests_src_files := \
    arpa_inet_test.cpp \
    buffer_tests.cpp \
    complex_test.cpp \
    ctype_test.cpp \
    dirent_test.cpp \
    error_test.cpp \
    eventfd_test.cpp \
    fcntl_test.cpp \
    fenv_test.cpp \
    ftw_test.cpp \
    getauxval_test.cpp \
    getcwd_test.cpp \
    inttypes_test.cpp \
    libc_logging_test.cpp \
    libgen_basename_test.cpp \
    libgen_test.cpp \
    locale_test.cpp \
    malloc_test.cpp \
    math_test.cpp \
    mntent_test.cpp \
    netdb_test.cpp \
    pthread_test.cpp \
    pty_test.cpp \
    regex_test.cpp \
    sched_test.cpp \
    search_test.cpp \
    semaphore_test.cpp \
    setjmp_test.cpp \
    signal_test.cpp \
    stack_protector_test.cpp \
    stack_unwinding_test.cpp \
    stdatomic_test.cpp \
    stdint_test.cpp \
    stdio_test.cpp \
    stdio_ext_test.cpp \
    stdlib_test.cpp \
    string_test.cpp \
    string_posix_strerror_r_test.cpp \
    strings_test.cpp \
    stubs_test.cpp \
    sstream_test.cpp \
    sys_epoll_test.cpp \
    sys_mman_test.cpp \
    sys_personality_test.cpp \
    sys_procfs_test.cpp \
    sys_resource_test.cpp \
    sys_select_test.cpp \
    sys_sendfile_test.cpp \
    sys_socket_test.cpp \
    sys_stat_test.cpp \
    sys_statvfs_test.cpp \
    sys_syscall_test.cpp \
    sys_sysinfo_test.cpp \
    sys_time_test.cpp \
    sys_types_test.cpp \
    sys_uio_test.cpp \
    sys_vfs_test.cpp \
    sys_xattr_test.cpp \
    system_properties_test.cpp \
    time_test.cpp \
    uchar_test.cpp \
    uniqueptr_test.cpp \
    unistd_test.cpp \
    utmp_test.cpp \
    wchar_test.cpp \
=======
bionic_tests_module := libtest_invalid-textrels.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk
>>>>>>> android_bionic/lineage-15.1

bionic_tests_module := libtest_invalid-textrels2.so
include $(LOCAL_PATH)/Android.build.prebuilt.mk

ifeq ($(HOST_OS)-$(HOST_ARCH),$(filter $(HOST_OS)-$(HOST_ARCH),linux-x86 linux-x86_64))
build_host := true
else
build_host := false
endif

ifeq ($(HOST_OS)-$(HOST_ARCH),$(filter $(HOST_OS)-$(HOST_ARCH),linux-x86 linux-x86_64))

# -----------------------------------------------------------------------------
# Compile time tests.
# -----------------------------------------------------------------------------

# Some of these are intentionally using = instead of := since we need access to
# some variables not initialtized until we're in the build system.

include $(CLEAR_VARS)
LOCAL_ADDITIONAL_DEPENDENCIES := \
    $(LOCAL_PATH)/Android.mk \
    $(LOCAL_PATH)/file-check-cxx \
    | $(HOST_OUT_EXECUTABLES)/FileCheck$(HOST_EXECUTABLE_SUFFIX) \

LOCAL_CXX = $(LOCAL_PATH)/file-check-cxx \
    $(HOST_OUT_EXECUTABLES)/FileCheck \
    $($(LOCAL_2ND_ARCH_VAR_PREFIX)TARGET_CXX) \
    GCC \

LOCAL_CLANG := false
LOCAL_MODULE := bionic-compile-time-tests-g++
LOCAL_CPPFLAGS := -Wall
# Disable color diagnostics so the warnings output matches the source
LOCAL_CPPFLAGS += -fdiagnostics-color=never
LOCAL_SRC_FILES := fortify_compilation_test.cpp
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_ADDITIONAL_DEPENDENCIES := \
    $(LOCAL_PATH)/Android.mk \
    $(LOCAL_PATH)/file-check-cxx \
    | $(HOST_OUT_EXECUTABLES)/FileCheck$(HOST_EXECUTABLE_SUFFIX) \

LOCAL_CXX := $(LOCAL_PATH)/file-check-cxx \
    $(HOST_OUT_EXECUTABLES)/FileCheck \
    $(LLVM_PREBUILTS_PATH)/clang++ \
    CLANG \

LOCAL_CLANG := true
LOCAL_MODULE := bionic-compile-time-tests-clang++
LOCAL_CPPFLAGS := -Wall
LOCAL_CPPFLAGS += -fno-color-diagnostics -ferror-limit=10000
LOCAL_SRC_FILES := fortify_compilation_test.cpp
include $(BUILD_STATIC_LIBRARY)

endif # linux-x86

include $(call first-makefiles-under,$(LOCAL_PATH))
