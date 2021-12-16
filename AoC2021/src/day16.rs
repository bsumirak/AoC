

fn inspect_package(msg: &Vec::<bool>, ind: &mut usize, vrsSum: &mut u32) -> u64
{
	let mut vrs = 0;
	if msg[*ind] {vrs += 4;}
	if msg[*ind+1] {vrs += 2;}
	if msg[*ind+2] {vrs += 1;}
	*vrsSum += vrs;
	
	let mut tp = 0;
	if msg[*ind+3] {tp += 4;}
	if msg[*ind+4] {tp += 2;}
	if msg[*ind+5] {tp += 1;}
	
	if tp == 4
	{
		let mut val = 0;
		*ind = *ind + 6;
		loop
		{
			val = (val << 1) + msg[*ind+1] as u64;
			val = (val << 1) + msg[*ind+2] as u64;
			val = (val << 1) + msg[*ind+3] as u64;
			val = (val << 1) + msg[*ind+4] as u64;
			*ind += 5;
			if !msg[*ind - 5]
			{
				break;
			}
		}
		return val;
	}
	else
	{
		let mut vals = Vec::new();
		if !msg[*ind+6]
		{
			let mut len = 0 as usize;
			for i in 7..22
			{
				len = (len << 1) + msg[*ind + i] as usize;
			}
			*ind += 22;
	
			let stop = *ind + len;
			
			while *ind < stop
			{
				vals.push(inspect_package(msg, ind, vrsSum));
			}
			*ind = stop; // to be on the safe side
		}
		else
		{
			let mut n = 0;
			for i in 7..18
			{
				n = (n << 1) + msg[*ind + i] as usize;
			}
			
			*ind += 18;
			for _ in 0..n
			{
				vals.push(inspect_package(msg, ind, vrsSum));
			}
		}
		
		if tp == 0
		{
			let mut ret = 0;
			for v in vals
			{
				ret += v;
			}
			return ret;
		}
		if tp == 1
		{
			let mut ret = 1;
			for v in vals
			{
				ret *= v;
			}
			return ret;
		}
		if tp == 2
		{
			let mut ret = u64::MAX;
			for v in vals
			{
				if v < ret {ret = v;}
			}
			return ret;
		}
		if tp == 3
		{
			let mut ret = 0;
			for v in vals
			{
				if v > ret {ret = v;}
			}
			return ret;
		}
		if tp == 5
		{
			return (vals[0] > vals[1]) as u64;
		}
		if tp == 6
		{
			return (vals[0] < vals[1]) as u64;
		}
		if tp == 7
		{
			return (vals[0] == vals[1]) as u64;
		}
		println!("unexpected operator type: {}", tp);
	}
	
	return 0;
}


pub fn execute_day16(_fcr_fileName: &String)
{
	let msgStr = "420D5A802122FD25C8CD7CC010B00564D0E4B76C7D5A59C8C014E007325F116C958F2C7D31EB4EDF90A9803B2EB5340924CA002761803317E2B4793006E28C2286440087C5682312D0024B9EF464DF37EFA0CD031802FA00B4B7ED2D6BD2109485E3F3791FDEB3AF0D8802A899E49370012A926A9F8193801531C84F5F573004F803571006A2C46B8280008645C8B91924AD3753002E512400CC170038400A002BCD80A445002440082021DD807C0201C510066670035C00940125D803E170030400B7003C0018660034E6F1801201042575880A5004D9372A520E735C876FD2C3008274D24CDE614A68626D94804D4929693F003531006A1A47C85000084C4586B10D802F5977E88D2DD2898D6F17A614CC0109E9CE97D02D006EC00086C648591740010C8AF14E0E180253673400AA48D15E468A2000ADCCED1A174218D6C017DCFAA4EB2C8C5FA7F21D3F9152012F6C01797FF3B4AE38C32FFE7695C719A6AB5E25080250EE7BB7FEF72E13980553CE932EB26C72A2D26372D69759CC014F005E7E9F4E9FA7D3653FCC879803E200CC678470EC0010E82B11E34080330D211C663004F00101911791179296E7F869F9C017998EF11A1BCA52989F5EA778866008D8023255DFBB7BD2A552B65A98ECFEC51D540209DFF2FF2B9C1B9FE5D6A469F81590079160094CD73D85FD2699C5C9DCF21F0700094A1AC9EDA64AE3D37D34200B7B401596D678A73AFB2D0B1B88057230A42B2BD88E7F9F0C94F1ECB7B0DD393489182F9802D3F875C00DC40010F8911C61F8002111BA1FC2E400BEA5AA0334F9359EA741892D81100B83337BD2DDB4E43B401A800021F19A09C1F1006229C3F8726009E002A12D71B96B8E49BB180273AA722468002CC7B818C01B04F77B39EFDF53973D95ADB5CD921802980199CF4ADAA7B67B3D9ACFBEC4F82D19A4F75DE78002007CD6D1A24455200A0E5C47801559BF58665D80";
	let chs = msgStr.chars();
		
	let mut msg = Vec::<bool>::new();
	for ch in chs
	{
		let n = ch.to_digit(16).unwrap();
		msg.push(n & 8 == 8);
		msg.push(n & 4 == 4);
		msg.push(n & 2 == 2);
		msg.push(n & 1 == 1);
	}

	let mut vrsSum = 0;
	let mut ind = 0;
	let resB = inspect_package(&msg, &mut ind, &mut vrsSum);
	
	println!("part (a): {}", vrsSum);
	println!("part (b): {}", resB);
}