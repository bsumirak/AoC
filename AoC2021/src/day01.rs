use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn execute_day01(fcr_fileName: &String)
{
    let file = File::open(fcr_fileName).unwrap();
    let reader = BufReader::new(file);

	let mut vec = Vec::<u32>::new();

    for (index, line) in reader.lines().enumerate()
	{
		let line = line.unwrap(); // Ignore errors.
		match line.trim().parse()
		{
			Ok(num) => vec.push(num),
			Err(_) => {println!("Could not convert line {} to number.", index + 1); break;}
		};
    }

	let num = vec.len();
	let mut suma = 0;
	let mut sumb = 0;
	for ind in 1..num
	{
		if vec[ind] > vec[ind-1]
		{
			suma += 1;
		}
		if ind > 2 && vec[ind] > vec[ind-3]
		{
			sumb += 1;
		}
	}
	
	println!("part (a): {}", suma);
	println!("part (b): {}", sumb);
}
