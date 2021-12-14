use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn execute_day13(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);
	
	let folding = [[0, 655], [1, 447], [0, 327], [1, 223], [0, 163], [1, 111],
		[0, 81], [1, 55], [0, 40], [1, 27], [1, 13], [1, 6]];
	
	let mut coords = Vec::new();
	for (_, line) in reader.lines().enumerate()
	{
		let resVec = line.unwrap()
			.trim()
			.split_whitespace()
			.map(|s| s.parse::<u32>().unwrap())
			.collect::<Vec<u32>>();
		
		coords.push([resVec[0], resVec[1]]);
    }
	
	let mut resA = 0;
	for f in &folding
	{
		for c in &mut coords
		{
			if c[f[0]] > f[1] as u32
			{
				c[f[0]] = 2*f[1] as u32 - c[f[0]];
			}
		}
	
		coords.sort();
		coords.dedup();
		
		if resA == 0
		{
			resA = coords.len();
		}
	}
	
	let mut resB = [[' '; 40]; 6];
	for c in &coords
	{
		resB[c[1] as usize][c[0] as usize] = '#';
	}
	
	
	println!("part (a): {}", resA);
	println!("part (b):");
	for i in 0..6
	{
		let s: String = resB[i].into_iter().collect();
		println!("{}", s);
	}
}