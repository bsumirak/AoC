#![allow(non_snake_case)]

use std::env;

mod day01;
mod day02;
mod day03;
mod day04;
mod day05;
mod day06;
mod day07;


fn main()
{
	let args: Vec<String> = env::args().collect();
	
	// which day
	let mut day = 1;
	if args.len() >= 2
	{
		match args[1].parse()
		{
			Ok(num) => day = num,
			Err(_) => {println!("Could not convert day argument \"{}\" to number.", &args[1]);}
		};
	}
	
	// non-standard input file postfix (useful for debugging)
	let mut fileNameAdd = String::new();
	if args.len() >= 3
	{
		fileNameAdd = args[2].clone();
	}
	
	// construct input file name
	let inputFileName = format!("input/input{:02}{}.dat", day, fileNameAdd);

	// execute day's work
	match day
	{
		1 => day01::execute_day01(&inputFileName),
		2 => day02::execute_day02(&inputFileName),
		3 => day03::execute_day03(&inputFileName),
		4 => day04::execute_day04(&inputFileName),
		5 => day05::execute_day05(&inputFileName),
		6 => day06::execute_day06(&inputFileName),
		7 => day07::execute_day07(&inputFileName),
		_other => println!("Specified day ({}) is invalid.", day),
	};
}