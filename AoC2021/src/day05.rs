use std::fs::File;
use std::io::{BufRead, BufReader};


fn markDangerZones(fcr_fileName: &String, withDiags: bool) -> u32
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);

	let mut ocean: [u32; 1000000] = [0; 1000000];
	
	let mut dangerZones = 0;
	for (_, line) in reader.lines().enumerate()
	{
		let resVec = line.unwrap()
			.trim()
			.split_whitespace()
			.map(|s| s.parse::<usize>().unwrap())
			.collect::<Vec<usize>>();
		
		if resVec.len() != 4
		{
			println!("Read error.");
			return 0;
		}
		
		if resVec[0] != resVec[2]
			&& resVec[1] != resVec[3]
			&& ((resVec[0] as i32 - resVec[2] as i32).abs() != (resVec[1] as i32 - resVec[3] as i32).abs() || !withDiags)
		{
			continue;
		}
		
		let nx = resVec[2] as i32 - resVec[0] as i32;
		let ny = resVec[3] as i32 - resVec[1] as i32;
		let n = {if nx.abs() > ny.abs() {nx.abs()} else {ny.abs()}};
		
		for i in 0..n+1
		{
			let x = {if nx > 0 {resVec[0]+i as usize} else if nx < 0 {resVec[0]-i as usize} else {resVec[0]}};
			let y = {if ny > 0 {resVec[1]+i as usize} else if ny < 0 {resVec[1]-i as usize} else {resVec[1]}};
    
			ocean[1000*x + y] += 1;
			if ocean[1000*x + y] == 2
			{
				dangerZones += 1;
			}
		}
	}
	
	return dangerZones;	
}

pub fn execute_day05(fcr_fileName: &String)
{
	let dangerZones = markDangerZones(&fcr_fileName, false);
	let diagDangerZones = markDangerZones(&fcr_fileName, true);
	
	println!("part (a): {}", dangerZones);
	println!("part (b): {}", diagDangerZones);
}