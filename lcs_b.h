#pragma once

#include <vector>
#include <queue>
#include <optional>

template<typename InL, typename InR> auto lcs_b(InL const& a, InR const& b, std::vector<int>& out) -> int
{
    using node_t = std::pair<int, int>;
    auto right = [&](node_t n) -> std::optional<node_t>
    {
        if( n.first > a.size())
            return std::nullopt;
        return {{n.first + 1, n.second}};
    };
    auto down = [&](node_t n) -> std::optional<node_t>
    {
        if( n.second  >= b.size())
            return std::nullopt;
        return {{n.first, n.second + 1}};
    };
    auto diag = [&](node_t n) -> std::optional<node_t>
    {
        if( n.first + 1 >= a.size() || n.second + 1 >= b.size() || a[n.first] != b[n.second])
            return std::nullopt;
        return {{n.first + 1, n.second + 1}};
    };
    auto offset = [&](node_t n)
    {
        return n.second * (a.size()+ 1) + n.first;
    };
    // 'visited' workspace
    std::vector<bool> visited ((a.size() + 1) * (b.size() + 1));
    // 'previous' record
    std::vector<node_t> previous((a.size() + 1) * (b.size() + 1));
    // work queue
    std::queue<node_t> q;
    auto push = [&](node_t n, node_t u)
    {
        if( !visited[offset(n)])
        {
            visited[offset(n)] = true;
            previous[offset(n)] = u;
            q.push(n);
        }
    };

    q.push({0, 0});
    visited[0] = true;
    while( !q.empty())
    {
		auto u = q.front(); q.pop();
        auto r = right(u);
        if(r)
            push(r.value(), u);
        auto dn = down(u);
        if(dn )
            push(dn.value(), u);
        auto dg = diag(u);
        if(dg)
            push(dg.value(), u);
    }
    int ecnt{0};
    node_t p { a.size(), b.size()};
	do
	{
		p = previous[offset(p)];
		if (diag(p))
        {
            ++ecnt;
			out[p.first] = 1;
        }
	} while (p != node_t{0, 0});
    return ecnt;
}
