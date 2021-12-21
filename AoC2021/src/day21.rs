
const POSS: [u64; 7] = [1, 3, 6, 7, 6, 3, 1];


fn play(p: usize, wins: &mut [u64; 2], mut pos: [u32; 2], mut score: [u32; 2], cnt: u64)
{
	pos[p] += 2;
	let oldScore = score[p];
	for i in 3..10
	{
		pos[p] = pos[p] % 10 + 1;
		score[p] = oldScore + pos[p];
		if score[p] >= 21
		{
			wins[p] += cnt * POSS[i - 3];
		}
		else
		{
			play((p+1)%2, wins, pos, score, cnt * POSS[i-3]);
		}
	}
}


pub fn execute_day21(_fcr_fileName: &String)
{
	// part a
	let mut pos = [7, 6];
	let mut score = [0, 0];
	let mut nextDice = 1;

	let mut cnt = 0;
	let resA;
	loop
	{
		pos[0] = (pos[0] + 3*(nextDice + 1) + 9) % 10 + 1;
		score[0] += pos[0];
		nextDice = (nextDice + 3 + 99) % 100 + 1;
		cnt += 3;
		if score[0] >= 1000
		{
			resA = score[1] * cnt;
			break;
		}
		pos[1] = (pos[1] + 3*(nextDice + 1) + 9) % 10 + 1;
		score[1] += pos[1];
		nextDice = (nextDice + 3 + 9) % 100 + 1;
		cnt += 3;
		if score[1] >= 1000
		{
			resA = score[0] * cnt;
			break;
		}
	}
	
	// part b
	let mut wins = [0u64; 2];
	play(0, &mut wins, [7, 6], [0, 0], 1);
	let resB = std::cmp::max(wins[0], wins[1]);
	
	
	println!("part (a): {}", resA);
	println!("part (b): {}", resB);
}