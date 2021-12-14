use std::fs::File;
use std::io::{BufRead, BufReader};


fn computeSolution(pairCnts: &[u64; 26*26], poly: &str) -> u64
{
	let mut minCnt = u64::MAX;
	let mut maxCnt = 0u64;
	for i in 0..26
	{
		let mut cnt = 0u64;
		for j in 0..26
		{
			cnt += pairCnts[26*i + j];
			cnt += pairCnts[26*j + i];
		}
		
		// correct for borders
		if poly.chars().nth(0).unwrap() as u8 - b'A' == i as u8
		{
			cnt += 1;
		}
		let num = poly.chars().count();
		if poly.chars().nth(num-1).unwrap() as u8 - b'A' == i as u8
		{
			cnt += 1;
		}
		cnt /= 2;
		
		if cnt > 0
		{
			if cnt < minCnt
			{
				minCnt = cnt;
			}
			if cnt > maxCnt
			{
				maxCnt = cnt;
			}
		}
	}
	
	return maxCnt - minCnt;
}


pub fn execute_day14(fcr_fileName: &String)
{
	let poly = "CVKKFSSNNHNPSPPKBHPB";

	// read rules from file
	let mut rules = [26 as u8; 26*26];
	
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);
	for (_, line) in reader.lines().enumerate()
	{
		let line = line.unwrap();
		let c1 = line.chars().nth(0).unwrap() as u8 - b'A';
		let c2 = line.chars().nth(1).unwrap() as u8 - b'A';
		let c3 = line.chars().nth(2).unwrap() as u8 - b'A';
		
		rules[26*c1 as usize + c2 as usize] = c3;	
	}
	
	let mut pairCnts = [0 as u64; 26*26];
	let num = poly.chars().count();
	for i in 0..num-1
	{
		let c1 = poly.chars().nth(i).unwrap() as u8 - b'A';
		let c2 = poly.chars().nth(i+1).unwrap() as u8 - b'A';
		pairCnts[26*c1 as usize + c2 as usize] += 1;
	}
	
	let mut solA = 0;
	for iter in 0..40
	{
		let mut newPairCnts = [0; 26*26];
		for i in 0..26*26
		{
			if rules[i] != 26
			{
				newPairCnts[i - i%26 + rules[i] as usize] += pairCnts[i];
				newPairCnts[rules[i] as usize * 26 + i%26] += pairCnts[i];
			}
			else
			{
				newPairCnts[i] += pairCnts[i];
			}
		}
		pairCnts = newPairCnts;
		
		if iter == 9
		{
			solA = computeSolution(&pairCnts, poly);
		}
	}
	let solB = computeSolution(&pairCnts, poly);
	
	
	println!("part (a): {}", solA);
	println!("part (b): {}", solB);
}

