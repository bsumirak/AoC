use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn execute_day20(fcr_fileName: &String)
{
	// read the input
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);

	let algoStr = "#.#.##..#..#..###.#.#....#.########.#.##.#..#.###..###.##.#.##.#.#.....#..##.#.#..###.###.######..#.#..#######.#..#....####..###.####.###.#.#######.#...#...#.##.###..###..##.#.#.###........##.#.....#.##.#.####...#...#.#..###.#.#...#....#...####..#.########.#...#.####.#####..#.#.###......#.##...###..##..#.#..#....#..###.#.##.....##.#####..##.####.#.###....##.###...#.##....##.#..#.#..#..#.##...#.##..#####.####.#.##...##...##...#.##.#.#.####..##...#.....#......#.#......#..###..#..##..##.###..#####..#..##.#..#.";
	let mut algo = [false; 512];
	
	let mut i = 0;
	for c in algoStr.chars()
	{
		algo[i] = c == '#';
		i += 1;
	}
		
	const EXTRA_SZ: usize = 51;
	const SZ: usize = 100 + 2 * EXTRA_SZ;
	
	let mut img = [false; SZ*SZ];
	for (i, line) in reader.lines().enumerate()
	{
		let line = line.unwrap();
		for j in 0..100
		{
			let c = line.chars().nth(j).unwrap();
			img[SZ * (i + EXTRA_SZ) + j + EXTRA_SZ] = c == '#';
		}
    }
	
	// iterate image enhancement
	let mut resA = 0;
	let mut resB = 0;
	
	let mut img2 = [true; SZ*SZ];
	
	const MAX_IT: usize = 50;
	for it in 0..MAX_IT
	{
		let (prev,next) = if it % 2 == 0 {(&img, &mut img2)} else {(&img2, &mut img)};
		
		for i in MAX_IT - it .. SZ - MAX_IT + it
		{
			for j in MAX_IT - it .. SZ - MAX_IT + it
			{
				let mut ind = 0;
				ind += (prev[SZ*(i-1) + j-1] as usize) << 8;
				ind += (prev[SZ*(i-1) + j] as usize) << 7;
				ind += (prev[SZ*(i-1) + j+1] as usize) << 6;
				
				ind += (prev[SZ*(i) + j-1] as usize) << 5;
				ind += (prev[SZ*(i) + j] as usize) << 4;
				ind += (prev[SZ*(i) + j+1] as usize) << 3;
				
				ind += (prev[SZ*(i+1) + j-1] as usize) << 2;
				ind += (prev[SZ*(i+1) + j] as usize) << 1;
				ind += (prev[SZ*(i+1) + j+1] as usize) << 0;
				
				next[SZ*i + j] = algo[ind];
				
				if next[SZ*i + j]
				{
					if it == 1
					{
						resA += 1;
					}
					else if it == 49
					{
						resB += 1;
					}
				}
			}
		}
	}
	
	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}