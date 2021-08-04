#pragma once
#include <vector>
#include <string>
#include "skills.h"

class Mission {
public:
	std::string name;
	int slots, level;
	SkillRequirements skillRequirements;

	Mission(std::string name, int slots, int level, int skillReq1, int skillReq2, int skillReq3, int skillReq4, int skillReq5, int skillReq6, int skillReq7, int skillReq8, int skillReq9)
		: name(name), slots(slots), level(level), skillRequirements { skillReq1, skillReq2, skillReq3, skillReq4, skillReq5, skillReq6, skillReq7, skillReq8, skillReq9 } {}

	friend std::ostream& operator<< (std::ostream& out, const Mission& mission) {
		return out << mission.name << " (" << mission.level << ")";
	}
};

// comment out missions you are not interested in
static const std::vector<Mission> allMissions = {
	/* Name, Slots, Level, Tear, Taunt, Search, Poison, Regen, Transport, Vigilance, Exhaust, Stun*/
	/* Patrol Missions */
	{"Serious Camp Patrol 1", 4, 4, 0, 3, 2, 1, 1, 0, 0, 0, 0},
	{"Serious Camp Patrol 2", 4, 4, 0, 3, 0, 2, 1, 1, 0, 0, 0},
	{"Serious Camp Patrol 3", 4, 4, 0, 3, 0, 0, 2, 1, 1, 0, 0},
	{"Extreme Camp Patrol 1", 4, 6, 0, 3, 3, 3, 2, 2, 0, 0, 0},
	{"Extreme Camp Patrol 2", 4, 6, 0, 3, 0, 3, 3, 2, 2, 0, 0},
	{"Extreme Camp Patrol 3", 4, 6, 0, 3, 0, 0, 3, 3, 2, 2, 0},
	/* Material Collection Missions */
	{"Hard Material Collection 1", 4, 6, 0, 0, 3, 3, 3, 2, 2, 0, 0},
	{"Hard Material Collection 2", 4, 6, 0, 0, 3, 0, 3, 3, 2, 2, 0},
	{"Hard Material Collection 3", 4, 6, 2, 0, 3, 0, 0, 3, 3, 2, 0},
	{"Hard Material Collection 4", 4, 6, 2, 2, 3, 0, 0, 0, 3, 3, 0},
	{"Hard Material Collection 5", 4, 6, 3, 2, 3, 2, 0, 0, 0, 3, 0},
	{"Special Material Collection 1", 4, 8, 3, 2, 4, 2, 2, 0, 0, 3, 3},
	{"Special Material Collection 2", 4, 8, 3, 3, 4, 2, 2, 2, 0, 0, 3},
	{"Special Material Collection 3", 4, 8, 3, 2, 4, 2, 0, 0, 0, 3, 3},
	{"Special Material Collection 4", 4, 8, 3, 2, 4, 2, 2, 0, 0, 0, 4},
	{"Special Material Collection 5", 4, 8, 4, 3, 4, 2, 2, 2, 0, 0, 0},
	/* Training Missions */
	{"Serious Battle Training 1", 4, 4, 2, 1, 1, 0, 3, 0, 0, 0, 0},
	{"Serious Battle Training 2", 4, 4, 0, 2, 1, 1, 3, 0, 0, 0, 0},
	{"Serious Battle Training 3", 4, 4, 0, 0, 2, 1, 3, 1, 0, 0, 0},
	{"Serious Battle Training 4", 4, 4, 0, 0, 0, 2, 3, 1, 1, 0, 0},
	{"Serious Battle Training 5", 4, 4, 2, 0, 1, 0, 3, 0, 1, 0, 0},
	{"Serious Battle Training 6", 4, 4, 2, 1, 0, 1, 3, 0, 0, 0, 0},
	{"Extreme Battle Training 1", 4, 7, 3, 2, 2, 2, 3, 2, 0, 0, 0},
	{"Extreme Battle Training 2", 4, 7, 0, 3, 2, 2, 3, 2, 2, 0, 0},
	{"Extreme Battle Training 3", 4, 7, 0, 0, 3, 2, 3, 2, 2, 2, 0},
	{"Extreme Battle Training 4", 4, 7, 3, 3, 2, 2, 3, 2, 0, 0, 0},
	{"Extreme Battle Training 5", 4, 7, 0, 3, 3, 2, 3, 2, 2, 0, 0},
	{"Extreme Battle Training 6", 4, 7, 0, 0, 3, 3, 3, 2, 2, 2, 0},
	/* Food Storage Missions */
	{"Medium Food Storage 1", 4, 5, 3, 0, 2, 1, 0, 3, 1, 0, 0},
	{"Medium Food Storage 2", 4, 5, 0, 0, 3, 2, 0, 3, 1, 1, 0},
	{"Medium Food Storage 3", 4, 5, 1, 1, 2, 0, 3, 3, 0, 0, 0},
//	{"Hard Food Storage 1", 4, 8, 2, 2, 3, 3, 3, 4, 0, 0, 2},
//	{"Hard Food Storage 2", 4, 8, 2, 3, 3, 3, 0, 4, 2, 0, 2},
//	{"Hard Food Storage 3", 4, 8, 0, 2, 0, 0, 4, 4, 3, 2, 2},
	/* Field Check Missions */
	{"Field Check 4 Prairie", 4, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0},
	{"Field Check 4 Totemtaff", 4, 4, 3, 0, 2, 1, 1, 0, 0, 0, 0},
	{"Field Check 4 Valley", 4, 4, 3, 0, 0, 2, 1, 1, 0, 0, 0},
	{"Field Check 4 Mapple Lake", 4, 4, 3, 0, 0, 0, 2, 1, 1, 0, 0},
	{"Field Check 4 Poleva", 4, 4, 3, 2, 0, 1, 0, 1, 0, 0, 0},
	{"Field Check 4 Atlas", 4, 4, 3, 0, 2, 0, 1, 0, 1, 0, 0},
	{"Field Check 5 Prairie", 4, 5, 3, 3, 2, 1, 1, 0, 0, 0, 0},
	{"Field Check 5 Totemtaff", 4, 5, 3, 0, 3, 2, 1, 1, 0, 0, 0},
	{"Field Check 5 Valley", 4, 5, 3, 0, 0, 3, 2, 1, 1, 0, 0},
	{"Field Check 5 Mapple Lake", 4, 5, 3, 0, 0, 0, 3, 2, 1, 1, 0},
	{"Field Check 5 Poleva", 4, 5, 3, 1, 0, 1, 0, 2, 0, 3, 0},
	{"Field Check 5 Atlas", 4, 5, 3, 0, 1, 1, 2, 0, 3, 0, 0},
	{"Field Check 6 Prairie", 4, 6, 3, 3, 3, 2, 2, 0, 0, 0, 0},
	{"Field Check 6 Totemtaff", 4, 6, 3, 0, 3, 3, 2, 2, 0, 0, 0},
	{"Field Check 6 Valley", 4, 6, 3, 0, 0, 3, 3, 2, 2, 0, 0},
	{"Field Check 6 Mapple Lake", 4, 6, 3, 0, 0, 0, 3, 3, 2, 2, 0},
	{"Field Check 6 Poleva", 4, 6, 3, 2, 0, 0, 0, 3, 3, 2, 0},
	{"Field Check 6 Atlas", 4, 6, 3, 2, 2, 0, 0, 0, 3, 3, 0},
	{"Field Check 7 Prairie", 4, 7, 3, 3, 2, 2, 2, 2, 0, 0, 0},
	{"Field Check 7 Totemtaff", 4, 7, 3, 0, 3, 2, 2, 2, 2, 0, 0},
	{"Field Check 7 Valley", 4, 7, 3, 0, 0, 3, 2, 2, 2, 2, 0},
	{"Field Check 7 Mapple Lake", 4, 7, 3, 3, 3, 2, 2, 2, 0, 0, 0},
	{"Field Check 7 Poleva", 4, 7, 3, 0, 3, 3, 2, 2, 2, 0, 0},
	{"Field Check 7 Atlas", 4, 7, 3, 0, 0, 3, 3, 2, 2, 2, 0},
//	{"Field Check 8 Prairie", 4, 8, 4, 3, 3, 3, 2, 2, 2, 0, 0},
	//{"Field Check 8 Totemtaff", 4, 8, 4, 0, 3, 3, 3, 2, 2, 2, 0},
	//{"Field Check 8 Valley", 4, 8, 4, 0, 0, 3, 3, 3, 2, 2, 2},
	//{"Field Check 8 Mapple Lake", 4, 8, 4, 4, 3, 2, 2, 2, 0, 0, 0},
	//{"Field Check 8 Poleva", 4, 8, 4, 0, 4, 3, 2, 2, 2, 0, 0},
	//{"Field Check 8 Atlas", 4, 8, 4, 0, 0, 4, 3, 2, 2, 2, 0},
	/* Crystals Missions */
	{"Treasure Scouting Prairie", 4, 4, 2, 1, 1, 0, 0, 0, 3, 0, 0},
	{"Treasure Scouting Totemtaff", 4, 4, 0, 2, 1, 1, 0, 0, 3, 0, 0},
	{"Treasure Scouting Valley", 4, 4, 0, 0, 2, 1, 1, 0, 3, 0, 0},
	{"Treasure Scouting Maple Lake", 4, 4, 0, 0, 0, 2, 1, 1, 3, 0, 0},
	{"Treasure Scouting Poleva", 4, 4, 1, 0, 0, 0, 2, 1, 3, 0, 0},
	{"Treasure Scouting Atlas", 4, 4, 0, 2, 0, 1, 0, 1, 3, 0, 0},
	{"Treasure Investigation Prairie", 4, 7, 3, 2, 2, 2, 2, 0, 0, 0, 3},
	{"Treasure Investigation Totemtaff", 4, 7, 0, 3, 2, 2, 2, 2, 0, 0, 3},
	{"Treasure Investigation Valley", 4, 7, 0, 0, 3, 2, 2, 2, 2, 0, 3},
	{"Treasure Investigation Maple Lake", 4, 7, 0, 0, 0, 3, 2, 2, 2, 2, 3},
	{"Treasure Investigation Poleva", 4, 7, 3, 3, 2, 2, 2, 0, 0, 0, 3},
	{"Treasure Investigation Atlas", 4, 7, 0, 3, 3, 2, 2, 2, 0, 0, 3},
	/* Crystallines Missions */
	{"Area Prospecting Prairie", 4, 5, 3, 2, 1, 1, 0, 0, 0, 3, 0},
	{"Area Prospecting Totemtaff", 4, 5, 0, 3, 2, 1, 1, 0, 0, 3, 0},
	{"Area Prospecting Valley", 4, 5, 0, 0, 3, 2, 1, 1, 0, 3, 0},
	{"Area Prospecting Maple Lake", 4, 5, 0, 0, 0, 3, 2, 1, 1, 3, 0},
	{"Area Prospecting Poleva", 4, 5, 1, 0, 0, 0, 3, 2, 1, 3, 0},
	{"Area Prospecting Atlas", 4, 5, 1, 1, 0, 0, 0, 3, 2, 3, 0},
	{"Area Prospecting 8* Prairie", 4, 8, 3, 3, 2, 2, 2, 0, 0, 4, 3},
	{"Area Prospecting 8* Totemtaff", 4, 8, 3, 3, 3, 2, 2, 2, 0, 4, 0},
	{"Area Prospecting 8* Valley", 4, 8, 0, 3, 3, 3, 2, 2, 2, 4, 0},
	{"Area Prospecting 8* Maple Lake", 4, 8, 3, 2, 2, 2, 0, 0, 0, 4, 4},
	{"Area Prospecting 8* Poleva", 4, 8, 4, 3, 2, 2, 2, 0, 0, 4, 0},
	{"Area Prospecting 8* Atlas", 4, 8, 0, 4, 3, 2, 2, 2, 0, 4, 0},
	/* Name, Slots, Level, Tear, Taunt, Search, Poison, Regen, Transport, Vigilance, Exhaust, Stun*/
	/* Level 8 Missions */
	//{"Bonfire Expansion 8", 4, 8, 4, 3, 3, 3, 2, 2, 2, 0, 0},
	//{"Stable Expansion 8", 4, 8, 0, 4, 3, 3, 3, 2, 2, 2, 0},
	//{"Encampment Upgrade 8", 4, 8, 2, 0, 0, 4, 3, 3, 3, 2, 2},
};
