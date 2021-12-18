use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::LinkedList;


struct Digit
{
//	name: String,
	isLeaf: bool,
	val: [usize; 2],
}

impl Digit
{
	pub fn new() -> Self
	{
		Self
		{
			isLeaf: true,
			val: [usize::MAX, 2]
        }
	}
}

/*
fn printNumber(i: usize, digits: &Vec::<Digit>)
{
	let mut stack = LinkedList::new();
	stack.push_back([i, 0]);
	while !stack.is_empty()
	{
		let s = stack.back_mut().unwrap();
		
		if s[1] == 0
		{
			if digits[s[0]].isLeaf
			{
				print!("{}", digits[s[0]].val[0]);
				stack.pop_back();
				continue;
			}
			else
			{
				print!("[");
				s[1] = 1;
				let nextInd = digits[s[0]].val[0];
				stack.push_back([nextInd, 0]);
			}
		}
		else if s[1] == 1
		{
			print!(",");
			s[1] = 2;
			let nextInd = digits[s[0]].val[1];
			stack.push_back([nextInd, 0]);
			continue;
		}
		else if s[1] == 2
		{
			print!("]");
			stack.pop_back();
			continue;
		}
	}
	println!("");
}
*/

/*
fn printNumberAsTree(i: usize, digits: &Vec::<Digit>)
{
	let mut stack = LinkedList::new();
	stack.push_back([i, 0]);
	while !stack.is_empty()
	{
		let len = stack.len();
		let s = stack.back_mut().unwrap();
		
		if s[1] == 0
		{
			if digits[s[0]].isLeaf
			{
				for _ in 2..len
				{
					print!("   ");
				}
				println!("|_ {}", digits[s[0]].val[0]);
				stack.pop_back();
				continue;
			}
			else
			{
				for _ in 2..len
				{
					print!("   ");
				}
				if len > 1
				{
					println!("|_ o");
				}
				else
				{
					println!("o");
				}
				s[1] = 1;
				let nextInd = digits[s[0]].val[0];
				stack.push_back([nextInd, 0]);
			}
		}
		else if s[1] == 1
		{
			s[1] = 2;
			let nextInd = digits[s[0]].val[1];
			stack.push_back([nextInd, 0]);
			continue;
		}
		else if s[1] == 2
		{
			stack.pop_back();
			continue;
		}
	}
}
*/


fn reduce(i: usize, digits: &mut Vec::<Digit>)
{
	loop
	{
		//printNumber(i, &digits);
	
		// check for explosion
		let mut prevLeaf = usize::MAX;
		let mut explodingPair = usize::MAX;
		let mut nextLeaf = usize::MAX;
		
		let mut stack = LinkedList::new();
		stack.push_back([i, 0]);
		while !stack.is_empty()
		{
			//print!("stack: ");
			//for pair in &stack
			//{
			//	print!("{} ", pair[1]);
			//}
			//println!("");
			
			let sz = stack.len();
			let s = stack.back_mut().unwrap();
			if sz == 5 && explodingPair == usize::MAX
			{
				if !digits[digits[s[0]].val[0]].isLeaf {println!("unexpected!");}
				if !digits[digits[s[0]].val[1]].isLeaf {println!("unexpected!");}
				explodingPair = s[0];
				stack.pop_back();
				continue;
			}
			
			if s[1] == 2
			{
				stack.pop_back();
				continue;
			}
			
			let d = &mut digits[s[0]];
			let next = d.val[s[1]];
			s[1] += 1;
			if digits[next].isLeaf
			{
				if explodingPair == usize::MAX
				{
					prevLeaf = next;
				}
				else
				{
					nextLeaf = next;
					break;
				}
			}
			else
			{
				stack.push_back([next, 0]);
			}
		}
		
		// explode
		if explodingPair != usize::MAX
		{
			//println!("explode [{},{}]!",
			//	digits[digits[explodingPair].val[0]].val[0],
			//	digits[digits[explodingPair].val[1]].val[0]);
			if prevLeaf != usize::MAX
			{
				digits[prevLeaf].val[0] += digits[digits[explodingPair].val[0]].val[0];
			}
			if nextLeaf != usize::MAX
			{
				digits[nextLeaf].val[0] += digits[digits[explodingPair].val[1]].val[0];
			}
			digits[explodingPair].isLeaf = true;
			digits[explodingPair].val[0] = 0;
			digits[explodingPair].val[1] = usize::MAX;

			continue;
		}
		
		// check for split
		let mut splitLeaf = usize::MAX;
		stack.clear();
		stack.push_back([i, 0]);
		while !stack.is_empty()
		{
			let s = stack.back_mut().unwrap();
			if s[1] >= 2
			{
				stack.pop_back();
				continue;
			}
			
			let d = &mut digits[s[0]];
			if d.isLeaf
			{
				if d.val[0] >= 10
				{
					splitLeaf = s[0];
					break;
				}
				else
				{
					stack.pop_back();
				}
			}
			else
			{
				let next = d.val[s[1]];
				s[1] += 1;
				stack.push_back([next, 0]);
			}
		}

		// split
		if splitLeaf != usize::MAX
		{
			//println!("split {}!", digits[splitLeaf].val[0]);

			let new1 = digits.len();
			digits.push(Digit::new());
			digits[new1].isLeaf = true;
			digits[new1].val[0] = digits[splitLeaf].val[0] / 2;
			
			let new2 = digits.len();
			digits.push(Digit::new());
			digits[new2].isLeaf = true;
			digits[new2].val[0] = digits[splitLeaf].val[0] - digits[new1].val[0];
			
			digits[splitLeaf].isLeaf = false;
			digits[splitLeaf].val[0] = new1;
			digits[splitLeaf].val[1] = new2;
			
			continue;
		}		
		
		break;		
	}
}


fn compute_magnitude(i: usize, digits: &Vec::<Digit>) -> usize
{
	let mut ret = 0;
	let mut stack = LinkedList::new();
	stack.push_back([i, 0, 0]);
	while !stack.is_empty()
	{
		let s = stack.back_mut().unwrap();
		
		if s[1] == 0
		{
			if digits[s[0]].isLeaf
			{
				ret = digits[s[0]].val[0];
				stack.pop_back();
				continue;
			}
			else
			{
				s[1] = 1;
				let nextInd = digits[s[0]].val[0];
				stack.push_back([nextInd, 0, 0]);
			}
		}
		else if s[1] == 1
		{
			s[1] = 2;
			s[2] = 3 * ret;
			let nextInd = digits[s[0]].val[1];
			stack.push_back([nextInd, 0, 0]);
			continue;
		}
		else if s[1] == 2
		{
			ret = s[2] + 2 * ret;
			stack.pop_back();
			continue;
		}
	}
	
	return ret;
}


fn read_input(fileName: &String, digits: &mut Vec::<Digit>, numbers: &mut Vec::<usize>)
{
	let file = File::open(fileName).unwrap();
	let reader = BufReader::new(file);
	for (_, line) in reader.lines().enumerate()
	{
		let line = line.unwrap();
		
		numbers.push(digits.len());
		
		let mut stack = LinkedList::<usize>::new();
		
		for c in line.chars()
		{
			if c == '['
			{
				let curr = digits.len();
				digits.push(Digit::new());
				digits[curr].isLeaf = false;
				
				if !stack.is_empty()
				{
					let mut d = &mut digits[*stack.back().unwrap()];
					if d.val[0] == usize::MAX
					{
						d.val[0] = curr;
					}
					else
					{
						d.val[1] = curr;
					}
				}
				stack.push_back(curr);				
			}
			else if c == ']'
			{
				stack.pop_back();
			}
			else if c == ','
			{
				// ignore
			}
			else
			{
				let curr = digits.len();
				digits.push(Digit::new());
				digits[curr].isLeaf = true;
				digits[curr].val[0] = c.to_digit(10).unwrap() as usize;
				
				let mut d = &mut digits[*stack.back().unwrap()];
				if d.val[0] == usize::MAX
				{
					d.val[0] = curr;
				}
				else
				{
					d.val[1] = curr;
				}
			}
		}
    }
}


pub fn execute_day18(fcr_fileName: &String)
{
	// PART (A) //
	// read the input
	let mut digits = Vec::<Digit>::new();
	let mut numbers = Vec::<usize>::new();
	read_input(&fcr_fileName, &mut digits, &mut numbers);

	// add up all numbers
	let mut latestSum = numbers[0];
	for i in 1..numbers.len()
	{
		let n = digits.len();
		digits.push(Digit::new());
		let mut d = &mut digits[n];
		d.isLeaf = false;
		d.val[0] = latestSum;
		d.val[1] = numbers[i];
		
		latestSum = n;
			
		reduce(n, &mut digits);
	}
	
	// compute magnitude
	let resA = compute_magnitude(latestSum, &digits);
	
	
	// PART (B) //
	let mut maxMag = 0;
	for i in 0..numbers.len()
	{
		for j in 0..numbers.len()
		{
			// re-read the input
			digits.clear();
			numbers.clear();
			read_input(&fcr_fileName, &mut digits, &mut numbers);
			
			let n = digits.len();
			digits.push(Digit::new());
			let mut d = &mut digits[n];
			d.isLeaf = false;
			d.val[0] = numbers[i];
			d.val[1] = numbers[j];
				
			reduce(n, &mut digits);
			let mag = compute_magnitude(n, &digits);
			if mag > maxMag
			{
				maxMag = mag;
			}
		}
	}	
	
	
	println!("part (a): {}", resA);
	println!("part (b): {}", maxMag);
}