use std::fs::File;
use std::io::{BufRead, BufReader};


pub fn execute_day02(fcr_fileName: &String)
{
    let file = File::open(fcr_fileName).unwrap();
    let reader = BufReader::new(file);

	let mut x = 0;
	let mut z = 0;
	let mut aim = 0;
	let mut x2 = 0;
	let mut z2 = 0;
    for (index, line) in reader.lines().enumerate()
	{
		let line = line.unwrap(); // Ignore errors.
		match line.chars().nth(0).unwrap()
		{
			'f' => 
			{
				match line[8..9].parse::<i32>()
				{
					Ok(num) => {x += num; x2 += num; z2 += aim * num;},
					Err(_) => {println!("Could not convert line {} number.", index + 1); break;}
				}
			},
			'u' =>
			{
				match line[3..4].parse::<i32>()
				{
					Ok(num) => {z -= num; aim -= num;},
					Err(_) => {println!("Could not convert line {} number.", index + 1); break;}
				}
			},
			'd' =>
			{
				match line[5..6].parse::<i32>()
				{
					Ok(num) => {z += num; aim += num;},
					Err(_) => {println!("Could not convert line {} number.", index + 1); break;}
				}
			},
			_other => println!("unknown command {}", line)
		};
    }
	
	println!("part (a): {}", x*z);
	println!("part (b): {}", x2*z2);
}