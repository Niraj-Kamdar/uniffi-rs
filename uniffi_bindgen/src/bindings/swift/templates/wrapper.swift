// This file was autogenerated by some hot garbage in the `uniffi` crate.
// Trust me, you don't want to mess with it!
{%- import "macros.swift" as swift %}
import Foundation
{%- for imported_class in self.imports() %}
import {{ imported_class }}
{%- endfor %}

// Depending on the consumer's build setup, the low-level FFI code
// might be in a separate module, or it might be compiled inline into
// this module. This is a bit of light hackery to work with both.
#if canImport({{ config.ffi_module_name() }})
import {{ config.ffi_module_name() }}
#endif

{% include "RustBufferTemplate.swift" %}
{% include "Helpers.swift" %}

// Public interface members begin here.
{{ type_helper_code }}

{%- for func in ci.function_definitions() %}
{%- include "TopLevelFunctionTemplate.swift" %}
{%- endfor %}

private enum CheckVersionResult {
    case ok
    case contractVersionMismatch
    case apiChecksumMismatch
}
// Use a global variables to perform the versioning checks. Swift ensures that
// the code inside is only computed once.
private var checkVersionResult: CheckVersionResult {
    // Get the bindings contract version from our ComponentInterface
    let bindings_contract_version = {{ ci.uniffi_contract_version() }}
    // Get the scaffolding contract version by calling the into the dylib
    let scaffolding_contract_version = {{ ci.ffi_uniffi_contract_version().name() }}()
    if bindings_contract_version != scaffolding_contract_version {
        return CheckVersionResult.contractVersionMismatch
    }

    {%- for (name, expected_checksum) in ci.iter_checksums() %}
    if ({{ name }}() != {{ expected_checksum }}) {
        return CheckVersionResult.apiChecksumMismatch
    }
    {%- endfor %}
    return CheckVersionResult.ok
}

private func uniffiCheckFfiVersionMismatch() {
    switch checkVersionResult {
    case .ok:
        break
    case .contractVersionMismatch:
        fatalError("UniFFI contract version mismatch: try cleaning and rebuilding your project")
    case .apiChecksumMismatch:
        fatalError("UniFFI API checksum mismatch: try cleaning and rebuilding your project")
    }
}
