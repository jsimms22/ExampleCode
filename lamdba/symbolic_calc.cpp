// Following https://youtu.be/lPfA4SFojao?feature=shared to create symbolic math in cpp with a lambda expression approach
// alternatively, https://github.com/CppCon/CppCon2023/blob/main/Presentations/Symbolic_Calculus_for_High_Performance_Computing_from_Scratch_using_Cpp23_CppCon_2023_Vincent_Reverdy.pdf

// The following does not compile unless using -std=c++20 or more recent

#include<iostream>
#include<cmath>
#include<compare>
#include<type_traits>

// slide 29 code
//l-value traits
template <class T>
struct remove_lvalue_reference: std::type_identity<T> {};

template <class T> 
requires std::is_lvalue_reference_v<T>
struct remove_lvalue_reference<T>: std::type_identity<std::remove_reference_t<T>> {};

template <class T>
using remove_lvalue_reference_t = remove_lvalue_reference<T>::type;

//r-value traits 
template <class T>
struct remove_rvalue_reference: std::type_identity<T> {};

template <class T> 
requires std::is_rvalue_reference_v<T>
struct remove_rvalue_reference<T>: std::type_identity<std::remove_reference_t<T>> {};

template <class T>
using remove_rvalue_reference_t = remove_rvalue_reference<T>::type;
// end slide

// slide 30 code
// converting t& to connst T& 
template <class T>
// conditional flow, conditional<B,T,F>
// if B is true, evaluate member typedef as type T
// if B is fale, evaluate member typedef as type F
struct requalify_as_const: std::conditional<
    std::is_lvalue_reference_v<T>,
    // if lvalue, remove reference, add const, then add back reference
    std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<T>>>,
    std::conditional<
        std::is_rvalue_reference_v<T>,
        // if rvalue, remove reference, add const, then add back reference
        std::add_rvalue_reference_t<std::add_const_t<std::remove_reference_t<T>>>,
        // if neither, just add const
        std::add_const_t<T>
    >
> {};
template <class T>
using requalify_as_const_t = requalify_as_const<T>::type;

// do same thing for volatile
template <class T>
struct requalify_as_volatile;
template <class T>
using requalify_as_volatile_t = requalify_as_volatile<T>::type;

// do same thing for cv (const and volatile)
template <class T>
struct requalify_as_cv;
template <class T>
using requalify_as_cv_t = requalify_as_cv<T>::type;
// end slide

// slide 13 code
// auto a = []{};
// auto b = []{};
// auto d = []{};
// auto c = []{};
// end slide

// slide 27 + 31 code
template <class _Symbol, class T>
struct symbol_binder
{
public:
    // types and constants
    using symbol_type = _Symbol;
    using value_type = std::remove_cvref_t<T>;
    static constexpr _Symbol symbol = {};

    // constructors
    template <class U>
    requires std::is_convertible_v<U&&, requalify_as_const_t<remove_rvalue_reference_t<T>>>
    constexpr symbol_binder(_Symbol , U&& x) noexcept (
        std::is_nothrow_convertible_v<U&&, requalify_as_const_t<remove_rvalue_reference_t<T>>>
    ): value(std::forward<U>(x)) {}
    
    // accessors
    const value_type& operator()() const noexcept { return value; }
    
private:
    requalify_as_const_t<remove_rvalue_reference_t<T>> value;
};

// deduction guide
// https://stackoverflow.com/questions/40951697/what-are-template-deduction-guides-and-when-should-we-use-them
template <class _Symbol, class T>
symbol_binder(_Symbol, T&&) -> symbol_binder<_Symbol, T&&>;

// moving symbol_id from below for use in the new version of our symbol class
template <class>
struct symbol_id 
{
    static constexpr auto singleton = []{}; // provides an address that is unique to each symbol id
                                            // singleton type could be any substantiable type
    static constexpr const void* address = std::addressof(singleton);
};

// updating to include lightweight binder in symbol class from below
template <
    auto = []{}, 
    auto _Id = symbol_id<decltype([]{})>{}
> struct symbol {
    static constexpr auto id = _Id;
    template <class T>
    constexpr symbol_binder<symbol, T&&> operator=(T&& value) const {
        return symbol_binder(*this, std::forward<T>(value));
    }
};
// end slide

// slide 14 + 19 + 20 code
// template <class>
// struct symbol_id 
// {
//     static constexpr auto singleton = []{}; // provides an address that is unique to each symbol id
//                                             // singleton type could be any substantiable type
//     static constexpr const void* address = std::addressof(singleton);
// };

// template <auto _Id = symbol_id<decltype([]{})>{}>
// struct symbol 
// {   
//     static constexpr auto id = _Id;
//     template <class T>
//     constexpr symbol_binder<symbol, T> operator=(T value) 
//     {
//         return symbol_binder(*this, value);
//     }
// };
symbol x;
symbol y;
// x and y are always going to be two different types using this "lamdba" trick
// end slide

// slide 23 code
template <class Lhs, class Rhs>
constexpr bool operator<(symbol_id<Lhs>,symbol_id<Rhs>) 
{
    return std::less{}(symbol_id<Lhs>::address, symbol_id<Rhs>::address);
}
// end slide

// slide 24 code
template <class Lhs, class Rhs>
// <=> spaceship operator
// returns <0 val if Lhs is less than Rhs
// returns 0 if Lhs equals Rhs
// returns >0 if Lhs is greater than Rhs
constexpr std::strong_ordering operator<=>(
    symbol_id<Lhs>,
    symbol_id<Rhs>
) {
    return std::compare_three_way{}(
        symbol_id<Lhs>::address,
        symbol_id<Rhs>::address
    );
};
// end slide

// slide 15 code
symbol a;
symbol w;
symbol t;
symbol phi;
// end slide

//double f(symbol , symbol , symbol , symbol ) {}

int main()
{
    // slide 13 code
    // std::cout << std::is_same_v<decltype(a),decltype(a)> << std::endl; // 1
    // std::cout << std::is_same_v<decltype(a),decltype(b)> << std::endl; // 0
    // end slide

    // slide 14 + 19 code
    std::cout << std::is_same_v<decltype(x),decltype(x)> << std::endl; // 1
    std::cout << std::is_same_v<decltype(x),decltype(y)> << std::endl; // 0
    // end slide

    // if (a < w) {
    //     std::cout << "a < a" << std::endl;
    // } else if (a == w) {
    //     std::cout << "a == a" << std::endl;
    // } else if ( a > w) {
    //     std::cout << "a > a" << std::endl;
    // }
}