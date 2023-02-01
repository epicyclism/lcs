//
// Copyright (c) 2021 Paul Ranson, paul@epicyclism.com
//
//
// diff.h : implements a diff algorithm quite flexibly.
//
//

#pragma once

namespace DIFF
{
	// the output is a list of these ( hopefully the 'Shortest Edit Sequence', SES )
	//
	template<typename val> struct EditOp
	{
		bool   ins_; // else delete
		int    off_;
		val    val_;
		EditOp(int off, val v) : ins_(true), off_(off), val_(v)
		{
		}
		EditOp(int off) : ins_(false), off_(off)
		{
		}
	};

	// recursively traverse the edit graph to produce the SES
	//
	template<typename InL, typename InR, typename Out> void ListPath(size_t D, std::vector<std::vector<int>>& s, int k, InL const& a, InR const& b, Out& out)
	{
		int MAX = int(a.size() + b.size());
		int x = s[D][k + MAX];
		int y = x - k;

		if (D == 0)
		{
			// do nothing
			return;
		}
		else
		{
			// up the snake
			int nextx = s[D][k + MAX + 1]; // cannot be less than zero!
			while (x > nextx && y > 0 && (a[x - 1] == b[y - 1]))
			{
				--x;
				--y;
			}
			// vertical or horizontal?
			if (nextx == x)
			{
				// vertical
				ListPath(D - 1, s, k + 1, a, b, out);
				// list the edge
				out.push_back(typename Out::value_type(x - 1, b[y - 1]));
			}
			else
			{
				// horizontal
				ListPath(D - 1, s, k - 1, a, b, out);
				// list the edge
				out.push_back(typename Out::value_type(x - 1));
			}
			return;
		}
	}

	// the meat
	//
	template<typename InL, typename InR, typename Out> size_t diff(InL const& a, InR const& b, Out& out)
	{
		int MAX = int(a.size() + b.size());
		std::vector<std::vector<int> > s;
		std::vector<int> v;
		v.resize((MAX + 1) * 2);
		v[MAX] = 0;
		int x;
		int y;

		for (int D = 0; D <= MAX; ++D)
		{
			for (int k = -D; k <= D; k += 2)
			{
				if (k == -D || k != D && v[k - 1 + MAX] < v[k + 1 + MAX])
				{
					x = v[k + 1 + MAX]; // MAX means the total will never be negative
				}
				else
				{
					x = v[k - 1 + MAX] + 1;
				}
				y = x - k;
				while (x < int(a.size()) && y < int(b.size()) && a[x] == b[y])
				{
					++x;
					++y;
				}
				v[k + MAX] = x;
				if (x >= int(a.size()) && y >= int(b.size()))
				{
					s.push_back(v);
					ListPath(D, s, k, a, b, out);
					return D;
				}
			}
			s.push_back(v);
		}
		return 0;
	}
	// if we get consecutive deletes at the same point, increment the offset.
	// fix at origin one day. Definitely a bodge.
	//
	template<typename VO>  void BodgeDeletes(VO& vo)
	{
		int off_base = -1;

		for (auto& eo : vo)
		{
			if (!eo.ins_)
			{
				if (eo.off_ == off_base)
					++eo.off_;
				off_base = eo.off_;
			}
		}
	}
	template<typename VO>  void Bodge(VO& vo)
	{
		int off_base{ -1 };
		int off_cnt{ -1 };
		for (auto& eo : vo)
		{
			if (eo.off_ == off_base)
			{
				++off_cnt;
				eo.off_ = off_cnt;
			}
			else
			{
				off_cnt = eo.off_;
				off_base = eo.off_;
			}
		}
	}

	template<typename InL, typename InR, typename Out> void list_path(size_t D, std::vector<std::vector<int>>& s, int k, InL const& a, InR const& b, Out& out)
	{
		int MAX = int(a.size() + b.size());
		int x = s[D][k + MAX];
		int y = x - k;

		if (D == 0)
		{
			if (x == y)
				while (x != 0)
				{
					--x;
					out[x] = 1;
				}
			return;
		}
		else
		{
			// up the snake
			int nextx = s[D][k + MAX + 1]; // cannot be less than zero!
			while (x > nextx && y > 0 && (a[x - 1] == b[y - 1]))
			{
				--x;
				--y;
				out[x] = 1;
			}
			// vertical or horizontal?
			if (nextx == x)
			{
				// vertical
				list_path(D - 1, s, k + 1, a, b, out);
			}
			else
			{
				// horizontal
				list_path(D - 1, s, k - 1, a, b, out);
			}
			return;
		}
	}

	// the meat
	//
	template<typename InL, typename InR, typename Out> size_t diff_e(InL const& a, InR const& b, Out& out)
	{
		int MAX = int(a.size() + b.size());
		std::vector<std::vector<int> > s;
		std::vector<int> v;
		v.resize((MAX + 1) * 2);
		v[MAX] = 0;
		int x;
		int y;

		for (int D = 0; D <= MAX; ++D)
		{
			for (int k = -D; k <= D; k += 2)
			{
				if (k == -D || k != D && v[k - 1 + MAX] < v[k + 1 + MAX])
				{
					x = v[k + 1 + MAX]; // MAX means the total will never be negative
				}
				else
				{
					x = v[k - 1 + MAX] + 1;
				}
				y = x - k;
				while (x < int(a.size()) && y < int(b.size()) && a[x] == b[y])
				{
					++x;
					++y;
				}
				v[k + MAX] = x;
				if (x >= int(a.size()) && y >= int(b.size()))
				{
					s.push_back(v);
					list_path(D, s, k, a, b, out);
					return D;
				}
			}
			s.push_back(v);
		}
		return 0;
	}
} // namespace diff