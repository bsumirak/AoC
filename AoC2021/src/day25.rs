use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn execute_day25(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);

	let mut ground = [0u8; 137*139];
	for (ind, line) in reader.lines().enumerate()
	{
		let line = line.unwrap();
		
		let mut cnt = 0;
		for c in line.chars()
		{
			ground[139*ind + cnt] = if c == '>' {1} else if c == 'v' {2} else {0};
			cnt += 1;
		}
    }
	
	let mut resA = 1;
	let mut nextGround = ground;
	loop
	{
		let mut someoneMoved = false;
		for i in 0..137*139
		{
			if ground[i] != 1
			{
				continue;
			}
			let next = if (i+1) % 139 == 0 {i-138} else {i+1};
			if ground[next] != 0
			{
				continue;
			}
			someoneMoved = true;
			nextGround[i] = 0;
			nextGround[next] = 1;
		}
		ground = nextGround;
		
		for i in 0..137*139
		{
			if ground[i] != 2
			{
				continue;
			}
			let next = if i+139 >= 137*139 {i-136*139} else {i+139};
			if ground[next] != 0
			{
				continue;
			}
			someoneMoved = true;
			nextGround[i] = 0;
			nextGround[next] = 2;
		}
		
		if !someoneMoved
		{
			break;
		}
		else
		{
			ground = nextGround;
			resA += 1;
		}
	}
	
	
	println!("part (a): {}", resA);
	println!("part (b): {}", 0);
}