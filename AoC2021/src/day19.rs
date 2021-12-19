use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::BTreeSet;


fn checkTransformedPair(s1: &Vec::<[i32; 3]>, s2: &Vec::<[i32; 3]>, transl: &mut [i32]) -> bool
{
	let l1 = s1.len();
	let l2 = s2.len();
	
	for i1 in 0..l1
	{
		let ref1 = s1[i1];
		let mut d1 = BTreeSet::<[i32; 3]>::new();
		for j1 in 0..l1
		{
			d1.insert([s1[j1][0] - ref1[0], s1[j1][1] - ref1[1], s1[j1][2] - ref1[2]]);
		}
		
		for i2 in 0..l2
		{
			let ref2 = s2[i2];
			
			let mut cnt = 0;
			for j2 in 0..l2
			{
				let d2 = [s2[j2][0] - ref2[0], s2[j2][1] - ref2[1], s2[j2][2] - ref2[2]];
				if d1.contains(&d2)
				{
					cnt += 1;
				}
			}
				
			if cnt >= 11
			{
				transl[0] = ref1[0] - ref2[0];
				transl[1] = ref1[1] - ref2[1];
				transl[2] = ref1[2] - ref2[2];
				return true;
			}
		}
	}
		
	return false;
}


fn checkPair(s1: &Vec::<[i32; 3]>, s2: &Vec::<[i32; 3]>, trafo: &mut [i32; 12]) -> bool
{
	for m in 0..4
	{
		let sinM = (m % 2) * (2 - m);
		let cosM = ((m+1) % 2) * (1 - m);
		for n in 0..4
		{
			let sinN = (n % 2) * (2 - n);
			let cosN = ((n+1) % 2) * (1 - n);
			let t = [cosN, -sinN, 0, sinN*cosM, cosN*cosM, -sinM, sinN*sinM, cosN*sinM, cosM];
		
			let mut s3 = Vec::<[i32; 3]>::new();
			for c in s2
			{
				s3.push([t[0] * c[0] + t[1] * c[1] + t[2] * c[2],
						t[3] * c[0] + t[4] * c[1] + t[5] * c[2],
						t[6] * c[0] + t[7] * c[1] + t[8] * c[2]]);
			}
			
			if checkTransformedPair(s1, &s3, &mut trafo[9..12])
			{
				for i in 0..9
				{
					trafo[i] = t[i];
				}
				return true;
			}
		}
		for n in (1..4).step_by(2)
		{
			let sinN = (n % 2) * (2 - n);
			let cosN = ((n+1) % 2) * (1 - n);			
			let t = [cosN, 0, -sinN, -sinN*sinM, cosM, -cosN*sinM, sinN*cosM, sinM, cosN*cosM];	
		
			let mut s3 = Vec::<[i32; 3]>::new();
			for c in s2
			{
				s3.push([t[0] * c[0] + t[1] * c[1] + t[2] * c[2],
						t[3] * c[0] + t[4] * c[1] + t[5] * c[2],
						t[6] * c[0] + t[7] * c[1] + t[8] * c[2]]);
			}
			
			if checkTransformedPair(s1, &s3, &mut trafo[9..12])
			{
				for i in 0..9
				{
					trafo[i] = t[i];
				}
				return true;
			}
		}
	}
	
	return false;
}



pub fn execute_day19(fcr_fileName: &String)
{
	let file = File::open(fcr_fileName).unwrap();
	let reader = BufReader::new(file);

	let mut scanners: Vec::<Vec::<[i32; 3]>> = Vec::<Vec::<[i32; 3]>>::new();
	let mut next = true;
	for (_, line) in reader.lines().enumerate()
	{
		let line = line.unwrap();
		
		if line.len() == 0
		{
			next = true;
			continue;	
		}
		if next
		{
			scanners.push(Vec::<[i32; 3]>::new());
			next = false;
			continue;
		}
	
		let resVec = line.trim()
		.split_whitespace()
		.map(|s| s.parse::<i32>().unwrap())
		.collect::<Vec<i32>>();
		
		let scanner = scanners.last_mut().unwrap();
		scanner.push([resVec[0], resVec[1], resVec[2]]);
    }

	let numSc = scanners.len();
	
	let mut trafos = vec![[0i32; 12]; numSc];
	trafos[0][0] = 1;
	trafos[0][4] = 1;
	trafos[0][8] = 1;
	
	let mut t = [0i32; 12];
	
	let mut fixed = vec![false; numSc];
	let mut newlyFixed = vec![0; 1];
	fixed[0] = true;
	let mut nFixed = 1;
	while nFixed < numSc
	{
		let mut nextNewlyFixed = Vec::<usize>::new();
		
		for s in 1..numSc
		{
			if fixed[s]
			{
				continue;
			}
			
			let sc = &scanners[s];
			for f in &newlyFixed
			{
				let refSc = &scanners[*f];
				if checkPair(refSc, sc, &mut t)
				{
					//trafos[s] = trafos[*f] * t;
					trafos[s][0] = trafos[*f][0] * t[0] + trafos[*f][1] * t[3] + trafos[*f][2] * t[6];
					trafos[s][1] = trafos[*f][0] * t[1] + trafos[*f][1] * t[4] + trafos[*f][2] * t[7];
					trafos[s][2] = trafos[*f][0] * t[2] + trafos[*f][1] * t[5] + trafos[*f][2] * t[8];
					trafos[s][3] = trafos[*f][3] * t[0] + trafos[*f][4] * t[3] + trafos[*f][5] * t[6];
					trafos[s][4] = trafos[*f][3] * t[1] + trafos[*f][4] * t[4] + trafos[*f][5] * t[7];
					trafos[s][5] = trafos[*f][3] * t[2] + trafos[*f][4] * t[5] + trafos[*f][5] * t[8];
					trafos[s][6] = trafos[*f][6] * t[0] + trafos[*f][7] * t[3] + trafos[*f][8] * t[6];
					trafos[s][7] = trafos[*f][6] * t[1] + trafos[*f][7] * t[4] + trafos[*f][8] * t[7];
					trafos[s][8] = trafos[*f][6] * t[2] + trafos[*f][7] * t[5] + trafos[*f][8] * t[8];
					
					trafos[s][9] = trafos[*f][9] + trafos[*f][0] * t[9] + trafos[*f][1] * t[10] + trafos[*f][2] * t[11];
					trafos[s][10] = trafos[*f][10] + trafos[*f][3] * t[9] + trafos[*f][4] * t[10] + trafos[*f][5] * t[11];
					trafos[s][11] = trafos[*f][11] + trafos[*f][6] * t[9] + trafos[*f][7] * t[10] + trafos[*f][8] * t[11];
					
					//println!("fixed scanner {}", s);
					nFixed += 1;
					fixed[s] = true;
					nextNewlyFixed.push(s);
					break;
				}
			}
		}
		newlyFixed = nextNewlyFixed;
		if newlyFixed.is_empty()
		{
			print!("error - unfixable scanners: ");
			for s in 0..numSc
			{
				if !fixed[s]
				{
					print!("{} ", s);
				}
			}
			println!("");
			
			break;
		}
	}
	
	
	// part a: count all stars
	let mut beacons = BTreeSet::<[i32; 3]>::new();
	for s in 0..numSc
	{
		let t = &trafos[s];
		
		for b in &scanners[s]
		{
			beacons.insert([t[0] * b[0] + t[1] * b[1] + t[2] * b[2] + t[9],
						t[3] * b[0] + t[4] * b[1] + t[5] * b[2] + t[10],
						t[6] * b[0] + t[7] * b[1] + t[8] * b[2] + t[11]]);
		}
	}
	let resA = beacons.len();
	
	let mut maxDist = 0;
	for s1 in 0..numSc
	{
		for s2 in s1+1..numSc
		{
			let dist = (trafos[s1][9] - trafos[s2][9]).abs()
			+ (trafos[s1][10] - trafos[s2][10]).abs()
			+ (trafos[s1][11] - trafos[s2][11]).abs();
			
			if dist > maxDist
			{
				maxDist = dist;
			}
		}
	}
	
	println!("part (a): {}", resA);
	println!("part (b): {}", maxDist);
}