/*
 * day24.h
 *
 *  Created on: 2018-12-24
 *      Author: mbreit
 */


enum AttackType
{
	AT_BLUDGEONING = 1 << 1,
	AT_COLD        = 1 << 2,
	AT_FIRE        = 1 << 3,
	AT_SLASHING    = 1 << 4,
	AT_RADIATION   = 1 << 5
};

struct AttackGroup
{
	size_t units;
	size_t hp;
	uint imm;
	uint weak;
	size_t damage;
	AttackType type;
	size_t initative;
	bool infect;
};

struct SortByEffectiveness
{
	bool operator()(const AttackGroup* ag1, const AttackGroup* ag2)
	{
		if (ag1->units*ag1->damage > ag2->units*ag2->damage)
			return true;
		if (ag1->units*ag1->damage < ag2->units*ag2->damage)
			return false;

		return ag1->initative > ag2->initative;
	}
};

struct SortByInitiative
{
	bool operator()
	(
		const std::pair<AttackGroup*, AttackGroup*>& ag1,
		const std::pair<AttackGroup*, AttackGroup*>& ag2
	)
	{
		return ag1.second->initative > ag2.second->initative;
	}
};


size_t calculateDamage(const AttackGroup* ag1, const AttackGroup* ag2)
{
	size_t dam = ag1->units * ag1->damage;

	if (ag2->weak & ag1->type)
		return 2*dam;

	if (ag2->imm & ag1->type)
		return 0;

	return dam;
};

struct SortByDamage
{
	bool operator() (const std::pair<AttackGroup*, size_t>& ag1, const std::pair<AttackGroup*, size_t>& ag2)
	{
		if (ag1.second < ag2.second)
			return true;
		if (ag1.second > ag2.second)
			return false;

		size_t effPower1 = ag1.first->units*ag1.first->damage;
		size_t effPower2 = ag2.first->units*ag2.first->damage;
		if (effPower1 < effPower2)
			return true;
		if (effPower1 > effPower2)
			return false;

		return ag1.first->initative < ag2.first->initative;
	}
};


void assign_attack_groups
(
	std::vector<AttackGroup>& attackers,
	std::vector<AttackGroup>& defenders,
	std::vector<std::pair<AttackGroup*, AttackGroup*> >& attackPairs // first is defender, second attacker
)
{
	const size_t attackSz = attackers.size();
	const size_t defendSz = defenders.size();
	std::vector<AttackGroup*> remainingAttackers(attackSz);
	for (size_t i = 0; i < attackSz; ++i)
		remainingAttackers[i] = &attackers[i];
	std::sort(remainingAttackers.begin(), remainingAttackers.end(), SortByEffectiveness());
	size_t nRemainingDefenders = defendSz;
	std::vector<bool> infRemaining(defendSz, true);
	for (size_t i = 0; i < attackSz; ++i)
	{
		size_t maxDamage = 0;
		size_t maxInd = 0;
		for (size_t j = 0; j < defendSz; ++j)
		{
			if (!infRemaining[j])
				continue;

			size_t damage = calculateDamage(remainingAttackers[i], &defenders[j]);
			if ((damage > 0) &&
				((damage > maxDamage) ||
					((damage == maxDamage) &&
						((defenders[j].units*defenders[j].damage > defenders[maxInd].units*defenders[maxInd].damage) ||
							((defenders[j].units*defenders[j].damage == defenders[maxInd].units*defenders[maxInd].damage) &&
								(defenders[j].initative > defenders[maxInd].initative))))))
			{
				maxDamage = damage;
				maxInd = j;
			}
		}
		if (maxDamage > 0)
		{
			attackPairs.push_back(std::make_pair(&defenders[maxInd], remainingAttackers[i]));
			infRemaining[maxInd] = false;
			--nRemainingDefenders;
			if (!nRemainingDefenders)
				break;
		}
	}
}


bool fight(std::vector<AttackGroup>& immunies, std::vector<AttackGroup>& infections, size_t& unitsOut)
{
	while (infections.size() && immunies.size())
	{
		// target selection
		std::vector<std::pair<AttackGroup*, AttackGroup*> > damageReceivers;
		damageReceivers.reserve(immunies.size() + infections.size());

		assign_attack_groups(immunies, infections, damageReceivers);
		assign_attack_groups(infections, immunies, damageReceivers);


		// deal damage
		bool unitKilled = false;
		std::sort(damageReceivers.begin(), damageReceivers.end(), SortByInitiative());
		const size_t nDamRecv = damageReceivers.size();
		for (size_t i = 0; i < nDamRecv; ++i)
		{
			if (damageReceivers[i].second->units > 0 && damageReceivers[i].second->units < 10000000)
			{
				const size_t damage = calculateDamage(damageReceivers[i].second, damageReceivers[i].first);
				damageReceivers[i].first->units -= damage / damageReceivers[i].first->hp;
				if (damage / damageReceivers[i].first->hp)
					unitKilled = true;
			}
		}
		if (!unitKilled)
		{
			// no critical damage can be given by anyone
			break;
		}


		// remove killed groups
		for (size_t i = 0; i < infections.size();)
		{
			if (infections[i].units == 0 || infections[i].units > 10000000)
				infections.erase(infections.begin() + i);
			else
				++i;
		}
		for (size_t i = 0; i < immunies.size();)
		{
			if (immunies[i].units == 0 || immunies[i].units > 10000000)
				immunies.erase(immunies.begin() + i);
			else
				++i;
		}
	}


	// evaluate outcome
	unitsOut = 0;
	if (infections.size())
	{
		for (size_t i = 0; i < infections.size(); ++i)
			unitsOut += infections[i].units;
		return false;
	}
	else
	{
		for (size_t i = 0; i < immunies.size(); ++i)
			unitsOut += immunies[i].units;
		return true;
	}
}




template <>
void executeDay<24>(const std::string& fn)
{
	std::vector<AttackGroup> infections(10);
	std::vector<AttackGroup> immunies(10);

	size_t i = 0;
	immunies[i].units = 2129;
	immunies[i].hp = 1138;
	immunies[i].imm = 0;
	immunies[i].weak = AT_COLD | AT_RADIATION;
	immunies[i].damage = 5;
	immunies[i].type = AT_BLUDGEONING;
	immunies[i].initative = 3;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 1224;
	immunies[i].hp = 4983;
	immunies[i].imm = AT_BLUDGEONING | AT_COLD | AT_FIRE | AT_SLASHING;
	immunies[i].weak = 0;
	immunies[i].damage = 37;
	immunies[i].type = AT_RADIATION;
	immunies[i].initative = 6;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 4081;
	immunies[i].hp = 8009;
	immunies[i].imm = AT_SLASHING | AT_RADIATION;
	immunies[i].weak = AT_BLUDGEONING | AT_COLD;
	immunies[i].damage = 17;
	immunies[i].type = AT_FIRE;
	immunies[i].initative = 7;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 1462;
	immunies[i].hp = 6747;
	immunies[i].imm = 0;
	immunies[i].weak = 0;
	immunies[i].damage = 41;
	immunies[i].type = AT_BLUDGEONING;
	immunies[i].initative = 10;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 4232;
	immunies[i].hp = 4848;
	immunies[i].imm = 0;
	immunies[i].weak = AT_SLASHING;
	immunies[i].damage = 11;
	immunies[i].type = AT_BLUDGEONING;
	immunies[i].initative = 13;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 1836;
	immunies[i].hp = 8018;
	immunies[i].imm = AT_RADIATION;
	immunies[i].weak = 0;
	immunies[i].damage = 37;
	immunies[i].type = AT_SLASHING;
	immunies[i].initative = 15;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 2599;
	immunies[i].hp = 11625;
	immunies[i].imm = 0;
	immunies[i].weak = 0;
	immunies[i].damage = 36;
	immunies[i].type = AT_BLUDGEONING;
	immunies[i].initative = 17;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 2192;
	immunies[i].hp = 8410;
	immunies[i].imm = AT_FIRE | AT_RADIATION;
	immunies[i].weak = AT_COLD;
	immunies[i].damage = 36;
	immunies[i].type = AT_BLUDGEONING;
	immunies[i].initative = 18;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 815;
	immunies[i].hp = 2261;
	immunies[i].imm = 0;
	immunies[i].weak = AT_COLD;
	immunies[i].damage = 22;
	immunies[i].type = AT_COLD;
	immunies[i].initative = 19;
	immunies[i].infect = false;
	++i;
	immunies[i].units = 4040;
	immunies[i].hp = 8260;
	immunies[i].imm = AT_COLD;
	immunies[i].weak = 0;
	immunies[i].damage = 17;
	immunies[i].type = AT_BLUDGEONING;
	immunies[i].initative = 20;
	immunies[i].infect = false;

	i=0;
	infections[i].units = 7704;
	infections[i].hp = 14742;
	infections[i].imm = AT_COLD;
	infections[i].weak = 0;
	infections[i].damage = 3;
	infections[i].type = AT_FIRE;
	infections[i].initative = 1;
	infections[i].infect = true;
	++i;
	infections[i].units = 65;
	infections[i].hp = 32784;
	infections[i].imm = AT_BLUDGEONING;
	infections[i].weak = AT_COLD;
	infections[i].damage = 957;
	infections[i].type = AT_FIRE;
	infections[i].initative = 2;
	infections[i].infect = true;
	++i;
	infections[i].units = 909;
	infections[i].hp = 34180;
	infections[i].imm = 0;
	infections[i].weak = AT_BLUDGEONING | AT_SLASHING;
	infections[i].damage = 72;
	infections[i].type = AT_BLUDGEONING;
	infections[i].initative = 4;
	infections[i].infect = true;
	++i;
	infections[i].units = 99;
	infections[i].hp = 49137;
	infections[i].imm = 0;
	infections[i].weak = 0;
	infections[i].damage = 855;
	infections[i].type = AT_FIRE;
	infections[i].initative = 5;
	infections[i].infect = true;
	++i;
	infections[i].units = 3271;
	infections[i].hp = 32145;
	infections[i].imm = 0;
	infections[i].weak = AT_BLUDGEONING | AT_RADIATION;
	infections[i].damage = 19;
	infections[i].type = AT_BLUDGEONING;
	infections[i].initative = 8;
	infections[i].infect = true;
	++i;
	infections[i].units = 5428;
	infections[i].hp = 51701;
	infections[i].imm = 0;
	infections[i].weak = AT_FIRE;
	infections[i].damage = 14;
	infections[i].type = AT_FIRE;
	infections[i].initative = 9;
	infections[i].infect = true;
	++i;
	infections[i].units = 398;
	infections[i].hp = 29275;
	infections[i].imm = AT_SLASHING;
	infections[i].weak = AT_FIRE;
	infections[i].damage = 137;
	infections[i].type = AT_COLD;
	infections[i].initative = 11;
	infections[i].infect = true;
	++i;
	infections[i].units = 5427;
	infections[i].hp = 50754;
	infections[i].imm = 0;
	infections[i].weak = 0;
	infections[i].damage = 14;
	infections[i].type = AT_RADIATION;
	infections[i].initative = 12;
	infections[i].infect = true;
	++i;
	infections[i].units = 908;
	infections[i].hp = 57557;
	infections[i].imm = 0;
	infections[i].weak = AT_BLUDGEONING;
	infections[i].damage = 96;
	infections[i].type = AT_FIRE;
	infections[i].initative = 14;
	infections[i].infect = true;
	++i;
	infections[i].units = 3788;
	infections[i].hp = 27222;
	infections[i].imm = AT_BLUDGEONING | AT_COLD;
	infections[i].weak = 0;
	infections[i].damage = 14;
	infections[i].type = AT_SLASHING;
	infections[i].initative = 16;
	infections[i].infect = true;

	std::vector<AttackGroup> infectionsCopy(infections);
	std::vector<AttackGroup> immuniesCopy(immunies);


	// part a
	size_t sola;
	fight(immunies, infections, sola);

	// part b
	size_t solb;
	size_t boost = 1;
	while (true)
	{
		immunies = immuniesCopy;
		infections = infectionsCopy;

		for (size_t i = 0; i < 10; ++i)
			immunies[i].damage += boost;

		if (fight(immunies, infections, solb))
			break;

		++boost;
	}

	writeSolution(sola, solb);
}


