use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn execute_day04(fcr_fileName: &String)
{
    let file = File::open(fcr_fileName).unwrap();
    let reader = BufReader::new(file);

	let draws = [49,48,98,84,71,59,37,36,6,21,46,30,5,33,3,62,63,45,43,35,65,77,57,75,19,44,4,76,88,92,12,27,7,51,14,72,96,9,0,17,83,64,38,95,54,20,1,74,69,80,81,56,10,68,42,15,99,53,93,94,47,13,29,34,60,41,82,90,25,85,78,91,32,70,58,28,61,24,55,87,39,11,79,50,22,8,89,26,16,2,73,23,18,66,52,31,86,97,67,40];

	const INIT_BOARD: Vec::<u32> = Vec::<u32>::new();
	let mut boards: [Vec::<u32>; 100] = [INIT_BOARD; 100];
	for (index, line) in reader.lines().enumerate()
	{
		let resVec = line.unwrap()
			.trim()
			.split_whitespace()
			.map(|s| s.parse::<u32>().unwrap())
			.collect::<Vec<u32>>();
		
		let v : usize = index / 6;
		for item in &resVec
		{
			boards[v].push(*item);
		}
    }
	
	/*
	for board in &boards
	{
		for i in 0..5
		{
			println!("{} {} {} {} {}", board[5*i], board[5*i+1], board[5*i+2], board[5*i+3], board[5*i+4]);					
		}
		println!("");
	}
	*/
	let mut winCnt = 0;
	let mut winnerBoards = [false; 100];
	let mut firstWinningValue = 0;
	let mut lastWinningValue = 0;
	for draw in draws
	{
		for b in 0..100
		{
			if winnerBoards[b]
			{
				continue;
			}
			
			let mut hit = usize::MAX;
			for entry in 0..25
			{
				if boards[b][entry] == draw
				{
					boards[b][entry] = 100;
					hit = entry;
					break;
				}
			}
			
			if hit == usize::MAX
			{
				continue;
			}
			
			// check for win
			let mut win = true;
			let hitRow = hit/5;
			for i in 0..5
			{
				if boards[b][5*hitRow + i] != 100
				{
					win = false;	
					break;
				}
			}
			
			if !win
			{
				win = true;
				let hitCol = hit%5;
				for i in 0..5
				{
					if boards[b][5*i + hitCol] != 100
					{
						win = false;	
						break;
					}
				}
			}
			
			if !win
			{
				continue;
			}
			
			winnerBoards[b] = true;
			winCnt += 1;
			
			// find first winner
			if winCnt == 1
			{
				for e in 0..25
				{
					if boards[b][e] != 100
					{
						firstWinningValue += boards[b][e];
					}
				}
				firstWinningValue *= draw;
			}
			
			// find last winner
			if winCnt == 100
			{
				for e in 0..25
				{
					if boards[b][e] != 100
					{
						lastWinningValue += boards[b][e];
					}
				}
				lastWinningValue *= draw;
				break;
			}
		}
		
		if winCnt == 100
		{
			break;
		}
	}
	
	println!("part (a): {}", firstWinningValue);
	println!("part (b): {}", lastWinningValue);
}