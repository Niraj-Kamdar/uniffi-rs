// This file was autogenerated by some hot garbage in the `uniffi` crate.
// Trust me, you don't want to mess with it!

#pragma once

#include <stdbool.h>
#include <stdint.h>

// The following structs are used to implement the lowest level
// of the FFI, and thus useful to multiple uniffied crates.
// We ensure they are declared exactly once, with a header guard, UNIFFI_SHARED_H.
#ifdef UNIFFI_SHARED_H
    // We also try to prevent mixing versions of shared uniffi header structs.
    // If you add anything to the #else block, you must increment the version suffix in UNIFFI_SHARED_HEADER_V4
    #ifndef UNIFFI_SHARED_HEADER_V4
        #error Combining helper code from multiple versions of uniffi is not supported
    #endif // ndef UNIFFI_SHARED_HEADER_V4
#else
#define UNIFFI_SHARED_H
#define UNIFFI_SHARED_HEADER_V4
// ⚠️ Attention: If you change this #else block (ending in `#endif // def UNIFFI_SHARED_H`) you *must* ⚠️
// ⚠️ increment the version suffix in all instances of UNIFFI_SHARED_HEADER_V4 in this file.           ⚠️

typedef struct RustBuffer
{
    int32_t capacity;
    int32_t len;
    uint8_t *_Nullable data;
} RustBuffer;

typedef int32_t (*ForeignCallback)(uint64_t, int32_t, const RustBuffer *_Nonnull, RustBuffer *_Nonnull);

typedef struct ForeignBytes
{
    int32_t len;
    const uint8_t *_Nullable data;
} ForeignBytes;

// `RustFuture` is an opaque type.
typedef struct RustFuture RustFuture;

typedef void rust_future_waker_environment_t;
typedef void (*rust_future_waker_t)(rust_future_waker_environment_t*_Nullable);

// Error definitions
typedef struct RustCallStatus {
    int8_t code;
    RustBuffer errorBuf;
} RustCallStatus;

// ⚠️ Attention: If you change this #else block (ending in `#endif // def UNIFFI_SHARED_H`) you *must* ⚠️
// ⚠️ increment the version suffix in all instances of UNIFFI_SHARED_HEADER_V4 in this file.           ⚠️
#endif // def UNIFFI_SHARED_H

{%- for func in ci.iter_ffi_function_definitions() -%}
{%- if func.is_async() %}

RustFuture*_Nonnull {{ func.name() }}({% call swift::arg_list_ffi_decl(func) %});

bool {{ func.name() }}_poll(
    RustFuture*_Nonnull const,
    rust_future_waker_t _Nonnull,
    rust_future_waker_environment_t*_Nullable const,
    {% match func.return_type() %}{% when Some with (type_) %}{{ type_|ffi_type_name }}{% when None %}void{% endmatch %}*_Nullable,
    RustCallStatus*_Nonnull
);

void {{ func.name() }}_drop(RustFuture*_Nonnull, RustCallStatus*_Nonnull);
{%- else %}

{% match func.return_type() -%}{%- when Some with (type_) %}{{ type_|ffi_type_name }}{% when None %}void{% endmatch %} {{ func.name() }}(
    {% call swift::arg_list_ffi_decl(func) %}
);
{%- endif -%}
{%- endfor -%}

{% import "macros.swift" as swift %}
