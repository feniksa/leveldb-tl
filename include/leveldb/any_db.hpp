#pragma once

#include <string>
#include <memory>

#include <leveldb/db.h>

namespace leveldb
{
    class AnyDB
    {
    public:
        virtual ~AnyDB() noexcept = default;

        virtual Status Get(const Slice &key, std::string &value) noexcept = 0;
        virtual Status Put(const Slice &key, const Slice &value) noexcept = 0;
        virtual Status Delete(const Slice &key) noexcept = 0;

        virtual std::unique_ptr<Iterator> NewIterator() noexcept = 0;
    };

    template <typename T>
    class AsIterator final : public Iterator
    {
        T impl;
    public:
        AsIterator(const T &origin) : impl(origin)
        {}

        AsIterator(T &&origin) : impl(origin)
        {}

        bool Valid() const override { return impl.Valid(); }
        void SeekToFirst() override { impl.SeekToFirst(); }
        void SeekToLast() override { impl.SeekToLast(); }

        void Seek(const Slice &target) override
        { impl.Seek(target); }

        void Next() override { impl.Next(); }
        void Prev() override { impl.Prev(); }

        Slice key() const override { return impl.key(); }
        Slice value() const override { return impl.value(); }

        Status status() const override { return impl.status(); }
    };
}