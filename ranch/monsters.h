#pragma once
#include <string>
#include <vector>
#include "skills.h"

class Monster {
public:
	std::string name;
	Color color;
	Skill skill1, skill2;
	size_t id;

	Monster(const std::string & name, const std::string & color, const std::string & skill1, const std::string & skill2)
		: name(name), color(color), skill1(skill1), skill2(skill2) {}

	bool Satisfies(int skill, int level) const {
		return this->skill1.skill == skill || (level <= 2 && this->skill2.skill == skill);
	}

	typename SkillRequirements Apply(const SkillRequirements& requirements) const {
		SkillRequirements res = requirements;
		res[skill1.skill] = 0;
		if (res[skill2.skill] <= 2) {
			res[skill2.skill] = 0;
		}

		return res;
	}

	friend std::ostream& operator<< (std::ostream& out, const Monster & monster) {
		return out << monster.name << " (" << monster.color << ")";
	}
};

// comment out monsters you don't want to consider, i.e. are currently unobtainable
static const std::vector<Monster> allMonsters = {
	{"Blue Wolf", "White", "Tear", "Taunt"},
	{"Boomshroom", "Black", "Taunt", "Search"},
	{"Blazetail Lizard", "Gold", "Search", "Poison"},
	{"Red Wolf", "Black", "Poison", "Regen"},
	{"Brown Wolf", "Gold", "Regen", "Transport"},
	{"Young Golem", "White", "Transport", "Vigilance"},
	{"Prickear Monkey", "Gold", "Vigilance", "Exhaust"},
	{"Buzzwing Bug", "Black", "Exhaust", "Stun"},
	{"Serpent", "White", "Stun", "Tear"},
	{"Helmetal Thief", "Black", "Tear", "Search"},
	{"Algae Ball", "White", "Search", "Regen"},
	{"Bilgebat", "Gold", "Regen", "Vigilance"},
	{"Young Wild Frogodile", "Black", "Vigilance", "Stun"},
	{"Platypus", "White", "Stun", "Taunt"},
	{"Bigmouth Puck", "Gold", "Taunt", "Poison"},
	{"Beaver Lil' Tommy", "Black", "Poison", "Transport"},
	{"Beaver Lil' Dicky", "White", "Transport", "Exhaust"},
	{"Beaver Lil' Harry", "Gold", "Exhaust", "Tear"},
	{"Mother Boomshroom", "Black", "Tear", "Poison"},
	{"Awful Acorn", "White", "Poison", "Vigilance"},
	{"Kalta Beast", "Gold", "Vigilance", "Taunt"},
	{"Flying Snout Whale", "Black", "Taunt", "Regen"},
	{"Withered Flea", "White", "Regen", "Exhaust"},
	{"Crimson Narwhal", "Gold", "Exhaust", "Search"},
	{"Striped Prickear Monkey", "Black", "Search", "Transport"},
	{"Leafy Flea", "White", "Transport", "Stun"},
	{"Adult Frogodile", "Gold", "Stun", "Tear"},

	{"May Gumball", "White", "Search", "Transport"},
	{"Slime Gumball", "Gold", "Exhaust", "Vigilance"},
	{"Princess Gumball", "Black", "Taunt", "Exhaust"},
	{"Sycth Gumball", "White", "Poison", "Search"},
	{"Warrior Gumball", "Gold", "Stun", "Tear"},
	{"Black Gumball", "Black", "Tear", "Poison"},
	{"Santa Gumball", "Black", "Transport", "Stun"},
	{"Pang Gumball", "Gold", "Regen", "Tear"},
	{"Puggi Gumball", "White", "Vigilance", "Exhaust"},
	{"Skewgrass Goose", "Gold", "Taunt", "Vigilance"},
	{"Hexopus", "White", "Search", "Exhaust"},
	{"Lake Mudpye", "Black", "Exhaust", "Poison"},
	{"Vomito Dragon", "White", "Vigilance", "Poison"},
	{"Wild Mongrel", "White", "Stun", "Regen"},
	{"Bobble", "Black", "Exhaust", "Regen"},
	{"Redthorn Cactus", "Gold", "Poison", "Tear"},
	{"Darting Ostrich", "Black", "Stun", "Vigilance"},
	{"Temple Bird", "White", "Tear", "Transport"},
//	{"War Scorpion", "Black", "Vigilance", "Regen"},
//	{"Mandora", "Gold", "Transport", "Vigilance"},
//	{"Carrodora", "White", "Search", "Poison"},
//	{"Butterfly Mandora", "Black", "Poison", "Regen"},
//	{"Dream Mandora", "White", "Stun", "Regen"},
//	{"Security Mandora", "Gold", "Tear", "Taunt"},
	{"Frogodora", "Gold", "Tear", "Poison"},
	{"Queen Adora", "Black", "Regen", "Vigilance"},
	{"Custumandora", "White", "Exhaust", "Regen"}
};
