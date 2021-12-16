use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::VecDeque;


fn findShortestPath<const L: usize, const LL: usize>(cave: &[u8; LL]) -> u32
{
	let mut pathLen: [u32; LL] = [20*L as u32; LL];
	let initVal = (20*LL) as u32;
	for i in 0..LL
	{
		pathLen[i] = initVal;
	}
	
	let mut q = VecDeque::<(usize, u32)>::new();
	q.push_back((0, 0));
	while !q.is_empty()
	{
		let (pos, risk) = q.pop_front().unwrap();
		
		if pathLen[pos] <= risk
		{
			continue;
		}
		pathLen[pos] = risk;
		if pos == LL-1
		{
			continue;
		}
		
		if pos >= L && pathLen[pos - L] > risk + cave[pos - L] as u32
		{
			q.push_back((pos - L, risk + cave[pos - L] as u32));
		}
		if pos < L*(L-1) && pathLen[pos + L] > risk + cave[pos + L] as u32
		{
			q.push_back((pos + L, risk + cave[pos + L] as u32));
		}
		if pos % L != 0 && pathLen[pos - 1] > risk + cave[pos - 1] as u32
		{
			q.push_back((pos - 1, risk + cave[pos - 1] as u32));
		}
		if pos % L != L-1 && pathLen[pos + 1] > risk + cave[pos + 1] as u32
		{
			q.push_back((pos + 1, risk + cave[pos + 1] as u32));
		}
	}
	
	return pathLen[LL-1];
}


pub fn execute_day15(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);

	let mut cave: [u8; 10000] = [0; 10000];
	for (index, line) in reader.lines().enumerate()
	{
		let res = line.unwrap();
		for cnt in 0..100
		{
			cave[100*index + cnt] = res.chars().nth(cnt).unwrap() as u8 - b'0';
		}
    }
	
	let resA = findShortestPath::<100, 10000>(&cave);

	
	let mut cave2: [u8; 250000] = [0; 250000];
	for i in 0..500
	{
		for j in 0..500
		{
			let mut val = cave[(i%100)*100 + (j%100)] + (i/100) as u8 + (j/100) as u8;
			val = val % 9;
			if val == 0
			{
				val = 9;
			}
			cave2[500*i + j] = val;
		}
	}
	
	let resB = findShortestPath::<500, 250000>(&cave2);
	
	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}