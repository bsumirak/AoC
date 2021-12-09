use std::fs::File;
use std::io::{BufRead, BufReader};
use std::string::String;


fn convertToNumber(fcr_str: &String) -> u32
{
	let mut res = 0;
	if fcr_str.contains("a")
	{
		res += 1;
	}
	if fcr_str.contains("b")
	{
		res += 2;
	}
	if fcr_str.contains("c")
	{
		res += 4;
	}
	if fcr_str.contains("d")
	{
		res += 8;
	}
	if fcr_str.contains("e")
	{
		res += 16;
	}
	if fcr_str.contains("f")
	{
		res += 32;
	}
	if fcr_str.contains("g")
	{
		res += 64;
	}
	
	return res;
}


pub fn execute_day08(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);
	
	const INIT_VEC: Vec::<u32> = Vec::<u32>::new();
	let mut input: [Vec<u32>; 200] = [INIT_VEC; 200];
	let mut output: [Vec<u32>; 200] = [INIT_VEC; 200];
	
	//let mut boards: [Vec::<u32>; 100] = [INIT_BOARD; 100];
	for (index, line) in reader.lines().enumerate()
	{
		let resVec = line.unwrap()
			.trim()
			.split_whitespace()
			.map(|s| s.parse::<String>().unwrap())
			.collect::<Vec<String>>();
		
		for i in 0..10
		{
			input[index].push(convertToNumber(&resVec[i]));
		}
		for i in 10..14
		{
			output[index].push(convertToNumber(&resVec[i]));
		}
    }
	
	let mut resA = 0;
	let mut resB = 0;
	for l in 0..200
	{
		let mut cnt = [0; 7];
		for i in 0..10
		{
			for k in 0..7
			{
				if input[l][i] & (1 << k) != 0
				{
					cnt[k] += 1;
				}
			}
		}
		
		let mut map = [7; 7];
		let mut eInd = 7;
		let mut sevens = Vec::<usize>::new();
		let mut eights = Vec::<usize>::new();
		for i in 0..7
		{
			if cnt[i] == 9
			{
				map[i] = 5;
			}
			else if cnt[i] == 4
			{
				map[i] = 4;
				eInd = i;
			}
			else if cnt[i] == 6
			{
				map[i] = 1;
			}
			else if cnt[i] == 7
			{
				sevens.push(i);
			}
			else if cnt[i] == 8
			{
				eights.push(i);
			}
		}
		
		let mut cnt7 = 0;
		let mut cnt8 = 0;
		for i in 0..10
		{
			if input[l][i] & (1 << eInd) != 0
			{
				if input[l][i] & (1 << sevens[0]) != 0
				{
					cnt7 += 1;
				}
				if input[l][i] & (1 << eights[0]) != 0
				{
					cnt8 += 1;
				}
			}
		}
		
		map[sevens[0]] = if cnt7 == 4 {6} else {3};
		map[sevens[1]] = if cnt7 == 4 {3} else {6};
		
		map[eights[0]] = if cnt8 == 4 {0} else {2};
		map[eights[1]] = if cnt8 == 4 {2} else {0};
		
		let mut base = 1000;
		for i in 0..4
		{
			let mut res = 0;
			
			for k in 0..7
			{
				if output[l][i] & (1 << k) != 0
				{
					res += 1 << map[k];
				}
			}
			
			match res
			{
				119 => {},
				36 => {resB += base; resA += 1;},
				93 => resB += 2*base,
				109 => resB += 3*base,
				46 => {resB += 4*base; resA += 1;},
				107 => resB += 5*base,
				123 => resB += 6*base,
				37 => {resB += 7*base; resA += 1;},
				127 => {resB += 8*base; resA += 1;},
				111 => resB += 9*base,
				_other => println!("Error decoding!"),
			}
			
			base /= 10;	
		}
	}

	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}