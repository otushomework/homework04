#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

/*! \file */

/**
 * @brief IP в интегральном виде.
 * @tparam T - любой интегральный тип.
 * @param ip - значение ip-адреса представленное в интегральном типе.
 */
template <typename T>
typename std::enable_if_t<std::is_integral<T>::value> print_ip(const T& ip)
{
    for (size_t i = sizeof(T); i != 0 ; i--)
        std::cout << ((ip >> (8*(i-1))) & 0xff) << (i != 1 ? "." : "");
}

/**
 * @brief IP в строковом виде.
 * @tparam T - тип std::string.
 * @param ip - значение ip-адреса представленное в виде std::string.
 */
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(T ip)
{
    std::cout << ip;
}

template <typename T>
struct is_container : std::false_type { };
template <typename... Ts> struct is_container<std::list<Ts...> > : std::true_type { };
template <typename... Ts> struct is_container<std::vector<Ts...> > : std::true_type { };

/**
 * @brief IP в контейнерном.
 * @tparam T - контейнерный тип: vactor / list.
 * @param ip - значение ip-адреса представленное в виде контейнера.
 */
template <typename T>
std::enable_if_t<is_container<T>::value>
print_ip(const T& ip)
{
    for (const auto& item : ip)
    {
        std::cout << item;
        std::cout <<  (&item != &ip.back() ? "." : "");
    }
}

//template <typename T>
//struct is_tuple : std::false_type {};
//template <typename... Args>
//struct is_tuple<std::tuple<Args...>> : std::true_type {};

/**
 * @brief Функция main
 */
int main(int, char *[])
{
    print_ip(char(-1));
    std::cout << std::endl;

    print_ip(short(0));
    std::cout << std::endl;

    print_ip(int(2130706433));
    std::cout << std::endl;

    print_ip(long(8875824491850138409));
    std::cout << std::endl;

    print_ip(std::string("127.0.0.1"));
    std::cout << std::endl;

    print_ip(std::vector<uint>{127, 0, 0, 1});
    std::cout << std::endl;

    print_ip(std::list<uint>{127, 0, 0, 1});
    std::cout << std::endl;

    return 0;
}
