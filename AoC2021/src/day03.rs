use std::fs::File;
use std::io::{BufRead, BufReader};


pub fn execute_day03(fcr_fileName: &String)
{
    let file = File::open(fcr_fileName).unwrap();
    let reader = BufReader::new(file);
	
	let mut a = [0; 12];
	let mut cnt = 0;
	let mut data = Vec::<u32>::new();
    for (_, line) in reader.lines().enumerate()
	{
		let line = line.unwrap(); // Ignore errors.
		
		let mut num = 0;
		for i in 0..12
		{
			if line.chars().nth(i).unwrap() == '1'
			{
				a[i] += 1;
				num += 1 << (11 - i);
			}
		}
		
		data.push(num);
		cnt += 1;
    }
	
	let mut eps = 0;
	let mut gam = 0;
	
	for i in 0..12
	{
		if a[i] > cnt / 2
		{
			eps += 1 << (11-i);
		}
		else	
		{
			gam += 1 << (11-i);
		}
	}
	
	
	let mut oxVal = 0;
	let mut dataOx = data.clone();
	for i in (0..12).rev()
	{
		let mut cnt = 0;
		for num in &dataOx
		{
			if num & (1 << i) > 0
			{
				cnt += 1;
			}
		}
		
		let sz = dataOx.len();
		let mut j = 0;
		while j < dataOx.len()
		{
			if dataOx[j] & (1 << i) > 0 && cnt < sz / 2
				|| dataOx[j] & (1 << i) == 0 && cnt >= sz / 2
			{
				dataOx.remove(j);
			}
			else
			{
				j += 1;
			}
		}
		if dataOx.len() == 1
		{
			oxVal = dataOx[0];
			break;
		}	
	}
	
	let mut co2Val = 0;
	let mut dataCO2 = data.clone();
	for i in (0..12).rev()
	{
		let mut cnt = 0;
		for num in &dataCO2
		{
			if num & (1 << i) > 0
			{
				cnt += 1;
			}
		}
		
		let sz = dataCO2.len();
		let mut j = 0;
		while j < dataCO2.len()
		{
			if dataCO2[j] & (1 << i) > 0 && cnt >= sz / 2
				|| dataCO2[j] & (1 << i) == 0 && cnt < sz / 2
			{
				dataCO2.remove(j);
			}
			else
			{
				j += 1;
			}
		}
		if dataCO2.len() == 1
		{
			co2Val = dataCO2[0];
			break;
		}	
	}
	
	
	println!("part (a): {}", eps * gam);
	println!("part (b): {}", oxVal * co2Val);
}
