#pragma once

template<typename element_type>
struct array {
    size_t length;
    element_type* data;
};

template<typename value_type>
value_type copy(value_type const& value) {
    return value;
}

template<typename element_type, size_t length>
inline array<element_type> array_from_static(element_type (&a)[length]) {
    return array<element_type> { length, a };
}

template<typename element_type, size_t length>
struct value_array {
    element_type value[length];
};

template<typename storage_type>
inline storage_type const* const_ptr(storage_type const& value) {
    return &value;
}