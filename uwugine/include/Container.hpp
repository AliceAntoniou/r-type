/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Engine
*/

#pragma once

#include "Exception.hpp"
#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <variant>
#include <vector>

static constexpr float max_density = 0.4;
static constexpr float min_density = 0.2;

namespace uwugine
{
    using Entity = std::size_t;
    template <typename Component> class SparseArray;
    template <typename Component> class IndexedVector {
        public:
            struct Index {
                    Component comp;
                    size_t idx;
            };

            using container_t = std::vector<typename IndexedVector<Component>::Index>;
            using size_type = typename container_t::size_type;
            using iterator = typename container_t::iterator;
            using const_iterator = typename container_t::const_iterator;

            IndexedVector(void) noexcept = default;
            IndexedVector(SparseArray<Component> &&a)
            {
                size_t i = 0;

                for (auto &&it : a) {
                    if (a.is_at(i))
                        insert_at(i, std::move(*it));
                    i++;
                }
            }

            IndexedVector(IndexedVector const &) = default;
            IndexedVector(IndexedVector &&) noexcept = default;
            ~IndexedVector(void) = default;

            IndexedVector &operator=(IndexedVector const &) = default;
            IndexedVector &operator=(IndexedVector &&) noexcept = default;

            Component &operator[](std::size_t i)
            {
                std::vector<std::size_t>::const_iterator it = std::lower_bound(idx.begin(), idx.end(), i);

                if (*it != i)
                    throw Exception("There is no data at this index");
                return data[it - idx.begin()].comp;
            }
            Component const &operator[](std::size_t i) const
            {
                std::vector<std::size_t>::const_iterator it = std::lower_bound(idx.begin(), idx.end(), i);

                if (*it != i)
                    throw Exception("There is no data at this index");
                return data[it - idx.begin()].comp;
            }

            iterator begin() { return data.begin(); }
            const_iterator begin() const { return data.begin(); }
            const_iterator cbegin() const { return data.cbegin(); }

            iterator end() { return data.end(); }
            const_iterator end() const { return data.end(); }
            const_iterator cend() const { return data.cend(); }

            std::size_t size() const
            {
                if (idx.size() == 0)
                    return 0;
                return idx[idx.size() - 1] + 1;
            }

            Component &insert_at(size_type pos, Component const &comp)
            {
                if (std::find(idx.begin(), idx.end(), pos) != idx.end()) {
                    data[pos].comp = comp;
                    return data[pos].comp;
                }
                std::vector<std::size_t>::iterator idx_it = std::lower_bound(idx.begin(), idx.end(), pos);
                const_iterator data_it = data.begin() + (idx_it - idx.begin());

                data.insert(data_it, {comp, pos});
                idx.insert(idx_it, pos);
                return data[pos].comp;
            }
            Component &insert_at(size_type pos, Component &&comp)
            {
                if (std::find(idx.begin(), idx.end(), pos) != idx.end()) {
                    data[pos].comp = std::move(comp);
                    return data[pos].comp;
                }
                std::vector<std::size_t>::iterator idx_it = std::lower_bound(idx.begin(), idx.end(), pos);
                const_iterator data_it = data.begin() + (idx_it - idx.begin());

                data.insert(data_it, {std::move(comp), pos});
                idx.insert(idx_it, pos);
                return data[pos].comp;
            }
            size_t get_first_pos()
            {
                size_t i = 0;

                if (idx.size() == 0)
                    return 0;
                auto it = idx.begin();
                while (it != idx.end()) {
                    if (*it + 1 == *(it + 1)) {
                        it++;
                        continue;
                    }
                    return *it + 1;
                }
                return *(idx.end());
            }
            Component &insert_at(iterator &pos, Component &comp)
            {
                size_t i = pos - data.begin();
                std::vector<std::size_t>::iterator idx_it = idx.begin() + i;
                data.insert(pos, {comp, i});
                idx.insert(idx_it, i);
            }
            Component &insert_at(iterator &pos, Component &&comp)
            {
                size_t i = pos - data.begin();
                std::vector<std::size_t>::iterator idx_it = idx.begin() + i;
                data.insert(pos, {std::move(comp), i});
                idx.insert(idx_it, i);
            }

            template <class... Params> Component &emplace_at(size_type pos, Params &&...args)
            {
                if (std::find(idx.begin(), idx.end(), pos) != idx.end()) {
                    data[pos].comp = Component{std::forward<Params>(args)...};
                    return data[pos].comp;
                }
                std::vector<std::size_t>::iterator idx_it = std::lower_bound(idx.begin(), idx.end(), pos);
                const_iterator data_it = data.begin() + (idx_it - idx.begin());

                data.insert(data_it, {Component{std::forward<Params>(args)...}, pos});
                idx.insert(idx_it, pos);
                return data[pos].comp;
            }

            bool erase(size_type pos)
            {
                std::vector<std::size_t>::iterator idx_it = std::lower_bound(idx.begin(), idx.end(), pos);
                if (*idx_it != pos)
                    return false;
                const_iterator data_it = data.begin() + (idx_it - idx.begin());
                data.erase(data_it);
                idx.erase(idx_it);
                return true;
            }

            size_type get_index(Component const &comp) const
            {
                for (auto i = data.begin(); i != data.end(); i++) {
                    if (std::addressof(i->second) == std::addressof(comp))
                        return i->first;
                }
                throw std::out_of_range("get_index");
                return 0;
            }

            bool is_at(size_type pos)
            {
                std::vector<std::size_t>::const_iterator it = std::lower_bound(idx.begin(), idx.end(), pos);

                return *it == pos;
            }

            size_t get_max()
            {
                if (idx.size() == 0)
                    return 0;
                return *(idx.end() - 1) + 1;
            }

        private:
            container_t data;
            std::vector<std::size_t> idx;
    };
    template <typename Component> class SparseArray {
        public:
            using container_t = std::vector<std::optional<Component>>;
            using size_type = typename container_t::size_type;
            using iterator = typename container_t::iterator;
            using const_iterator = typename container_t::const_iterator;

            SparseArray(void) noexcept = default;
            SparseArray(IndexedVector<Component> &&a)
            {
                for (auto &&it : a) {
                    insert_at(it.idx, std::move(it.comp));
                }
            }

            SparseArray(SparseArray const &) = default;
            SparseArray(SparseArray &&) noexcept = default;
            ~SparseArray(void) = default;

            SparseArray &operator=(SparseArray const &) = default;
            SparseArray &operator=(SparseArray &&) noexcept = default;

            Component &operator[](std::size_t i)
            {
                if (data[i].has_value())
                    return *data[i];
                throw Exception("There is no data at this index");
            }
            Component const &operator[](std::size_t i) const
            {
                if (data[i].has_value())
                    return *data[i];
                throw Exception("There is no data at this index");
            }

            iterator begin() { return data.begin(); }
            const_iterator begin() const { return data.begin(); }
            const_iterator cbegin() const { return data.cbegin(); }

            iterator end() { return data.end(); }
            const_iterator end() const { return data.end(); }
            const_iterator cend() const { return data.cend(); }

            std::size_t size() const { return data.size(); }

            Component &insert_at(size_type pos, Component const &comp)
            {
                while (data.size() < pos) {
                    data.push_back(std::nullopt);
                }
                if (data.size() == pos) {
                    data.push_back(comp);
                } else {
                    data[pos] = comp;
                }
                return *data[pos];
            }
            Component &insert_at(size_type pos, Component &&comp)
            {
                while (data.size() < pos) {
                    data.push_back(std::nullopt);
                }
                if (data.size() == pos) {
                    data.push_back(std::move(comp));
                } else {
                    data[pos] = std::move(comp);
                }
                return *data[pos];
            }
            size_t get_first_pos()
            {
                size_t pos = 0;

                try {
                    for (pos = 0; data.at(pos); pos++)
                        ;
                } catch (const std::exception &) {
                    return pos;
                }
                return pos;
            }
            Component &insert_at(iterator &pos, Component const &comp) { return *data.insert(pos, (comp)); }
            Component &insert_at(iterator &pos, Component &&comp) { return *data.insert(pos, (std::move(comp))); }

            template <class... Params> Component &emplace_at(size_type pos, Params &&...args)
            {
                while (data.size() < pos) {
                    data.push_back(std::nullopt);
                }
                if (data.size() == pos) {
                    data.push_back(std::forward<Params>(args)...);
                } else {
                    data[pos] = std::move(Component{std::forward<Params>(args)...});
                }
                return *data[pos];
            }

            bool erase(size_type pos)
            {
                if (data.size() <= pos)
                    return false;
                data[pos] = std::nullopt;
                while (data.size() > 0 && *(data.end() - 1) == std::nullopt) {
                    data.pop_back();
                }
                return true;
            }

            size_type get_index(Component const &comp) const
            {
                for (auto i = data.begin(); i != data.end(); i++) {
                    if (std::addressof(**i) == std::addressof(comp))
                        return i->first;
                }
                throw std::out_of_range("get_index");
                return 0;
            }

            bool is_at(size_type pos)
            {
                if (data.size() <= pos)
                    return false;
                return data[pos].has_value();
            }

        private:
            container_t data;
    };
    template <typename Component> class Container {
        public:
            class iterator {
                public:
                    iterator(void) noexcept = delete;
                    iterator(const SparseArray<Component> &c, typename std::vector<std::optional<Component>>::iterator &&a)
                        : it(a), max(c.end() - c.begin()), is_sparse(true), idx(a - c.cbegin()),
                          sparse(&std::get<typename std::vector<std::optional<Component>>::iterator>(it))
                    {
                        if (max == 0)
                            return;
                        while (!(**sparse).has_value()) {
                            if (idx + 1 >= max)
                                return;
                            idx++;
                            (*sparse)++;
                        }
                    }
                    iterator(IndexedVector<Component> &c, typename std::vector<typename IndexedVector<Component>::Index>::iterator &&a)
                        : it(a), max(c.get_max()), is_sparse(false), idx(0),
                          indexed(&std::get<typename std::vector<typename IndexedVector<Component>::Index>::iterator>(it))
                    {
                        if (max == 0)
                            return;
                        idx = (*indexed)->idx;
                    }

                    iterator(iterator const &copy) : it(copy.it), idx(copy.idx), max(copy.max), is_sparse(copy.is_sparse)
                    {
                        if (is_sparse) {
                            sparse = &std::get<typename std::vector<std::optional<Component>>::iterator>(it);
                        } else {
                            indexed = &std::get<typename std::vector<typename IndexedVector<Component>::Index>::iterator>(it);
                        }
                    }
                    iterator(iterator &&copy) noexcept
                        : it(std::move(copy.it)), idx(std::move(copy.idx)), max(std::move(copy.max)), is_sparse(std::move(copy.is_sparse))
                    {
                        if (is_sparse) {
                            sparse = &std::get<typename std::vector<std::optional<Component>>::iterator>(it);
                        } else {
                            indexed = &std::get<typename std::vector<typename IndexedVector<Component>::Index>::iterator>(it);
                        }
                    }
                    ~iterator(void) = default;

                    iterator &operator=(iterator const &) = default;
                    iterator &operator=(iterator &&) noexcept = default;

                    /**
                     * @brief Increment on the container
                     *
                     * @return iterator
                     */
                    iterator operator++()
                    {
                        if (!is_sparse) {
                            if (idx + 1 >= max)
                                throw std::out_of_range("Container<IndexedArray>::iterator::operator++");
                            (*indexed)++;
                            idx++;
                            return *this;
                        }
                        do {
                            if (idx + 1 >= max)
                                throw std::out_of_range("Container<SparseArray>::iterator::operator++");
                            idx++;
                            (*sparse)++;
                        } while (!(**sparse).has_value());
                        return *this;
                    }
                    /**
                     * @brief Increment on the container
                     *
                     * @return iterator
                     */
                    iterator operator++(int)
                    {
                        if (!is_sparse) {
                            if (idx + 1 >= max)
                                throw std::out_of_range("Container<IndexedArray>::iterator::operator++");
                            (*indexed)++;
                            idx++;
                            return *this;
                        }
                        do {
                            if (idx + 1 >= max)
                                throw std::out_of_range("Container<SparseArray>::iterator::operator++");
                            idx++;
                            (*sparse)++;
                        } while (!(**sparse).has_value());
                        return *this;
                    }
                    /**
                     * @brief Desincrement on the container
                     *
                     * @return iterator
                     */
                    iterator operator--()
                    {
                        if (!is_sparse) {
                            if (idx == 0)
                                throw std::out_of_range("Container<IndexedArray>::iterator::operator--");
                            (*indexed)--;
                            idx--;
                            return *this;
                        }
                        do {
                            if (idx == 0)
                                throw std::out_of_range("Container<SparseArray>::iterator::operator--");
                            (*sparse)--;
                            idx--;
                        } while (!(**sparse).has_value());
                        return *this;
                    }
                    /**
                     * @brief Increment on the container
                     *
                     * @param to_add
                     * @return iterator
                     */
                    iterator operator+(size_t to_add)
                    {
                        if (!is_sparse) {
                            if (idx + to_add >= max)
                                throw std::out_of_range("Container<IndexedArray>::iterator::operator+");
                            (*indexed) += to_add;
                            idx += to_add;
                            return *this;
                        }
                        auto &it_m = std::get<typename std::vector<std::optional<Component>>::iterator>(it);
                        for (size_t i = 0; i < to_add; i++) {
                            do {
                                if (idx + 1 >= max)
                                    throw std::out_of_range("Container<SparseArray>::iterator::operator+");
                                idx++;
                                (*sparse)++;
                            } while (!(**sparse).has_value());
                        }
                        return *this;
                    }
                    /**
                     * @brief Return the component
                     *
                     * @return Component&
                     */
                    Component &operator*() const
                    {
                        if (!is_sparse) {
                            return (**indexed).comp;
                        }
                        return ***sparse;
                    }
                    /**
                     * @brief Return the component
                     *
                     * @return Component&
                     */
                    Component &operator->() const
                    {
                        if (!is_sparse) {
                            return (**indexed).comp;
                        }
                        return ***sparse;
                    }

                    friend bool operator==(iterator const &lhs, iterator const &rhs) { return std::addressof(lhs) == std::addressof(rhs); }
                    friend bool operator!=(iterator const &lhs, iterator const &rhs) { return std::addressof(lhs) == std::addressof(rhs); }

                    std::variant<typename std::vector<std::optional<Component>>::iterator,
                        typename std::vector<typename IndexedVector<Component>::Index>::iterator> &
                    get_handle(void) const
                    {
                        return it;
                    }

                    std::size_t get_index(void) const { return idx; }
                    std::size_t get_max(void) const { return max; }

                private:
                    std::variant<typename std::vector<std::optional<Component>>::iterator,
                        typename std::vector<typename IndexedVector<Component>::Index>::iterator>
                        it;
                    bool is_sparse = true;
                    typename std::vector<std::optional<Component>>::iterator *sparse = nullptr;
                    typename std::vector<typename IndexedVector<Component>::Index>::iterator *indexed = nullptr;
                    std::size_t idx = 0;
                    std::size_t max = 0;
            };
            using const_iterator = const iterator;

            Container(void) noexcept
            {
                is_sparse = true;
                array = SparseArray<Component>();
                sparse = &std::get<SparseArray<Component>>(array);
            }

            Container(Container const &c) : is_sparse(c.is_sparse), value_nbr(c.value_nbr)
            {
                if (is_sparse) {
                    array = std::get<SparseArray<Component>>(c.array);
                    sparse = &std::get<SparseArray<Component>>(array);
                } else {
                    array = std::get<IndexedVector<Component>>(c.array);
                    indexed = &std::get<IndexedVector<Component>>(array);
                }
            };
            Container(Container &&) noexcept = default;
            ~Container(void) = default;

            Container &operator=(Container const &) = default;
            Container &operator=(Container &&) noexcept = default;

            /**
             * @brief Return the component at index i
             *
             * @param i Index
             * @return Component const&
             */
            Component &operator[](std::size_t i)
            {
                if (is_sparse)
                    return (*sparse)[i];
                return (*indexed)[i];
            }
            /**
             * @brief Return the component at index i
             *
             * @param i Index
             * @return Component const&
             */
            Component const &operator[](std::size_t i) const
            {
                if (is_sparse)
                    return (*sparse)[i];
                return (*indexed)[i];
            }

            /**
             * @brief Begin of the container
             *
             * @return iterator
             */
            iterator begin()
            {
                if (is_sparse)
                    return iterator(*sparse, sparse->begin());
                return iterator(*indexed, indexed->begin());
            }
            /**
             * @brief Begin of the container
             *
             * @return const_iterator
             */
            const_iterator begin() const
            {
                if (is_sparse)
                    return iterator(*sparse, sparse->begin());
                return iterator(*indexed, indexed->begin());
            }
            /**
             * @brief Begin of the container
             *
             * @return const_iterator
             */
            const_iterator cbegin() const
            {
                if (is_sparse)
                    return iterator(*sparse, sparse->cbegin());
                return iterator(*indexed, indexed->cbegin());
            }

            /**
             * @brief End of the container
             *
             * @return iterator
             */
            iterator end()
            {
                if (is_sparse)
                    return iterator(*sparse, sparse->end());
                return iterator(*indexed, indexed->end());
            }
            /**
             * @brief End of the container
             *
             * @return const_iterator
             */
            const_iterator end() const
            {
                if (is_sparse)
                    return iterator(*sparse, sparse->end());
                return iterator(*indexed, indexed->end());
            }
            /**
             * @brief End of the container
             *
             * @return const_iterator
             */
            const_iterator cend() const
            {
                if (is_sparse)
                    return iterator(*sparse, sparse->cend());
                return iterator(*indexed, indexed->cend());
            }

            /**
             * @brief Size of container
             *
             * @return std::size_t
             */
            std::size_t size() const
            {
                if (is_sparse)
                    return sparse->size();
                return indexed->size();
            }

            /**
             * @brief Insert a component at pos
             *
             * @param pos Index
             * @param comp Component
             * @return Component&
             */
            Component &insert_at(std::size_t pos, Component const &comp)
            {
                value_nbr++;
                if (is_sparse) {
                    if (get_density() > min_density)
                        return sparse->insert_at(pos, comp);
                    swap();
                }
                if (get_density() < max_density)
                    return indexed->insert_at(pos, comp);
                swap();
                return sparse->insert_at(pos, comp);
            }
            /**
             * @brief Insert a component at pos
             *
             * @param pos Index
             * @param comp Component
             * @return Component&
             */
            Component &insert_at(std::size_t pos, Component &&comp)
            {
                value_nbr++;
                if (is_sparse) {
                    if (get_density() > min_density)
                        return sparse->insert_at(pos, std::move(comp));
                    swap();
                }
                if (get_density() < max_density)
                    return indexed->insert_at(pos, std::move(comp));
                swap();
                return sparse->insert_at(pos, std::move(comp));
            }

            /**
             * @return size_t First position without a component
             */
            size_t get_first_pos()
            {
                if (is_sparse) {
                    return sparse->get_first_pos();
                }
                return indexed->get_first_pos();
            }

            /**
             * @brief Insert a component at pos
             *
             * @param pos Container iterator
             * @param comp Component
             * @return Component&
             */
            Component &insert_at(iterator pos, Component &comp)
            {
                value_nbr++;
                if (is_sparse) {
                    if (get_density() > min_density)
                        return sparse->insert_at(
                            std::get<typename std::vector<std::optional<Component>>::iterator>(pos.get_handle()), comp);
                    swap();
                }
                if (get_density() < max_density)
                    return indexed->insert_at(std::get<typename std::vector<Component>::iterator>(pos.get_handle()), comp);
                swap();
                return sparse->insert_at(std::get<typename std::vector<std::optional<Component>>::iterator>(pos.get_handle()), comp);
            }
            /**
             * @brief Insert a component at pos
             *
             * @param pos Container iterator
             * @param comp Component
             * @return Component&
             */
            Component &insert_at(iterator pos, Component &&comp)
            {
                value_nbr++;
                if (is_sparse) {
                    if (get_density() > min_density)
                        return sparse->insert_at(
                            std::get<typename std::vector<std::optional<Component>>::iterator>(pos.get_handle()), std::move(comp));
                    swap();
                }
                if (get_density() < max_density)
                    return indexed->insert_at(std::get<typename std::vector<Component>::iterator>(pos.get_handle()), std::move(comp));
                swap();
                return sparse->insert_at(
                    std::get<typename std::vector<std::optional<Component>>::iterator>(pos.get_handle()), std::move(comp));
            }

            /**
             * @brief Emplace a new component at pos
             *
             * @param pos Index
             * @param args Component constructor arguments
             * @return Component&
             */
            template <class... Params> Component &emplace_at(std::size_t pos, Params &&...args)
            {
                value_nbr++;
                if (is_sparse) {
                    if (get_density() > min_density)
                        return sparse->emplace_at(pos, args...);
                    swap();
                }
                if (get_density() < max_density)
                    return indexed->emplace_at(pos, args...);
                swap();
                return sparse->emplace_at(pos, args...);
            }

            /**
             * @brief Erase the component at pos
             *
             * @param pos Index
             */
            void erase(std::size_t pos)
            {
                if (is_sparse) {
                    if (sparse->erase(pos))
                        value_nbr--;
                    return;
                }
                if (indexed->erase(pos))
                    value_nbr--;
            }

            /**
             * @param comp The component
             * @return std::size_t Index of the component
             */
            std::size_t get_index(Component const &comp) const
            {
                if (is_sparse)
                    return sparse->get_inex(comp);
                return indexed->get_inex(comp);
            }

            /**
             * @brief Check if there is a component at pos index
             *
             * @param pos index
             */
            bool is_at(size_t pos)
            {
                if (is_sparse)
                    return sparse->is_at(pos);
                return indexed->is_at(pos);
            }

            /**
             * @brief Get the density of the container (number of value / max)
             *
             * @return float between 0 and 1
             */
            float get_density(void)
            {
                return 1;
                if (is_sparse) {
                    if (sparse->size() == 0)
                        return 1;
                    return static_cast<float>(value_nbr) / static_cast<float>(sparse->size());
                }
                if (indexed->size() == 0)
                    return 1;
                return static_cast<float>(value_nbr) / static_cast<float>(indexed->size());
            }

            /**
             * @brief Swap between SparseArray and IndexedVector
             *
             */
            void swap(void)
            {
                if (is_sparse) {
                    array = IndexedVector(std::move(*sparse));
                    is_sparse = false;
                    sparse = nullptr;
                    indexed = &std::get<IndexedVector<Component>>(array);
                    return;
                }
                array = SparseArray(std::move(*indexed));
                is_sparse = true;
                indexed = nullptr;
                sparse = &std::get<SparseArray<Component>>(array);
            }

        private:
            std::variant<SparseArray<Component>, IndexedVector<Component>> array;
            bool is_sparse = true;
            SparseArray<Component> *sparse = nullptr;
            IndexedVector<Component> *indexed = nullptr;
            size_t value_nbr = 0;
    };
}
