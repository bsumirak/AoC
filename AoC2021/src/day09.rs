use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::VecDeque;

pub fn execute_day09(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);

	let mut cave: [u32; 10000] = [0; 10000];
	for (index, line) in reader.lines().enumerate()
	{
		let line = line.unwrap(); // Ignore errors.
		
		for i in 0..100
		{
			let c = line.chars().nth(i).unwrap().to_digit(10).unwrap();
			cave[100*index + i] = c;
		}
    }

	let mut maxRisk = 0;
	let mut basinSizes: [u32; 3] = [0; 3];
	let mut visited: [bool; 10000] = [false; 10000]; 
	
	for i in 0..10000
	{
		if i / 100 > 0 && cave[i] >= cave[i - 100]
		{
			continue;	
		}
		if i / 100 < 99 && cave[i] >= cave[i+100]
		{
			continue;	
		}
		if i % 100 > 0 && cave[i] >= cave[i-1]
		{
			continue;	
		}
		if i % 100 < 99 && cave[i] >= cave[i+1]
		{
			continue;	
		}
		maxRisk += cave[i] + 1;
		
		// find entire basin
		let mut sz = 0;
		let mut q = VecDeque::<usize>::new();
		q.push_back(i);
		while !q.is_empty()
		{
			let x = q.pop_front().unwrap();
			
			if visited[x] || cave[x] == 9
			{
				continue;
			}
			
			visited[x] = true;
			sz += 1;
			
			if x / 100 > 0 && cave[x] <= cave[x - 100]
			{
				q.push_back(x - 100);
			}
			if x / 100 < 99 && cave[x] <= cave[x + 100]
			{
				q.push_back(x + 100);
			}
			if x % 100 > 0 && cave[x] <= cave[x - 1]
			{
				q.push_back(x - 1);
			}
			if x % 100 < 99 && cave[x] <= cave[x + 1]
			{
				q.push_back(x + 1);
			}
		}
		if sz > basinSizes[0]
		{
			basinSizes[2] = basinSizes[1];
			basinSizes[1] = basinSizes[0];
			basinSizes[0] = sz;
		}
		else if sz > basinSizes[1]
		{
			basinSizes[2] = basinSizes[1];
			basinSizes[1] = sz;
		}
		else if sz > basinSizes[2]
		{
			basinSizes[2] = sz;
		}
	}
	
	println!("part (a): {}", maxRisk);
	println!("part (b): {}", basinSizes[0] * basinSizes[1] * basinSizes[2]);
}