#include <iostream>
#include "monsters.h"
#include "missions.h"

static std::vector<Monster> monsters{};
static std::vector<Mission> missions{};

class MonsterGroup;

class MissionSolutions {
public:
	std::vector<MonsterGroup> solutions;
	const Mission* mission;

	MissionSolutions(const Mission* mission)
		: mission(mission) {}
};

class MonsterGroup {
public:
	std::vector<const Monster *> monsters;
	SkillRequirements coverage{}, coverageCount{}, originalRequirements;
	std::vector<size_t> monsterIds;

	MonsterGroup(SkillRequirements originalRequirements)
		: originalRequirements(originalRequirements), monsterIds(::monsters.size()) {}

	bool HasAllColors() const {
		if (this->monsters.size() < numColors) {
			return true;
		}

		auto usedColors = std::array<bool, numColors> {};
		int unusedColors = numColors;
		for (const auto monster : this->monsters) {
			if (!usedColors[monster->color.color]) {
				usedColors[monster->color.color] = true;
				if (--unusedColors == 0) {
					return true;
				}
			}
		}

		return false;
	}

	void addCoverage(const Skill & skill, int level) {
		this->coverage[skill.skill] = std::max(this->coverage[skill.skill], level);
		if (this->originalRequirements[skill.skill] > 0 && this->originalRequirements[skill.skill] <= level) {
			++this->coverageCount[skill.skill];
		}
	}
	
	void addCoverage(const Monster* monster) {
		this->addCoverage(monster->skill1, 4);
		this->addCoverage(monster->skill2, 2);
	}

	bool isSuperfluous(const Skill & skill, int level) const {
		return (this->originalRequirements[skill.skill] == 0 || this->originalRequirements[skill.skill] > level || this->coverageCount[skill.skill] > 1);
	}

	bool isSuperfluous(const Monster* monster) const {
		return this->isSuperfluous(monster->skill1, 4) && this->isSuperfluous(monster->skill2, 2);
	}

	bool isNeeded(const Monster * monster) const {
		//return this->coverage[monster->skill1.skill] < 4 || this->coverage[monster->skill2.skill] < 2;
		return this->monsterIds[monster->id] == 0;
	}

	bool ComputeCoverage() {
		for (auto i = 0u; i < coverage.size(); ++i) {
			coverage[i] = 0;
			coverageCount[i] = 0;
		}

		for (const auto monster : this->monsters) {
			this->addCoverage(monster);
		}

		for (const auto monster : this->monsters) {
			if (this->isSuperfluous(monster)) {
				return false;
			}
		}

		return true;
	}
	
	void Push(const Monster* monster) {
		this->monsters.push_back(monster);
		++this->monsterIds[monster->id];
		this->addCoverage(monster);
	}

	void Pop() {
		--this->monsterIds[this->monsters.back()->id];
		this->monsters.pop_back();

	}

	bool IsSubset(const MonsterGroup& group) const {
		for (const auto * monster : group.monsters) {
			if (this->monsterIds[monster->id] == 0) {
				return false;
			}
		}

		return true;
	}

	bool Satisfies(const MissionSolutions & solutions) const {
		for (const auto& solution : solutions.solutions) {
			if (this->IsSubset(solution)) {
				return true;
			}
		}
		return false;
	}

	void Join(const MonsterGroup & group) {
		for (const auto & monster : group.monsters) {
			if (this->isNeeded(monster)) {
				this->Push(monster);
			}
		}
	}

	void Sort() {
		std::sort(this->monsters.begin(), this->monsters.end(), [](const auto a, const auto b) {
			return a->name < b->name;
			});
	}

	int Compare(const MonsterGroup & group) const {
		if (this->monsters.size() < group.monsters.size()) {
			return -1;
		}
		if (this->monsters.size() > group.monsters.size()) {
			return 1;
		}

		for (auto i = 0u; i < this->monsters.size(); ++i) {
			if (this->monsters[i]->name < group.monsters[i]->name) {
				return -1;
			}
			if (this->monsters[i]->name > group.monsters[i]->name) {
				return 1;
			}
		}

		return 0;
	}

	friend std::ostream& operator<< (std::ostream& out, const MonsterGroup& group) {
		for (const auto monster : group.monsters) {
			out << *monster << " ";
		}
		return out;
	}
};

void searchMatch(SkillRequirements reqs, MonsterGroup & group, int remaining, std::vector<int> reserved, std::vector<MonsterGroup> & solutions) {
	const auto pos = std::find_if(reqs.cbegin(), reqs.cend(), [](auto e) { return e > 0; });
	if (pos == reqs.cend()) {
		if (group.HasAllColors() && group.ComputeCoverage()) {
			solutions.push_back(group);
			//std::cout << group << std::endl;
		}
		return;
	}

	const int skillNum = pos - reqs.cbegin();

	if (remaining <= 0) {
		return;
	}

	for (auto i = 0u; i < monsters.size(); ++i) {
		if (reserved[i] == 0) {
			auto& monster = monsters[i];
			if (monster.Satisfies(skillNum, *pos)) {
				reserved[i] = remaining;
			}
		}
	}

	for (auto i = 0u; i < monsters.size(); ++i) {
		auto& monster = monsters[i];
		if (reserved[i] == remaining) {
			group.monsters.push_back(&monster);
			searchMatch(std::move(monster.Apply(reqs)), group, remaining - 1, reserved, solutions);
			group.monsters.pop_back();
		}
	}
}

MissionSolutions getAllMatches(const Mission & mission) {
	auto group = MonsterGroup(mission.skillRequirements);
	auto reserved = std::vector<int>(monsters.size());
	MissionSolutions solutions(&mission);
	searchMatch(mission.skillRequirements, group, mission.slots, reserved, solutions.solutions);
//	std::cout << "Count for " << mission << ": " << solutions.size() << std::endl;
	return solutions;
}

class MissionsSolutions {
public:
	std::vector<MonsterGroup> solutions;

	size_t CurrentSize() {
		if (this->solutions.size() == 0) {
			return 9999999;
		}

		return this->solutions[0].monsters.size();
	}

	void AddSolution(const MonsterGroup& group) {
		if (this->solutions.size() > 0 && group.monsters.size() < this->solutions[0].monsters.size()) {
			std::cout << "Best size " << group.monsters.size() << std::endl;
			this->solutions.clear();
		}

		this->solutions.push_back(group);
		this->solutions.back().Sort();
	}

	void RemoveDups() {
		if (this->solutions.size() < 2) {
			return;
		}

		std::sort(this->solutions.begin(), this->solutions.end(), [](const auto& a, const auto& b) {
			return a.Compare(b) < 0;
			});

		std::vector<MonsterGroup> newSolutions{this->solutions[0]};

		for (auto i = 1u; i < this->solutions.size(); ++i) {
			if (this->solutions[i].Compare(this->solutions[i - 1]) != 0) {
				newSolutions.push_back(this->solutions[i]);
			}
		}

		this->solutions = std::move(newSolutions);
	}
};

void addMission(const std::vector<MissionSolutions>& solutions, const MonsterGroup& group, size_t index, MissionsSolutions & missionsSolutions, size_t limit) {
	if (index >= solutions.size()) {
		missionsSolutions.AddSolution(group);
		return;
	}

	if (group.Satisfies(solutions[index])) {
		addMission(solutions, group, index + 1, missionsSolutions, limit);
		return;
	}

	for (const auto & solution : solutions[index].solutions) {
		auto newGroup = group;
		newGroup.Join(solution);
		if (newGroup.monsters.size() <= limit && newGroup.monsters.size() <= missionsSolutions.CurrentSize()) {
			addMission(solutions, newGroup, index + 1, missionsSolutions, limit);
		}
	}
}

const Monster* monsterByNameAll(std::string name) {
	for (const auto& monster : allMonsters) {
		if (monster.name == name) {
			return &monster;
		}
	}

	return nullptr;
}

const Monster* monsterByName(std::string name) {
	for (const auto& monster : monsters) {
		if (monster.name == name) {
			return &monster;
		}
	}

	return nullptr;
}

void initMonsters() {
	//monsters.push_back(*monsterByNameAll("Bigmouth Puck"));
	//monsters.push_back(*monsterByNameAll("Beaver Lil' Tommy"));

	//monsters.push_back(*monsterByNameAll("Algae Ball"));
	//monsters.push_back(*monsterByNameAll("Blazetail Lizard"));
	//monsters.push_back(*monsterByNameAll("Serpent"));
	//monsters.push_back(*monsterByNameAll("Helmetal Thief"));
	//monsters.push_back(*monsterByNameAll("Crimson Narwhal"));
	//monsters.push_back(*monsterByNameAll("Bilgebat"));

	//monsters.push_back(*monsterByNameAll("Striped Prickear Monkey"));
	//monsters.push_back(*monsterByNameAll("Red Wolf"));
	//monsters.push_back(*monsterByNameAll("Buzzwing Bug"));
	//monsters.push_back(*monsterByNameAll("Leafy Flea"));
	//monsters.push_back(*monsterByNameAll("Brown Wolf"));
	//monsters.push_back(*monsterByNameAll("Beaver Lil' Harry"));
	//monsters.push_back(*monsterByNameAll("Awful Acorn"));
	//monsters.push_back(*monsterByNameAll("Blue Wolf"));
	//monsters.push_back(*monsterByNameAll("Beaver Lil' Dicky"));
	//monsters.push_back(*monsterByNameAll("Young Wild Frogodile"));
	//monsters.push_back(*monsterByNameAll("Boomshroom"));
	//monsters.push_back(*monsterByNameAll("Temple Bird"));

	monsters = allMonsters;

	for (auto i = 0u; i < monsters.size(); ++i) {
		monsters[i].id = i;
	}
}

void initMissions() {
	for (auto& mission : allMissions) {
		if (mission.level >= 8) {
			missions.push_back(mission);
		}
	}
}

int main()
{
	initMonsters();
	initMissions();

	std::vector<MissionSolutions> solutions;

	for (const auto & mission : missions) {
		solutions.push_back(std::move(getAllMatches(mission)));
	}

	std::sort(solutions.begin(), solutions.end(), [](const auto& a, const auto& b) { return a.solutions.size() < b.solutions.size(); });

	for (const auto& solution : solutions) {
		std::cout << "Count for " << *solution.mission << ": " << solution.solutions.size() << std::endl;
		/*
		if (solution.mission->name == "Area Prospecting 8* Prairie") {
			for (const auto& group : solution.solutions) {
				std::cout << "- " << group << std::endl;
			}
		}
		*/
	}

	auto group = MonsterGroup{ SkillRequirements {} };

	// Mandatory monsters included in every solution can be added here,
	// i.e. monsters already with double team III trait
	group.Push(monsterByName("Beaver Lil' Tommy"));
	group.Push(monsterByName("Algae Ball"));
	group.Push(monsterByName("Bigmouth Puck"));
/*
	group.Push(monsterByName("Blazetail Lizard"));
	group.Push(monsterByName("Serpent"));
	group.Push(monsterByName("Leafy Flea"));
	group.Push(monsterByName("Helmetal Thief"));
	group.Push(monsterByName("Crimson Narwhal"));
	group.Push(monsterByName("Bilgebat"));
	group.Push(monsterByName("Temple Bird"));
	group.Push(monsterByName("Platypus"));

	group.Push(monsterByName("Boomshroom"));
	group.Push(monsterByName("Awful Acorn"));
	group.Push(monsterByName("Striped Prickear Monkey"));
	group.Push(monsterByName("Red Wolf"));
	group.Push(monsterByName("Buzzwing Bug"));
	group.Push(monsterByName("Brown Wolf"));
	group.Push(monsterByName("Beaver Lil' Harry"));
	group.Push(monsterByName("Blue Wolf"));
	group.Push(monsterByName("Beaver Lil' Dicky"));
	group.Push(monsterByName("Young Wild Frogodile"));
	group.Push(monsterByName("Withered Flea"));
*/
	MissionsSolutions missionsSolutions{};
	for (auto limit = 0u; limit < monsters.size(); ++limit) {
		std::cout << "Investigating limit " << limit << std::endl;
		missionsSolutions = {};
		addMission(solutions, group, 0, missionsSolutions, limit);
		if (missionsSolutions.solutions.size() > 0) {
			break;
		}
		
		missionsSolutions.RemoveDups();
	}
	
	std::cout << "BEST solution: size " << missionsSolutions.CurrentSize() << " count " << missionsSolutions.solutions.size() << std::endl;

	std::vector<std::pair<const Monster*, size_t>> monsterRanking{};
	for (const auto & monster : monsters) {
		size_t count = 0;
		for (const auto& solution : missionsSolutions.solutions) {
			for (const auto* solMonster : solution.monsters) {
				if (solMonster->name == monster.name) {
					++count;
					break;
				}
			}
		}
		monsterRanking.push_back({ &monster, count });
	}

	std::sort(monsterRanking.begin(), monsterRanking.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});

	for (const auto& monsterRank : monsterRanking) {
		std::cout << *monsterRank.first << ": " << monsterRank.second << std::endl;
	}

	if (missionsSolutions.solutions.size() < 20) {
		for (const auto& solution : missionsSolutions.solutions) {
			std::cout << solution << std::endl;
		}
	}
}
