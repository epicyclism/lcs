#pragma once

#include <vector>
#include <queue>

using v_t = std::pair<uint32_t, uint32_t>;

struct two_d
{
    const uint32_t x_;
    const uint32_t y_;
    two_d() = delete;
    two_d(uint32_t x, uint32_t y) : x_ { x }, y_{ y}
    {}
    size_t capacity() const
    {
        return x_ * y_;
    }
    size_t operator()(uint32_t x, uint32_t y) const
    {
        return y * x_ + x;
    }
    size_t operator()(v_t v) const
    {
        return v.second * x_ + v.first;
    }
    v_t operator()(size_t v) const
    {
        return {v % y_, v / y_}; 
    }
    bool valid_x(uint32_t x) const
    {
        return x < x_;
    }
    bool valid_y(uint32_t y) const
    {
        return y < y_;
    }
    bool valid_xy(uint32_t x, uint32_t y) const
    {
        return x < x_ && y < y_;
    }
    bool valid_v(v_t v) const
    {
        return v.first < x_ && v.second < y_;
    }
};

template<typename InL, typename InR, typename Out> auto lcs_n(InL const& a, InR const& b, Out& out)
{
    two_d d2{static_cast<uint32_t>(std::size(a)), static_cast<uint32_t>(std::size(b))};
    std::vector<bool> visited(d2.capacity());
    std::vector<v_t> previous(d2.capacity());

    v_t begin{ 0, 0};
    v_t end { d2.x_ - 1, d2.y_ - 1};
	std::queue<v_t> q;
    q.push(begin);
    visited[0] = true;
    while(!q.empty())
    {
	    auto u = q.front();
        q.pop();
        if(u == end)
            break;
        if(d2.valid_xy(u.first + 1, u.second + 1))
        {
            v_t vn{ u.first + 1, u.second + 1};
            while(d2.valid_v(vn) && !visited[d2(vn)] && a[vn.first] == b[vn.second])
            {
                visited[d2(vn)] = true;
                previous[d2(vn)] = u;
                q.push(vn);
                u = vn;
                ++vn.first;
                ++vn.second;
            }
        }
        else
        {
            v_t vnr{ u.first + 1, u.second};
            if(d2.valid_v(vnr) && !visited[d2(vnr)])
            {
                visited[d2(vnr)] = true;
                previous[d2(vnr)] = u;
                q.push(vnr);
            }
            v_t vnl{ u.first, u.second + 1};
            if(d2.valid_v(vnl) && !visited[d2(vnl)])
            {
                visited[d2(vnl)] = true;
                previous[d2(vnl)] = u;
                q.push(vnl);
            }
        }
    }
    auto cnt { 0 };
    auto v { end };
    do
    {
        if(a[v.first] == b[v.second])
        {
            out[d2(v)] = 1;
            ++cnt;
        }
        v = previous[d2(v)];
    } while (v != begin);

    if(a[v.first] == b[v.second])
    {
        out[d2(v)] = 1;
        ++cnt;
    }
    return cnt;
}
