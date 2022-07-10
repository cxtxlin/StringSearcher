#ifndef REGEXINFILE_BI_ISTREAM_ITERATOR_H
#define REGEXINFILE_BI_ISTREAM_ITERATOR_H

#include <iterator>

template<
        typename T = char
        , typename CharType = char
        , typename TraitsType = std::char_traits<CharType>
        , typename DistanceType = std::ptrdiff_t
>
class bi_istream_iterator
        : public std::iterator<
                std::input_iterator_tag
                , T
                , DistanceType
                , const T*
                , const T&
        >
{
public:
    typedef CharType                                 char_type;
    typedef TraitsType                               traits_type;
    typedef std::basic_istream<CharType, TraitsType> istream_type;

private:
    istream_type*   M_Stream;
    std::streampos  M_Pos;
    std::streamsize M_StreamSize;

public:
    explicit bi_istream_iterator(istream_type & _istream
                                 , std::streampos _pos = -1)
        : M_Stream(std::__addressof(_istream))
        , M_Pos(_pos)
    {
        std::streampos currentStreamPos = M_Stream -> tellg();
        M_Stream -> seekg(0, std::ios_base::end);
        M_StreamSize = M_Stream -> tellg();
        M_Stream ->seekg(currentStreamPos);

        if ((_pos < 0) || (_pos > M_StreamSize))
            M_Pos = M_StreamSize;
    }

    bi_istream_iterator()
        : M_Stream(nullptr)
        , M_Pos(0)
        , M_StreamSize(0)
    { }

    bi_istream_iterator(const bi_istream_iterator & obj)
        : M_Stream(obj.M_Stream)
        , M_Pos(obj.M_Pos)
        , M_StreamSize(obj.M_StreamSize)
    { }

    bi_istream_iterator & operator=(const bi_istream_iterator &) = default;
    ~bi_istream_iterator() = default;

    T operator*() const
    {
        if (M_Stream)
        {
            std::streampos currentStreamPos = M_Stream -> tellg();
            M_Stream -> seekg(M_Pos);
            T value = M_Stream -> peek();
            M_Stream -> seekg(currentStreamPos);

            return value;
        }
        else
            return -1;
    }

    bi_istream_iterator & operator++()
    {
        if (M_Pos < M_StreamSize)
            M_Pos += 1;
        return *this;
    }

    bi_istream_iterator operator++(int)
    {
        bi_istream_iterator tmp = *this;
        operator++();
        return tmp;
    }

    bi_istream_iterator & operator--()
    {
        if (M_Pos > 0)
            M_Pos -= 1;
        return *this;
    }

    bi_istream_iterator operator--(int)
    {
        bi_istream_iterator tmp = *this;
        operator--();
        return *this;
    }

private:
    bool equal(const bi_istream_iterator& obj) const
    {
        return M_Stream == obj.M_Stream
            && M_Pos == obj.M_Pos;
    }

    friend bool
    operator==(const bi_istream_iterator& left, const bi_istream_iterator& right)
    {
        return left.equal(right);
    }

    friend bool
    operator!=(const bi_istream_iterator& left, const bi_istream_iterator& right)
    {
        return !left.equal(right);
    }
};

#endif //REGEXINFILE_BI_ISTREAM_ITERATOR_H
