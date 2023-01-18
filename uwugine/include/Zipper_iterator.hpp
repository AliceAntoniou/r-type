#pragma once

#include "Container.hpp"
#include "Registery.hpp"
#include <algorithm>
#include <iostream>

namespace uwugine
{
    typedef std::size_t entity_t;
    template <class... Classes> class Zipper_iterator {
        public:
            // iterator on Container
            template <class Class> using container_t = typename uwugine::Container<Class>;

            // iterator on Container
            template <class Class> using iterator_t = typename uwugine::Container<Class>::iterator;

            // reference of value at iterator position for 1 Container
            template <class Class> using it_reference_t = Class &;

            // iterator on Containers
            using iterator_tuple = typename std::tuple<iterator_t<Classes>...>;

            // Containers
            using containers_tuple = typename std::tuple<container_t<Classes>...>;

            // tuple of reference for each component at zipper position
            using value_type = typename std::tuple<it_reference_t<Classes>...>;

            using iterator = Zipper_iterator<Classes...>;

            // current zipper position
            iterator_tuple _current;

            Zipper_iterator() = default;

            /**
             * @brief Construct a new Zipper_iterator
             *
             * @param r
             */
            Zipper_iterator(Registery &r) : _current(std::make_tuple(r.get_components<Classes>().begin()...))
            {
                auto seq = std::make_index_sequence<std::tuple_size<iterator_tuple>::value>{};

                if (get_min_current_max(seq) == 0) {
                    _is_end = true;
                    return;
                }
                while (!_is_end && !all_idxs_equals(seq)) {
                    incr_all(seq, 0);
                }
            }

            Zipper_iterator(Zipper_iterator const &z) = default;

            /**
             * @brief Increment
             *
             * @return Zipper_iterator
             */
            Zipper_iterator operator++()
            {
                auto seq = std::make_index_sequence<std::tuple_size<iterator_tuple>::value>{};

                incr_all(seq, 1);
                while (!_is_end && !all_idxs_equals(seq)) {
                    incr_all(seq, 0);
                }
                return *this;
            };
            /**
             * @brief Increment
             *
             * @return Zipper_iterator
             */
            Zipper_iterator operator++(int)
            {
                auto seq = std::make_index_sequence<std::tuple_size<iterator_tuple>::value>{};

                incr_all(seq, 1);
                while (!_is_end && !all_idxs_equals(seq)) {
                    incr_all(seq, 0);
                }
                return *this;
            };
            /**
             * @brief Increment
             *
             * @param add
             * @return Zipper_iterator&
             */
            Zipper_iterator &operator+(int add)
            {
                for (int i = 0; i < add; i++) {
                    (*this)++;
                }
                return *this;
            }
            [[deprecated("Use get() instead.")]] value_type operator*()
            {
                return to_value(std::make_index_sequence<std::tuple_size<iterator_tuple>::value>{});
            }
            [[deprecated("Use get() instead.")]] value_type operator->() { return operator*(); }

            /**
             * @brief Return the Class asked in template
             *
             * @tparam Class
             * @return Class&
             */
            template <class Class> Class &get() const { return *std::get<iterator_t<Class>>(_current); }

            // iterator_tuple begin() { return _begin; }

            // iterator_tuple end() { return _end; }

            /**
             * @return true The iterator can't iterate further
             */
            bool is_end() { return _is_end; }

            friend bool operator==(Zipper_iterator const &lhs, Zipper_iterator const &rhs) { return (lhs._current == rhs._current); }
            friend bool operator!=(Zipper_iterator const &lhs, Zipper_iterator const &rhs) { return (lhs._current != rhs._current); }

        private:
            bool _is_end = false;

            template <std::size_t... Is> constexpr size_t get_min_current_max(std::index_sequence<Is...>)
            {
                return std::min({std::get<Is>(_current).get_max()...});
            }

            template <std::size_t... Is> constexpr size_t get_max_current_pos(std::index_sequence<Is...>)
            {
                return std::max({std::get<Is>(_current).get_index()...});
            }

            template <std::size_t... Is> constexpr size_t isSameIdx(std::index_sequence<Is...>)
            {
                return std::max({std::get<Is>(_current).get_index()...});
            }

            template <typename Class> size_t incr_if(size_t max_idx, Class &n)
            {
                while (max_idx > n.get_index()) {
                    ++n;
                }
                return n.get_index();
            }

            template <std::size_t... Is> bool all_idxs_equals(std::index_sequence<Is...>)
            {
                std::vector<size_t> idxs;

                (idxs.push_back(std::get<Is>(_current).get_index()), ...);
                return (std::adjacent_find(idxs.begin(), idxs.end(), std::not_equal_to<>()) == idxs.end());
            }

            template <std::size_t... Is> void incr_all(std::index_sequence<Is...> seq, size_t add)
            {
                if (_is_end)
                    return;
                size_t idx = get_max_current_pos(std::make_index_sequence<std::tuple_size<iterator_tuple>::value>{}) + add;

                try {
                    (incr_if(idx, std::get<Is>(_current)), ...);
                } catch (const std::out_of_range &) {
                    _is_end = true;
                }
            }

            // return a tuple of reference to components .
            template <size_t... Is> value_type to_value(std::index_sequence<Is...>)
            {
                return std::tuple<Classes &...>({*std::get<Is>(_current)...});
            }
    };
};
