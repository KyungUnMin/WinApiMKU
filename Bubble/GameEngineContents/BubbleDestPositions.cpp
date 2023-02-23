#include "BubbleDestHelper.h"

const std::vector<std::vector<int>> BubbleDestHelper::RoundAEnter =
{
	{135, 139, 144, 149, 153}
};

const std::vector<std::vector<int>> BubbleDestHelper::RoundA1 =
{
	{675,259,701,285,272,144,688,432, 387, 413},

	{684,675,547,131,692,701,573,157,144,272,528},

	{150,138,132,
		260,266,277,285,
			413,407,395,388,
				516,523,535,541,
					701,695,683,675,
						907,919},

	{675,682,746 + (32 * 3),
		701,694,758 + (32 * 3),
			551,555,395,392,264,262,134,138,
				569,565,437,440,280,282,154,149,144,272},

	{682,675,515,291,131, 138, 10,
		694,701,541,317,157,150,22},

	{}
};

const std::vector<std::vector<int>> BubbleDestHelper::RoundA2 =
{
	{163, 168, 173,
		188,184,178},

	{643,515,387,227,131,136,
		669, 541, 413, 253, 157, 152,
			528, 400, 240, 144},

	{679, 583, 487, 359, 199, 135, 131,355,
		697, 601, 473, 377, 217,153, 157, 381},

	{678, 611, 419, 326, 390,
		698, 637, 445, 346, 410,
			559, 561, 207, 209},

	{579, 483, 355, 259, 163, 167,
		605, 509, 381, 285, 189, 182,
			464,368, 272, 176},

	{675, 547, 419,
		291, 300, 308, 317,
			157, 149, 140, 131, 3,
				684, 556, 396,
					692, 564, 404,
						701, 541, 445}
};

const std::vector<std::vector<int>> BubbleDestHelper::RoundA3 =
{
	{688, 528, 400, 240, 144},

	{547, 556, 396, 236, 244, 148, 140,
		573, 564, 404, 308,
			137, 151},

	{686, 590,
		690, 594,
			173, 269,365, 461,
				179, 275, 371, 467},

	{675, 547, 451, 323, 227, 131, 140,
		701, 573, 477, 349, 253, 157, 149,
			688, 528, 432, 272},

	{22, 186, 346, 442, 602, 694, 686, 675, 131, 141, 18 },

	{650, 552, 484, 420, 360, 296, 198, 6,
		660, 562, 494, 429, 304, 16,
			696, 600, 475, 411, 345, 249, 187, 27}
};
