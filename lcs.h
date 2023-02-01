#pragma once

#include <vector>
#include <queue>

struct v_full_t
{
	bool diag_    = false;// diagonal leaving here
	bool visited_ = false;// vertex seen
	int  prev_    = 0;    // the previous vertex on this path
	int  dist_    = 0;    // how far from the start
};

inline bool is_diag(v_full_t const& vft) { return vft.diag_; }
inline void set_diag(v_full_t& vft) { vft.diag_ = true; }
inline bool is_visited(v_full_t const& vft) { return vft.visited_; }
inline void set_visited(v_full_t& vft) { vft.visited_ = true; }
inline int  prev(v_full_t const& vft) { return vft.prev_; }
inline void set_prev(v_full_t& vft, int prev) { vft.prev_ = prev; }
inline int  dist(v_full_t const& vft) { return vft.dist_; }
inline void set_dist(v_full_t& vft, int dist) { vft.dist_ = dist; }

struct v_brief_t
{
	static constexpr uint16_t diag_bit { 0x8000};
	static constexpr uint16_t visit_b  { 0x4000};
	uint32_t v_;
};

inline bool is_diag(v_brief_t const& vft) { return vft.v_ & v_brief_t::diag_bit; }
inline void set_diag(v_brief_t& vft) { vft.v_ |= v_brief_t::diag_bit; }
inline bool is_visited(v_brief_t const& vft) { return vft.v_ & v_brief_t::visit_b; }
inline void set_visited(v_brief_t& vft) { vft.v_ |=  v_brief_t::visit_b; }
inline int  prev(v_brief_t const& vft) { return vft.v_ & ~(v_brief_t::diag_bit | v_brief_t::visit_b); }
inline void set_prev(v_brief_t& vft, int prev) { vft.v_ = prev | (vft.v_ & (v_brief_t::diag_bit | v_brief_t::visit_b)); }

#if 0
template<typename G> void print_g(G const& g, size_t mx, size_t my)
{
	for (auto v : g)
		std::cout << is_diag(v);
	std::cout << "\n";
	for (size_t y = 0; y < my; ++y)
	{
		for (size_t x = 0; x < mx; ++x)
		{
			if (is_diag(g[y * mx + x]))
				std::cout << "\\";
			else
				std::cout << " ";
		}
		std::cout << "\n";
	}
}

template<typename G> void print_d(G const& g, size_t mx, size_t my)
{
	for (size_t y = 0; y < my; ++y)
	{
		for (size_t x = 0; x < mx; ++x)
			std::cout << std::setw(2) << dist(g[y * mx + x]) << " ";
		std::cout << "\n";
	}
}

template<typename G> void print_p(G const& g, size_t mx, size_t my)
{
	for (size_t y = 0; y < my; ++y)
	{
		for (size_t x = 0; x < mx; ++x)
			std::cout << std::setw(2) << prev(g[y * mx + x]) << " ";
		std::cout << "\n";
	}
}
#endif

// record distances, useful for debug and test.
template<typename V = v_full_t, typename InL, typename InR, typename Out> size_t lcs_ed(InL const& a, InR const& b, Out& out)
{
	const auto dim_x{ a.size() + 1 };
	const auto dim_y{ b.size() + 1 };
	auto xy_tog = [&](auto x, auto y) { return dim_x * y + x; };
	auto g_tox  = [&](auto p) { return p % dim_x; };
	auto across = [&](auto p) { auto r = p + 1; return (r % dim_x) ? r : -1; };
	auto down   = [&](auto p) { auto r = p + dim_x; return (r < dim_x * dim_y) ? r : -1; };
	auto diag   = [&](auto p) { auto r = p + dim_x + 1; return (r < dim_x * dim_y) ? r : -1; };

	std::vector<V> g(dim_x * dim_y);

	// build the graph. Directed, you can always go across (delete) or down (insert)
	// mark the matches which are interpreted as diagonals.
	for (size_t bc{ 0 }; bc < b.size(); ++bc)
		for (size_t ac{ 0 }; ac < a.size(); ++ac)
			if (a[ac] == b[bc])
				set_diag(g[xy_tog(ac, bc)]);

	// I think a BFS will do since a diagonal gets you closer than a horizontal or vertical.
	// can the queue be eliminated?
	std::queue<size_t> q;
	q.push(0);
	set_visited(g[0]);
	int d{ 0 };
	auto e{ xy_tog(dim_x - 1, dim_y - 1) };
	while (!q.empty())
	{
		auto u = q.front(); q.pop();
		auto ud = dist(g[u]);
		if (is_diag(g[u]))
		{
			auto v = diag(u);
			if (!is_visited(g[v]))
			{
				set_visited(g[v]);
				set_dist(g[v], ud + 1);
				set_prev(g[v], u);
				q.push(v);
			}
			if (v == e)
				break;
		}
		auto v2 = down(u);
		if (v2 != -1 && !is_visited(g[v2]))
		{
			set_visited(g[v2]);
			set_dist(g[v2], ud + 1);
			set_prev(g[v2], u);
			q.push(v2);
			if (v2 == e)
				break;
		}
		auto v3 = across(u);
		if (v3 != -1 && !is_visited(g[v3]))
		{
			set_visited(g[v3]);
			set_dist(g[v3], ud + 1);
			set_prev(g[v3], u);
			q.push(v3);
			if (v3== e)
				break;
		}
	}

	// walk the path and mark the diagonals in 'out'
	auto p = e;
	do
	{
		p = prev(g[p]);
		if (is_diag(g[p]))
			out[g_tox(p)] = 1;
	} while (p != 0);

	return dist(g[xy_tog(dim_x - 1, dim_y - 1)]);
}

// just what we want
//
template<typename V = v_full_t, typename InL, typename InR, typename Out> auto lcs_e(InL const& a, InR const& b, Out& out)
{
	const auto dim_x{ a.size() + 1 };
	const auto dim_y{ b.size() + 1 };
	auto xy_tog = [&](auto x, auto y) { return dim_x * y + x; };
	auto g_tox = [&](auto p) { return p % dim_x; };
	auto across = [&](auto p) { auto r = p + 1; return (r % dim_x) ? r : -1; };
	auto down = [&](auto p) { auto r = p + dim_x; return (r < dim_x * dim_y) ? r : -1; };
	auto diag = [&](auto p) { auto r = p + dim_x + 1; return (r < dim_x * dim_y) ? r : -1; };

	std::vector<V> g(dim_x * dim_y);

	// build the graph. Directed, you can always go across (delete) or down (insert)
	// mark the matches which are interpreted as diagonals.
	for (size_t bc{ 0 }; bc < b.size(); ++bc)
		for (size_t ac{ 0 }; ac < a.size(); ++ac)
			if (a[ac] == b[bc])
				set_diag(g[xy_tog(ac, bc)]);

	// I think a BFS will do since a diagonal gets you closer than a horizontal or vertical.
	// can the queue be eliminated?
	std::queue<size_t> q;
	q.push(0);
	set_visited(g[0]);
	int d{ 0 };
	auto e{ xy_tog(dim_x - 1, dim_y - 1) };
	while (!q.empty())
	{
		auto u = q.front(); q.pop();
		if (is_diag(g[u]))
		{
			auto v = diag(u);
			if (!is_visited(g[v]))
			{
				set_visited(g[v]);
				set_prev(g[v], u);
				q.push(v);
			}
			if (v == e)
				break;
		}
		auto v2 = down(u);
		if (v2 != -1 && !is_visited(g[v2]))
		{
			set_visited(g[v2]);
			set_prev(g[v2], u);
			q.push(v2);
			if (v2 == e)
				break;
		}
		auto v3 = across(u);
		if (v3 != -1 && !is_visited(g[v3]))
		{
			set_visited(g[v3]);
			set_prev(g[v3], u);
			q.push(v3);
			if (v3 == e)
				break;
		}
	}

	// walk the path and mark the diagonals in 'out'
	int ecnt{ 0 };
	auto p = e;
	do
	{
		p = prev(g[p]);
		if (is_diag(g[p]))
		{
			out[g_tox(p)] = 1;
			++ecnt;
		}
	} while (p != 0);
	return ecnt;
}