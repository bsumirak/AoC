use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::LinkedList;


pub fn execute_day10(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);
	
	let mut resA = 0;
	let mut resBVec = Vec::<u64>::new();
	for (_, line) in reader.lines().enumerate()
	{
		let mut stack = LinkedList::<u8>::new();
		let line = line.unwrap();
		let mut corrupt = false;
		for i in 0..line.chars().count()
		{
			let c: u8 = line.chars().nth(i).unwrap() as u8;
			
			if c == b')'
			{
				if *stack.back().unwrap() != b'('
				{
					resA += 3;
					corrupt = true;
					break;
				}
				stack.pop_back();
			}
			else if c == b']'
			{
				if *stack.back().unwrap() != b'['
				{
					resA += 57;
					corrupt = true;
					break;
				}
				stack.pop_back();
			}
			else if c == b'}'
			{
				if *stack.back().unwrap() != b'{'
				{
					resA += 1197;
					corrupt = true;
					break;
				}
				stack.pop_back();
			}
			else if c == b'>'
			{
				if *stack.back().unwrap() != b'<'
				{
					resA += 25137;
					corrupt = true;
					break;
				}
				stack.pop_back();
			}
			else
			{
				stack.push_back(c);
			}
		}
		
		if !corrupt
		{
			let mut res = 0 as u64;
			while !stack.is_empty()
			{	
				match *stack.back().unwrap()
				{
					b'(' => res = 5 * res + 1,
					b'[' => res = 5 * res + 2,
					b'{' => res = 5 * res + 3,
					b'<' => res = 5 * res + 4,
					other => println!("unexpected char: {}", other),
				}
				stack.pop_back();
			}
			resBVec.push(res);
		}
    }
		
	resBVec.sort();
	let resB = resBVec[resBVec.len()/2];
	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}