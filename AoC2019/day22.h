/*
 * day22.h
 *
 *  Created on: 2019-12-22
 *      Author: mbreit
 */




uint64_t multiplyMod(uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t r = 0;
	for (uint i = 0; i < 64; ++i)
	{
		if (a & (uint64_t(1) << i))
			r = (r+b) % m;
		b = (b << 1) % m;
	}
	return r;
}

uint64_t divideMod(uint64_t a, uint64_t b, uint64_t m)
{
	uint64_t mult = a;
	a = m;
	std::vector<uint64_t> q;
	uint64_t tmp = 0;
	while (b != 1)
	{
		q.push_back(a/b);
		tmp = a - q.back()*b;
		a = b;
		b = tmp;
	}

	const std::size_t sz = q.size();
	a = 1;
	b = 0;
	for (std::size_t i = sz; i > 0; --i)
	{
		tmp = b;
		b = a;
		a = (m + tmp - multiplyMod(a, q[i-1], m)) % m;
	}

	return multiplyMod(mult, a, m);
}



void findShufflingFunction
(
	const std::vector<int>& code,
	const std::vector<uint64_t>& data,
	uint64_t mod,
	uint64_t& factor,
	uint64_t& offset
)
{
	factor = 1;
	offset = 0;
	std::size_t nShuffle = code.size();
	for (std::size_t i = 0; i < nShuffle; ++i)
	{
		switch (code[i])
		{
			case 0: // stack
				factor = (mod - factor) % mod;
				offset = mod - offset - 1;
				break;
			case 1:
				offset = (offset + mod - data[i]) % mod;
				break;
			case 2:
				factor = multiplyMod(factor, data[i], mod);
				offset = multiplyMod(offset, data[i], mod);
				break;
		}
	}
}


template <>
void executeDay<22>(const std::string& fn)
{
	std::ifstream infile(fn.c_str());

	// read data
	std::vector<int> code;
	std::vector<uint64_t> data;
	{
		uint64_t tmp;
		while (infile >> tmp)
		{
			code.push_back(tmp);
			if (tmp)
			{
				data.resize(data.size() + 1);
				infile >> data.back();
			}
			else
				data.push_back(0);
		}
	}


	// find the linear function defined by the shuffling instructions
	uint64_t mod = 10007;
	uint64_t factor = 1;
	uint64_t offset = 0;
	findShufflingFunction(code, data, mod, factor, offset);


	// part a
	uint64_t sola = (factor*uint64_t(2019) + offset) % mod;


	// part b
	mod = 119315717514047;
	findShufflingFunction(code, data, mod, factor, offset);

	// apply n times
	uint64_t finalFactor = 1;
	uint64_t finalOffset = 0;
	uint64_t nShuffles = 101741582076661;
	for (uint i = 0; i < 64; ++i)
	{
		if (nShuffles & ((uint64_t)1 << i))
		{
			finalFactor = multiplyMod(factor, finalFactor, mod);
			finalOffset = (multiplyMod(factor, finalOffset, mod) + offset) % mod;
		}

		offset = multiplyMod(factor+1, offset, mod);
		factor = multiplyMod(factor, factor, mod);
	}

	// inverse application of function
	uint64_t solb = divideMod((mod + uint64_t(2020) - finalOffset) % mod, finalFactor, mod);


	writeSolution(sola, solb);
}


