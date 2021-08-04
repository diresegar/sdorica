#pragma once
#include <string>
#include <vector>
#include <array>

static const int numColors = 3;
static const int numSkills = 9;

static const std::array<std::string, numColors> colors_raw = {
	"Gold",
	"Black",
	"White"
};

class Color {
public:
	int color;

	Color(const std::string & colorName) {
		auto s = std::find(colors_raw.cbegin(), colors_raw.cend(), colorName);

		if (s == colors_raw.cend()) {
			throw "invalid color name";
		}

		this->color = (s - colors_raw.cbegin());
	}

	friend std::ostream& operator<< (std::ostream& out, const Color & color) {
		return out << colors_raw[color.color];
	}
};

static const std::array<std::string, numSkills> skills_raw = {
	"Tear",
	"Taunt",
	"Search",
	"Poison",
	"Regen",
	"Transport",
	"Vigilance",
	"Exhaust",
	"Stun"
};

class Skill {
public:
	int skill;

	Skill(const std::string & skillName) {
		auto s = std::find(skills_raw.cbegin(), skills_raw.cend(), skillName);

		if (s == skills_raw.cend()) {
			throw "invalid skill name";
		}

		this->skill = (s - skills_raw.cbegin());
	}

	std::ostream& operator<< (std::ostream& out) {
		return out << skills_raw[this->skill];
	}
};

typedef std::array<int, numSkills> SkillRequirements;
