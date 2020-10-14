

#include <utility>
#include <tuple>

namespace sgpl {

namespace internal {

// adapted from https://stackoverflow.com/a/15418923
template<typename> struct LibraryInstantiator;

template<typename ...T>
struct LibraryInstantiator<std::tuple<T...>> {
  using type = sgpl::OpLibrary<T...>;
};

} // namespace internal

template<typename Library, typename... Ops>
class OpLibraryCoupler
: public internal::LibraryInstantiator< decltype(
  std::tuple_cat(
    std::declval<typename Library::parent_t>(),
    std::declval<std::tuple<Ops...>>()
  )
) >::type
{};


} //namespace sgpl
