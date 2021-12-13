use std::fs::File;
use std::io::{BufRead, BufReader};

struct Cave
{
	name: String,
	conn: Vec::<usize>,
	visited: u8
}

impl Cave
{
	pub fn new(name: String) -> Self
	{
		Self
		{
			name,
			conn: Vec::new(),
			visited: 0
        }
	}
	
	pub fn is_small(&self) -> bool
	{
		let firstChar = self.name.chars().nth(0).unwrap() as u8;
		if  firstChar >= b'a' && firstChar <= b'z'
		{
			return true;
		}
		return false;
	}
}


fn find_paths(i: usize, caves: &mut Vec::<Cave>, doubleVisit: bool) -> u32
{
	if caves[i].name == "end"
	{
		return 1;
	}
	
	caves[i].visited += 1;
	let conns = caves[i].conn.clone();
	let mut ret = 0;
	for j in conns
	{
		let smallCave = caves[j].is_small();
			
		if !doubleVisit && smallCave && caves[j].visited == 1 && caves[j].name != "start"
		{
			ret += find_paths(j, caves, true);
		}
		else if !smallCave || caves[j].visited == 0
		{
			ret += find_paths(j, caves, doubleVisit);
		}
	}
	caves[i].visited -= 1;
	return ret;
}


pub fn execute_day12(fcr_fileName: &String)
{
	// read graph from file
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);
	
	let mut startInd: usize = 0;
	let mut caves: Vec::<Cave> = Vec::<Cave>::new();
	for (_, line) in reader.lines().enumerate()
	{
		let resVec = line.unwrap()
			.trim()
			.split_whitespace()
			.map(|s| s.parse::<String>().unwrap())
			.collect::<Vec<String>>();
		
		let mut found1 = usize::MAX;
		let mut found2 = usize::MAX;
		for c in 0..caves.len()
		{
			if resVec[0] == caves[c].name
			{
				found1 = c;
			}
			if resVec[1] == caves[c].name
			{
				found2 = c;
			}
		}
		if found1 == usize::MAX
		{
			found1 = caves.len();
			caves.push(Cave::new(resVec[0].clone()));
			if resVec[0] == "start"
			{
				startInd = found1;
			}
		}
		if found2 == usize::MAX
		{
			found2 = caves.len();
			caves.push(Cave::new(resVec[1].clone()));
			if resVec[0] == "start"
			{
				startInd = found2;
			}
		}
		
		caves[found1].conn.push(found2);
		caves[found2].conn.push(found1);
    }

	// recursively find all paths from start to end that fulfill the requirements
	let cntA = find_paths(startInd, &mut caves, true);
	let cntB = find_paths(startInd, &mut caves, false);
	
	println!("part (a): {}", cntA);
	println!("part (b): {}", cntB);
}