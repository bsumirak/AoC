/*
 * day24.h
 *
 *  Created on: 2023-12-24
 *      Author: mbreit
 */


template <>
void executeDay<24>(const std::string& fn)
{
	// parse input
	std::ifstream infile(fn.c_str());
	
	std::vector<std::array<int64_t, 6>> paths;
	int64_t i;
	while (infile >> i)
	{
		paths.emplace_back();
		paths.back()[0] = i;
		for (size_t k = 1; k < 6; ++k)
			infile >> paths.back()[k];
	}
	const size_t sz = paths.size();


	// part a
	unsigned resA = 0;
	std::array<int64_t, 2> bounds{int64_t(200000000000000), int64_t(400000000000000)};
	for (size_t k = 0; k < sz; ++k)
	{
		const auto& h1 = paths[k];
		int64_t px = h1[0];
		int64_t py = h1[1];
		int64_t vx = h1[3];
		int64_t vy = h1[4];

		for (size_t l = k + 1; l < sz; ++l)
		{
			const auto& h2 = paths[l];
			int64_t qx = h2[0];
			int64_t qy = h2[1];
			int64_t wx = h2[3];
			int64_t wy = h2[4];
			
			const int64_t det = -vx * wy + wx * vy;
			if (det == 0)
			{
				//if (px * vy - py * vx == qx * vy - qy * vx)
				//	++resA;
				continue;		
			}
			
			double s = (double)(-wy * (qx - px) + wx * (qy - py)) / (double)det;
			double t = (double)(-vy * (qx - px) + vx * (qy - py)) / (double)det;
			
			if (s <= 0 || t <= 0)
				continue;
			
			if (px + s * vx < (double)bounds[0] || px + s * vx > (double)bounds[1]
				|| py + s * vy < (double)bounds[0] || py + s * vy > (double)bounds[1])
			{
				continue;
			}

			++resA;
		}
	}
	
	
	// part b
	uint64_t resB = 0;
	
	std::array<double, 3> p1{(double)paths[0][0], (double)paths[0][1], (double)paths[0][2]};
	std::array<double, 3> p2{(double)paths[1][0], (double)paths[1][1], (double)paths[1][2]};
	std::array<double, 3> p3{(double)paths[2][0], (double)paths[2][1], (double)paths[2][2]};
	std::array<double, 3> p4{(double)paths[3][0], (double)paths[3][1], (double)paths[3][2]};
	
	std::array<double, 3> v1{(double)paths[0][3], (double)paths[0][4], (double)paths[0][5]};
	std::array<double, 3> v2{(double)paths[1][3], (double)paths[1][4], (double)paths[1][5]};
	std::array<double, 3> v3{(double)paths[2][3], (double)paths[2][4], (double)paths[2][5]};
	std::array<double, 3> v4{(double)paths[3][3], (double)paths[3][4], (double)paths[3][5]};
	
	auto diff = [](const std::array<double, 3>& a, const std::array<double, 3>& b)
	{
		return std::array<double, 3>{a[0] - b[0], a[1] - b[1], a[2] - b[2]};		
	};
	
	auto dot = [](const std::array<double, 3>& a, const std::array<double, 3>& b)
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	};
	
	auto cross = [](const std::array<double, 3>& a, const std::array<double, 3>& b)
	{
		return std::array<double, 3>{
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]};
	};
	
	const auto a = dot(diff(p3, p1), cross(v3, diff(p2, p1)));
	const auto b = dot(diff(p3, p1), cross(v3, v1)) + dot(v1, cross(v3, diff(p2, p1)));
	const auto c = dot(diff(p3, p1), cross(v3, v2));
	const auto d = dot(v1, cross(v3, v2));
	
	const auto e = dot(diff(p4, p1), cross(v4, diff(p2, p1)));
	const auto f = dot(diff(p4, p1), cross(v4, v1)) + dot(v1, cross(v4, diff(p2, p1)));
	const auto g = dot(diff(p4, p1), cross(v4, v2));
	const auto h = dot(v1, cross(v4, v2));
	
	const auto p_2 = (g*b-f*c+e*d-h*a) / (g*d-h*c);
	const auto q2 = (e*b-f*a) / (g*d-h*c);
	const auto t2 = -0.5*p_2 + std::sqrt(0.25*p_2*p_2 - q2);
	
	const auto p_1 = (b*g-c*f+a*h-d*e) / (d*f-b*h);
	const auto q1 = (c*e-a*g) / (d*f-b*h);
	const auto t1 = -0.5*p_1 + std::sqrt(0.25*p_1*p_1 - q1);
	
	for (size_t k = 0; k < 3; ++k)
	{
		const auto vk = (p2[k] - p1[k] + t2*v2[k] - t1*v1[k]) / (t2 - t1);
		const auto pk = p1[k] + t1*v1[k] - t1*vk;
		resB += (uint64_t)pk;
		if (pk - (double)(uint64_t)pk > 0.5)
			++resB;
	}
	
	
	writeSolution(resA, resB);
}


