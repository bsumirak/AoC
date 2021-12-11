use std::collections::LinkedList;

pub fn execute_day11(_fcr_fileName: &String)
{
	let mut oct = [5,6,5,1,3,4,1,4,5,2,
					1,3,8,1,5,4,1,2,5,2,
					1,8,7,8,4,3,5,2,2,4,
					6,8,1,4,8,3,1,5,3,5,
					3,8,8,3,5,4,7,3,8,3,
					6,4,7,3,5,4,8,4,6,4,
					1,8,8,5,8,3,3,6,5,8,
					3,7,3,2,5,8,4,7,5,2,
					1,8,8,1,5,4,6,1,2,8,
					5,1,2,1,7,1,7,7,7,6];

	let mut resA = 0;
	let mut resB = 0;
	for i in 0..1000
	{
		let mut q = LinkedList::<usize>::new();
		let mut allFlash = true;
		
		for o in 0..100
		{
			if oct[o] > 9
			{
				if i <= 100
				{
					resA += 1;
				}
				oct[o] = 1;
			}
			else
			{
				oct[o] += 1;
				allFlash = false;
				if oct[o] == 10
				{
					q.push_back(o);
				}
			}
		}
		if allFlash
		{
			resB = i;
			break;
		}
		
		while !q.is_empty()
		{
			let o = q.pop_front().unwrap();
			
			if o / 10 > 0
			{
				if o % 10 > 0
				{
					oct[o - 11] += 1;
					if oct[o - 11] == 10
					{
						q.push_back(o-11);
					}
				}
				{
					oct[o - 10] += 1;
					if oct[o - 10] == 10
					{
						q.push_back(o-10);
					}
				}
				if o % 10 < 9
				{
					oct[o - 9] += 1;
					if oct[o - 9] == 10
					{
						q.push_back(o-9);
					}
				}
			}
			{
				if o % 10 > 0
				{
					oct[o - 1] += 1;
					if oct[o - 1] == 10
					{
						q.push_back(o-1);
					}
				}
				if o % 10 < 9
				{
					oct[o + 1] += 1;
					if oct[o + 1] == 10
					{
						q.push_back(o+1);
					}
				}
			}
			if o / 10 < 9
			{
				if o % 10 > 0
				{
					oct[o + 9] += 1;
					if oct[o + 9] == 10
					{
						q.push_back(o+9);
					}
				}
				{
					oct[o + 10] += 1;
					if oct[o + 10] == 10
					{
						q.push_back(o+10);
					}
				}
				if o % 10 < 9
				{
					oct[o + 11] += 1;
					if oct[o + 11] == 10
					{
						q.push_back(o+11);
					}
				}
			}
		}
	}
	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}