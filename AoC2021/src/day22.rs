use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::BTreeSet;

pub fn execute_day22(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);
	
	let mut cubesA = [false; 1000000];
	
	let mut setX = BTreeSet::<i32>::new();
	let mut setY = BTreeSet::<i32>::new();
	let mut setZ = BTreeSet::<i32>::new();

	let mut switches = Vec::<(bool, [i32; 6])>::new();
	for (ind, line) in reader.lines().enumerate()
	{
		let resVec = line.unwrap()
			.trim()
			.split_whitespace()
			.map(|s| s.parse::<i32>().unwrap())
			.collect::<Vec<i32>>();
		
		let on = resVec[0] == 1;
		switches.push((on, [resVec[1], resVec[2]+1, resVec[3], resVec[4]+1, resVec[5], resVec[6]+1]));
		
		setX.insert(resVec[1]);
		setX.insert(resVec[2]+1);
		setY.insert(resVec[3]);
		setY.insert(resVec[4]+1);
		setZ.insert(resVec[5]);
		setZ.insert(resVec[6]+1);
		
		if ind < 20
		{
			for x in resVec[1]..resVec[2]+1
			{
				for y in resVec[3]..resVec[4]+1
				{
					for z in resVec[5]..resVec[6]+1
					{
						let ind = 10000*(50 + x) as usize + 100*(50 + y) as usize + 50 + z as usize;
						cubesA[ind] = on;
					}
				}
			}
		}
    }

	// part a
	let mut resA = 0;
	for c in &cubesA
	{
		if *c
		{
			resA += 1;
		}
	}
		

	// part b		
	let sx = setX.len();
	let sy = setY.len();
	let sz = setZ.len();
	
	let mut xVals = vec![0; sx];
	let mut yVals = vec![0; sy];
	let mut zVals = vec![0; sz];
	
	let mut i = 0;
	for x in &setX
	{
		xVals[i] = *x;
		i += 1;
	}
	i = 0;
	for y in &setY
	{
		yVals[i] = *y;
		i += 1;
	}
	i = 0;
	for z in &setZ
	{
		zVals[i] = *z;
		i += 1;
	}
	
	
	let mut cubes = vec![false; sx*sy*sz];
	
	for c in &switches
	{
		let x1 = xVals.iter().position(|&r| r == c.1[0]).unwrap();
		let x2 = xVals.iter().position(|&r| r == c.1[1]).unwrap();
		let y1 = yVals.iter().position(|&r| r == c.1[2]).unwrap();
		let y2 = yVals.iter().position(|&r| r == c.1[3]).unwrap();
		let z1 = zVals.iter().position(|&r| r == c.1[4]).unwrap();
		let z2 = zVals.iter().position(|&r| r == c.1[5]).unwrap();
		
		for x in x1..x2
		{
			for y in y1..y2
			{
				for z in z1..z2
				{
					cubes[sy*sz*x + sz*y + z] = if c.0 {true} else {false};
				}
			}
		}
	}
		
	let mut resB = 0u64;
	for i in 0..sx-1
	{
		let dx = xVals[i+1] - xVals[i];
		for j in 0..sy-1
		{
			let dy = yVals[j+1] - yVals[j];
			for k in 0..sz-1
			{
				let dz = zVals[k+1] - zVals[k];
				if cubes[sy*sz*i + sz*j+ k]
				{
					resB += dx as u64 * dy as u64 * dz as u64;
				}
			}
		}	
	}
	
	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}