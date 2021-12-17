pub fn execute_day17(_fcr_fileName: &String)
{
	// target:
	let xMin = 85;
	let xMax = 145;
	let yMin = -163;
	let yMax = -108;

	let mut resA = 0;
	let mut resB = 0;
	for vxStart in 1..xMax+1
	{
		for vyStart in yMin..1000
		{
			let mut x = 0;
			let mut y = 0;
			let mut vx = vxStart;
			let mut vy = vyStart;
			let mut maxY = 0;
			let mut hit = false;
			loop
			{
				x += vx;
				y += vy;
				vx = if vx > 0 {vx - 1} else {vx};
				vy -= 1;
				
				if x > xMax || y < yMin
				{
					break;
				}
				
				if x >= xMin && x <= xMax && y >= yMin && y <= yMax
				{
					hit = true;
					break;
				}
				
				if y > maxY
				{
					maxY = y;
				}
			}
			if hit
			{
				if maxY > resA
				{
					resA = maxY;
				}
				resB += 1;
			}
		}
	}

	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}