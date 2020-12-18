/*
 * day18.h
 *
 *  Created on: 2020-12-18
 *      Author: mbreit
 */



template <>
void executeDay<18>(const std::string& fn)
{
	// read input
	uint64_t resA = 0;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			std::string op;
			std::stack<uint64_t> numberStack;
			numberStack.push(0);
			std::stack<char> opStack;
			opStack.push('+');
			while (iss >> op)
			{
				if (op == "(")
				{
					numberStack.push(0);
					opStack.push('+');
					continue;
				}
				if (op == ")")
				{
					uint64_t res = numberStack.top();
					char c = opStack.top();

					numberStack.pop();
					opStack.pop();

					if (c == '+')
						numberStack.top() += res;
					else if (c == '*')
						numberStack.top() *= res;

					continue;
				}
				if (op == "+")
				{
					opStack.push('+');
					continue;
				}
				if (op == "*")
				{
					opStack.push('*');
					continue;
				}
				uint64_t val = stoull(op);
				char c = opStack.top();
				opStack.pop();

				if (c == '+')
					numberStack.top() += val;
				else if (c == '*')
					numberStack.top() *= val;
			}
			resA += numberStack.top();
		}
		infile.close();
	}


	// part b
	uint64_t resB = 0;
	{
		std::ifstream infile(fn.c_str());
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			std::string op;
			std::stack<uint64_t> numberStack;
			numberStack.push(0);
			std::stack<bool> groupStack;
			groupStack.push(false);
			std::stack<char> opStack;
			opStack.push('+');
			while (iss >> op)
			{
				if (op == "(")
				{
					numberStack.push(0);
					groupStack.push(false);
					opStack.push('+');
					continue;
				}
				if (op == ")")
				{
					// close pseudo-parentheses
					if (groupStack.top())
					{
						uint64_t res = numberStack.top();
						numberStack.pop();
						opStack.pop();
						numberStack.top() *= res;
					}
					groupStack.pop();

					uint64_t res = numberStack.top();
					char c = opStack.top();

					numberStack.pop();
					opStack.pop();

					if (c == '+')
						numberStack.top() += res;
					else if (c == '*')
						numberStack.top() *= res;

					continue;
				}
				if (op == "+")
				{
					opStack.push('+');
					continue;
				}
				if (op == "*")
				{
					// close pseudo-parentheses
					if (groupStack.top())
					{
						uint64_t res = numberStack.top();
						numberStack.pop();
						opStack.pop();
						numberStack.top() *= res;
					}

					opStack.push('*');

					// open pseudo-parentheses
					numberStack.push(0);
					groupStack.top() = true;
					opStack.push('+');

					continue;
				}
				uint64_t val = stoull(op);
				char c = opStack.top();
				opStack.pop();

				if (c == '+')
					numberStack.top() += val;
				else if (c == '*')
					numberStack.top() *= val;
			}

			// close pseudo-parentheses
			if (groupStack.top())
			{
				uint64_t res = numberStack.top();
				numberStack.pop();
				opStack.pop();
				numberStack.top() *= res;
			}
			groupStack.pop();

			resB += numberStack.top();
		}
		infile.close();
	}

#if 0
	// alternative approach with much less "real" code for part 2
	struct MyInt64
	{
		MyInt64(int64_t i) : m_i(i) {}
		MyInt64 operator+(const MyInt64& b) {return MyInt64(m_i * b.m_i);}
		MyInt64 operator*(const MyInt64& b) {return MyInt64(m_i + b.m_i);}

		int64_t m_i;
	};

	MyInt64 myResB =
		(MyInt64(6) + MyInt64(6) + ( MyInt64(9) * MyInt64(4) ) * ( MyInt64(8) + MyInt64(7) ) )
		 * (MyInt64(3) + MyInt64(7) * MyInt64(3) + ( MyInt64(3) * MyInt64(6) + MyInt64(7) * MyInt64(9) * MyInt64(4) ) + MyInt64(9))
		 * (MyInt64(2) * MyInt64(5) * ( MyInt64(8) + MyInt64(7) ) + MyInt64(4) * MyInt64(4) * MyInt64(7))
		 * (MyInt64(6) * MyInt64(3) * MyInt64(4))
		 * (MyInt64(2) + MyInt64(8) + MyInt64(5) + ( ( MyInt64(6) * MyInt64(9) * MyInt64(3) + MyInt64(6) ) + MyInt64(4) + MyInt64(6) * MyInt64(3) ) + MyInt64(7))
		 * (MyInt64(7) * MyInt64(3) * MyInt64(4) + MyInt64(6) * ( ( MyInt64(8) * MyInt64(6) + MyInt64(5) + MyInt64(6) + MyInt64(2) + MyInt64(4) ) + MyInt64(9) + MyInt64(9) + MyInt64(3) ) )
		 * ( ( MyInt64(5) + MyInt64(6) * MyInt64(9) * MyInt64(7) * MyInt64(8) ) * MyInt64(9) + ( MyInt64(7) + MyInt64(9) * MyInt64(6) + MyInt64(2) * MyInt64(3) ) )
		 * ( ( MyInt64(7) * MyInt64(6) + MyInt64(3) * MyInt64(5) ) * ( MyInt64(2) + MyInt64(3) * MyInt64(6) + ( MyInt64(9) + MyInt64(2) + MyInt64(6) + MyInt64(3) * MyInt64(6) + MyInt64(3) ) ) )
		 * (MyInt64(3) + MyInt64(8) + ( ( MyInt64(9) * MyInt64(4) * MyInt64(2) + MyInt64(2) ) + MyInt64(9) ) )
		 * (MyInt64(6) + ( MyInt64(2) * ( MyInt64(7) * MyInt64(4) * MyInt64(3) ) ) + MyInt64(9) + MyInt64(8) + MyInt64(7))
		 * (MyInt64(5) * MyInt64(7) + MyInt64(2) + ( MyInt64(6) + MyInt64(3) * MyInt64(2) + ( MyInt64(4) + MyInt64(4) + MyInt64(8) ) ) * ( ( MyInt64(4) * MyInt64(5) + MyInt64(6) * MyInt64(7) * MyInt64(3) ) * MyInt64(9) ) + MyInt64(4))
		 * (MyInt64(5) * MyInt64(5) + ( MyInt64(3) * MyInt64(6) * MyInt64(8) ) )
		 * (MyInt64(5) + MyInt64(5) * MyInt64(6) + MyInt64(6) * MyInt64(2) * ( MyInt64(2) * MyInt64(6) ) )
		 * ( ( MyInt64(3) + MyInt64(6) * MyInt64(8) ) + MyInt64(8) * ( ( MyInt64(2) * MyInt64(5) * MyInt64(4) * MyInt64(9) * MyInt64(4) * MyInt64(8) ) + MyInt64(2) ) + MyInt64(7) + ( MyInt64(2) + MyInt64(6) * MyInt64(8) * MyInt64(5) * MyInt64(2) ) * MyInt64(2))
		 * (MyInt64(7) + MyInt64(7) + MyInt64(3) + MyInt64(9) * ( MyInt64(4) + ( MyInt64(6) * MyInt64(3) ) * ( MyInt64(9) * MyInt64(2) * MyInt64(9) ) * ( MyInt64(5) + MyInt64(3) * MyInt64(6) + MyInt64(3) + MyInt64(8) ) + MyInt64(2) + MyInt64(9) ) + MyInt64(9))
		 * (MyInt64(3) * ( ( MyInt64(8) * MyInt64(9) ) * ( MyInt64(6) + MyInt64(8) + MyInt64(9) * MyInt64(4) + MyInt64(8) * MyInt64(2) ) + MyInt64(2) * ( MyInt64(9) * MyInt64(3) * MyInt64(8) + MyInt64(5) * MyInt64(3) ) + MyInt64(8) ) * MyInt64(8) + MyInt64(8) * MyInt64(8) * ( MyInt64(9) + MyInt64(2) * MyInt64(8) + MyInt64(9) + ( MyInt64(7) + MyInt64(3) * MyInt64(3) ) + MyInt64(2) ) )
		 * ( ( MyInt64(3) + MyInt64(7) * MyInt64(5) + ( MyInt64(6) + MyInt64(3) + MyInt64(2) * MyInt64(8) + MyInt64(6) ) ) + MyInt64(9) * MyInt64(6) + MyInt64(3) * MyInt64(6) * MyInt64(4))
		 * ( ( MyInt64(7) * MyInt64(7) * MyInt64(9) + MyInt64(8) ) + MyInt64(6) * MyInt64(5) * MyInt64(8) + MyInt64(4) * ( MyInt64(5) * MyInt64(4) + MyInt64(5) * MyInt64(4) ) )
		 * ( ( MyInt64(3) + MyInt64(6) + MyInt64(3) + MyInt64(3) * MyInt64(3) ) + MyInt64(7) + MyInt64(4) + MyInt64(3))
		 * (MyInt64(6) * MyInt64(8) * MyInt64(3) + MyInt64(6) + ( MyInt64(8) + MyInt64(4) * MyInt64(7) * MyInt64(2) + MyInt64(5) ) + ( MyInt64(6) + MyInt64(4) + MyInt64(9) * MyInt64(2) * MyInt64(6) * MyInt64(3) ) )
		 * (MyInt64(7) * MyInt64(8) * MyInt64(6) + MyInt64(5) + MyInt64(4) * MyInt64(7))
		 * (MyInt64(4) * ( MyInt64(4) * MyInt64(7) + MyInt64(3) * MyInt64(8) ) * ( MyInt64(4) + MyInt64(5) ) * MyInt64(9) * ( MyInt64(8) + MyInt64(7) * MyInt64(5) * MyInt64(3) * MyInt64(8) * MyInt64(9) ) + MyInt64(6))
		 * (MyInt64(4) + MyInt64(5) * MyInt64(2) + ( MyInt64(9) * ( MyInt64(3) * MyInt64(9) * MyInt64(2) * MyInt64(3) * MyInt64(4) ) ) )
		 * (MyInt64(2) * MyInt64(9) * ( MyInt64(4) + MyInt64(3) ) + MyInt64(9) + MyInt64(8))
		 * (MyInt64(2) * MyInt64(8) + ( MyInt64(8) * MyInt64(6) + MyInt64(3) * ( MyInt64(9) + MyInt64(6) + MyInt64(7) * MyInt64(7) * MyInt64(6) ) + ( MyInt64(6) * MyInt64(2) * MyInt64(9) ) * ( MyInt64(2) + MyInt64(6) + MyInt64(2) + MyInt64(2) * MyInt64(8) ) ) )
		 * ( ( MyInt64(2) + MyInt64(5) + MyInt64(5) * MyInt64(7) * MyInt64(8) ) * MyInt64(4) + ( MyInt64(8) + ( MyInt64(4) * MyInt64(8) + MyInt64(7) * MyInt64(3) ) + MyInt64(4) * MyInt64(2) + MyInt64(8) * MyInt64(2) ) + MyInt64(7) + MyInt64(6) * MyInt64(4))
		 * (MyInt64(5) * MyInt64(8) * MyInt64(7) + MyInt64(9) * MyInt64(3) + ( MyInt64(6) + ( MyInt64(2) * MyInt64(5) ) + MyInt64(2) * MyInt64(3) + ( MyInt64(6) * MyInt64(7) ) ) )
		 * (MyInt64(3) * MyInt64(2) + ( MyInt64(7) + ( MyInt64(8) + MyInt64(8) ) + MyInt64(4) * MyInt64(2) * MyInt64(4) + MyInt64(9) ) )
		 * ( ( MyInt64(5) + MyInt64(4) + MyInt64(4) * MyInt64(7) ) * MyInt64(5) + ( MyInt64(6) * MyInt64(8) ) + MyInt64(7))
		 * (MyInt64(5) * MyInt64(4) * ( ( MyInt64(8) + MyInt64(9) + MyInt64(8) * MyInt64(6) ) * MyInt64(4) + MyInt64(9) * MyInt64(3) + MyInt64(6) + MyInt64(8) ) + MyInt64(5))
		 * ( ( MyInt64(6) * MyInt64(5) + MyInt64(9) + ( MyInt64(3) * MyInt64(7) * MyInt64(2) + MyInt64(2) + MyInt64(7) * MyInt64(7) ) ) + MyInt64(7) * ( MyInt64(7) + MyInt64(4) ) + MyInt64(4) + MyInt64(5))
		 * (MyInt64(6) + MyInt64(8) * MyInt64(6) * ( MyInt64(5) * ( MyInt64(7) + MyInt64(6) + MyInt64(7) + MyInt64(5) + MyInt64(4) * MyInt64(8) ) + MyInt64(5) * MyInt64(7) + ( MyInt64(7) * MyInt64(4) + MyInt64(5) * MyInt64(6) ) * MyInt64(7) ) * ( MyInt64(6) * MyInt64(6) + MyInt64(6) * MyInt64(7) ) )
		 * ( ( MyInt64(6) + MyInt64(8) * MyInt64(4) * MyInt64(6) + MyInt64(5) + MyInt64(9) ) + MyInt64(5) + ( ( MyInt64(4) + MyInt64(3) + MyInt64(5) + MyInt64(2) ) + ( MyInt64(4) * MyInt64(7) * MyInt64(8) + MyInt64(4) + MyInt64(5) * MyInt64(6) ) * ( MyInt64(6) + MyInt64(4) * MyInt64(4) + MyInt64(7) ) + MyInt64(7) * ( MyInt64(9) + MyInt64(8) ) + ( MyInt64(5) + MyInt64(2) * MyInt64(7) * MyInt64(3) + MyInt64(2) ) ) * MyInt64(6) + MyInt64(6))
		 * ( ( MyInt64(8) * ( MyInt64(9) * MyInt64(2) ) + MyInt64(2) + MyInt64(2) * MyInt64(2) + MyInt64(8) ) * MyInt64(5) + MyInt64(4) + MyInt64(2) * MyInt64(4) * ( MyInt64(5) * MyInt64(9) + MyInt64(7) ) )
		 * ( ( MyInt64(5) + MyInt64(4) + MyInt64(5) * MyInt64(2) * MyInt64(5) ) + MyInt64(3) * ( MyInt64(8) * MyInt64(9) ) + MyInt64(9) + MyInt64(2) * ( MyInt64(5) * MyInt64(7) + MyInt64(5) ) )
		 * ( ( MyInt64(6) * MyInt64(3) + ( MyInt64(8) * MyInt64(6) ) + MyInt64(4) * MyInt64(8) + ( MyInt64(4) + MyInt64(5) * MyInt64(6) ) ) + MyInt64(2) + ( MyInt64(6) * ( MyInt64(5) * MyInt64(5) * MyInt64(9) * MyInt64(3) + MyInt64(2) * MyInt64(7) ) * MyInt64(7) * ( MyInt64(2) * MyInt64(6) ) * ( MyInt64(8) * MyInt64(8) + MyInt64(2) + MyInt64(5) ) ) )
		 * (MyInt64(6) * MyInt64(3) + ( MyInt64(2) * ( MyInt64(3) * MyInt64(8) * MyInt64(9) ) * MyInt64(4) * MyInt64(4) ) + MyInt64(4))
		 * (MyInt64(6) + MyInt64(5) + ( MyInt64(2) + MyInt64(6) + MyInt64(5) ) + ( ( MyInt64(9) + MyInt64(2) + MyInt64(5) * MyInt64(8) * MyInt64(4) * MyInt64(3) ) * MyInt64(3) + MyInt64(9) ) * MyInt64(6))
		 * (MyInt64(3) * ( MyInt64(9) + MyInt64(6) + MyInt64(5) * MyInt64(2) + MyInt64(4) ) )
		 * (MyInt64(5) + MyInt64(4) * MyInt64(2) + MyInt64(3) * ( MyInt64(8) * MyInt64(9) * MyInt64(9) + MyInt64(6) + MyInt64(4) + ( MyInt64(3) * MyInt64(8) * MyInt64(4) * MyInt64(2) ) ) * MyInt64(6))
		 * (MyInt64(2) * MyInt64(7) + MyInt64(6) * ( MyInt64(2) + MyInt64(5) + MyInt64(9) + MyInt64(6) * MyInt64(8) ) )
		 * (MyInt64(3) + MyInt64(7) * MyInt64(9) + ( MyInt64(4) * MyInt64(4) * MyInt64(8) * MyInt64(8) + MyInt64(7) ) * MyInt64(3) * ( MyInt64(9) + MyInt64(2) + MyInt64(7) * MyInt64(6) ) )
		 * (MyInt64(2) * MyInt64(8) + MyInt64(9) + ( MyInt64(7) + MyInt64(9) + MyInt64(6) * ( MyInt64(3) * MyInt64(3) ) * MyInt64(3) ) * MyInt64(5) + MyInt64(4))
		 * (MyInt64(9) * MyInt64(9) + MyInt64(9) * ( MyInt64(9) + MyInt64(5) * MyInt64(7) * MyInt64(6) ) )
		 * (MyInt64(6) * MyInt64(7) * ( ( MyInt64(3) + MyInt64(7) * MyInt64(6) * MyInt64(5) ) * MyInt64(3) ) + MyInt64(6) * MyInt64(6))
		 * (MyInt64(7) * ( MyInt64(4) * MyInt64(6) + ( MyInt64(4) + MyInt64(2) * MyInt64(5) * MyInt64(5) + MyInt64(8) * MyInt64(4) ) * MyInt64(3) * MyInt64(4) ) * MyInt64(4) * MyInt64(9) * MyInt64(3) * MyInt64(4))
		 * ( ( ( MyInt64(4) * MyInt64(8) * MyInt64(4) * MyInt64(5) + MyInt64(8) ) * MyInt64(5) ) + MyInt64(9) * MyInt64(3) + ( ( MyInt64(7) + MyInt64(6) ) * ( MyInt64(7) + MyInt64(9) + MyInt64(9) + MyInt64(4) + MyInt64(2) * MyInt64(7) ) * MyInt64(6) * ( MyInt64(6) + MyInt64(2) + MyInt64(3) + MyInt64(8) ) ) * ( MyInt64(9) + MyInt64(4) * MyInt64(7) ) + ( ( MyInt64(5) + MyInt64(6) * MyInt64(2) ) + MyInt64(7) + MyInt64(3) ) )
		 * ( ( MyInt64(4) * MyInt64(8) * MyInt64(5) * MyInt64(2) * MyInt64(7) * MyInt64(8) ) * ( MyInt64(9) + MyInt64(5) ) + MyInt64(8) * MyInt64(8) * MyInt64(2) + MyInt64(8))
		 * ( ( MyInt64(8) + MyInt64(4) + ( MyInt64(7) * MyInt64(6) ) + MyInt64(5) * MyInt64(3) ) * MyInt64(5) * MyInt64(5) * ( MyInt64(8) * ( MyInt64(4) + MyInt64(9) + MyInt64(5) ) + MyInt64(7) ) )
		 * (MyInt64(2) * MyInt64(2) + ( MyInt64(6) * MyInt64(6) * MyInt64(6) * MyInt64(7) * MyInt64(9) * MyInt64(5) ) * MyInt64(2) + ( MyInt64(8) + MyInt64(2) * MyInt64(9) ) )
		 * (MyInt64(5) * MyInt64(6) * MyInt64(2) + MyInt64(2) + MyInt64(3))
		 * (MyInt64(6) * MyInt64(6) * ( MyInt64(8) + MyInt64(6) + MyInt64(3) + MyInt64(3) ) )
		 * ( ( ( MyInt64(4) * MyInt64(8) * MyInt64(8) ) + MyInt64(8) + ( MyInt64(4) + MyInt64(7) * MyInt64(8) * MyInt64(9) + MyInt64(7) ) ) + MyInt64(9) * ( ( MyInt64(4) + MyInt64(6) * MyInt64(5) * MyInt64(3) + MyInt64(2) + MyInt64(4) ) * MyInt64(9) + MyInt64(4) ) + MyInt64(6) + ( MyInt64(4) * ( MyInt64(6) * MyInt64(4) + MyInt64(6) + MyInt64(8) + MyInt64(3) * MyInt64(2) ) * MyInt64(4) ) + MyInt64(4))
		 * ( ( MyInt64(3) * MyInt64(7) * ( MyInt64(5) * MyInt64(2) * MyInt64(5) + MyInt64(8) * MyInt64(8) ) + MyInt64(8) ) * ( MyInt64(4) + MyInt64(8) + MyInt64(3) + MyInt64(2) + MyInt64(6) ) + MyInt64(3) * MyInt64(8) + MyInt64(5))
		 * ( ( ( MyInt64(3) * MyInt64(7) + MyInt64(6) * MyInt64(2) ) + ( MyInt64(4) + MyInt64(6) + MyInt64(7) ) * MyInt64(3) + MyInt64(7) ) + MyInt64(2) * MyInt64(7) + MyInt64(5))
		 * (MyInt64(5) + MyInt64(9) * MyInt64(5) + MyInt64(2) + MyInt64(8) * MyInt64(8))
		 * ( ( MyInt64(8) * MyInt64(3) + MyInt64(6) ) + MyInt64(7) + ( ( MyInt64(2) * MyInt64(4) ) + MyInt64(4) ) + ( MyInt64(3) * ( MyInt64(6) * MyInt64(2) * MyInt64(3) + MyInt64(2) * MyInt64(3) * MyInt64(5) ) * MyInt64(3) ) + MyInt64(2) + MyInt64(8))
		 * ( ( MyInt64(9) * MyInt64(7) * MyInt64(9) * MyInt64(2) ) + MyInt64(6) + MyInt64(4))
		 * (MyInt64(3) + ( ( MyInt64(9) * MyInt64(5) * MyInt64(7) ) + MyInt64(6) + MyInt64(4) ) * ( MyInt64(6) * MyInt64(3) * MyInt64(4) * MyInt64(9) * MyInt64(3) + MyInt64(8) ) * MyInt64(9) + MyInt64(4))
		 * ( ( MyInt64(5) + MyInt64(8) * MyInt64(4) * MyInt64(7) * MyInt64(3) ) * MyInt64(5) + MyInt64(5) * ( ( MyInt64(9) * MyInt64(9) ) + MyInt64(5) * MyInt64(9) * ( MyInt64(4) * MyInt64(4) ) + ( MyInt64(7) + MyInt64(7) * MyInt64(2) + MyInt64(8) * MyInt64(2) ) + MyInt64(6) ) )
		 * ( ( ( MyInt64(7) + MyInt64(4) + MyInt64(6) * MyInt64(2) ) + ( MyInt64(3) + MyInt64(7) + MyInt64(9) ) + MyInt64(6) * MyInt64(8) ) + MyInt64(4) * ( MyInt64(8) * ( MyInt64(2) * MyInt64(3) * MyInt64(3) * MyInt64(4) ) * ( MyInt64(5) + MyInt64(4) + MyInt64(2) * MyInt64(2) ) + MyInt64(5) * ( MyInt64(8) + MyInt64(8) * MyInt64(9) * MyInt64(7) + MyInt64(4) * MyInt64(6) ) + MyInt64(6) ) * MyInt64(7) + MyInt64(5))
		 * (MyInt64(3) * ( ( MyInt64(7) + MyInt64(4) * MyInt64(4) ) * MyInt64(6) ) * MyInt64(6) * ( MyInt64(5) * MyInt64(7) * MyInt64(5) ) * ( ( MyInt64(4) + MyInt64(4) ) * MyInt64(3) ) + ( MyInt64(9) + MyInt64(5) ) )
		 * ( ( MyInt64(9) + MyInt64(5) * MyInt64(3) * MyInt64(7) ) + ( ( MyInt64(4) + MyInt64(9) + MyInt64(9) + MyInt64(9) + MyInt64(2) ) + MyInt64(4) * MyInt64(4) ) )
		 * (MyInt64(6) + ( MyInt64(7) * MyInt64(6) + ( MyInt64(4) + MyInt64(9) * MyInt64(5) * MyInt64(7) ) + MyInt64(8) + ( MyInt64(5) * MyInt64(2) * MyInt64(9) * MyInt64(6) + MyInt64(6) * MyInt64(5) ) * MyInt64(2) ) * ( MyInt64(9) * MyInt64(9) + MyInt64(8) + ( MyInt64(4) + MyInt64(5) + MyInt64(2) * MyInt64(6) * MyInt64(5) + MyInt64(6) ) + MyInt64(4) + MyInt64(7) ) + MyInt64(8) * MyInt64(3))
		 * ( ( MyInt64(9) + MyInt64(7) ) * ( MyInt64(2) + MyInt64(4) + MyInt64(2) + MyInt64(9) ) + MyInt64(2) + MyInt64(6))
		 * ( ( MyInt64(2) * ( MyInt64(6) + MyInt64(9) ) * MyInt64(9) + MyInt64(5) + MyInt64(3) ) + MyInt64(2) + ( MyInt64(8) * MyInt64(7) * MyInt64(4) + MyInt64(4) + MyInt64(6) ) * MyInt64(3))
		 * ( ( MyInt64(6) * MyInt64(3) * ( MyInt64(4) * MyInt64(2) * MyInt64(2) * MyInt64(9) + MyInt64(3) ) + MyInt64(5) + ( MyInt64(3) + MyInt64(6) + MyInt64(3) + MyInt64(2) * MyInt64(6) ) * ( MyInt64(6) * MyInt64(8) * MyInt64(6) * MyInt64(4) + MyInt64(5) + MyInt64(5) ) ) * MyInt64(3))
		 * (MyInt64(2) + MyInt64(8) + ( ( MyInt64(7) * MyInt64(9) * MyInt64(2) * MyInt64(3) ) + MyInt64(5) * MyInt64(2) + ( MyInt64(8) + MyInt64(3) ) * MyInt64(3) + MyInt64(5) ) + ( MyInt64(4) * MyInt64(7) * MyInt64(7) * MyInt64(7) ) * MyInt64(2))
		 * (MyInt64(4) * MyInt64(5) + ( MyInt64(6) * MyInt64(8) + ( MyInt64(6) * MyInt64(9) + MyInt64(5) ) + MyInt64(8) ) + ( MyInt64(4) * MyInt64(9) * MyInt64(9) * ( MyInt64(3) * MyInt64(7) * MyInt64(7) * MyInt64(8) ) * MyInt64(3) + MyInt64(5) ) + MyInt64(9))
		 * ( ( MyInt64(4) * MyInt64(8) + MyInt64(7) + MyInt64(2) * ( MyInt64(3) + MyInt64(3) * MyInt64(6) + MyInt64(9) + MyInt64(6) ) * MyInt64(3) ) * MyInt64(6))
		 * (MyInt64(5) * ( MyInt64(5) * MyInt64(9) * ( MyInt64(4) + MyInt64(5) + MyInt64(4) + MyInt64(4) * MyInt64(2) * MyInt64(5) ) * ( MyInt64(8) * MyInt64(8) * MyInt64(4) + MyInt64(9) * MyInt64(6) ) ) * MyInt64(2) + MyInt64(4) + MyInt64(8))
		 * (MyInt64(4) + ( MyInt64(5) + MyInt64(3) ) * MyInt64(9) + MyInt64(6) + MyInt64(9))
		 * (MyInt64(9) + ( MyInt64(3) + MyInt64(4) * MyInt64(6) * MyInt64(2) * MyInt64(6) ) * MyInt64(9) + MyInt64(4) + MyInt64(7))
		 * (MyInt64(3) + MyInt64(7) + MyInt64(9) * ( MyInt64(7) * MyInt64(2) + MyInt64(9) * MyInt64(4) * MyInt64(7) + MyInt64(2) ) + MyInt64(6) + MyInt64(8))
		 * ( ( MyInt64(7) + ( MyInt64(6) * MyInt64(7) * MyInt64(4) + MyInt64(8) ) + MyInt64(7) + MyInt64(9) * MyInt64(6) ) * MyInt64(9) * ( MyInt64(8) * MyInt64(9) + MyInt64(9) ) + MyInt64(6))
		 * (MyInt64(2) * MyInt64(6) + ( MyInt64(9) * MyInt64(9) * MyInt64(3) + MyInt64(3) * MyInt64(8) * ( MyInt64(5) + MyInt64(5) ) ) * MyInt64(7) + MyInt64(8) * ( MyInt64(8) * MyInt64(3) * MyInt64(3) + MyInt64(5) + ( MyInt64(9) + MyInt64(6) + MyInt64(6) + MyInt64(2) * MyInt64(6) * MyInt64(4) ) + MyInt64(4) ) )
		 * (MyInt64(8) * ( MyInt64(8) + MyInt64(2) + ( MyInt64(6) * MyInt64(5) + MyInt64(2) * MyInt64(6) * MyInt64(8) ) ) )
		 * (MyInt64(9) * MyInt64(9) + MyInt64(4) + MyInt64(4))
		 * ( ( MyInt64(8) * ( MyInt64(7) * MyInt64(3) * MyInt64(3) ) ) + MyInt64(3) * ( MyInt64(4) * MyInt64(7) * ( MyInt64(3) + MyInt64(9) + MyInt64(3) + MyInt64(8) ) + MyInt64(4) + MyInt64(8) ) + MyInt64(6))
		 * ( ( MyInt64(5) * MyInt64(7) * MyInt64(5) * MyInt64(3) + MyInt64(5) ) + MyInt64(7) * MyInt64(6))
		 * (MyInt64(5) + MyInt64(3) + ( MyInt64(2) * MyInt64(3) + ( MyInt64(8) + MyInt64(8) * MyInt64(6) * MyInt64(9) + MyInt64(3) ) + MyInt64(9) ) * ( MyInt64(4) + ( MyInt64(8) * MyInt64(6) + MyInt64(6) + MyInt64(5) ) * MyInt64(7) * MyInt64(5) + MyInt64(2) ) + MyInt64(6) * MyInt64(7))
		 * (MyInt64(8) + ( MyInt64(9) * MyInt64(3) * ( MyInt64(2) + MyInt64(6) + MyInt64(6) ) * MyInt64(3) * MyInt64(4) + MyInt64(8) ) + MyInt64(5) * ( MyInt64(6) + ( MyInt64(8) * MyInt64(4) * MyInt64(8) + MyInt64(2) + MyInt64(8) ) + MyInt64(4) * MyInt64(3) + ( MyInt64(7) + MyInt64(7) * MyInt64(5) + MyInt64(5) + MyInt64(3) * MyInt64(3) ) ) + MyInt64(9))
		 * (MyInt64(7) + MyInt64(9) + ( MyInt64(4) * MyInt64(4) * MyInt64(3) * MyInt64(3) * MyInt64(2) ) + MyInt64(2) * MyInt64(2) * MyInt64(6))
		 * (MyInt64(8) + MyInt64(8) * ( ( MyInt64(7) * MyInt64(2) + MyInt64(7) + MyInt64(9) + MyInt64(2) ) + MyInt64(4) * MyInt64(9) * ( MyInt64(9) * MyInt64(2) * MyInt64(5) * MyInt64(6) ) * MyInt64(7) ) * MyInt64(4))
		 * (MyInt64(2) + MyInt64(8) * ( MyInt64(9) + MyInt64(6) + MyInt64(3) + ( MyInt64(9) + MyInt64(9) * MyInt64(3) * MyInt64(3) + MyInt64(6) ) + MyInt64(3) ) * MyInt64(7))
		 * ( ( ( MyInt64(6) * MyInt64(7) * MyInt64(6) ) + MyInt64(8) * MyInt64(7) + MyInt64(7) ) * ( ( MyInt64(2) * MyInt64(8) ) * MyInt64(8) ) * MyInt64(9) + MyInt64(3))
		 * ( ( MyInt64(8) * MyInt64(8) * MyInt64(9) ) + MyInt64(6) + MyInt64(4) * MyInt64(9) * MyInt64(4))
		 * (MyInt64(8) + MyInt64(8) + MyInt64(6) * MyInt64(9) * MyInt64(3) * MyInt64(2))
		 * (MyInt64(7) + MyInt64(8) + MyInt64(7) * ( MyInt64(2) + MyInt64(9) + MyInt64(9) * MyInt64(9) + MyInt64(8) ) * MyInt64(2) + MyInt64(5))
		 * (MyInt64(3) * ( MyInt64(7) + MyInt64(9) + ( MyInt64(7) + MyInt64(2) + MyInt64(9) * MyInt64(4) ) * MyInt64(5) + MyInt64(5) * MyInt64(8) ) + MyInt64(7))
		 * (MyInt64(4) * MyInt64(3) * MyInt64(4) + ( MyInt64(6) * MyInt64(2) + ( MyInt64(2) * MyInt64(8) * MyInt64(9) * MyInt64(2) + MyInt64(9) * MyInt64(2) ) * MyInt64(3) + MyInt64(5) ) )
		 * ( ( MyInt64(5) * MyInt64(2) + MyInt64(7) + MyInt64(9) * ( MyInt64(9) + MyInt64(7) + MyInt64(6) + MyInt64(5) + MyInt64(9) ) ) + MyInt64(6) * MyInt64(5) * MyInt64(2) * MyInt64(3) + MyInt64(4))
		 * ( ( MyInt64(7) + MyInt64(7) + ( MyInt64(2) + MyInt64(8) ) + MyInt64(6) ) + MyInt64(5) * MyInt64(3) + MyInt64(8) * MyInt64(2) * MyInt64(2))
		 * (MyInt64(5) * MyInt64(9) * MyInt64(8) + ( MyInt64(6) + ( MyInt64(5) * MyInt64(7) * MyInt64(7) ) + MyInt64(7) + MyInt64(5) * MyInt64(4) * MyInt64(2) ) * MyInt64(4))
		 * (MyInt64(5) + MyInt64(5) + ( MyInt64(7) + MyInt64(6) * MyInt64(6) + MyInt64(7) + MyInt64(9) * ( MyInt64(2) + MyInt64(3) ) ) + MyInt64(4) * MyInt64(3) + ( MyInt64(2) + MyInt64(5) + MyInt64(9) ) )
		 * (MyInt64(6) + MyInt64(4) * ( MyInt64(7) * MyInt64(4) + MyInt64(4) ) * ( MyInt64(5) + ( MyInt64(3) * MyInt64(9) ) * MyInt64(6) * MyInt64(7) + MyInt64(8) ) )
		 * ( ( MyInt64(3) * MyInt64(3) + MyInt64(8) * MyInt64(5) + ( MyInt64(2) + MyInt64(2) + MyInt64(9) + MyInt64(4) + MyInt64(6) ) ) + MyInt64(9))
		 * ( ( ( MyInt64(2) * MyInt64(2) + MyInt64(6) * MyInt64(3) * MyInt64(8) ) + MyInt64(5) * MyInt64(7) ) + ( MyInt64(9) * ( MyInt64(7) * MyInt64(2) ) ) * ( ( MyInt64(9) + MyInt64(9) + MyInt64(6) ) * MyInt64(7) + MyInt64(6) + MyInt64(5) ) + ( ( MyInt64(5) + MyInt64(8) + MyInt64(6) + MyInt64(7) + MyInt64(6) * MyInt64(5) ) * MyInt64(8) * MyInt64(5) + MyInt64(9) * ( MyInt64(9) + MyInt64(5) ) * ( MyInt64(4) * MyInt64(7) * MyInt64(9) * MyInt64(4) ) ) * ( MyInt64(5) + MyInt64(6) * MyInt64(7) * MyInt64(8) + MyInt64(7) + MyInt64(3) ) + MyInt64(2))
		 * (MyInt64(3) * MyInt64(6) * ( MyInt64(5) + MyInt64(4) * ( MyInt64(4) * MyInt64(2) + MyInt64(8) * MyInt64(3) ) ) + MyInt64(4) * ( MyInt64(7) * MyInt64(6) + MyInt64(4) ) + MyInt64(2))
		 * (MyInt64(6) * MyInt64(8))
		 * (MyInt64(8) + MyInt64(4) * MyInt64(7))
		 * (MyInt64(8) + ( MyInt64(3) + MyInt64(4) * MyInt64(4) + ( MyInt64(2) + MyInt64(9) * MyInt64(8) + MyInt64(9) + MyInt64(7) + MyInt64(6) ) * MyInt64(4) + MyInt64(6) ) + MyInt64(7) + MyInt64(7))
		 * ( ( ( MyInt64(8) + MyInt64(3) * MyInt64(6) * MyInt64(2) * MyInt64(7) * MyInt64(4) ) * MyInt64(8) ) + ( MyInt64(7) + MyInt64(3) ) * MyInt64(9))
		 * (MyInt64(4) * MyInt64(8) * MyInt64(7) + ( MyInt64(4) + ( MyInt64(7) + MyInt64(6) + MyInt64(4) ) + MyInt64(4) + MyInt64(4) * MyInt64(4) * MyInt64(8) ) )
		 * (MyInt64(5) * ( MyInt64(3) * MyInt64(7) * MyInt64(3) ) + ( MyInt64(3) + MyInt64(9) ) + MyInt64(8))
		 * ( ( MyInt64(6) * ( MyInt64(3) + MyInt64(5) ) + ( MyInt64(4) + MyInt64(9) * MyInt64(6) * MyInt64(3) + MyInt64(7) ) + ( MyInt64(6) * MyInt64(7) * MyInt64(6) ) * MyInt64(9) + MyInt64(6) ) * MyInt64(5))
		 * (MyInt64(9) * MyInt64(8) + ( MyInt64(4) + MyInt64(8) + MyInt64(4) ) * MyInt64(7) + MyInt64(8) * MyInt64(6))
		 * (MyInt64(9) * ( MyInt64(3) * MyInt64(8) + MyInt64(3) + MyInt64(2) + MyInt64(7) * MyInt64(8) ) )
		 * (MyInt64(4) * ( ( MyInt64(4) * MyInt64(9) + MyInt64(4) + MyInt64(5) ) + MyInt64(7) + MyInt64(6) ) * MyInt64(6))
		 * (MyInt64(8) * ( MyInt64(4) * MyInt64(6) + MyInt64(8) * MyInt64(7) ) + ( MyInt64(4) * MyInt64(8) + MyInt64(7) + ( MyInt64(4) + MyInt64(7) + MyInt64(6) ) * MyInt64(9) ) + MyInt64(3) + MyInt64(9) * MyInt64(7))
		 * (MyInt64(4) * MyInt64(3) + ( ( MyInt64(6) + MyInt64(6) ) + MyInt64(2) ) * ( MyInt64(7) + MyInt64(5) + ( MyInt64(2) * MyInt64(5) * MyInt64(8) + MyInt64(5) * MyInt64(5) * MyInt64(2) ) * MyInt64(8) * MyInt64(3) * MyInt64(9) ) )
		 * (MyInt64(2) + MyInt64(9) * ( MyInt64(6) + MyInt64(6) * MyInt64(7) ) + MyInt64(4) + MyInt64(3) + ( MyInt64(9) * MyInt64(2) * ( MyInt64(9) * MyInt64(3) * MyInt64(7) ) * MyInt64(8) * MyInt64(3) * MyInt64(5) ) )
		 * ( ( MyInt64(2) + MyInt64(5) + MyInt64(7) + MyInt64(9) * MyInt64(3) ) * MyInt64(9))
		 * (MyInt64(7) * MyInt64(9) * ( MyInt64(9) * MyInt64(3) + MyInt64(3) + MyInt64(7) + MyInt64(2) * MyInt64(8) ) * MyInt64(8) + MyInt64(6))
		 * (MyInt64(2) * MyInt64(3) + MyInt64(5) + ( MyInt64(3) + MyInt64(3) * MyInt64(4) + ( MyInt64(4) + MyInt64(4) * MyInt64(4) ) ) + MyInt64(5))
		 * (MyInt64(9) * MyInt64(3) + ( MyInt64(5) * ( MyInt64(5) * MyInt64(8) ) ) * MyInt64(3) * ( MyInt64(5) * MyInt64(2) * ( MyInt64(4) + MyInt64(7) + MyInt64(7) + MyInt64(5) ) * MyInt64(2) ) * MyInt64(7))
		 * ( ( MyInt64(9) * MyInt64(3) + MyInt64(9) + MyInt64(8) * MyInt64(5) * MyInt64(8) ) * ( MyInt64(3) + MyInt64(6) * MyInt64(3) + MyInt64(4) * MyInt64(8) + MyInt64(6) ) * MyInt64(2) + MyInt64(2) + MyInt64(3) * MyInt64(8))
		 * (MyInt64(7) + ( MyInt64(9) * MyInt64(2) * MyInt64(3) + ( MyInt64(5) + MyInt64(8) + MyInt64(7) + MyInt64(2) ) + ( MyInt64(6) + MyInt64(6) + MyInt64(2) + MyInt64(9) + MyInt64(7) ) ) * MyInt64(6) * MyInt64(3))
		 * (MyInt64(3) * ( MyInt64(8) * MyInt64(8) + MyInt64(5) + MyInt64(8) + MyInt64(7) ) * ( MyInt64(5) + MyInt64(6) ) + MyInt64(9) * ( MyInt64(3) * MyInt64(5) + ( MyInt64(4) + MyInt64(9) + MyInt64(5) * MyInt64(9) * MyInt64(4) + MyInt64(3) ) * MyInt64(6) ) * MyInt64(5))
		 * ( ( MyInt64(6) * ( MyInt64(9) + MyInt64(2) ) ) * MyInt64(7) + MyInt64(7))
		 * (MyInt64(9) + ( ( MyInt64(5) * MyInt64(7) * MyInt64(8) + MyInt64(9) * MyInt64(9) + MyInt64(3) ) + MyInt64(8) + MyInt64(8) * MyInt64(9) + ( MyInt64(8) + MyInt64(2) + MyInt64(3) + MyInt64(2) * MyInt64(9) ) ) * MyInt64(4) + ( MyInt64(4) * ( MyInt64(5) + MyInt64(4) * MyInt64(6) ) ) + MyInt64(3) + MyInt64(3))
		 * (MyInt64(7) * MyInt64(9) * MyInt64(9) * MyInt64(5) * ( ( MyInt64(2) + MyInt64(8) * MyInt64(6) * MyInt64(4) + MyInt64(6) * MyInt64(4) ) + MyInt64(8) + MyInt64(5) ) + MyInt64(9))
		 * (MyInt64(3) * MyInt64(9) + MyInt64(4) * MyInt64(3) * MyInt64(6) * ( MyInt64(6) * MyInt64(3) + MyInt64(5) * MyInt64(6) + MyInt64(2) * MyInt64(3) ) )
		 * (MyInt64(4) * MyInt64(2) + ( MyInt64(5) + MyInt64(6) ) * MyInt64(2))
		 * (MyInt64(5) * ( MyInt64(6) + MyInt64(2) * ( MyInt64(3) + MyInt64(4) ) * MyInt64(9) ) * MyInt64(5))
		 * (MyInt64(3) + ( MyInt64(4) + ( MyInt64(6) + MyInt64(6) + MyInt64(5) + MyInt64(8) ) ) * ( MyInt64(4) * MyInt64(4) ) + ( ( MyInt64(2) * MyInt64(7) + MyInt64(7) + MyInt64(6) * MyInt64(7) ) + MyInt64(9) * MyInt64(2) + MyInt64(5) * MyInt64(3) ) )
		 * (MyInt64(5) * ( ( MyInt64(6) * MyInt64(2) * MyInt64(5) + MyInt64(3) ) * MyInt64(7) * MyInt64(5) + MyInt64(5) ) * MyInt64(5))
		 * (MyInt64(8) * ( MyInt64(6) * MyInt64(4) * MyInt64(8) ) )
		 * (MyInt64(6) + ( MyInt64(9) + MyInt64(4) ) * MyInt64(8) * ( MyInt64(5) * MyInt64(2) ) + MyInt64(4))
		 * (MyInt64(2) + MyInt64(9))
		 * ( ( MyInt64(5) * MyInt64(4) * MyInt64(7) * ( MyInt64(4) + MyInt64(5) * MyInt64(8) ) * MyInt64(4) * ( MyInt64(9) + MyInt64(7) + MyInt64(6) ) ) * MyInt64(4))
		 * (MyInt64(3) + MyInt64(5) + MyInt64(5) * MyInt64(6) * ( MyInt64(3) * MyInt64(3) + ( MyInt64(3) + MyInt64(6) * MyInt64(2) * MyInt64(6) ) + MyInt64(5) * MyInt64(3) ) )
		 * (MyInt64(3) + MyInt64(2) * MyInt64(3) * MyInt64(2) * MyInt64(7) + ( MyInt64(4) + MyInt64(3) + MyInt64(6) * MyInt64(9) * MyInt64(5) ) )
		 * ( ( ( MyInt64(6) + MyInt64(6) + MyInt64(9) * MyInt64(8) ) * MyInt64(4) * MyInt64(5) * MyInt64(4) ) * MyInt64(3) * MyInt64(9))
		 * (MyInt64(7) + MyInt64(2) * ( MyInt64(8) + ( MyInt64(7) + MyInt64(2) + MyInt64(8) ) * MyInt64(5) * ( MyInt64(3) + MyInt64(4) + MyInt64(8) + MyInt64(9) * MyInt64(7) + MyInt64(8) ) * MyInt64(3) ) )
		 * (MyInt64(6) + MyInt64(3) * ( MyInt64(8) * MyInt64(4) * MyInt64(5) * MyInt64(6) * MyInt64(7) + MyInt64(3) ) * MyInt64(6))
		 * (MyInt64(5) + ( ( MyInt64(8) + MyInt64(7) + MyInt64(9) + MyInt64(8) * MyInt64(9) ) * MyInt64(9) + MyInt64(9) ) + ( MyInt64(5) * MyInt64(2) + MyInt64(9) * MyInt64(5) + MyInt64(8) + MyInt64(8) ) * MyInt64(6))
		 * (MyInt64(8) + ( MyInt64(5) + MyInt64(9) * MyInt64(3) * MyInt64(5) * MyInt64(4) ) + MyInt64(7) + ( MyInt64(5) + ( MyInt64(6) * MyInt64(7) + MyInt64(7) + MyInt64(4) + MyInt64(3) ) * MyInt64(9) * MyInt64(6) + MyInt64(6) ) )
		 * (MyInt64(3) + ( MyInt64(6) * MyInt64(5) + MyInt64(3) + MyInt64(9) * MyInt64(2) * ( MyInt64(5) * MyInt64(5) ) ) )
		 * (MyInt64(7) * ( MyInt64(9) + MyInt64(5) ) * MyInt64(9))
		 * (MyInt64(2) * MyInt64(4) * ( MyInt64(9) * MyInt64(3) + ( MyInt64(6) + MyInt64(8) + MyInt64(8) + MyInt64(8) * MyInt64(8) ) + ( MyInt64(6) * MyInt64(7) + MyInt64(5) ) * MyInt64(8) ) )
		 * ( ( MyInt64(5) + MyInt64(6) + MyInt64(8) * MyInt64(5) ) + MyInt64(7) * MyInt64(9) * MyInt64(8) + MyInt64(4))
		 * (MyInt64(9) * ( MyInt64(3) * MyInt64(4) ) * MyInt64(6) + MyInt64(6) + MyInt64(3) * ( ( MyInt64(3) * MyInt64(4) * MyInt64(2) ) * ( MyInt64(2) + MyInt64(2) * MyInt64(7) * MyInt64(5) ) * MyInt64(7) ) )
		 * (MyInt64(9) + ( MyInt64(2) + ( MyInt64(2) + MyInt64(2) * MyInt64(6) + MyInt64(6) ) * MyInt64(4) + ( MyInt64(5) * MyInt64(6) ) + MyInt64(9) * MyInt64(9) ) * MyInt64(2))
		 * ( ( MyInt64(7) * MyInt64(2) + MyInt64(2) ) + MyInt64(9) + ( ( MyInt64(2) + MyInt64(7) * MyInt64(9) ) + MyInt64(7) + MyInt64(7) * ( MyInt64(4) * MyInt64(9) * MyInt64(7) + MyInt64(3) * MyInt64(6) ) + MyInt64(4) + MyInt64(5) ) )
		 * (MyInt64(8) * MyInt64(3) + MyInt64(5) * MyInt64(7) * ( MyInt64(6) + MyInt64(9) + ( MyInt64(2) + MyInt64(7) ) ) + ( MyInt64(2) * MyInt64(7) ) )
		 * ( ( MyInt64(8) * MyInt64(7) + MyInt64(7) + MyInt64(2) ) + MyInt64(8) * ( ( MyInt64(4) * MyInt64(4) * MyInt64(8) + MyInt64(5) ) * MyInt64(2) ) )
		 * (MyInt64(5) + ( MyInt64(5) * MyInt64(6) + ( MyInt64(4) * MyInt64(8) * MyInt64(7) + MyInt64(3) + MyInt64(7) * MyInt64(6) ) + MyInt64(3) + MyInt64(5) ) )
		 * ( ( MyInt64(5) + MyInt64(5) ) + MyInt64(6) + MyInt64(8) * MyInt64(5))
		 * (MyInt64(9) + ( MyInt64(5) * ( MyInt64(3) + MyInt64(8) ) * MyInt64(9) + MyInt64(3) ) * MyInt64(2) + MyInt64(2))
		 * ( ( MyInt64(3) * ( MyInt64(7) + MyInt64(4) * MyInt64(2) + MyInt64(4) + MyInt64(6) ) * MyInt64(5) * MyInt64(7) ) + MyInt64(8))
		 * (MyInt64(8) * MyInt64(7) * ( MyInt64(5) * MyInt64(3) * MyInt64(5) * MyInt64(9) + MyInt64(8) ) + MyInt64(9))
		 * (MyInt64(3) + MyInt64(3) * MyInt64(5) + MyInt64(9) + ( MyInt64(8) + ( MyInt64(9) * MyInt64(4) * MyInt64(3) ) + MyInt64(8) * ( MyInt64(3) + MyInt64(9) + MyInt64(6) + MyInt64(7) * MyInt64(9) + MyInt64(4) ) + MyInt64(3) ) + MyInt64(8))
		 * ( ( MyInt64(7) * ( MyInt64(7) + MyInt64(7) ) + MyInt64(5) ) * MyInt64(4) * MyInt64(5) + MyInt64(5) + MyInt64(8))
		 * (MyInt64(3) * MyInt64(4) * MyInt64(9) * MyInt64(8) + ( MyInt64(6) + MyInt64(2) + MyInt64(2) + MyInt64(9) ) )
		 * ( ( MyInt64(7) + MyInt64(3) ) * MyInt64(3) + MyInt64(7) * ( MyInt64(3) * MyInt64(8) ) * MyInt64(3))
		 * ( ( MyInt64(4) * MyInt64(7) + ( MyInt64(2) + MyInt64(7) ) * MyInt64(7) + MyInt64(6) + ( MyInt64(5) + MyInt64(9) ) ) + MyInt64(2))
		 * (MyInt64(3) * MyInt64(9) * MyInt64(7) + ( MyInt64(3) * MyInt64(2) ) * MyInt64(7))
		 * (MyInt64(2) + ( MyInt64(9) * MyInt64(4) + ( MyInt64(3) + MyInt64(7) * MyInt64(6) + MyInt64(4) ) ) )
		 * ( ( MyInt64(2) * MyInt64(3) ) + MyInt64(2) + MyInt64(4) + MyInt64(5) * MyInt64(6))
		 * (MyInt64(4) + MyInt64(4) * MyInt64(2))
		 * (MyInt64(7) + ( ( MyInt64(2) * MyInt64(2) + MyInt64(8) + MyInt64(5) * MyInt64(9) + MyInt64(9) ) + MyInt64(8) ) * MyInt64(2) * MyInt64(9) * ( MyInt64(3) * MyInt64(4) + MyInt64(6) + MyInt64(3) ) )
		 * (MyInt64(5) + MyInt64(5) + MyInt64(6) + ( ( MyInt64(5) * MyInt64(3) + MyInt64(7) * MyInt64(3) + MyInt64(9) + MyInt64(5) ) + ( MyInt64(2) * MyInt64(8) ) * MyInt64(8) * MyInt64(3) ) * MyInt64(5) * MyInt64(7))
		 * (MyInt64(7) * ( MyInt64(8) * MyInt64(2) ) + MyInt64(8) * MyInt64(2))
		 * (MyInt64(8) + MyInt64(3) + MyInt64(4) * MyInt64(5) + ( ( MyInt64(2) + MyInt64(5) * MyInt64(7) ) * ( MyInt64(8) * MyInt64(6) + MyInt64(7) + MyInt64(4) + MyInt64(8) ) + MyInt64(3) ) )
		 * (MyInt64(2) + MyInt64(6) * ( MyInt64(4) * MyInt64(8) * ( MyInt64(4) + MyInt64(9) + MyInt64(2) + MyInt64(9) + MyInt64(7) + MyInt64(3) ) * MyInt64(4) * MyInt64(4) + MyInt64(6) ) + MyInt64(6))
		 * ( ( MyInt64(2) + ( MyInt64(4) + MyInt64(4) * MyInt64(4) ) ) + MyInt64(2) * MyInt64(6) * MyInt64(2) * MyInt64(2) + MyInt64(8))
		 * (MyInt64(9) * MyInt64(8) + ( ( MyInt64(6) + MyInt64(3) * MyInt64(5) + MyInt64(9) + MyInt64(9) ) * MyInt64(5) ) )
		 * ( ( MyInt64(7) * MyInt64(7) * MyInt64(6) + MyInt64(4) + MyInt64(9) * MyInt64(6) ) + MyInt64(6) * MyInt64(5) + ( MyInt64(8) + ( MyInt64(5) + MyInt64(9) * MyInt64(3) * MyInt64(3) * MyInt64(2) + MyInt64(9) ) + ( MyInt64(5) + MyInt64(8) * MyInt64(8) ) + MyInt64(6) * MyInt64(6) ) + MyInt64(5) * MyInt64(8))
		 * (MyInt64(9) + ( MyInt64(8) * MyInt64(7) ) + MyInt64(6) + ( ( MyInt64(9) * MyInt64(5) * MyInt64(7) * MyInt64(8) * MyInt64(8) * MyInt64(7) ) + ( MyInt64(9) + MyInt64(2) + MyInt64(9) ) * MyInt64(7) + MyInt64(7) ) + ( MyInt64(4) + MyInt64(8) * ( MyInt64(9) + MyInt64(6) * MyInt64(9) * MyInt64(5) + MyInt64(5) * MyInt64(9) ) + MyInt64(2) * ( MyInt64(5) + MyInt64(5) * MyInt64(8) * MyInt64(7) * MyInt64(9) ) ) * MyInt64(2))
		 * (MyInt64(3) * MyInt64(6) * ( MyInt64(2) * MyInt64(9) ) * MyInt64(5) * ( MyInt64(7) * MyInt64(4) * MyInt64(9) * MyInt64(6) * MyInt64(8) ) )
		 * (MyInt64(5) + MyInt64(5) * ( ( MyInt64(9) + MyInt64(2) + MyInt64(6) ) * MyInt64(8) * MyInt64(5) ) + MyInt64(4))
		 * ( ( MyInt64(4) * ( MyInt64(9) + MyInt64(6) + MyInt64(7) * MyInt64(7) + MyInt64(7) * MyInt64(6) ) * MyInt64(6) * MyInt64(8) ) + MyInt64(5))
		 * (MyInt64(6) * MyInt64(8) * MyInt64(5) + MyInt64(8))
		 * (MyInt64(3) + ( MyInt64(8) + MyInt64(4) * MyInt64(8) + MyInt64(3) ) * MyInt64(8) * MyInt64(9) * MyInt64(7))
		 * (MyInt64(5) * MyInt64(6) * MyInt64(3))
		 * (MyInt64(6) + MyInt64(3) + MyInt64(3) * ( MyInt64(3) * MyInt64(3) + MyInt64(2) * ( MyInt64(7) + MyInt64(9) + MyInt64(5) * MyInt64(8) ) * MyInt64(4) + MyInt64(7) ) * ( MyInt64(6) + MyInt64(5) * MyInt64(2) ) + MyInt64(7))
		 * ( ( MyInt64(3) + ( MyInt64(7) + MyInt64(4) + MyInt64(6) * MyInt64(8) * MyInt64(8) + MyInt64(6) ) ) * ( ( MyInt64(3) + MyInt64(2) + MyInt64(6) ) + MyInt64(6) + MyInt64(3) * ( MyInt64(9) + MyInt64(5) + MyInt64(4) ) + ( MyInt64(2) + MyInt64(8) * MyInt64(4) * MyInt64(8) ) + MyInt64(2) ) + MyInt64(6))
		 * ( ( MyInt64(8) * MyInt64(9) * MyInt64(2) * MyInt64(4) + ( MyInt64(2) + MyInt64(9) + MyInt64(7) ) * ( MyInt64(3) + MyInt64(7) ) ) + ( ( MyInt64(7) + MyInt64(8) + MyInt64(9) * MyInt64(6) + MyInt64(7) ) * MyInt64(6) * MyInt64(6) * MyInt64(7) ) )
		 * (MyInt64(3) * MyInt64(8) + MyInt64(2) + MyInt64(5) + MyInt64(9))
		 * (MyInt64(8) * ( ( MyInt64(6) + MyInt64(6) ) + MyInt64(4) ) + MyInt64(7) * MyInt64(9))
		 * (MyInt64(5) + ( MyInt64(6) + ( MyInt64(7) + MyInt64(5) * MyInt64(9) * MyInt64(2) * MyInt64(7) + MyInt64(8) ) * MyInt64(7) + MyInt64(3) * ( MyInt64(8) + MyInt64(7) ) ) )
		 * (MyInt64(2) + MyInt64(4) + MyInt64(4) + ( MyInt64(4) * MyInt64(6) * MyInt64(2) ) + ( MyInt64(9) * MyInt64(5) + MyInt64(7) * ( MyInt64(2) + MyInt64(2) * MyInt64(2) * MyInt64(9) * MyInt64(3) ) * MyInt64(4) ) )
		 * (MyInt64(7) * MyInt64(6) * ( MyInt64(9) + MyInt64(2) * MyInt64(5) + MyInt64(8) * MyInt64(3) + MyInt64(4) ) + ( MyInt64(8) + MyInt64(4) + MyInt64(5) * MyInt64(7) + MyInt64(6) ) )
		 * (MyInt64(4) * MyInt64(2) + MyInt64(5) + ( MyInt64(4) * MyInt64(8) + MyInt64(8) ) )
		 * (MyInt64(9) + MyInt64(9) * ( ( MyInt64(6) + MyInt64(6) * MyInt64(6) * MyInt64(9) ) * MyInt64(2) + MyInt64(3) * ( MyInt64(9) * MyInt64(9) + MyInt64(5) + MyInt64(6) + MyInt64(4) + MyInt64(4) ) * ( MyInt64(5) * MyInt64(7) + MyInt64(2) + MyInt64(3) ) ) * ( MyInt64(9) + MyInt64(5) * MyInt64(9) * MyInt64(8) ) + ( MyInt64(3) * MyInt64(6) + MyInt64(4) * MyInt64(5) * MyInt64(8) * MyInt64(2) ) * MyInt64(6))
		 * (MyInt64(6) + ( MyInt64(7) * MyInt64(3) ) * MyInt64(9) * MyInt64(9) * ( MyInt64(3) + MyInt64(7) + MyInt64(5) + MyInt64(5) ) )
		 * ( ( ( MyInt64(9) + MyInt64(5) + MyInt64(7) * MyInt64(6) + MyInt64(9) * MyInt64(4) ) * MyInt64(6) * MyInt64(8) ) + MyInt64(7) + MyInt64(9) + MyInt64(8))
		 * (MyInt64(8) + MyInt64(6) * ( ( MyInt64(8) * MyInt64(6) ) * ( MyInt64(4) + MyInt64(5) ) + MyInt64(7) * MyInt64(5) * MyInt64(3) ) * MyInt64(7) * ( MyInt64(4) * MyInt64(5) * MyInt64(5) + MyInt64(2) + MyInt64(6) * MyInt64(8) ) + MyInt64(5))
		 * ( ( MyInt64(9) + MyInt64(2) * MyInt64(5) * MyInt64(4) * MyInt64(7) * MyInt64(6) ) * MyInt64(3) + MyInt64(8) * MyInt64(5))
		 * ( ( MyInt64(7) * ( MyInt64(8) + MyInt64(7) ) + ( MyInt64(5) * MyInt64(3) + MyInt64(3) * MyInt64(2) + MyInt64(5) * MyInt64(5) ) * MyInt64(2) ) + MyInt64(7))
		 * ( ( MyInt64(6) * MyInt64(8) * MyInt64(2) * MyInt64(3) ) * MyInt64(5) * MyInt64(3) * MyInt64(5) + MyInt64(7) * ( MyInt64(2) * MyInt64(2) + MyInt64(7) ) )
		 * ( ( MyInt64(5) + MyInt64(6) + MyInt64(2) * MyInt64(2) * MyInt64(8) + MyInt64(9) ) * MyInt64(3) + MyInt64(6))
		 * (MyInt64(2) * ( MyInt64(4) + ( MyInt64(3) + MyInt64(5) + MyInt64(9) + MyInt64(9) + MyInt64(8) + MyInt64(8) ) ) )
		 * (MyInt64(7) + ( MyInt64(8) + ( MyInt64(5) + MyInt64(9) * MyInt64(9) * MyInt64(5) + MyInt64(2) ) * MyInt64(3) ) * MyInt64(3))
		 * (MyInt64(5) * MyInt64(2) * ( ( MyInt64(9) + MyInt64(4) * MyInt64(4) + MyInt64(7) * MyInt64(2) ) * MyInt64(2) ) * MyInt64(9))
		 * ( ( ( MyInt64(6) * MyInt64(3) + MyInt64(9) ) + MyInt64(3) + ( MyInt64(7) * MyInt64(5) * MyInt64(7) * MyInt64(8) * MyInt64(4) * MyInt64(8) ) + MyInt64(7) ) * MyInt64(7) + MyInt64(9))
		 * (MyInt64(6) * ( MyInt64(4) + ( MyInt64(8) * MyInt64(4) + MyInt64(2) ) * ( MyInt64(5) * MyInt64(7) + MyInt64(3) * MyInt64(4) * MyInt64(5) ) ) )
		 * (MyInt64(8) * MyInt64(7) + MyInt64(4) * MyInt64(5) + MyInt64(3))
		 * (MyInt64(8) + MyInt64(6) + MyInt64(7) * MyInt64(2) * ( MyInt64(3) + MyInt64(3) + ( MyInt64(7) * MyInt64(4) * MyInt64(4) + MyInt64(8) ) + MyInt64(4) ) + MyInt64(4))
		 * (MyInt64(8) + MyInt64(8) * MyInt64(8) + MyInt64(3) + ( ( MyInt64(9) + MyInt64(9) ) * MyInt64(3) ) + ( MyInt64(8) + MyInt64(2) + MyInt64(4) ) )
		 * ( ( MyInt64(4) * ( MyInt64(8) + MyInt64(6) + MyInt64(4) + MyInt64(4) * MyInt64(4) ) * ( MyInt64(6) * MyInt64(9) ) ) * MyInt64(2) * MyInt64(4) + MyInt64(4) * MyInt64(4) + ( MyInt64(7) + MyInt64(8) * ( MyInt64(5) * MyInt64(7) ) + MyInt64(7) * MyInt64(4) + MyInt64(4) ) )
		 * ( ( ( MyInt64(3) * MyInt64(7) * MyInt64(3) + MyInt64(3) + MyInt64(3) * MyInt64(3) ) * MyInt64(3) + MyInt64(4) * MyInt64(2) ) + MyInt64(8) + MyInt64(5) * MyInt64(2) + ( MyInt64(6) + MyInt64(3) * MyInt64(3) + ( MyInt64(5) + MyInt64(9) * MyInt64(5) + MyInt64(4) ) + MyInt64(2) + ( MyInt64(4) * MyInt64(4) * MyInt64(7) + MyInt64(9) + MyInt64(2) ) ) )
		 * ( ( MyInt64(6) + MyInt64(7) * ( MyInt64(2) * MyInt64(5) + MyInt64(9) + MyInt64(3) * MyInt64(7) + MyInt64(3) ) * MyInt64(3) * ( MyInt64(5) + MyInt64(3) * MyInt64(8) ) ) + MyInt64(4) * MyInt64(7) + MyInt64(9) * ( MyInt64(7) * ( MyInt64(7) + MyInt64(6) * MyInt64(6) + MyInt64(5) + MyInt64(5) ) + MyInt64(6) ) )
		 * (MyInt64(6) + MyInt64(4) + MyInt64(5) + MyInt64(5) + ( ( MyInt64(8) * MyInt64(5) + MyInt64(7) ) + ( MyInt64(6) + MyInt64(8) + MyInt64(4) * MyInt64(9) ) + MyInt64(2) * MyInt64(6) * MyInt64(2) ) )
		 * (MyInt64(6) + ( MyInt64(2) + MyInt64(4) + MyInt64(2) ) * MyInt64(4))
		 * (MyInt64(4) * MyInt64(6) * ( MyInt64(3) + MyInt64(2) + MyInt64(7) + MyInt64(4) ) + ( ( MyInt64(9) * MyInt64(2) + MyInt64(4) * MyInt64(5) ) * MyInt64(6) + MyInt64(3) ) * MyInt64(6) * MyInt64(9))
		 * (MyInt64(9) + MyInt64(3) + MyInt64(3) * MyInt64(4) + MyInt64(6) * ( ( MyInt64(5) + MyInt64(9) * MyInt64(9) + MyInt64(6) + MyInt64(5) * MyInt64(2) ) * MyInt64(6) * MyInt64(9) + MyInt64(2) ) )
		 * (MyInt64(3) * MyInt64(9) + MyInt64(2) + ( MyInt64(2) + MyInt64(2) + ( MyInt64(9) * MyInt64(7) * MyInt64(9) + MyInt64(9) * MyInt64(7) * MyInt64(3) ) ) + MyInt64(8))
		 * ( ( ( MyInt64(5) + MyInt64(6) * MyInt64(2) + MyInt64(9) + MyInt64(8) + MyInt64(5) ) * MyInt64(6) * MyInt64(6) ) + MyInt64(7))
		 * ( ( ( MyInt64(4) * MyInt64(9) + MyInt64(2) ) + MyInt64(2) + MyInt64(4) + MyInt64(3) + MyInt64(3) * MyInt64(7) ) * MyInt64(5) * MyInt64(2) + MyInt64(4) + ( MyInt64(7) + MyInt64(3) * MyInt64(6) + ( MyInt64(8) + MyInt64(4) * MyInt64(6) ) + ( MyInt64(9) * MyInt64(9) * MyInt64(8) * MyInt64(6) + MyInt64(2) ) ) )
		 * (MyInt64(7) + ( MyInt64(7) * MyInt64(7) * ( MyInt64(7) * MyInt64(7) + MyInt64(6) * MyInt64(4) * MyInt64(3) ) * MyInt64(5) ) )
		 * ( ( MyInt64(7) + MyInt64(3) ) * ( MyInt64(3) * MyInt64(5) * MyInt64(7) * MyInt64(2) ) + MyInt64(2) * MyInt64(2) + ( ( MyInt64(2) + MyInt64(7) * MyInt64(6) + MyInt64(8) ) * ( MyInt64(8) + MyInt64(5) ) * MyInt64(2) ) )
		 * ( ( MyInt64(5) * MyInt64(8) * MyInt64(2) * MyInt64(4) * MyInt64(3) + MyInt64(5) ) * ( MyInt64(8) + MyInt64(2) * MyInt64(8) * MyInt64(4) * MyInt64(5) * MyInt64(7) ) + MyInt64(6) + MyInt64(8) * ( ( MyInt64(4) * MyInt64(6) + MyInt64(8) * MyInt64(4) + MyInt64(5) ) + MyInt64(5) + MyInt64(3) * MyInt64(4) ) )
		 * ( ( MyInt64(9) * ( MyInt64(8) * MyInt64(6) + MyInt64(9) ) + MyInt64(4) + MyInt64(9) ) * MyInt64(3) + MyInt64(6) + ( MyInt64(2) + MyInt64(6) ) + MyInt64(6) * MyInt64(2))
		 * (MyInt64(5) + MyInt64(9))
		 * (MyInt64(2) * MyInt64(8) + ( MyInt64(4) + MyInt64(2) * ( MyInt64(3) + MyInt64(9) ) + MyInt64(4) * MyInt64(5) + MyInt64(6) ) + MyInt64(3) * MyInt64(6))
		 * ( ( MyInt64(7) * MyInt64(4) + MyInt64(9) * MyInt64(2) + MyInt64(8) + MyInt64(5) ) * MyInt64(9) + MyInt64(2) + MyInt64(7) + MyInt64(8))
		 * (MyInt64(6) + ( ( MyInt64(7) + MyInt64(7) * MyInt64(3) + MyInt64(5) + MyInt64(6) ) + MyInt64(5) + MyInt64(6) * ( MyInt64(3) + MyInt64(8) + MyInt64(7) ) + MyInt64(3) * MyInt64(9) ) + MyInt64(2))
		 * ( ( ( MyInt64(5) + MyInt64(6) * MyInt64(8) + MyInt64(2) + MyInt64(4) ) * MyInt64(6) * MyInt64(8) ) * MyInt64(5) + MyInt64(5) * MyInt64(6))
		 * (MyInt64(4) + ( MyInt64(4) * MyInt64(2) * ( MyInt64(9) * MyInt64(3) + MyInt64(7) * MyInt64(8) * MyInt64(2) ) + MyInt64(2) + MyInt64(4) ) + ( MyInt64(9) * MyInt64(8) * MyInt64(6) * MyInt64(8) * ( MyInt64(6) * MyInt64(3) + MyInt64(2) * MyInt64(7) * MyInt64(4) * MyInt64(7) ) ) )
		 * ( ( MyInt64(9) + MyInt64(9) ) + MyInt64(6))
		 * (MyInt64(9) * MyInt64(5) * ( MyInt64(6) + ( MyInt64(7) * MyInt64(7) + MyInt64(5) * MyInt64(2) + MyInt64(6) * MyInt64(2) ) + MyInt64(7) ) )
		 * (MyInt64(7) * MyInt64(8) * MyInt64(6))
		 * ( ( MyInt64(2) + MyInt64(4) * MyInt64(7) * MyInt64(2) + MyInt64(4) + MyInt64(8) ) + MyInt64(5) + MyInt64(2) + MyInt64(5) * ( MyInt64(8) * MyInt64(6) * MyInt64(3) + MyInt64(8) * ( MyInt64(4) * MyInt64(7) + MyInt64(2) + MyInt64(7) ) ) * MyInt64(7))
		 * (MyInt64(2) + MyInt64(6) * MyInt64(3) + MyInt64(7) + ( MyInt64(6) * MyInt64(7) * MyInt64(3) * MyInt64(4) * MyInt64(6) + MyInt64(8) ) )
		 * (MyInt64(9) * ( MyInt64(9) + MyInt64(3) * MyInt64(7) ) * MyInt64(3) * MyInt64(3))
		 * (MyInt64(6) * MyInt64(4) * ( MyInt64(4) * ( MyInt64(4) + MyInt64(8) ) + ( MyInt64(9) * MyInt64(9) + MyInt64(4) ) + MyInt64(6) ) )
		 * ( ( MyInt64(3) + MyInt64(3) * MyInt64(7) * MyInt64(7) * MyInt64(3) ) + MyInt64(5) + MyInt64(7) * ( MyInt64(6) + ( MyInt64(7) * MyInt64(7) * MyInt64(6) + MyInt64(2) + MyInt64(6) + MyInt64(6) ) ) * MyInt64(2) * MyInt64(5))
		 * (MyInt64(6) + MyInt64(8) + ( MyInt64(8) * ( MyInt64(7) + MyInt64(8) * MyInt64(3) ) + MyInt64(9) * MyInt64(5) ) )
		 * (MyInt64(3) + MyInt64(4) * MyInt64(3) * ( MyInt64(4) * MyInt64(2) + MyInt64(2) ) + MyInt64(8) * ( MyInt64(8) + ( MyInt64(2) * MyInt64(5) ) + ( MyInt64(5) + MyInt64(3) + MyInt64(9) * MyInt64(2) + MyInt64(6) ) + MyInt64(9) ) )
		 * ( ( ( MyInt64(8) + MyInt64(6) * MyInt64(5) ) * ( MyInt64(6) + MyInt64(3) + MyInt64(6) ) ) + MyInt64(7))
		 * ( ( MyInt64(8) + MyInt64(4) + MyInt64(2) * ( MyInt64(5) + MyInt64(8) + MyInt64(5) * MyInt64(7) * MyInt64(3) * MyInt64(5) ) + MyInt64(8) * MyInt64(5) ) + MyInt64(7) * ( MyInt64(6) * MyInt64(9) ) + ( MyInt64(8) * MyInt64(3) + MyInt64(7) ) * ( MyInt64(9) + MyInt64(9) + MyInt64(6) + MyInt64(2) * MyInt64(8) ) * MyInt64(2))
		 * (MyInt64(7) * MyInt64(5) + ( MyInt64(8) * ( MyInt64(6) + MyInt64(8) ) ) * ( ( MyInt64(9) + MyInt64(4) * MyInt64(5) + MyInt64(5) ) * MyInt64(8) + MyInt64(5) * MyInt64(3) * MyInt64(8) + MyInt64(4) ) + ( MyInt64(8) * MyInt64(3) ) + ( MyInt64(8) * MyInt64(8) * ( MyInt64(6) + MyInt64(4) + MyInt64(2) + MyInt64(5) * MyInt64(7) ) * MyInt64(3) ) )
		 * (MyInt64(9) * MyInt64(7) + MyInt64(6) * MyInt64(2) + MyInt64(3) * ( ( MyInt64(2) * MyInt64(6) * MyInt64(9) + MyInt64(8) ) * MyInt64(3) * MyInt64(9) + MyInt64(3) * ( MyInt64(3) * MyInt64(3) + MyInt64(4) ) ) )
		 * (MyInt64(7) + ( MyInt64(8) + MyInt64(9) + MyInt64(5) ) * MyInt64(6) + ( MyInt64(3) * ( MyInt64(5) * MyInt64(4) + MyInt64(4) ) ) + MyInt64(2) * MyInt64(9))
		 * (MyInt64(4) * MyInt64(7) + MyInt64(5) + ( MyInt64(8) + ( MyInt64(5) * MyInt64(5) * MyInt64(6) ) * MyInt64(5) + MyInt64(6) * MyInt64(9) ) )
		 * (MyInt64(4) * MyInt64(3) + ( MyInt64(2) + MyInt64(2) * MyInt64(8) + MyInt64(2) ) + MyInt64(7) + MyInt64(5) + MyInt64(6))
		 * (MyInt64(4) * MyInt64(7) + MyInt64(5) + ( MyInt64(6) + MyInt64(6) + MyInt64(3) * ( MyInt64(8) * MyInt64(8) * MyInt64(3) + MyInt64(7) + MyInt64(4) + MyInt64(8) ) ) + ( MyInt64(5) + MyInt64(6) + MyInt64(9) * MyInt64(7) * MyInt64(9) ) )
		 * ( ( ( MyInt64(4) + MyInt64(6) + MyInt64(2) ) * MyInt64(2) ) + MyInt64(8) + MyInt64(7) * MyInt64(2))
		 * (MyInt64(9) * MyInt64(7) * ( MyInt64(4) * MyInt64(4) * MyInt64(2) * MyInt64(2) + MyInt64(4) * MyInt64(9) ) + MyInt64(8) * MyInt64(8) * MyInt64(7))
		 * ( ( MyInt64(8) * ( MyInt64(7) * MyInt64(8) ) + MyInt64(6) + ( MyInt64(5) * MyInt64(6) * MyInt64(9) + MyInt64(8) ) + MyInt64(6) * MyInt64(9) ) * MyInt64(5) + MyInt64(9) * MyInt64(8))
		 * ( ( ( MyInt64(5) * MyInt64(2) ) * MyInt64(7) * MyInt64(2) * ( MyInt64(4) + MyInt64(6) * MyInt64(8) * MyInt64(6) ) + MyInt64(6) ) + MyInt64(6) * MyInt64(5) + MyInt64(4) * MyInt64(9))
		 * (MyInt64(4) * MyInt64(5) + MyInt64(6) + MyInt64(7) + MyInt64(9))
		 * (MyInt64(8) + ( ( MyInt64(6) + MyInt64(6) * MyInt64(6) * MyInt64(4) + MyInt64(4) + MyInt64(8) ) + ( MyInt64(9) * MyInt64(3) ) * MyInt64(6) + ( MyInt64(7) * MyInt64(6) + MyInt64(2) ) ) * MyInt64(2))
		 * ( ( ( MyInt64(3) * MyInt64(5) * MyInt64(9) ) * MyInt64(7) * MyInt64(4) + MyInt64(2) * ( MyInt64(9) * MyInt64(7) * MyInt64(5) + MyInt64(8) ) + MyInt64(9) ) * MyInt64(2))
		 * (MyInt64(3) + ( ( MyInt64(6) + MyInt64(9) + MyInt64(6) + MyInt64(5) * MyInt64(5) * MyInt64(4) ) * MyInt64(8) ) * ( MyInt64(6) + ( MyInt64(8) + MyInt64(6) + MyInt64(3) + MyInt64(7) ) ) * MyInt64(3))
		 * ( ( MyInt64(9) * MyInt64(9) * MyInt64(2) + MyInt64(2) + MyInt64(3) + ( MyInt64(9) * MyInt64(4) * MyInt64(9) ) ) + MyInt64(5) * MyInt64(4) + MyInt64(7))
		 * ( ( MyInt64(4) + MyInt64(4) * MyInt64(9) ) + MyInt64(8) + MyInt64(8) + ( MyInt64(9) * MyInt64(3) ) )
		 * (MyInt64(5) * ( MyInt64(3) + MyInt64(5) * MyInt64(2) * ( MyInt64(2) + MyInt64(7) ) + MyInt64(4) * MyInt64(8) ) * MyInt64(6) * MyInt64(9) * ( MyInt64(2) * MyInt64(7) + ( MyInt64(3) + MyInt64(6) ) + MyInt64(6) + MyInt64(6) * MyInt64(8) ) )
		 * (MyInt64(2) * MyInt64(4) * ( MyInt64(5) + MyInt64(3) * MyInt64(6) + ( MyInt64(7) + MyInt64(7) + MyInt64(4) * MyInt64(3) ) * MyInt64(6) * MyInt64(7) ) + MyInt64(2))
		 * ( ( MyInt64(5) * MyInt64(6) * MyInt64(3) * ( MyInt64(8) + MyInt64(3) ) ) + MyInt64(3) * MyInt64(6))
		 * (MyInt64(4) * MyInt64(6) * ( MyInt64(3) + MyInt64(9) * MyInt64(5) + ( MyInt64(7) + MyInt64(9) * MyInt64(4) ) * MyInt64(4) * MyInt64(4) ) * MyInt64(3) * MyInt64(5) * MyInt64(6))
		 * (MyInt64(4) + MyInt64(9) + MyInt64(7) * MyInt64(2) * MyInt64(6))
		 * (MyInt64(6) + ( MyInt64(5) + MyInt64(5) * MyInt64(3) + MyInt64(8) ) )
		 * (MyInt64(5) * MyInt64(6) * MyInt64(3) + MyInt64(7) + MyInt64(5) * ( MyInt64(8) + MyInt64(3) * MyInt64(4) * MyInt64(7) ) )
		 * ( ( MyInt64(3) * MyInt64(2) + ( MyInt64(2) + MyInt64(2) * MyInt64(5) * MyInt64(2) ) + MyInt64(3) + ( MyInt64(7) + MyInt64(6) + MyInt64(2) * MyInt64(3) ) * MyInt64(2) ) * ( ( MyInt64(9) + MyInt64(6) + MyInt64(7) ) + ( MyInt64(2) * MyInt64(7) * MyInt64(8) * MyInt64(2) * MyInt64(6) + MyInt64(4) ) + MyInt64(7) * MyInt64(9) ) + MyInt64(6) + ( ( MyInt64(6) * MyInt64(7) ) + ( MyInt64(4) + MyInt64(6) * MyInt64(4) + MyInt64(7) ) + MyInt64(9) + MyInt64(3) ) + MyInt64(2))
		 * (MyInt64(9) * MyInt64(2) * MyInt64(7) + ( MyInt64(6) + MyInt64(5) ) + MyInt64(6) + MyInt64(6))
		 * ( ( MyInt64(7) + MyInt64(6) * MyInt64(7) ) + MyInt64(6) * MyInt64(3) * MyInt64(6) * MyInt64(2) * MyInt64(7))
		 * (MyInt64(6) + MyInt64(4) * ( ( MyInt64(3) * MyInt64(5) ) * MyInt64(8) + MyInt64(8) * MyInt64(3) + ( MyInt64(7) + MyInt64(3) ) ) * MyInt64(3) + MyInt64(9))
		 * (MyInt64(5) * MyInt64(4) * ( ( MyInt64(6) + MyInt64(8) * MyInt64(4) + MyInt64(9) ) * MyInt64(7) + ( MyInt64(6) + MyInt64(3) + MyInt64(4) + MyInt64(4) * MyInt64(5) * MyInt64(3) ) + MyInt64(5) + MyInt64(6) * MyInt64(9) ) + MyInt64(2) + MyInt64(5) * MyInt64(8))
		 * (MyInt64(3) * ( ( MyInt64(7) * MyInt64(7) * MyInt64(3) ) + MyInt64(8) ) * MyInt64(7) * MyInt64(8) + MyInt64(2) + MyInt64(9))
		 * (MyInt64(3) * MyInt64(9) + MyInt64(2) + ( ( MyInt64(8) * MyInt64(9) + MyInt64(8) ) + MyInt64(4) + MyInt64(9) * MyInt64(2) ) + MyInt64(2) * ( MyInt64(5) * ( MyInt64(3) * MyInt64(8) * MyInt64(4) * MyInt64(3) + MyInt64(8) ) + MyInt64(8) * ( MyInt64(8) + MyInt64(9) * MyInt64(7) + MyInt64(4) ) * MyInt64(6) + MyInt64(7) ) )
		 * (MyInt64(6) * MyInt64(4) * MyInt64(7) * ( ( MyInt64(9) + MyInt64(7) * MyInt64(6) ) * MyInt64(6) + MyInt64(2) * MyInt64(6) * MyInt64(2) * MyInt64(5) ) )
		 * (MyInt64(7) * MyInt64(8) * MyInt64(5) + MyInt64(3) * ( MyInt64(8) + MyInt64(5) + MyInt64(3) * MyInt64(7) * MyInt64(4) ) )
		 * ( ( MyInt64(4) + MyInt64(7) ) * MyInt64(5) + ( MyInt64(8) + MyInt64(9) + MyInt64(6) + MyInt64(7) * MyInt64(6) + MyInt64(8) ) )
		 * (MyInt64(8) * MyInt64(5) + MyInt64(7) + MyInt64(6) * ( MyInt64(9) + MyInt64(2) + MyInt64(3) * ( MyInt64(7) * MyInt64(7) ) + MyInt64(9) * MyInt64(4) ) )
		 * ( ( ( MyInt64(5) + MyInt64(8) * MyInt64(9) + MyInt64(6) ) + MyInt64(8) + ( MyInt64(3) * MyInt64(5) * MyInt64(5) * MyInt64(7) ) ) + MyInt64(5) * ( MyInt64(6) * ( MyInt64(2) + MyInt64(8) + MyInt64(4) + MyInt64(6) * MyInt64(7) ) + MyInt64(5) ) * MyInt64(7))
		 * (MyInt64(6) + MyInt64(8) * ( MyInt64(3) * ( MyInt64(7) * MyInt64(3) ) * MyInt64(8) + ( MyInt64(6) * MyInt64(9) * MyInt64(9) + MyInt64(9) * MyInt64(2) * MyInt64(2) ) * ( MyInt64(8) + MyInt64(6) * MyInt64(5) ) * MyInt64(2) ) * MyInt64(5))
		 * (MyInt64(7) * MyInt64(6) + MyInt64(7) * MyInt64(8))
		 * (MyInt64(7) + ( MyInt64(3) * ( MyInt64(3) * MyInt64(7) ) * MyInt64(4) ) + ( MyInt64(5) + MyInt64(7) + MyInt64(6) + MyInt64(2) ) * MyInt64(5) * MyInt64(3) + MyInt64(5))
		 * (MyInt64(3) * ( MyInt64(4) + MyInt64(7) * ( MyInt64(4) * MyInt64(6) + MyInt64(7) * MyInt64(8) + MyInt64(7) + MyInt64(4) ) ) + MyInt64(8))
		 * ( ( ( MyInt64(9) + MyInt64(3) * MyInt64(6) + MyInt64(7) * MyInt64(9) * MyInt64(6) ) * MyInt64(6) * MyInt64(7) * MyInt64(4) * MyInt64(2) + ( MyInt64(5) * MyInt64(6) + MyInt64(2) + MyInt64(4) ) ) + MyInt64(5))
		 * ( ( MyInt64(8) * MyInt64(7) * MyInt64(7) ) * MyInt64(7) * ( MyInt64(3) + MyInt64(6) + MyInt64(6) * MyInt64(9) + MyInt64(2) ) )
		 * ( ( MyInt64(7) * ( MyInt64(3) * MyInt64(6) + MyInt64(8) ) ) * ( MyInt64(9) * MyInt64(6) * ( MyInt64(8) + MyInt64(5) * MyInt64(7) * MyInt64(3) ) + MyInt64(2) * MyInt64(4) ) )
		 * ( ( MyInt64(6) * ( MyInt64(7) * MyInt64(5) + MyInt64(5) + MyInt64(7) ) ) + ( ( MyInt64(8) * MyInt64(3) ) * ( MyInt64(5) * MyInt64(4) + MyInt64(5) + MyInt64(8) * MyInt64(6) * MyInt64(6) ) * MyInt64(9) + MyInt64(3) * MyInt64(8) * ( MyInt64(4) * MyInt64(2) + MyInt64(5) * MyInt64(3) + MyInt64(6) * MyInt64(5) ) ) )
		 * (MyInt64(8) + MyInt64(7) * MyInt64(8) + ( MyInt64(2) + MyInt64(9) * MyInt64(5) + ( MyInt64(5) + MyInt64(2) ) ) * MyInt64(9) + MyInt64(2))
		 * (MyInt64(2) * MyInt64(9) + MyInt64(8) + MyInt64(7) + ( MyInt64(2) * MyInt64(9) * MyInt64(7) + MyInt64(7) ) * MyInt64(5))
		 * (MyInt64(4) * ( MyInt64(8) + MyInt64(2) * MyInt64(7) ) + MyInt64(7) * MyInt64(3) * MyInt64(8) + ( MyInt64(7) * MyInt64(8) + MyInt64(9) * MyInt64(2) + MyInt64(2) ) )
		 * ( ( MyInt64(7) * MyInt64(7) + MyInt64(2) ) * MyInt64(4))
		 * ( ( MyInt64(9) * MyInt64(5) + MyInt64(3) * MyInt64(4) ) + MyInt64(4))
		 * (MyInt64(2) * MyInt64(2) + ( MyInt64(9) + MyInt64(7) * MyInt64(5) * ( MyInt64(2) * MyInt64(8) ) * ( MyInt64(5) + MyInt64(6) * MyInt64(8) + MyInt64(5) ) ) * MyInt64(2))
		 * (MyInt64(4) + ( MyInt64(4) + ( MyInt64(8) * MyInt64(9) * MyInt64(3) + MyInt64(5) + MyInt64(8) * MyInt64(2) ) * ( MyInt64(5) + MyInt64(2) ) + MyInt64(3) + MyInt64(4) * MyInt64(6) ) * MyInt64(2) * MyInt64(7))
		 * (MyInt64(4) + MyInt64(2) + ( MyInt64(7) * MyInt64(2) * MyInt64(9) * MyInt64(7) ) + MyInt64(9) * MyInt64(2))
		 * ( ( MyInt64(6) * MyInt64(2) * MyInt64(4) + MyInt64(3) ) * MyInt64(8) * MyInt64(9) * MyInt64(5))
		 * (MyInt64(7) + MyInt64(4) + ( MyInt64(5) + MyInt64(3) + ( MyInt64(6) + MyInt64(4) ) * MyInt64(2) ) * MyInt64(6))
		 * (MyInt64(5) + MyInt64(5) + ( MyInt64(6) + ( MyInt64(5) * MyInt64(7) * MyInt64(4) + MyInt64(2) * MyInt64(7) + MyInt64(9) ) * MyInt64(8) * MyInt64(8) + MyInt64(2) ) )
		 * ( ( MyInt64(6) + MyInt64(4) + MyInt64(2) + MyInt64(6) ) * MyInt64(6) + MyInt64(7) + MyInt64(9) * MyInt64(2) * MyInt64(2))
		 * (MyInt64(3) + ( MyInt64(8) + MyInt64(4) ) )
		 * ( ( MyInt64(8) * MyInt64(9) + MyInt64(7) ) * MyInt64(8) + MyInt64(7) + MyInt64(4))
		 * (MyInt64(4) * ( MyInt64(9) + MyInt64(6) * MyInt64(3) * MyInt64(5) * MyInt64(2) ) + MyInt64(5) * ( MyInt64(4) * ( MyInt64(4) + MyInt64(5) * MyInt64(2) * MyInt64(4) + MyInt64(2) ) * MyInt64(3) * MyInt64(2) * MyInt64(5) ) + ( MyInt64(9) * MyInt64(5) ) )
		 * ( ( MyInt64(6) + MyInt64(7) * MyInt64(6) * MyInt64(9) * MyInt64(7) ) + MyInt64(5) * ( ( MyInt64(9) * MyInt64(6) ) + MyInt64(9) + MyInt64(7) * MyInt64(2) * MyInt64(9) ) * MyInt64(2) * ( MyInt64(3) + MyInt64(2) ) * ( MyInt64(3) * MyInt64(7) ) )
		 * ( ( MyInt64(4) * ( MyInt64(6) + MyInt64(7) + MyInt64(5) * MyInt64(7) ) ) + MyInt64(4) + MyInt64(7) * MyInt64(5))
		 * ( ( MyInt64(3) * MyInt64(9) * ( MyInt64(8) + MyInt64(8) * MyInt64(6) * MyInt64(8) + MyInt64(9) ) * MyInt64(8) * ( MyInt64(5) + MyInt64(3) + MyInt64(4) + MyInt64(5) ) + ( MyInt64(3) * MyInt64(8) + MyInt64(7) + MyInt64(7) + MyInt64(2) + MyInt64(3) ) ) + MyInt64(5) * ( MyInt64(6) + ( MyInt64(3) * MyInt64(7) * MyInt64(4) ) * MyInt64(4) * ( MyInt64(5) + MyInt64(9) + MyInt64(6) + MyInt64(2) + MyInt64(8) * MyInt64(4) ) + MyInt64(4) ) )
		 * (MyInt64(7) * ( MyInt64(5) * MyInt64(9) * MyInt64(9) * MyInt64(7) ) + MyInt64(8))
		 * (MyInt64(5) * MyInt64(3) * MyInt64(8) * MyInt64(3) + MyInt64(4) + MyInt64(2))
		 * ( ( MyInt64(3) + MyInt64(5) ) * MyInt64(7) * ( MyInt64(3) + MyInt64(5) + MyInt64(6) * MyInt64(6) * MyInt64(2) ) + MyInt64(7) * ( MyInt64(5) * MyInt64(7) + MyInt64(7) + MyInt64(5) * MyInt64(8) ) )
		 * (MyInt64(8) * MyInt64(5) * ( ( MyInt64(3) + MyInt64(5) * MyInt64(8) * MyInt64(8) + MyInt64(7) * MyInt64(7) ) + MyInt64(2) * MyInt64(2) ) )
		 * ( ( ( MyInt64(7) + MyInt64(5) * MyInt64(2) + MyInt64(5) ) + MyInt64(6) * MyInt64(5) ) + ( ( MyInt64(4) * MyInt64(7) * MyInt64(3) + MyInt64(5) ) + MyInt64(8) * MyInt64(4) + ( MyInt64(3) * MyInt64(9) * MyInt64(5) * MyInt64(8) + MyInt64(7) * MyInt64(8) ) * MyInt64(5) + MyInt64(2) ) * ( MyInt64(8) + MyInt64(9) * MyInt64(8) * MyInt64(7) + MyInt64(6) + MyInt64(8) ) + MyInt64(4) + MyInt64(3))
		 * (MyInt64(4) + ( MyInt64(5) * ( MyInt64(7) + MyInt64(5) ) ) * MyInt64(5) + ( MyInt64(8) + MyInt64(6) + MyInt64(8) ) * ( MyInt64(8) * MyInt64(6) + MyInt64(3) * MyInt64(5) ) + MyInt64(5))
		 * (MyInt64(2) * ( MyInt64(8) * MyInt64(5) * MyInt64(5) ) + MyInt64(9) + MyInt64(3) + ( MyInt64(5) + MyInt64(3) + MyInt64(5) ) * ( ( MyInt64(4) + MyInt64(4) + MyInt64(4) * MyInt64(5) * MyInt64(7) * MyInt64(3) ) * MyInt64(9) * ( MyInt64(2) * MyInt64(7) + MyInt64(5) ) * ( MyInt64(9) * MyInt64(9) + MyInt64(2) + MyInt64(2) + MyInt64(4) + MyInt64(4) ) + MyInt64(9) ) )
		 * (MyInt64(4) * MyInt64(7) + ( MyInt64(9) + MyInt64(2) * ( MyInt64(3) + MyInt64(7) * MyInt64(8) * MyInt64(9) * MyInt64(5) ) * ( MyInt64(7) * MyInt64(4) + MyInt64(8) * MyInt64(7) * MyInt64(7) ) * MyInt64(3) ) )
		 * (MyInt64(8) * MyInt64(6) * MyInt64(6) + MyInt64(9))
		 * ( ( MyInt64(7) + MyInt64(2) + ( MyInt64(8) + MyInt64(3) + MyInt64(6) * MyInt64(5) ) * MyInt64(4) + MyInt64(6) ) + ( MyInt64(3) * MyInt64(2) ) + MyInt64(4) * MyInt64(5) + ( MyInt64(8) + MyInt64(8) * MyInt64(6) ) * MyInt64(9))
		 * ( ( MyInt64(6) * MyInt64(2) ) + ( MyInt64(7) + MyInt64(4) + MyInt64(5) * MyInt64(7) + MyInt64(2) * ( MyInt64(3) + MyInt64(8) * MyInt64(3) ) ) * MyInt64(2))
		 * ( ( MyInt64(3) + MyInt64(6) + ( MyInt64(6) + MyInt64(6) + MyInt64(6) * MyInt64(6) + MyInt64(7) + MyInt64(3) ) ) * MyInt64(4) * MyInt64(8))
		 * (MyInt64(4) + MyInt64(8) * ( MyInt64(5) * MyInt64(9) + MyInt64(8) * MyInt64(8) + MyInt64(4) ) )
		 * (MyInt64(6) + ( MyInt64(4) * MyInt64(6) + ( MyInt64(8) * MyInt64(2) ) * MyInt64(5) ) + MyInt64(6) * MyInt64(4) * MyInt64(4) * MyInt64(2))
		 * (MyInt64(7) * ( MyInt64(8) * MyInt64(8) + MyInt64(9) + MyInt64(5) + MyInt64(9) + MyInt64(6) ) * MyInt64(4) * MyInt64(6) + MyInt64(4) * MyInt64(6))
		 * (MyInt64(8) * ( ( MyInt64(4) + MyInt64(7) ) * MyInt64(3) ) + MyInt64(3) * MyInt64(3) * MyInt64(6) + MyInt64(7))
		 * (MyInt64(3) + MyInt64(3))
		 * ( ( MyInt64(5) + MyInt64(8) + MyInt64(5) + MyInt64(2) * MyInt64(8) * MyInt64(8) ) * MyInt64(9) + MyInt64(3) * ( ( MyInt64(2) * MyInt64(2) + MyInt64(3) * MyInt64(6) + MyInt64(2) + MyInt64(5) ) + MyInt64(6) + MyInt64(4) * MyInt64(3) + MyInt64(6) + MyInt64(8) ) * ( ( MyInt64(7) * MyInt64(2) ) + MyInt64(7) + ( MyInt64(7) + MyInt64(9) ) + MyInt64(2) + MyInt64(5) ) * MyInt64(7))
		 * (MyInt64(4) + MyInt64(3))
		 * ( ( MyInt64(4) * MyInt64(6) * MyInt64(8) * MyInt64(8) ) + MyInt64(6) * ( MyInt64(9) + MyInt64(6) + MyInt64(2) + MyInt64(8) ) * MyInt64(4) + MyInt64(4))
		 * (MyInt64(7) * ( MyInt64(5) * ( MyInt64(8) * MyInt64(2) ) * ( MyInt64(4) * MyInt64(5) ) ) )
		 * ( ( MyInt64(8) + MyInt64(6) + ( MyInt64(3) + MyInt64(9) ) ) * MyInt64(3) + MyInt64(5) * MyInt64(2) + MyInt64(7) + MyInt64(5))
		 * (MyInt64(6) + ( MyInt64(9) * MyInt64(3) * MyInt64(6) * MyInt64(4) + MyInt64(3) * MyInt64(4) ) * MyInt64(4) + ( MyInt64(7) + MyInt64(7) ) + MyInt64(5))
		 * (MyInt64(8) * ( ( MyInt64(7) * MyInt64(2) * MyInt64(2) ) * MyInt64(2) * MyInt64(7) + MyInt64(4) + MyInt64(3) * MyInt64(6) ) * MyInt64(9) + MyInt64(2))
		 * ( ( MyInt64(8) * MyInt64(9) * MyInt64(6) + ( MyInt64(7) + MyInt64(9) + MyInt64(6) + MyInt64(5) + MyInt64(9) ) * MyInt64(4) * MyInt64(2) ) + ( MyInt64(6) * MyInt64(6) * MyInt64(3) + MyInt64(4) ) * MyInt64(4) * MyInt64(9))
		 * (MyInt64(9) * ( MyInt64(3) + MyInt64(2) + MyInt64(6) + MyInt64(9) * MyInt64(6) ) * MyInt64(8) * MyInt64(3) * MyInt64(7) * MyInt64(6))
		 * (MyInt64(3) * ( MyInt64(8) * ( MyInt64(4) * MyInt64(4) * MyInt64(4) * MyInt64(2) ) + MyInt64(9) + ( MyInt64(7) * MyInt64(9) * MyInt64(5) ) + MyInt64(2) ) * MyInt64(3))
		 * ( ( MyInt64(2) + ( MyInt64(3) + MyInt64(3) * MyInt64(5) * MyInt64(5) + MyInt64(4) * MyInt64(4) ) + MyInt64(7) + MyInt64(3) + MyInt64(7) + MyInt64(6) ) * MyInt64(2))
		 * (MyInt64(3) * MyInt64(6) + MyInt64(4) + ( MyInt64(5) + MyInt64(9) + MyInt64(3) ) + ( MyInt64(6) + MyInt64(2) + MyInt64(4) ) + MyInt64(2))
		 * (MyInt64(2) * ( ( MyInt64(4) * MyInt64(8) * MyInt64(8) * MyInt64(6) ) + MyInt64(8) * MyInt64(9) + MyInt64(5) * MyInt64(7) + MyInt64(2) ) * MyInt64(7) * MyInt64(3))
		 * (MyInt64(5) + MyInt64(6) + ( MyInt64(9) * MyInt64(8) ) * ( MyInt64(2) * MyInt64(6) * MyInt64(4) * MyInt64(9) ) * MyInt64(9) + ( MyInt64(7) + MyInt64(6) + MyInt64(6) * MyInt64(2) * MyInt64(9) ) )
		 * (MyInt64(5) * MyInt64(4) + MyInt64(7) + MyInt64(9) * MyInt64(3) * MyInt64(4))
		 * (MyInt64(7) * MyInt64(9) + ( MyInt64(4) * MyInt64(7) * MyInt64(7) * MyInt64(3) ) + ( MyInt64(2) * MyInt64(7) + MyInt64(4) ) )
		 * ( ( MyInt64(2) * MyInt64(7) ) + ( ( MyInt64(3) * MyInt64(3) + MyInt64(4) + MyInt64(7) + MyInt64(4) ) + MyInt64(8) + MyInt64(6) * MyInt64(9) * MyInt64(8) + MyInt64(2) ) * ( ( MyInt64(7) + MyInt64(4) ) + ( MyInt64(9) + MyInt64(5) + MyInt64(5) * MyInt64(9) + MyInt64(9) ) + MyInt64(3) + MyInt64(7) * ( MyInt64(7) * MyInt64(4) + MyInt64(4) + MyInt64(9) + MyInt64(5) ) + ( MyInt64(5) * MyInt64(2) * MyInt64(3) * MyInt64(8) * MyInt64(3) * MyInt64(4) ) ) * MyInt64(2) * MyInt64(3) + MyInt64(7))
		 * (MyInt64(7) * MyInt64(2) + ( MyInt64(2) * MyInt64(2) + MyInt64(4) + MyInt64(8) + ( MyInt64(9) * MyInt64(7) * MyInt64(2) * MyInt64(8) ) * ( MyInt64(2) + MyInt64(2) * MyInt64(5) * MyInt64(7) + MyInt64(7) ) ) + MyInt64(7))
		 * (MyInt64(7) * ( ( MyInt64(7) * MyInt64(3) + MyInt64(3) + MyInt64(4) ) + MyInt64(3) + MyInt64(9) ) )
		 * (MyInt64(9) * ( ( MyInt64(5) + MyInt64(2) * MyInt64(6) ) * MyInt64(2) * ( MyInt64(8) * MyInt64(4) * MyInt64(5) * MyInt64(6) ) * MyInt64(9) ) + MyInt64(5))
		 * (MyInt64(8) * MyInt64(2) * ( MyInt64(5) + MyInt64(3) * MyInt64(3) ) + MyInt64(4))
		 * ( ( MyInt64(8) + MyInt64(7) + ( MyInt64(2) + MyInt64(3) ) * ( MyInt64(7) + MyInt64(8) * MyInt64(3) * MyInt64(5) * MyInt64(2) + MyInt64(3) ) * MyInt64(4) * MyInt64(9) ) * MyInt64(4) * MyInt64(2) * ( MyInt64(5) * ( MyInt64(4) * MyInt64(4) + MyInt64(6) + MyInt64(6) * MyInt64(5) ) * MyInt64(8) + MyInt64(6) * ( MyInt64(8) + MyInt64(4) + MyInt64(9) + MyInt64(4) * MyInt64(4) + MyInt64(4) ) ) + MyInt64(4))
		 * ( ( MyInt64(9) * MyInt64(5) + MyInt64(3) ) * MyInt64(7) * MyInt64(9) * ( MyInt64(3) + ( MyInt64(7) * MyInt64(4) + MyInt64(2) * MyInt64(9) ) * MyInt64(4) + MyInt64(7) ) )
		 * (MyInt64(3) + MyInt64(7) + ( MyInt64(3) + ( MyInt64(2) + MyInt64(5) * MyInt64(3) ) + MyInt64(9) ) * MyInt64(9) * ( ( MyInt64(9) + MyInt64(3) + MyInt64(7) * MyInt64(9) * MyInt64(3) + MyInt64(6) ) + ( MyInt64(2) * MyInt64(3) * MyInt64(9) * MyInt64(8) * MyInt64(9) + MyInt64(5) ) + MyInt64(2) * MyInt64(5) ) )
		 * (MyInt64(5) * ( MyInt64(5) + MyInt64(9) * ( MyInt64(2) + MyInt64(3) * MyInt64(7) + MyInt64(3) + MyInt64(7) ) * MyInt64(8) * MyInt64(8) ) )
		 * (MyInt64(7) * ( MyInt64(4) * ( MyInt64(8) * MyInt64(3) + MyInt64(4) ) * MyInt64(3) * MyInt64(9) * MyInt64(8) ) + MyInt64(4) * MyInt64(2) * MyInt64(3) + ( ( MyInt64(2) * MyInt64(5) * MyInt64(4) + MyInt64(9) * MyInt64(9) ) * ( MyInt64(3) * MyInt64(3) + MyInt64(8) + MyInt64(7) ) ) )
		 * (MyInt64(3) + MyInt64(6) * MyInt64(2) + MyInt64(4) + ( ( MyInt64(4) + MyInt64(4) ) + MyInt64(3) + MyInt64(4) * MyInt64(3) ) * MyInt64(5))
		 * (MyInt64(8) * MyInt64(6) * MyInt64(7) * ( MyInt64(5) + MyInt64(9) + MyInt64(9) + MyInt64(4) * MyInt64(5) ) * ( MyInt64(4) * MyInt64(8) ) + ( MyInt64(9) + MyInt64(7) ) )
		 * (MyInt64(9) * MyInt64(3) + MyInt64(3) * ( MyInt64(2) * ( MyInt64(7) + MyInt64(5) + MyInt64(9) + MyInt64(2) + MyInt64(8) ) + MyInt64(3) + MyInt64(2) * MyInt64(8) * MyInt64(4) ) + MyInt64(7) + ( ( MyInt64(9) * MyInt64(4) + MyInt64(6) ) + MyInt64(7) ) )
		 * ( ( MyInt64(8) + MyInt64(9) * MyInt64(5) + ( MyInt64(4) * MyInt64(7) ) + MyInt64(4) ) * MyInt64(7) * MyInt64(9) + ( MyInt64(4) * MyInt64(5) * MyInt64(8) ) + MyInt64(4) + ( MyInt64(9) + ( MyInt64(8) + MyInt64(9) * MyInt64(3) + MyInt64(3) ) * MyInt64(8) + MyInt64(7) * MyInt64(3) ) )
		 * ( ( MyInt64(8) * ( MyInt64(2) * MyInt64(8) + MyInt64(3) + MyInt64(3) + MyInt64(3) * MyInt64(5) ) + MyInt64(7) * ( MyInt64(7) * MyInt64(6) + MyInt64(8) + MyInt64(9) + MyInt64(6) ) * MyInt64(5) ) * MyInt64(5) * MyInt64(8) * MyInt64(4) * ( MyInt64(4) + MyInt64(2) + MyInt64(2) * MyInt64(2) * MyInt64(2) + MyInt64(4) ) )
		 * ( ( MyInt64(6) + MyInt64(7) * ( MyInt64(2) + MyInt64(4) ) + MyInt64(9) ) * MyInt64(4) + ( MyInt64(7) * MyInt64(7) + MyInt64(6) ) + MyInt64(3))
		 * ( ( MyInt64(9) * MyInt64(6) ) + MyInt64(6) * MyInt64(3))
		 * (MyInt64(6) * MyInt64(2) + MyInt64(7) + ( MyInt64(9) * MyInt64(7) * MyInt64(6) ) + ( ( MyInt64(9) + MyInt64(4) * MyInt64(2) ) + MyInt64(7) + MyInt64(4) + MyInt64(7) + ( MyInt64(9) + MyInt64(5) + MyInt64(7) ) * MyInt64(2) ) )
		 * (MyInt64(4) * ( MyInt64(4) * MyInt64(8) + ( MyInt64(8) * MyInt64(9) * MyInt64(5) + MyInt64(7) + MyInt64(6) * MyInt64(8) ) + MyInt64(3) * MyInt64(8) + MyInt64(2) ) * ( ( MyInt64(4) + MyInt64(9) + MyInt64(8) + MyInt64(4) * MyInt64(2) ) * ( MyInt64(6) + MyInt64(2) * MyInt64(8) * MyInt64(3) + MyInt64(9) + MyInt64(5) ) * MyInt64(9) * MyInt64(4) ) )
		 * (MyInt64(6) + MyInt64(5) + ( MyInt64(2) + MyInt64(4) * MyInt64(3) + MyInt64(6) + ( MyInt64(5) * MyInt64(9) + MyInt64(4) ) + MyInt64(4) ) * MyInt64(4) * MyInt64(4) * MyInt64(8))
		 * ( ( ( MyInt64(5) + MyInt64(3) * MyInt64(2) * MyInt64(3) + MyInt64(9) ) * MyInt64(8) * MyInt64(4) + MyInt64(8) ) + ( ( MyInt64(9) * MyInt64(3) * MyInt64(7) * MyInt64(5) + MyInt64(4) + MyInt64(4) ) + MyInt64(5) + MyInt64(7) * MyInt64(9) ) * MyInt64(7) + ( MyInt64(3) * MyInt64(5) * MyInt64(4) * ( MyInt64(2) + MyInt64(5) ) ) + ( MyInt64(4) * MyInt64(6) + MyInt64(2) ) )
		 * (MyInt64(5) + MyInt64(4) * MyInt64(2) * ( MyInt64(5) + MyInt64(9) + MyInt64(8) + MyInt64(8) * MyInt64(2) * ( MyInt64(8) * MyInt64(9) + MyInt64(2) * MyInt64(7) * MyInt64(8) + MyInt64(3) ) ) )
		 * ( ( MyInt64(6) + MyInt64(5) * MyInt64(9) * ( MyInt64(9) + MyInt64(8) + MyInt64(9) + MyInt64(6) + MyInt64(4) ) * MyInt64(2) * ( MyInt64(5) + MyInt64(6) ) ) * ( MyInt64(4) * MyInt64(9) * MyInt64(6) ) * MyInt64(6) * MyInt64(9))
		 * (MyInt64(8) + MyInt64(6) * ( MyInt64(9) + MyInt64(8) ) )
		 * (MyInt64(6) + MyInt64(9) * MyInt64(6) + ( MyInt64(5) + MyInt64(7) * MyInt64(7) * MyInt64(4) ) * MyInt64(9) + MyInt64(9))
		 * (MyInt64(7) + MyInt64(3) + MyInt64(9) + MyInt64(8) + ( MyInt64(7) + MyInt64(2) * MyInt64(9) ) * ( MyInt64(4) * MyInt64(8) ) )
		 * ( ( ( MyInt64(7) * MyInt64(2) ) * MyInt64(5) ) * MyInt64(8) + MyInt64(6))
		 * (MyInt64(8) * ( MyInt64(9) + MyInt64(7) * MyInt64(5) ) * ( MyInt64(7) * MyInt64(9) ) * ( MyInt64(5) + MyInt64(3) ) + MyInt64(8))
		 * (MyInt64(8) + MyInt64(7) * MyInt64(6) * MyInt64(8) + MyInt64(7) + ( MyInt64(6) + ( MyInt64(9) + MyInt64(6) * MyInt64(8) * MyInt64(5) + MyInt64(7) ) + MyInt64(9) ) )
		 * ( ( MyInt64(3) + MyInt64(5) ) * MyInt64(3) + ( MyInt64(6) * ( MyInt64(2) + MyInt64(3) ) + MyInt64(5) + MyInt64(2) + MyInt64(3) * MyInt64(5) ) + MyInt64(7) * MyInt64(5) * MyInt64(4))
		 * ( ( MyInt64(9) + MyInt64(8) ) * ( MyInt64(6) * MyInt64(9) ) * MyInt64(4) * MyInt64(6))
		 * (MyInt64(7) + ( MyInt64(9) * MyInt64(9) * MyInt64(9) + MyInt64(5) ) * MyInt64(6) + ( ( MyInt64(3) * MyInt64(6) * MyInt64(6) ) * MyInt64(8) + MyInt64(9) + MyInt64(5) ) * MyInt64(3))
		 * (MyInt64(6) * MyInt64(7) + MyInt64(8) + ( ( MyInt64(5) * MyInt64(6) * MyInt64(2) + MyInt64(6) * MyInt64(9) ) * MyInt64(6) * MyInt64(2) * MyInt64(5) ) + MyInt64(9))
		 * ( ( MyInt64(5) + ( MyInt64(8) * MyInt64(9) * MyInt64(9) + MyInt64(3) ) + MyInt64(9) + MyInt64(3) ) * ( MyInt64(5) + MyInt64(8) * MyInt64(8) ) + MyInt64(3) + MyInt64(5) * MyInt64(7))
		 * (MyInt64(5) * ( MyInt64(8) * MyInt64(6) + MyInt64(2) ) + MyInt64(8) * ( MyInt64(8) * MyInt64(2) * MyInt64(9) * MyInt64(7) + MyInt64(2) * ( MyInt64(4) + MyInt64(4) + MyInt64(9) + MyInt64(9) * MyInt64(4) ) ) )
		 * (MyInt64(4) + ( MyInt64(9) * ( MyInt64(2) * MyInt64(4) * MyInt64(2) + MyInt64(8) + MyInt64(6) + MyInt64(2) ) * MyInt64(4) + MyInt64(3) ) )
		 * (MyInt64(6) * ( ( MyInt64(4) + MyInt64(2) ) + MyInt64(9) + ( MyInt64(5) * MyInt64(9) + MyInt64(2) * MyInt64(6) + MyInt64(3) + MyInt64(3) ) * MyInt64(2) * MyInt64(9) * ( MyInt64(4) + MyInt64(9) * MyInt64(8) * MyInt64(5) * MyInt64(6) + MyInt64(2) ) ) + ( MyInt64(7) + MyInt64(9) + MyInt64(7) + MyInt64(7) + MyInt64(2) * MyInt64(4) ) + MyInt64(8))
		 * (MyInt64(5) * ( MyInt64(6) * ( MyInt64(9) * MyInt64(9) ) + ( MyInt64(9) * MyInt64(4) + MyInt64(9) ) * MyInt64(6) ) * MyInt64(4))
		 * (MyInt64(9) * ( MyInt64(7) * ( MyInt64(9) + MyInt64(8) * MyInt64(9) * MyInt64(5) + MyInt64(4) ) + MyInt64(3) ) * MyInt64(8) * MyInt64(8))
		 * (MyInt64(9) + MyInt64(3) + MyInt64(4) + MyInt64(9) + MyInt64(3) * ( ( MyInt64(2) + MyInt64(4) ) + ( MyInt64(7) + MyInt64(3) ) * ( MyInt64(6) * MyInt64(7) + MyInt64(3) * MyInt64(4) + MyInt64(5) * MyInt64(2) ) * MyInt64(3) ) )
		 * ( ( MyInt64(4) * MyInt64(8) ) * MyInt64(5) + MyInt64(8) + ( MyInt64(6) * MyInt64(2) * MyInt64(9) + MyInt64(2) ) )
		 * (MyInt64(5) + MyInt64(2) + MyInt64(4) * ( MyInt64(6) + MyInt64(2) ) )
		 * ( ( MyInt64(6) * MyInt64(3) * MyInt64(7) ) + MyInt64(6) + MyInt64(9))
		 * (MyInt64(6) * ( MyInt64(8) * MyInt64(8) * MyInt64(8) ) + ( MyInt64(7) + MyInt64(6) + MyInt64(9) ) + MyInt64(9) + ( MyInt64(2) * MyInt64(6) * MyInt64(3) + MyInt64(4) + MyInt64(6) ) * MyInt64(4))
		 * ( ( MyInt64(6) + MyInt64(4) + MyInt64(7) * ( MyInt64(3) + MyInt64(4) ) + MyInt64(8) + MyInt64(8) ) + MyInt64(8) * MyInt64(8) + MyInt64(6) * MyInt64(8))
		 * (MyInt64(9) * MyInt64(6) + MyInt64(7) + MyInt64(8))
		 * ( ( MyInt64(5) + MyInt64(7) + ( MyInt64(7) * MyInt64(8) + MyInt64(9) * MyInt64(5) ) + MyInt64(6) ) * MyInt64(5))
		 * (MyInt64(7) + MyInt64(4) * ( ( MyInt64(6) * MyInt64(9) * MyInt64(6) * MyInt64(6) ) * MyInt64(6) * MyInt64(2) * MyInt64(5) * MyInt64(6) ) + MyInt64(4) + ( MyInt64(3) * ( MyInt64(2) * MyInt64(2) + MyInt64(9) + MyInt64(2) + MyInt64(5) ) + MyInt64(9) * MyInt64(4) * MyInt64(3) ) + ( MyInt64(7) + ( MyInt64(6) + MyInt64(3) ) * ( MyInt64(3) * MyInt64(6) + MyInt64(5) * MyInt64(8) ) ) )
		 * (MyInt64(6) * MyInt64(3) + MyInt64(5) * MyInt64(9) + ( MyInt64(5) * MyInt64(5) + MyInt64(5) + MyInt64(9) * ( MyInt64(8) + MyInt64(6) * MyInt64(8) ) + MyInt64(4) ) )
		 * (MyInt64(5) + MyInt64(5) * MyInt64(9) + MyInt64(9) + MyInt64(6) * ( MyInt64(9) * ( MyInt64(9) + MyInt64(2) + MyInt64(2) ) ) );


	uint64_t resB = myResB.m_i;
#endif


	writeSolution(resA, resB);
}


