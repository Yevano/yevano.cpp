#pragma once

// type_eq //
template<typename lhs, typename rhs>
constexpr bool type_eq = false;

template<typename type>
constexpr bool type_eq<type, type> = true;

// is_ptr //
template<typename type>
constexpr bool is_ptr = false;

template<typename type>
constexpr bool is_ptr<type*> = true;

template<typename type>
constexpr bool is_ptr<type* const> = true;

// is_ref //
template<typename type>
constexpr bool is_ref = false;

template<typename type>
constexpr bool is_ref<type&> = true;

// is_by_copy //
template<typename type>
constexpr bool is_by_copy = !is_ptr<type> && !is_ref<type>;

// is_const //
template<typename type>
constexpr bool is_const = false;

template<typename type>
constexpr bool is_const<type const> = true;

// is_instantiation //
template<template<typename> typename temp, typename type>
constexpr bool is_instantiation = false;

template<template<typename> typename temp, typename type>
constexpr bool is_instantiation<temp, temp<type>> = true;

// remove_ref //
namespace {
    template<typename t>
    struct remove_ref_struct { using type = t; };

    template<typename t>
    struct remove_ref_struct<t&> { using type = t; };
}

template<typename t>
using remove_ref = typename remove_ref_struct<t>::type;

// remove_ptr //
namespace {
    template<typename t>
    struct remove_ptr_struct { using type = t; };

    template<typename t>
    struct remove_ptr_struct<t*> { using type = t; };
}

template<typename t>
using remove_ptr = typename remove_ptr_struct<t>::type;

// remove_const //
namespace {
    template<typename t>
    struct remove_const_struct { using type = t; };

    template<typename t>
    struct remove_const_struct<t const> { using type = t; };

    template<typename t>
    struct remove_const_struct<t* const> { using type = t; };

    template<typename t>
    struct remove_const_struct<t const* const> { using type = t; };
}

template<typename t>
using remove_const = typename remove_const_struct<t>::type;

// remove_const_from_ptr //
template<typename t>
using remove_const_from_ptr = remove_const<remove_ptr<t>>*;

// remove_const_from_ref //
template<typename t>
using remove_const_from_ref = remove_const<remove_ref<t>>&;

// branch //
namespace {
    template<bool b, typename t, typename f>
    struct branch_struct;

    template<typename t, typename f>
    struct branch_struct<true, t, f> { using type = t; };

    template<typename t, typename f>
    struct branch_struct<false, t, f> { using type = f; };
}

template<bool b, typename t, typename f>
using branch = typename branch_struct<b, t, f>::type;

// concepts //
template<typename type>
concept by_copy = is_by_copy<type>;

template<typename type>
concept non_const_by_copy = is_by_copy<type> && !is_const<type>;

template<typename type>
concept const_by_copy = is_by_copy<type> && is_const<type>;

template<typename type>
concept ptr = is_ptr<type>;

template<typename type>
concept non_const_ptr = is_ptr<type> && !is_const<remove_ptr<type>>;

template<typename type>
concept const_ptr = is_ptr<type> && is_const<remove_ptr<type>>;

template<typename type>
concept ref = is_ref<type>;

template<typename type>
concept non_const_ref = is_ref<type> && !is_const<remove_ref<type>>;

template<typename type>
concept const_ref = is_ref<type> && is_const<remove_ref<type>>;