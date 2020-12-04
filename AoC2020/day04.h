/*
 * day01.h
 *
 *  Created on: 2020-12-04
 *      Author: mbreit
 */


template <>
void executeDay<4>(const std::string& fn)
{
	// read input
	struct Data
	{
		std::string byr;
		std::string iyr;
		std::string eyr;
		std::string hgt;
		std::string hcl;
		std::string ecl;
		std::string pid;
		std::string cid;
	};
	std::vector<Data> passports;

	std::size_t resA = 0;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		std::string key;
		std::string val;
		while (std::getline(infile, line))
		{
			passports.resize(passports.size() + 1);
			Data& data = passports.back();

			// parse input line
			std::istringstream iss(line);
			while (iss >> key)
			{
				if (key == "byr")
					iss >> data.byr;
				else if (key == "iyr")
					iss >> data.iyr;
				else if (key == "eyr")
					iss >> data.eyr;
				else if (key == "hgt")
					iss >> data.hgt;
				else if (key == "hcl")
					iss >> data.hcl;
				else if (key == "ecl")
					iss >> data.ecl;
				else if (key == "pid")
					iss >> data.pid;
				else if (key == "cid")
					iss >> data.cid;
			}


			// part a
			if (!data.byr.size()
				|| !data.iyr.size()
				|| !data.eyr.size()
				|| !data.hgt.size()
				|| !data.hcl.size()
				|| !data.ecl.size()
				|| !data.pid.size())
				continue;

			++resA;

		}
		infile.close();
	}



	// part b
	auto checkValid = [] (Data& data)
	{
		auto checkYear = [] (const std::string& y, unsigned min, unsigned max)
		{
			static const std::regex re("^[[:d:]]{4,4}$");
			std::smatch match;
			if (!std::regex_match(y, match, re))
				return false;

			std::istringstream iss(y);
			unsigned yr;
			iss >> yr;
			if (yr < min || yr > max)
				return false;

			return true;
		};

		if (!checkYear(data.byr, 1920u, 2002u))
			return false;
		if (!checkYear(data.iyr, 2010u, 2020u))
			return false;
		if (!checkYear(data.eyr, 2020u, 2030u))
			return false;


		{
			static const std::regex re("^([[:d:]]{2,3})(in|cm)$");
			std::smatch match;
			if (!std::regex_match(data.hgt, match, re))
				return false;

			std::istringstream iss(match[1]);
			unsigned h;
			iss >> h;
			if ((match[2] == "in" && (h < 59u || h > 76u))
				|| (match[2] == "cm" && (h < 150u || h > 193u)))
				return false;
		}

		{
			static const std::regex re("^#[[:xdigit:]]{6,6}$");
			std::smatch match;
			if (!std::regex_match(data.hcl, match, re))
				return false;
		}

		{
			static const std::regex re("^(amb|blu|brn|gry|grn|hzl|oth)$");
			std::smatch match;
			if (!std::regex_match(data.ecl, match, re))
				return false;
		}

		{
			static const std::regex re("^[[:d:]]{9,9}$");
			std::smatch match;
			if (!std::regex_match(data.pid, match, re))
				return false;
		}

		return true;
	};


	std::size_t resB = 0;
	const std::size_t sz = passports.size();
	for (size_t p = 0; p < sz; ++p)
	{
		Data& data = passports[p];

		if (checkValid(data))
			++resB;
	}


	writeSolution(resA, resB);
}


